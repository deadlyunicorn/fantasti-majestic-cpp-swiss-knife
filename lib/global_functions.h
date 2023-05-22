#ifndef globals_h
    #define globals_h

    #include <iostream>
    #include <fstream>
    #include <vector>

    using namespace std;

    void bar(){
        cout << "=======================" << endl;
    };

    void optionBar(){
        cout << "-----------------------" << endl;
    };

    void replaceChars(string& input,char charToReplace,char replaceWith);

    void getCommand(string& userInput,string& command,string& argument);


    
    void replaceChars(string& input,char charToReplace,char replaceWith){
            for(int i=0;i<input.length();i++){
                if(input[i]==charToReplace){
                        input[i]=replaceWith;
                };
            };
    }
    
    void getCommand(string& userInput,string& command,string& argument){

        command.clear();
        argument.clear();

        int i,j;
        
        //start iterating through the input's characters
        for (i=0;userInput[i]!='\0';i++){ 

            
            if(userInput[i]!=' '){ //if we find a non blank space character
                for(j=0;(userInput[i])!=' '&&(userInput[i])!='\0';i++,j++){ //until we find another non blank space character
                    

                    command.push_back(userInput[i]);  //store the letters inside command //if we use [j] instead of pushBack it will get weird
                }
                command.push_back('\0'); //mark end of word
                break; //exit the first loop when the command word is found
            }
            
        }


        
        for(j=0;(userInput[i]!='\0');i++){ //until we reach line end, continue iterating over the line

            

            if(userInput[i]!=' '){ //If user input is not empty -- (find the beginning of the next word)
                
                if(j>0){

                    argument.push_back(' ');   //leave spaces between arguments in case we have multiple arguments.
                    j++;
                }
                for (true;(userInput[i]!=' ')&&userInput[i]!='\0';j++,i++){ //until user reading is not blank space or end of line
                    
                    argument.push_back(userInput[i]);

                }
                if (userInput[i]=='\0'){
                    break;
                }

                
            }
        }

        argument.push_back('\0');//mark end of line

    }


#endif // A_H


