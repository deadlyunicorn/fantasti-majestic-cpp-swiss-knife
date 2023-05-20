
#include <iostream>
#include <fstream>
#include <cstdio>
#include "lib/global_functions.h"
#include "lib/sql_queries.h"

void mainProcess();


using namespace std;

int main(){
    bar();
    cout << "---Type 'help' for help" <<endl;
    //mainProcess();

    string filename="goodfilename";
    

    readFromFile(filename);
    
    return 0;
}

void mainProcess(){
    while (true){
        bar();
        cout << "What to do?" <<endl;
        string userInput;
        cout << ":";
        getline(cin,userInput);

        if(userInput=="exit"){
            break;
        }
        else if(userInput=="help"){
            cout << "====== Help Menu ======" <<endl;
            cout << "help-> show this menu" << endl;
            cout << "sql-> sql query creator" << endl;
        }
        else if(userInput=="sql"){
            sqlProcedure(userInput);
        }
        else{
            cout << "Error: function not found" << endl;
        }

    }
}
