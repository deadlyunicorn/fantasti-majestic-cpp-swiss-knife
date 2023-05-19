#ifndef globals_h
    #define globals_h

    #include <iostream>

    void bar(){
        std::cout << "=======================" << std::endl;
    };

    void optionBar(){
        std::cout << "-----------------------" << std::endl;
    };

    void replaceChars(std::string& input,char charToReplace,char replaceWith){

        for(int i=0;i<input.length();i++){
        if(input[i]==charToReplace){
                input[i]=replaceWith;
        };
        };
    };

    void getCommand(char* ,char* ,char* );
    ///Unfinished


    ///Functions that seperates user input to command and arguments
    void getCommand(char* userInput,char* command,char* argument){
        int i,j;
        
        //start iterating through the input's characters
        for (i=0;userInput[i]!='\0';i++){ 
            
            if(userInput[i]!=' '){ //if we find a non blank space character
                for(j=0;(userInput[i])!=' '&&(userInput[i])!='\0';i++,j++){ //until we find another non blank space character
                    
                    command[j]=userInput[i];  //store the letters inside command
                }
                command[j+1]='\0'; //mark end of word
                break; //exit the first loop when the command word is found
            }
            
        }


        i++;
        
        
        for(j=0;(userInput[i]!='\0');i++){ //until we reach line end, continue iterating over the line
            
            if(userInput[i]!=' '){ //If user input is not empty -- (find the beginning of the next word)
                if(j>0){
                    argument[j]=' ';   //leave spaces between arguments in case we have multiple arguments.
                    j++;
                }
                for (true;(userInput[i]!=' ')&&userInput[i]!='\0';j++,i++){ //until user reading is not blank space or end of line
                    argument[j]=userInput[i];
                }
                
            }
        }
        argument[j]='\0';//mark end of line
    }


///example
// int main(){
	
// 	char userInput[100]=" a b c d e d                 asd";
// 	char command[100];
// 	char argument[100];
	
// // 	std::cout << "Enter your input: " << std::endl;

// 	getCommand(userInput,command,argument);
	
// 	std::cout << "Input: " << userInput << std::endl;
// 	std::cout << "Command: " << command << std::endl;
// 	std::cout << "Argument: " << argument << std::endl;
	
// 	return 0;
	
// }

#endif // A_H


