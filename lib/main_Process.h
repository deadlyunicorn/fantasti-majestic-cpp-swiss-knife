#include <iostream>
#include "SQL_Procedures/main_SQL_Procedure.h"
#include "friendProcedure.h"


using namespace std;

void displayHelpMenu(){
    cout << "========== Help Menu =========="   <<  endl          << endl;
    cout << "========== Commands  =========="   <<  endl          << endl;
    cout << "help:      | Show this menu"                         << endl;
    cout << "sql :      | SQL Query Creator"                      << endl;
    cout << "friendlist:| *Save* your friends!"               << endl;
    cout << "desc:      | Command description. Usage: 'desc sql'" << endl; 
    cout << "readme:    | Display ReadMe file"                    << endl;
    cout << "readfile:  | Read any file user wants"               << endl;
    cout << "credits:   | Show credits"                           << endl;
    
    cout << endl;
}

void showDescriptions(string);

void mainProcess(){
    while (true){

        string userInput;
        string command;
        string argument;

        cout << "What to do? -- use 'help'" << endl;
        cout << ":"; 
        getline(cin,userInput);
        cout << endl;

        getCommand(userInput,command,argument);

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
        else if(userInput=="friendlist"){
        
            friendProcedure(userInput);
        
        }

        else if(userInput=="readme"){
        
            readFile("README.md"); // sqlProcedure(&string);
        
        }
        else if(userInput=="credits"){
            bar();
            cout << "This project was built by Alexander Petrache aka. deadlyunicorn" << endl; 
            cout << "  And was the deliverable of the closing project on C++ "        << endl; 
            cout << "               It was built on May 2023. "                       << endl; 
            cout << "  It was such a pleasure working with our great proffessors "    << endl; 
            cout << "           Drakopoulos Anastasios and Rorri Anastasia "          << endl; 
            cout << "Taking on new challenges and learning C++ and the basics of OOP "<< endl; 
            cout << " On the premises of the Vocational Instute of Peristeri, Greece."<< endl; 
            bar();
        }


        else if(userInput=="readfile"){

            string* tempName=new string(getValidInput("What is the path to the file you want to read?"));
            readFile(*tempName); // sqlProcedure(&string);
            delete tempName;
        }
        else if(command=="desc"){
            showDescriptions(argument);
        }

        else{

            cout << "Error: function not found" << endl;
            waitBeforeContinue();
        }

    }
}

void showDescriptions(string argument){

    bar();

    if(argument=="exit"){
        cout << "This command returns back to the main process" << endl;
        cout << "       if you are already there, "             << endl;
        cout << "        it terminates the app."                << endl;


        }

    else if(argument=="help"){

        cout << "This command shows a list of the available" << endl;
        cout << "       commands the user can run. "             << endl;
        
    
    }

    else if(argument=="sql"){
    
        cout << "This starts the process of a simple" << endl;
        cout << "        SQL Query Editor. "          << endl;
        optionBar();
        cout << "       Most of the time"             << endl;
        cout << "     Invested on this project"       << endl;
        cout << "           Went here."               << endl;
        optionBar();
        cout << "  The most advanced functions of it" << endl;
        cout << "  Are: "                             << endl;
        bar();
        cout << "  1.Data Insertion using template "  << endl << endl;
        optionBar();
        cout << "  This is due to some type-checking" << endl;
        cout << "  That it does, based on the"        << endl;
        cout << "             selected table."        << endl;
        optionBar();


        bar();
        cout << "  2.Table Creation"                  << endl << endl;
        optionBar();
        cout << "  You basically are able to create" << endl;
        cout << "       A new table from scratch"    << endl;
        cout << "  While having some possible types" << endl;
        cout << "           Always on screen "       << endl;
        cout << "     And simply inputting numbers " << endl;
        cout << "     To select the preffered one."  << endl;
        optionBar();
        cout << "  You have the ability to write  "  << endl;
        cout << "            to file "               << endl;
        cout << "  And then use the table template " << endl;
        cout << "  For you INSERT Query generation." << endl;
        bar();

        cout << "  3.Data Selection"                 << endl << endl;
        optionBar();
        cout << "  What is unique about this is that"<< endl;
        cout << "    if you don't make a 'SELECT *' "<< endl;
        cout << "  It validates your ORDER/GROUP BY" << endl;
        cout << "              arguments. "          << endl;
        optionBar();
        bar();
        cout << "         Of course all those  "     << endl;
        cout << "  Could have more advanced features"<< endl;
        cout << "       But let's be honest,"        << endl;
        cout << "   it's easier and better for all " << endl;
        cout << "      simply learning SQL "         << endl;
        optionBar();
        cout << "   Despite all that, if you are new"<< endl;
        cout << "      like completely new to the  " << endl;
        cout << "     IT Applications world   "      << endl;
        cout << "     It might serve some purpose "  << endl;
        bar();



        
    
    }
    else if(argument=="friendlist"){
        cout << " A procedure where you can input your friends " << endl;
        cout << "       Save them inside a file  "               << endl;
        cout << "    and learn some things about them! "         << endl;
    }
    else if(argument=="readme"){
    
        cout << "This command displays the read me file" << endl;
        cout << "   included on the same directory. "    << endl;
        cout << "        with the executable. "          << endl;
        
    }

    else if(argument=="readfile"){

        cout << "     This command reads a file"         << endl;
        cout << "    on the path the user defines."      << endl;
        
    }
    else if(argument=="desc"){

        cout << "     This command  shows"               << endl;
        cout << "the descriptions of each command."      << endl;
        optionBar();
        cout << "use: 'desc sql'"                        << endl;

    }
    else if(argument=="credits"){
        cout << "     This command  shows"               << endl;
        cout << "         the credits."                  << endl;

    }
    else{
        cout << "Uknown argument." << endl;
    }
    waitBeforeContinue();
}