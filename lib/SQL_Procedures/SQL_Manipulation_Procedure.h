#include <iostream>
#include "../global_Functions.h"

using namespace std;

void sqlDataManipulationProcedure(string& userInput,ofstream &file);


void sqlDataManipulationProcedure(string& userInput,ofstream &file){
    
    
    do{
        
        cout << "Select one of the below" << endl;
        optionBar();

        cout << "1: SELECT data from a Database" << endl;
        cout << "2: INSERT data into a Database" << endl;
        cout << "3: UPDATE data  on  a Database" << endl;
        cout << "4: DELETE data  on  a Database" << endl;
        optionBar();

        cout << ": ";
        getline(cin,userInput);


        if ( 
            userInput=="1" || userInput=="2" || 
            userInput=="3" || userInput=="4"  
        ){
            
            if ( userSaidYesTo("Import and use table from file?") ){
                
                cout << "Okay we will import  your file in about 5-7 working days, have a nice weekend." << endl;

            }


        }


        if ( userInput == "1" ){
            cout << "User wants to select.. " << endl;
        }
        else if ( userInput == "2" ){

        }
        else if ( userInput == "3" ){
            
        }
        else if ( userInput == "4" ){
            
        }
        else if ( userInput == "exit" ){
            break;
        }
        else{
            cout << "Invalid input." << endl;
            waitBeforeContinue();
        }
    }while( true );
}

// string filename="goodfilename";
    // sqlTableList listA;
    // listA.generateFromFile(filename);
    // listA.getTableNames();
    // listA.showTables();