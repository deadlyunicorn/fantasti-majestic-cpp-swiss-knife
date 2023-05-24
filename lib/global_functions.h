#ifndef globals_h
    #define globals_h

    #include <iostream>
    #include <fstream>
    #include <vector>

    using namespace std;

    void replaceChars(string& input,char charToReplace,char replaceWith); // e.g. replaceChars(userInput,',',' ') will replace commas with spaces

    void getCommand(string& userInput,string& command,string& argument); // command and argument variables must in the process that calls the getCommand() 


    void bar(){
        cout << "=======================" << endl;
    };

    void optionBar(){
        cout << "-----------------------" << endl;
    };

    void waitBeforeContinue(){
        string input;
        optionBar();
        cout << "Press Enter to continue..." << endl;
        getline(cin,input);
        cout << endl;
    }

    void successBar(){
        cout << "-------- Success ------"<<endl;
        cout << "Your results are below" <<endl<<endl;
    };

    string getValidData(){
        
        while (true){
            
            string tempString;
            
            cout << ": ";
            getline( cin,tempString);
            replaceChars(tempString,' ','\0');

            if(tempString[0]!='\0'){
                return tempString;
            }
            else{
                cout << "Invalid Input." << endl;
            }
        }
    }

    bool userSaidYesTo(string textToDisplay){
        
        string userInput="!!!";
        do{
            if ( userInput != "!!!" ){
                cout << "Invalid input." << endl;
                waitBeforeContinue();
            }

            cout << textToDisplay << " (y or n)."<< endl;
            cout << ":";getline(cin,userInput);

        }while( userInput != "y"   &&   userInput != "n" );

        return ( userInput == "y" ); //;p

    }




    
    
    void replaceChars(string& input,char charToReplace,char replaceWith){

            for( int i=0 ;    i < input.length()    ; i++ ){ //O(N)

                if(input[i]==charToReplace){ //very efficient /s

                    input[i]=replaceWith;

                };
            };

    };

    string removeSpaces(const string& initialString){ //Doesn't affect initial string, unlike replaceChars().
        string tempString;
        for (int i=0;i<initialString.size();i++){
            if (initialString[i] != ' '){
                tempString.push_back(initialString[i]);
            }
        }
        return tempString;
    }

    string getValidInput(string prompt){
        while (true){
                string userInput;
                cout << prompt << endl;
                cout << ": ";
                getline(cin,userInput);

                if(removeSpaces(userInput).size()>0){

                    return userInput;
                }
                else{
                    cout << "Invalid Input. Try again." << endl;
                }
            }
    }

    void getCommand(string& userInput,string& command,string& argument){

        command.clear(); //We build the strings using .push_back()
        argument.clear(); //We need to make sure we start with empty string.

        int i;
        
        
        //start iterating through the input's characters
        for ( i=0 ;    userInput[i]!='\0'   ; i++ ){ //stop if line ends 

            
            if( userInput[i]!=' ' ){ //if we find a non blank space character - the beginning of an actual string
            
                for( true ;  ( userInput[i]  != ' ' ) && ( userInput[i] !='\0' ) ; i++ ){ //until we find the end of the string
                    
                    command.push_back(userInput[i]);  //store the letters inside command //if we use [j] instead of pushBack it will create a string table..

                }

                command.push_back('\0'); //When done, mark it in the string
                break; //exit the first loop when the command word is found
            
            }
            
        };

//when using char* instead of string we can replace 'true' with 'int j=0' and for the above add i++,'j++' . 
        
        
        for( bool firstArgumentFound = false ;  userInput[i] != '\0'  ; i++ ){ 
            

            if( userInput[i] != ' ' ){   //

                
                
                if( firstArgumentFound ){

                    argument.push_back(' ');   //separate arguments with spaces in case we have multiple arguments.

                }



                firstArgumentFound = true ;

                for( true ; ( userInput[i] != ' ' ) && ( userInput[i] != '\0' ) ; i++ ){ //Here we are building the individual arguments
                    
                    argument.push_back(userInput[i]);

                }

                if (userInput[i]=='\0'){ //this looks like it is not needed however if we remove it we get a core dump when using the procedure inside sql table generator..
                
                    break;
                
                }


                

                
            }
        }

        argument.push_back('\0');

    }


#endif 


