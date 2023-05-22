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
        sqlTable(){};

        

        void tableInsertCol(string columnName,string dataType){
            columnNames.push_back(columnName);
            dataTypes.push_back(dataType);
        }

        int columnSize(){
            return columnNames.size();
        }

        string columnNameAt(const int index){
            return columnNames[index];
        }

        string dataTypeAt(const int index){
            return dataTypes[index];
        }

        void displayColumns(){
            for (int i=0; i < this->columnSize() ; i++){

                cout << "Column Number: " << i << endl << 
                "Column Name: " << this->columnNameAt(i) << endl <<
                "Datatype: " << this->dataTypeAt(i) << endl;
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
        vector<sqlTable> tables;
    public:
        void addTable(sqlTable table){
            tables.push_back(table);
        }
        void generateFromFile(string& filename);

        void showTables(){
            for (int i=0;i<tables.size();i++){

                cout << "Table Name: " << tables[i].getName() << endl ;
                bar();
                tables[i].displayColumns();
                bar();
            }
        }
};

void sqlTableList::generateFromFile(string& filename){
        
        ifstream currentFile(filename);
        string line; //line we are currently reading from file
        
        bool foundTable=false;

        string phrase="CREATE TABLE";  //(#phrase)
        
        sqlTable currentTable;

        while(getline(currentFile,line)){

            int tableIndex=this->tables.size();
            int tableSearchIndex=line.find(phrase);
            int tableSearchLength=phrase.length(); //(#phrase)


            
            

            if(tableSearchIndex!=string::npos){ //If our 'phrase' is found

                foundTable=true;
                currentTable.tableClean();


                string tempName;

                for (int i=tableSearchIndex+tableSearchLength;line[i]!='('&&line[i]!='\0';i++){
                    tempName.push_back(line[i]);
                }
                currentTable.setName(tempName);

                // currentTable.tableNumber.push_back(tableIndex);
                // currentTable.columnName.push_back("");
                // currentTable.datatype.push_back("");
                

            }

            else if(foundTable){


                if( line.find(";") != string::npos ){

                    this->addTable(currentTable);
                    // tableIndex++;

                    foundTable=false;
                    
                    continue;
                }
                
                string tempColName;
                string tempDataType;
                


                getCommand(line,tempColName,tempDataType);
                replaceChars(tempDataType,',','\0');

                currentTable.tableInsertCol(tempColName,tempDataType);


                // cout << "Table name: " << currentTable.getName() <<
                //  endl << "Table number: "<< tableIndex << 
                //  endl <<"Name:" << currentTable.columnNameAt(tableIndex) <<
                //   "\tType: " <<  currentTable.dataTypeAt(tableIndex) << endl;


                // cout<< tableIndex << ":" <<line<<endl;
                // cout << "name: " << currentTable.columnName << ", type: " << currentTable.datatype << endl; 
            }
            
        };

        currentFile.close();
}

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



void sqlProcedure(string& userInput){
    string filename="tempSql";
    bool keepFiles=false;




    do{
        cout << "Do you want store the queries in a file? (y or n)" << endl;

        cout << ":";getline(cin,userInput);

    }while(userInput!="y"&&userInput!="n");



    if(userInput=="y"){
        keepFiles=true;
        cout << "How do you want your file to be named?" << endl;
        do{
            cout << "Please enter a filename with less than 20 characters" << endl;
            cout << ":";getline(cin,filename);

        }while(filename.length()>19);

        replaceChars(filename,' ','_');//removing spaces from filename
    }

    ofstream sqlFile;
    sqlFile.open(filename, ofstream::out | ofstream::app); //don't remove previous contents

    bar();
    cout << "type 'exit' to go back" << endl;
    bar();


    while (true){

        cout << "What kind of query do you want to create?" << endl;


        optionBar();
        cout << "1: Data Definition   " << endl;
        cout << "2: Data Manipulation " << endl;
        cout << "exit: Go to home menu" << endl;
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
        if(remove( filename.c_str() )!=0){
            cout << "Error:Your file was deleted or renamed" << endl;
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

                    if((tempNum>=1)||(tempNum<=7)){

                        //getting inside a function in order to save our eyes...
                        userInput=dataTypeQueryConstruct(userInput);

                        if(userInput!="!!!"){
                            ///Inserting new column only
                            /// if there is no "!!!" during all of
                            /// query creation stages
                            tempTable.tableInsertCol(tempColName,userInput);
                        }
                        break;
                    }

                    else if(userInput=="!!!"){
                        break;
                    }
                    else{
                        cout<<"Invalid input."<<endl;
                    }

                }
                catch(const std::invalid_argument& error){
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

        for(int i=0;i<tempTable.columnSize();i++){
            file << tempTable.columnNameAt(i) << " " << tempTable.dataTypeAt(i) << ","<< endl;
            cout << tempTable.columnNameAt(i) << " " << tempTable.dataTypeAt(i) << ","<< endl;

        }

        file << ");" <<endl<<endl;
        cout << ");" <<endl;
        bar();
        //
    }
}



string dataTypeQueryConstruct(string& userInput){
    do{

        if(userInput=="!!!"){
            return "!!!";
        }

        else if (userInput=="1"){ ///CHAR()
            cout << "What should be the length of the string?" << endl;
            getline(cin,userInput);
            return "CHAR("+userInput+")";
        }
        else if (userInput=="2"){ ///VARCHAR()
            cout << "What should be the max length of the string?" << endl;
            getline(cin,userInput);
            return "VARCHAR("+userInput+")";
        }
        else if (userInput=="3"){ ///BOOL
            return "BOOL";
        }
        else if (userInput=="4"){///INT
            return "INT";
        }
        else if (userInput=="5"){///FLOAT
            return "FLOAT";
        }
        else if (userInput=="6"){///DATE
            return "DATE";
        }
        else if (userInput=="7"){ ///YEAR
            return "YEAR";
        }
        else if (userInput=="8"){ ///CUSTOM
            cout << "Enter datatype" << endl <<":";
            getline(cin,userInput);
            return userInput;
        }
        else{cout << "Invalid input."<<endl;};
    }while(true);
}
