
#include <iostream>
#include <fstream>
#include <cstdio>
#include "lib/global_functions.h"
#include "lib/sql_queries.h"
#include "lib/mainProc.h"

void mainProcess();


using namespace std;

int main(){

    bar(); //Aesthetic - cout of a line bar
    cout << "---Type 'help' for help" <<endl;
    bar();

    // mainProcess();
    



    string filename="goodfilename";
    sqlTableList listA;
    listA.generateFromFile(filename);
    listA.showTables();

    
    return 0;
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
