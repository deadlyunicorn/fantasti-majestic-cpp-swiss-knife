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

    void readFromFile(string& filename);



    void readFromFile(string& filename){ //Filename or directory
        
        class tables{
            public:
                vector<string> tableName;
                vector<int> tableNumber;
                vector<string> columnName;
                vector<string> datatype;
        };
        
        ifstream currentFile(filename);
        
        string line;
        


        bool foundTable=false;
        int tableIndex=0;
        tables currentTables;


        while(getline(currentFile,line)){



            string phrase="CREATE TABLE";

            int tableSearchIndex=line.find(phrase);

            int tableSearchLength=phrase.length();


            if(tableSearchIndex!=string::npos){


                foundTable=true;

                currentTables.tableName.push_back("");


                for (int i=tableSearchIndex+tableSearchLength;line[i]!='('&&line[i]!='\0';i++){
                    currentTables.tableName[tableIndex].push_back(line[i]);
                }
                currentTables.tableNumber.push_back(tableIndex);
                currentTables.columnName.push_back("");
                currentTables.datatype.push_back("");
                

            }

            else if(foundTable){


                if( line.find(";") != string::npos ){

                    foundTable=false;
                    tableIndex++;

                    
                    continue;
                }
                
                



                getCommand(line,currentTables.columnName[tableIndex],currentTables.datatype[tableIndex]);
                replaceChars(currentTables.datatype[tableIndex],',','\0');

                cout << "Table name: " << currentTables.tableName[tableIndex] <<
                 endl << "Table number: "<< currentTables.tableNumber[tableIndex] << 
                 endl <<"Name:" << currentTables.columnName[tableIndex] <<
                  "\tType: " <<  currentTables.datatype[tableIndex] << endl;


                // cout<< tableIndex << ":" <<line<<endl;
                // cout << "name: " << currentTables.columnName << ", type: " << currentTables.datatype << endl; 
            }
            
        };

        currentFile.close();
        
    } 


    
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


