#include <iostream>
#include "../global_Functions.h"
#include "SQL_Objects.h"



using namespace std;


void sqlDdProcedure(string&,ofstream&);


void dataTypeDisp();
string dataTypeQueryConstruct(string& userInput);


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

        replaceChars(userInput,' ','_');

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
};

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

