#include <iostream>
#include "SQL_Procedures/main_SQL_Procedure.h"


using namespace std;

void displayHelpMenu(){
    cout << "====== Help Menu ======"   <<  endl << endl;
    cout << "====== Commands  ======"   <<  endl << endl;
    cout << "help: Show this menu"      <<  endl;
    cout << "sql : SQL Query Creator"   <<  endl;
    cout << "man : Command Manual"      <<  endl<< 
            "\te.g. 'man sql'"          <<  endl;
    cout << endl;
}

void mainProcess(){
    while (true){

        string userInput;

        cout << "What to do? -- use 'help'" << endl;
        cout << ":"; 
        getline(cin,userInput);
        cout << endl;


        if(userInput=="exit"){

            break;

        }

        else if(userInput=="help"){
        
            displayHelpMenu();
            waitBeforeContinue();
            
        
        }

        else if(userInput=="sql"){
        
            sqlProcedure(userInput); // sqlProcedure(&string);
        
        }

        else{

            cout << "Error: function not found" << endl;
            waitBeforeContinue();
        }

    }
}
