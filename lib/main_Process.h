#include <iostream>
#include "SQL_Procedures/main_SQL_Procedure.h"


using namespace std;

void displayHelpMenu(){
    cout << "====== Help Menu ======"   <<  endl;
    cout << "====== Commands  ======"   <<  endl;
    cout << "help: show this menu"      <<  endl;
    cout << "sql : sql query creator"   <<  endl;
    cout << "man : command manual"      <<  endl<< 
            "\t   e.g. 'man sql'"       <<  endl;
}

void mainProcess(){
    while (true){

        string userInput;

        cout << "What to do?" << endl;
        cout << ":"; 
        getline(cin,userInput);


        if(userInput=="exit"){

            break;

        }

        else if(userInput=="help"){
        
            displayHelpMenu();
        
        }

        else if(userInput=="sql"){
        
            sqlProcedure(userInput); // sqlProcedure(&string);
        
        }

        else{

            cout << "Error: function not found" << endl;
        
        }

    }
}
