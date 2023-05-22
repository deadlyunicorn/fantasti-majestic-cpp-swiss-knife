#include <iostream>
#include <fstream>
#include <vector>
#include "global_functions.h"

using namespace std;


void sqlProcedure(string&);

void sqlDdProcedure(string&,ofstream&);



class sqlTable{

    private:

        string name;
        vector<string> columnNames;
        vector<string> dataTypes;

    public:


        void tableInsertCol( string columnName , string dataType ){

            columnNames.push_back(columnName);
            dataTypes.push_back(dataType);
            
        };

        int columnSize(){
        
            return columnNames.size();
        
        };

        string columnNameAt( const int &index ){

            return columnNames[index];
        
        };


        string dataTypeAt( const int &index ){

            return dataTypes[index];

        };

        void displayColumns(){

            for ( int i=0 ;    i < this->columnSize()   ; i++ ){

                cout << "Column Number: "   << i                        << endl << 
                        "Column Name: "     << this->columnNameAt(i)    << endl <<
                        "Datatype: "        << this->dataTypeAt(i)      << endl;
            
            }
        
        }

        void setName(string name){

            this->name=name;
        
        }

        string getName(){

            return name;
        
        }

        void tableClean(){

            name.clear();
            columnNames.clear();
            dataTypes.clear();

        }

};

class sqlTableList{

    private:

        vector<sqlTable> tableList;

    public:

        void addTable( sqlTable& table ){

            tableList.push_back( table );

        }

        void showTables(){
            
            for ( int i=0 ;    i < tableList.size()    ; i++ ){

                cout << "Table Name: " << tableList[i].getName() << endl ;
                
                bar();
                
                tableList[i].displayColumns();
                
                bar();
            }
        }

        void generateFromFile( string& filename );

};


void dataTypeDisp(){
        bar();
        cout << "1: CHAR" <<endl;
        cout << "2: VARCHAR" <<endl;
        cout << "3: BOOL" <<endl;
        cout << "4: INT" <<endl;
        cout << "5: FLOAT" <<endl;
        cout << "6: DATE" <<endl;
        cout << "7: YEAR" <<endl;
        cout << "8: CUSTOM" <<endl;
        bar();
}

string dataTypeQueryConstruct(string& userInput);



void sqlProcedure( string& userInput ){

    string filename="tempSql";
    bool keepFiles=false;

    do{

        cout << "Do you want store the queries in a file? (y or n)" << endl;
        cout << ":";getline(cin,userInput);

    }while( userInput != "y"   &&   userInput != "n" );


    if(userInput=="y"){

        keepFiles=true;
        cout << "How do you want your file to be named?" << endl;
        
        do{

            cout << "Please enter a filename with less than 20 characters" << endl;
            cout << ":";getline(cin,filename);

        }while(filename.length()>19);

        replaceChars(filename,' ','_');    //removing spaces from filename

    }


// Opening a new file
    ofstream sqlFile;
    sqlFile.open(filename, ofstream::out | ofstream::app); //don't remove previous contents
// 


    bar();
    cout << "type 'exit' to go back" << endl;
    bar();



    while (true){

        cout << "What kind of query do you want to create?" << endl;

        optionBar();

        cout << "Exit: go to home menu" << endl;
        cout << "1: Data Definition   " << endl;
        cout << "2: Data Manipulation " << endl;
        
        optionBar();


        cout << ":";
        getline(cin,userInput);

        if (userInput=="exit"){
            break;
        }
        else if (userInput=="1"){

            sqlDdProcedure(userInput,sqlFile);
        }
        else if(userInput=="2"){
            cout << "DM then.." << endl;
            break;
        }
        else{
            cout << "Make sure you select one of the available options.." << endl;
        }
    }

    sqlFile.close();

    if(!keepFiles){
        if( remove( filename.c_str() ) != 0 ){

            cout << "Error: a file was deleted or renamed" << endl;

        }

    };
}

void sqlDdProcedure(string& userInput,ofstream& file){

    bar();
    cout << "Select one of the below?" << endl;

    optionBar();
    cout << "1: Create and use a database" << endl;
    cout << "2: Create a table" << endl;
    optionBar();

    cout << ":";
    getline(cin,userInput);

    if(userInput=="1"){

        optionBar();
        cout << "Enter database name" << endl;
        optionBar();

        cout << ":";
        getline(cin,userInput);

        cout << "-------- Success ------"<<endl;
        cout << "Your results are below" <<endl;
        replaceChars(userInput,' ','_');

        //        _______________________________
        bar();
        cout << "CREATE DATABASE " << userInput <<";"<< endl;
        cout << "USE " << userInput << ";" << endl;
        bar();

        waitBeforeContinue(); //Press enter to continue..
        //
        file << "CREATE DATABASE " << userInput <<";"<< endl;
        file << "USE " << userInput << ";" << endl<<endl;
    }

    else if(userInput=="2"){

        //Table Name
        sqlTable tempTable;

        optionBar();
        cout << "Enter a table name" << endl;
        optionBar();

        cout << ":";
        getline(cin,userInput);

        tempTable.setName(userInput);

        //Inserting Columns
        do{
            optionBar();
            cout << "Type '!!!' when you have finished." << endl;
            optionBar();
            cout << "New column insertion" << endl;


            //New column name
            string tempColName;

            cout << "Enter a column name" << endl;
            cout << ":";

            getline(cin,tempColName);

            if(tempColName=="!!!"){break;}; //STOP new column insertion if the user types "!!!"


            replaceChars(tempColName,' ','_'); //No spaces allowed...

            cout << "Select a data type" << endl;
            dataTypeDisp(); //List available datatypes to select

            do{

                int tempNum;

                cout << ":";
                getline(cin,userInput);

                try{
                    tempNum=stoi(userInput); //String TO Integer ()

                    if( tempNum>=1 || tempNum<=7 ){

                        //getting inside a function in order to save our eyes...
                        userInput=dataTypeQueryConstruct(userInput); //Cases of input

                        if(userInput!="!!!"){
                            ///Inserting new column only
                            /// in the situation there is no "!!!" during all of
                            /// the query creation stages
                            tempTable.tableInsertCol(tempColName,userInput);
                            /// that's why we do the insertion here.
                        }
                        break;
                    }

                    else if(userInput=="!!!"){
                        break;
                    }
                    else{
                        cout << "Invalid input." <<endl ;
                    }

                }
                catch(const std::invalid_argument& error){ //In case we don't input an integer --- get the corresponding ereror
                    cout << "Invalid input." << endl;
                }

            }while(true);


        }while(true);


        cout << "-------- Success ------"<<endl;
        cout << "Your results are below" <<endl;
        //        _______________________________
        bar();

        file << "CREATE TABLE " << tempTable.getName() << "(" << endl;
        cout << "CREATE TABLE " << tempTable.getName() << "(" << endl;

        for( int i = 0 ;    i < tempTable.columnSize()  ; i++ ){
            file << tempTable.columnNameAt(i) << " " << tempTable.dataTypeAt(i) << ","<< endl;
            cout << tempTable.columnNameAt(i) << " " << tempTable.dataTypeAt(i) << ","<< endl;

        }

        file << ");" <<endl<<endl;
        cout << ");" <<endl;
        bar();

        waitBeforeContinue();

        //
    }
}



string dataTypeQueryConstruct(string& userInput){

    do{
        if( userInput == "!!!" ){
            return "!!!" ;
        }

        else if ( userInput == "1" ){ ///CHAR()

            cout << "What should be the length of the string?" << endl;

            getline(cin,userInput);
            return "CHAR("+userInput+")";

        }
        else if ( userInput == "2" ){ ///VARCHAR()
        
            cout << "What should be the max length of the string?" << endl;
            
            getline(cin,userInput);
            return "VARCHAR("+userInput+")";
       
        }

        else if ( userInput == "3" ){ ///BOOL
       
            return "BOOL";
       
        }
        else if ( userInput == "4" ){///INT
       
            return "INT";
       
        }
        else if ( userInput == "5" ){///FLOAT
       
            return "FLOAT";
       
        }
        else if ( userInput == "6" ){///DATE
       
            return "DATE";
       
        }
        else if ( userInput == "7" ){ ///YEAR
       
            return "YEAR";
       
        }
        else if ( userInput == "8" ){ ///CUSTOM
       
            cout << "Enter datatype" << endl <<":";

            getline(cin,userInput);
            return userInput;
       
        }
        else{
            cout << "Invalid input."<<endl;
        };
    }while(true);
}


void sqlTableList::generateFromFile(string& filename){
        
        sqlTable currentTable;

        ifstream currentFile(filename);
        string line; //line we are currently reading from file
        bool foundTable=false;
        

        
        string phrase="CREATE TABLE";  //(#phrase)
        int tableSearchLength=phrase.length(); //(#phrase)



        while(getline(currentFile,line)){

            
            int tableSearchIndex=line.find(phrase);
            

            if( tableSearchIndex != string::npos ){ //When a 'CREATE TABLE' query is found

                int tableIndex =  this->tableList.size(); //get current vector size - list items. 


                foundTable = true;
                currentTable.tableClean();  //clear the previous table information every time a new table is found


                string* tempName = new string;

                //Getting the table name
                for ( int i= ( tableSearchIndex + tableSearchLength ) ;    line[i] != '(' && line[i] != '\0'    ; i++ ){

                    if ( line[i] == ' ' ){ continue; }

                    (*tempName).push_back(line[i]);
                    
                }

                currentTable.setName(*tempName);
                delete tempName;
                

            }

            else if( foundTable ){

                if( line.find(";") != string::npos ){  //In case we find a semicolon

                    this->addTable(currentTable);  // Submit the table  -----  void addTable( sqlTable& table ){
                    foundTable=false;
                    continue;
                }
                
                string *tempColName=new string;
                string *tempDataType=new string;
                


                getCommand(line,*tempColName,*tempDataType);
                replaceChars(*tempDataType,',','\0');

                currentTable.tableInsertCol(*tempColName,*tempDataType);

                delete tempColName,tempDataType;

            };
            
        };

        currentFile.close();
}
