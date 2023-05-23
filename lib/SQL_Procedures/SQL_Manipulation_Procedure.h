#include <iostream>
#include <vector>
#include "../global_Functions.h"
#include "SQL_Objects.h"

using namespace std;

void sqlDataManipulationProcedure(string& userInput,ofstream &file);

sqlTable getTableFromFile();

string verifyDatatype(string&,string&);

class tableSelectArguments{
    private:
        string tableToQuery; //could be "Tables to query"
        vector<string> selection;
        string whereCondition;
        string groupBy;
        string orderBy;

};

class insertQuery{
    private:
        string tableToQuery;
        vector<string> values;
    public:
        void setTableToQuery(string table){
            tableToQuery=table;
        }
        void insertValue(string value){
            values.push_back(value);
        }
        void showValues(){
            cout << "INSERT INTO "<< tableToQuery << "VALUES(";
            for (int i = 0 ; i < values.size() ; i ++){
                cout << values[i];
                if ( i != values.size()-1 ){
                    cout << ",";
                }
            }
            cout << ");" << endl;
        }
};


void sqlDataManipulationProcedure(string& userInput,ofstream &file){
    
    
    do{
        

        sqlTable dataTable; 

        cout << "Select one of the below" << endl;
        optionBar();

        cout << "1: SELECT data from a Database" << endl;
        cout << "2: INSERT data into a Database" << endl;
        cout << "3: UPDATE data  on  a Database" << endl;
        cout << "4: DELETE data  on  a Database" << endl;
        optionBar();
        cout << "exit: Go back" << endl;
        optionBar();

        cout << ": ";
        getline(cin,userInput);
        cout << endl;


        if ( 
            userInput=="1" || userInput=="2" || 
            userInput=="3" || userInput=="4"  
        ){
            
            if ( userSaidYesTo("Import and use table data from a file?") ){
                cout << endl;

                try{
                    dataTable.setFromTable( getTableFromFile() );
                }

                catch(int errorNumber){
                    if ( errorNumber == 101 ){
                        cout << "Could not generate table from file." << endl;
                    }
                };
            };


        };


        if ( userInput == "1" ){ //Select
            cout << "User wants to select.. " << endl;
        }
        else if ( userInput == "2" ){ //Insert
            
            insertQuery* insertArguments=new insertQuery;


            if ( dataTable.columnSize() > 0 ){

                insertArguments->setTableToQuery( dataTable.getName() );
                
                for ( int i = 0 ; i < dataTable.columnSize() ; i++ ){

                    string datatype = dataTable.dataTypeAt(i);

                    cout << "Inserting to field named '" << dataTable.columnNameAt(i) 
                         << "' of type: " << dataTable.dataTypeAt(i) << endl;

                       insertArguments->insertValue( verifyDatatype( userInput, datatype ) );

                    
                };
            }


            insertArguments->showValues();
            delete insertArguments;

            waitBeforeContinue();
        
        }
        else if ( userInput == "3" ){ //Update
            
        }
        else if ( userInput == "4" ){ //Delete
            
        }
        else if ( userInput == "exit" ){
            break;
        }
        else{
            cout << "Invalid input." << endl;
            waitBeforeContinue();
        }
    }while( true );
};


sqlTable getTableFromFile(){

    string filename;
    sqlTableList tempTableList;

    do{
        cout << "Enter filename" << endl;
        cout << ": ";
        getline ( cin , filename );

        tempTableList.generateFromFile(filename);

        if ( tempTableList.getTableCount() > 0 ){
            
            cout << "Found tables!!" << endl;
            tempTableList.showTables();
            waitBeforeContinue();

            do{
                    string tempInput;
                    int i;
                    
                    cout << endl << "Use table No.";
                    cin >> tempInput;

                try{
                    i=stoi(tempInput);
                    i=i-1; //Setting the actual list item.

                }
                catch(...){
                    cout << "Invalid Input." << endl;
                    continue;
                }

                if( i >= 0 &&  i < tempTableList.getTableCount() ){ //2 tables => [0,1]
                    
                    return tempTableList.getTable(i);

                }
                else{

                    cout << "Invalid Input." << endl;

                }

            }while(true);

            break;

        }
        else if ( filename == "exit" ){
            break;
        }
        else{
            cout << "No tables found." << endl;
            optionBar();
            cout << "Type 'exit' to go back." << endl;
            waitBeforeContinue();
        }

    }while (true);

    
    throw 101;
};
// string filename="goodfilename";
    // sqlTableList listA;
    // listA.generateFromFile(filename);
    // listA.getTableNames();
    // listA.showTables();

string verifyDatatype(string& userInput, string& datatype){

     do{
        cout << ":";
        getline(std::cin,userInput);

        if (userInput == "NULL"){
            return "NULL";
        }
        else if ( datatype.find("CHAR(") != string::npos ){ //This also covers the case type is VARCHAR 
            int inputLength;

            if ( datatype.find(")") == string::npos ){
                inputLength = 250;
            }
            else {
                int start = datatype.find("(")+1; //start after the '('
                int end = datatype.find(")");

                string charCountString;
                
                for ( int i=start; i<end ; i++ ){
                    charCountString.push_back(datatype[i]);
                };
                try{
                    inputLength=stoi(charCountString);
                }
                catch(...){
                    inputLength=250;
                }
                if (userInput.length() <= inputLength){
                    return userInput;
                }
                else{
                    cout << "Invalid Input (check string length)."<<endl;
                }



            }
        }
        else if (  datatype.find("BOOL") != string::npos ){
            if ( userInput == "TRUE" || userInput == "FALSE" || userInput == "True" || userInput == "true" || userInput == "False" || userInput == "false"){
                return userInput;
            }
            else {
                cout << "Invalid Input."<<endl;
            }
        }
        else if (  datatype.find("INT") != string::npos ){

            int i;
            try{
                i=stoi(userInput);
                return userInput;
            }
            catch(...){
                cout << "Invalid Input."<<endl;
            }
        }
        else if (  datatype.find("FLOAT") != string::npos ){
            float i;
            try{
                i=stof(userInput);
                return userInput;
            }
            catch(...){
                cout << "Invalid Input."<<endl;
            }
        }
        else if (  datatype.find("DATE") != string::npos ){ // YYYY-MM-DD
            
            int i;
            for ( i=0 ; i < 10 ; i++){

                int num;
                
                if( i==4 || i==7 ){
                    if ( userInput[i] != '-' ){
                        cout << "Invalid input" << endl;
                        break;
                        
                    }
                    else{continue;}
                }

                if ( isdigit(userInput[i]) ){
                    if( i==0 ){ //Checking if we input a year correctly
                        if( userInput[i]=='1' && userInput[1]=='9' ){
                            i++;
                            continue;
                        }
                        else if ( 
                            userInput[i]=='2' 
                            && ( userInput[1]=='0' || userInput[1]=='1' ) 
                            ){

                            if ( userInput[1]=='0' ){continue;}
                            else if ( userInput[2] - '0' > 5){
                                break;
                            }
                            else if( userInput[2] - '0' == 5 ){
                                if (userInput[3] - '0' > 5){
                                    break;
                                }
                                else { i=3; }
                            };
                        }
                        else{
                            break;
                        }
                    }
                    else if( i==5 ){
                        if ( userInput[i] - '0' == 0 || userInput[i] - '0' == 1 ){
                            if ( userInput[i] - '0' == 1 ){
                                if ( userInput[6] - '0' > 2 ){
                                    break;
                                }
                                else{
                                    i=6;
                                }
                            }
                            else{
                                if( userInput[6] - '0' == 0 ) {
                                    break;
                                }
                                else{ i=6;}
                            }
                            
                        }
                        else { break; }
                    }
                    else if( i==8 ){
                        if ( ((userInput[8] - '0')*10 + userInput[9] - '0') == 0 || ((userInput[8] - '0')*10 + userInput[9] - '0') > 31){
                            break;
                        }
                        else {i=9;}
                    }
                    // continue; Don't remember why I put this here..
                }
                else { break;}
            };

            if(i==10){
                return userInput;
            }
            else{
                cout << "Be sure you set a date between 1901-2155." << endl;
                cout << "Format is YYYY-MM-DD" << endl;
            }
        }

        else if (  datatype.find("YEAR") != string::npos ){ //1901-2155

            int year;
            try{
                year = stoi( userInput );
            }
            catch(...){
                cout << "Invalid Input." << endl;
            }

            if (year > 1900 & year < 2156){
                cout << "Success." << endl;
                // return userInput;
            }
            else{cout << "Year must be between 1901-2155" << endl;}
        }
    }while(true);
}