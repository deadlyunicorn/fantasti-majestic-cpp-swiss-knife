#include <iostream>
#include <fstream>
#include <vector>
#include "../global_Functions.h"
#include "SQL_Definition_Procedure.h"
#include "SQL_Manipulation_Procedure.h"
#include "SQL_Objects.h"


using namespace std;


void sqlProcedure(string&);


void sqlProcedure( string& userInput ){

    string filename="tempSql";
    bool keepFiles=false;

    do{

        cout << "Do you want to store the queries in a file? (y or n)" << endl;
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
    bar();



// Opening a new file
    ofstream sqlFile;
    sqlFile.open(filename, ofstream::out | ofstream::app); //don't remove previous contents
// 


    cout << "Type 'exit' to go home" << endl;
    optionBar();



    while (true){

        cout << "What kind of query to create" << endl;
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

            sqlDataManipulationProcedure(userInput,sqlFile);

        }
        else{
            cout << "Make sure you select one of the available options.." << endl;
            waitBeforeContinue();
        }
    }

    sqlFile.close();

    if(!keepFiles){
        if( remove( filename.c_str() ) != 0 ){

            cout << "Error: a file was deleted or renamed" << endl;

        }

    };

    bar();
}



