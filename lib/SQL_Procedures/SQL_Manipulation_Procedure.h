#include <iostream>
#include <vector>
#include "../global_Functions.h"
#include "SQL_Objects.h"

using namespace std;

void sqlDataManipulationProcedure(string& userInput,ofstream &file);

sqlTable getTableFromFile();

string verifyDatatype(string&,string&);

class selectQuery{
    private:
        vector<string> tableToQuery; //could be "Tables to query"
        vector<string> selection;
        string whereCondition;
        string groupBy;
        string havingCondition;
        string orderBy;
    public:
        void addTableToQuery(string table){
            tableToQuery.push_back(table);
        };
        void clearSelection(){
            this->selection.clear();
        }
        void addSelection(string table){
            selection.push_back(table);
        };
        void setWhereCondition(string where){
            whereCondition=where;
        };
        void setGroupBy(string column){
            groupBy=column;
        };
        void setHaving(string having){
            havingCondition=having;
        }
        void setOrderBy(string column){
            orderBy=column;
        }
        vector<string> getTableToQuery(){
            return tableToQuery;
        }
        vector<string> getSelection(){
            return selection;
        };
        string getWhereCondition(){
            return whereCondition;
        };
        string getGroupBy(){///comment
            return groupBy;
        };
        string getHaving(){
            return havingCondition;
        }
        string getOrderBy(){
            return orderBy;
        }
        void showSelection(){
            cout << "Submitted columns" << endl;
            optionBar();
            for (int i=0;i<selection.size();i++){
                cout << i+1 << ". " << selection[i] << endl;
            }
        }
        string getQuery(){
            string output;
            output="SELECT "+selection[0];
            for (int i=1; i < selection.size() ; i++ ){
                output=output+", "+selection[i];
            }
            output=output+"\nFROM "+tableToQuery[0];
            for (int i=1; i < tableToQuery.size() ; i++ ){
                output=output+", "+tableToQuery[i];
            }
            if(whereCondition.size()>0){
                output=output+"\nWHERE "+whereCondition;
            }
            if(groupBy.size()>0){
                output=output+"\nGROUP BY "+groupBy;
            }
            if(havingCondition.size()>0){
                output=output+"\nHAVING "+havingCondition;
            }
            if(orderBy.size()>0){
                output=output+"\nORDER BY "+orderBy;
            }
            output=output+";\n";
            return output;
        }

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
        string getQuery(){
            string output;
            output="INSERT INTO " + tableToQuery + " VALUES(";
            for (int i = 0 ; i < values.size() ; i ++){
                output = output + values[i];
                if ( i != values.size()-1 ){
                    output = output + ", ";
                }
            }
            output =  output + ");" ;
            return output;
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
            
            if ( userSaidYesTo("Import and show/use table data from a file?") ){
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

            selectQuery* selectArguments = new selectQuery;

            do{

            cout << "Select one of the below"<<endl;
            optionBar();
            cout << "1: Set COLUMNS to SELECT "     << endl;
            cout << "2: Set TABLES to SELECT from"  << endl;
            cout << "3: Set WHERE condition "       << endl;
            cout << "4: Set GROUP BY "              << endl;
            cout << "5: Set HAVING "                << endl;
            cout << "6: Set ORDER BY "              << endl;
            cout << "!!!: Exit or Finish Query"     << endl;
            optionBar();

                cout << ": ";
                getline( cin,userInput);

                if( userInput == "!!!" ){

                    if(selectArguments->getSelection().size() < 1 ){
                        cout << "Cannot create query. " << endl;
                        cout << "There were no columns selected." << endl;
                        if(userSaidYesTo("Confirm exit?")){
                            break;
                        }
                    }
                    else if(selectArguments->getTableToQuery().size() < 1){
                        cout << "Cannot create query. " << endl;
                        cout << "There were no tables selected." << endl;
                        if(userSaidYesTo("Confirm exit?")){
                            break;
                        }
                    }
                    else{
                        
                        cout << selectArguments->getQuery() << endl;
                        file << selectArguments->getQuery() << endl << endl;
                        break; 
                        // return result here
                    }
                    

                }
                else{
                    try{
                        int i=stoi(userInput);
                        if ( i<1 || i>6){
                            throw 404;
                        }
                    }
                    catch(...){
                        cout << "Invalid Input." << endl;
                        continue;
                    }
                    if (userInput=="1"){ //Columns
                        
                        cout << "Input '!!!' when done." << endl;

                        while( userInput!="*" ){

                            cout << "Enter a column to select" << endl;
                            optionBar();

                            userInput=getValidData();

                            if(userInput=="!!!"){break;}

                            if(userInput=="*"){selectArguments->clearSelection();}

                            selectArguments->addSelection(userInput);

                            
                        }

                        cout << "Successfully set." << endl;
                        waitBeforeContinue();
                    }
                    else if(userInput=="2"){//Tables

                        cout << "Input '!!!' when done." << endl;
                        while( userInput!="*" ){


                            cout << "Enter a table to select" << endl;
                            optionBar();

                            userInput=getValidData();

                            if(userInput=="!!!"){break;}

                            if(userInput=="*"){selectArguments->clearSelection();}

                            selectArguments->addTableToQuery(userInput);
                            
                        }

                        cout << "Successfully set." << endl;
                        waitBeforeContinue();

                    }
                    else if(userInput=="3"){ //Where

                        optionBar();
                        cout << "      Enter a WHERE condition       " << endl;
                        cout << "   including AND,OR statements      " << endl;
                        optionBar();
                        cout << "example:'age>18 AND registered=TRUE' " << endl;

                        userInput=getValidData();
                        selectArguments->setWhereCondition(userInput);

                        cout << "Successfully set." << endl;
                        waitBeforeContinue();
                    }
                    else if(userInput=="4"){ //Group

                        cout << "Enter a column name to GROUP BY" << endl;
                        optionBar();

                        if(selectArguments->getSelection().size()>0){

                            if( selectArguments->getSelection()[0] != "*"){
                                while(true){
                                    userInput=getValidData();
                                    if(userInput=="!!!"){break;}

                                    bool columnExists=false;
                                    for(int i=0;i<selectArguments->getSelection().size() ; i++ ){
                                        if (selectArguments->getSelection()[i]==userInput){
                                            columnExists=true;
                                        }
                                        
                                    }
                                    if (columnExists){
                                        selectArguments->setGroupBy(userInput);
                                        break;
                                    }
                                    else{
                                            cout << "Be sure to select " << endl;
                                            cout << "one of the columns,"<< endl;
                                            cout << "already included"  << endl;
                                            cout << "in your query. " << endl;
                                            waitBeforeContinue();
                                            selectArguments->showSelection();
                                    }
                                }
                            }
                            else{
                                userInput=getValidData();
                                selectArguments->setGroupBy(userInput);
                            }
                            cout << "Successfully set." << endl;
                            waitBeforeContinue();
                            
                        }
                        else{
                            cout << "Be sure to add columns" << endl;
                            cout << " to select from first " << endl;
                        }

                    }
                    else if(userInput=="5"){ //Having
                        optionBar();
                        cout << "Enter a HAVING condition  " << endl;
                        optionBar();
                        cout << "example: 'last_name LIKE 'S%''" << endl;

                        userInput=getValidData();
                        selectArguments->setHaving(userInput);

                        cout << "Successfully set." << endl;
                        waitBeforeContinue();

                    }
                    else if(userInput=="6"){ //Order

                        cout << "Enter a column name to ORDER BY" << endl;
                        optionBar();

                        if(selectArguments->getSelection().size()>0){

                            if( selectArguments->getSelection()[0] != "*"){
                                while(true){
                                    userInput=getValidData();
                                    if(userInput=="!!!"){break;}


                                    bool columnExists=false;
                                    for(int i=0;i<selectArguments->getSelection().size() ; i++ ){
                                        if (selectArguments->getSelection()[i]==userInput){
                                            columnExists=true;
                                        }
                                    }
                                    if (columnExists){
                                        selectArguments->setOrderBy(userInput);
                                        break;
                                    }
                                    else{
                                            cout << "Be sure to select " << endl;
                                            cout << "one of the columns,"<< endl;
                                            cout << "already included"  << endl;
                                            cout << "in your query. " << endl;
                                            waitBeforeContinue();
                                            selectArguments->showSelection();
                                    }
                                }
                            }
                            else{
                                userInput=getValidData();
                                selectArguments->setOrderBy(userInput);
                            }
                            cout << "Successfully set." << endl;
                            waitBeforeContinue();
                            
                        }
                        else{
                            cout << "Be sure to add columns" << endl;
                            cout << " to select from first " << endl;
                        }
                    }
                }
            
            }while(true);


            
            delete selectArguments;
            waitBeforeContinue();
        }
        else if ( userInput == "2" ){ //Insert
            


            if ( dataTable.columnSize() > 0 ){
                insertQuery* insertArguments=new insertQuery;

                insertArguments->setTableToQuery( dataTable.getName() );
                
                for ( int i = 0 ; i < dataTable.columnSize() ; i++ ){

                    string datatype = dataTable.dataTypeAt(i);

                    cout << "Inserting to field named '" << dataTable.columnNameAt(i) 
                         << "' of type: " << dataTable.dataTypeAt(i) << endl;

                       insertArguments->insertValue( verifyDatatype( userInput, datatype ) );

                    
                };

                successBar();
                cout << insertArguments->getQuery() << endl;
                file << insertArguments->getQuery() << endl << endl;

                delete insertArguments;
            }
            else{
                string tempTable;
                vector<string> data;

                optionBar();
                cout << "It seems you are not using a table template." << endl << endl;
                cout << "Note that the results you get will need" << endl;
                cout << "to have manually added quotes." << endl;
                bar();
                while(true){
                    cout << "Enter your table name" << endl;
                    cout << ":";
                    getline(cin,tempTable);

                    replaceChars(tempTable,' ','\0'); //basically this could have been approached differently.
                    if( tempTable[0] == '\0' ){
                        cout << "Invalid Input." << endl;
                    }
                    else{
                        break;                        
                    }
                }

                if(tempTable!="!!!"){


                    cout << "Now inserting data" << endl;
                    cout << "Type '!!!' when finished." << endl;
                    
                    int i=0;
                    while(true){
                        string tempString;
                        // string unfilteredString;

                        cout << "Enter data for the column No." << i+1 << endl;
                        cout << ": ";
                        getline(cin,tempString);
                        // unfilteredString=tempString;

                        replaceChars(tempString,' ','\0');


                        if ( tempString != "!!!" && tempString[0] != '\0' ){ //I have had errors with the \0 here.
                            data.push_back(tempString);
                            i++;
                        }
                        else if( tempString == "!!!"){
                            break;
                        }
                        else {
                            cout << "Invalid Input." << endl;
                        }
                    }
                }

                if( data.size() > 0 ){

                    string output;
                    output="INSERT INTO " + tempTable + " VALUES(";
                    
                    for (int i = 0 ; i < data.size() ; i ++){
                        output = output + data[i];
                        if ( i != data.size()-1 ){
                            output = output + ", ";
                        }
                    };
                    
                    output =  output + ");" ;

                    successBar();
                    cout << output << endl;
                    file << output << endl << endl;
                }
                
                else{
                    cout << "No data inserted." << endl;
                }

            }

            waitBeforeContinue();
        
        }
        else if ( userInput == "3" ){ //Update
            cout << "User wants to update.. " << endl;

            waitBeforeContinue();
        }
        else if ( userInput == "4" ){ //Delete
            cout << "User wants to delete.. " << endl;

            waitBeforeContinue();
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
                    
                    userInput.insert(userInput.begin(), '\'');
                    userInput.push_back('\'');
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
                    // continue; Don't remember why I put this here.. However I am too afraid to completely remove.
                }
                else { break;}
            };

            if(i==10){
                userInput.insert(userInput.begin(), '\'');
                userInput.push_back('\'');
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