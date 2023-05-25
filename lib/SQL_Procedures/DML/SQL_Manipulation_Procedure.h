#include <iostream>
#include <vector>


#include "Manipulation_Classes_And_Procedures.h"
#include "../../global_Functions.h"

using namespace std;

void sqlDataManipulationProcedure(string& userInput,ofstream &file);


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
                    //getTableFromFile() could be a method inside the class..
                    //The function also couts the tables found
                    //With their column data. In case of debugging.

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
            
            updateQuery* updateArguments=new updateQuery;
            cout << "UPDATING MODE" << endl;
            optionBar();
            updateArguments->setTable( getValidInput("Which table to update") );
            optionBar();
            cout << "Example Input: salary = salary+500, department = 'Sales'" << endl;
            updateArguments->setUpdateArguments( getValidInput("What should we update") );
            optionBar();
            if (userSaidYesTo("Add condition?")){
                cout << "Example Input: employee_id = 4512" << endl;
                updateArguments->setCondition( getValidInput("Enter condition"));
            };
            optionBar();

            cout << updateArguments->getQuery() << endl;
            file << updateArguments->getQuery() << endl << endl;

            delete updateArguments;

            waitBeforeContinue();

        }
        else if ( userInput == "4" ){ //Delete
            deleteQuery* deleteArguments=new deleteQuery;
            cout << "DELETING MODE" << endl;
            optionBar();
            deleteArguments->setTable( getValidInput("Which table to delete from") );
            optionBar();
            if (userSaidYesTo("Add condition?")){
                cout << "Example Input: employee_id = 4512" << endl;
                deleteArguments->setCondition( getValidInput("Enter condition"));
            };
            optionBar();

            cout << deleteArguments->getQuery() << endl;
            file << deleteArguments->getQuery() << endl << endl;

            delete deleteArguments;


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


