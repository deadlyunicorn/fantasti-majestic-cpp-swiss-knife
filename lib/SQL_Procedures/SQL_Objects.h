#ifndef SQL_Objects

#define SQL_Objects

#include <iostream>
#include <vector>
#include "../global_Functions.h"

using namespace std;

class sqlTable{

    private:

        string name;
        vector<string> columnNames;
        vector<string> dataTypes;

    public:


        void tableInsertCol( string columnName , string dataType ){

            columnNames.push_back(columnName);
            dataTypes.push_back(dataType);
            
        };

        int columnSize(){
        
            return columnNames.size();
        
        };

        string columnNameAt( const int &index ){

            return columnNames[index];
        
        };


        string dataTypeAt( const int &index ){

            return dataTypes[index];

        };

        void displayColumns(){

            for ( int i=0 ;    i < this->columnSize()   ; i++ ){

                cout << "Column Number: "   << i                        << endl << 
                        "Column Name: "     << this->columnNameAt(i)    << endl <<
                        "Datatype: "        << this->dataTypeAt(i)      << endl;
            
            }
        
        }

        void setName(string name){

            this->name=name;
        
        }

        string getName(){

            return name;
        
        }

        void tableClean(){

            name.clear();
            columnNames.clear();
            dataTypes.clear();

        }

};


//maybe move this class on DML
class sqlTableList{

    private:

        vector<sqlTable> tableList;

    public:

        void addTable( sqlTable& table ){

            tableList.push_back( table );

        }

        void showTables(){
            
            for ( int i=0 ;    i < tableList.size()    ; i++ ){

                cout << "Table Name: " << tableList[i].getName() << endl ;
                
                bar();
                
                tableList[i].displayColumns();
                
                bar();
            }
        }

        void getTableNames(){
            for ( int i=0 ;    i < tableList.size()    ; i++ ){

                cout << i <<". Table: " << tableList[i].getName() << endl ;
                
            }

            bar();

        }

        void generateFromFile( string& filename );

};


void sqlTableList::generateFromFile(string& filename){
        
        sqlTable currentTable;

        ifstream currentFile(filename);
        string line; //line we are currently reading from file
        bool foundTable=false;
        

        
        string phrase="CREATE TABLE";  //(#phrase)
        int tableSearchLength=phrase.length(); //(#phrase)



        while(getline(currentFile,line)){

            
            int tableSearchIndex=line.find(phrase);
            

            if( tableSearchIndex != string::npos ){ //When a 'CREATE TABLE' query is found

                int tableIndex =  this->tableList.size(); //get current vector size - list items. 


                foundTable = true;
                currentTable.tableClean();  //clear the previous table information every time a new table is found


                string* tempName = new string;

                //Getting the table name
                for ( int i= ( tableSearchIndex + tableSearchLength ) ;    line[i] != '(' && line[i] != '\0'    ; i++ ){

                    if ( line[i] == ' ' ){ continue; }

                    (*tempName).push_back(line[i]);
                    
                }

                currentTable.setName(*tempName);
                delete tempName;
                

            }

            else if( foundTable ){

                if( line.find(";") != string::npos ){  //In case we find a semicolon

                    this->addTable(currentTable);  // Submit the table  -----  void addTable( sqlTable& table ){
                    foundTable=false;
                    continue;
                }
                
                string *tempColName=new string;
                string *tempDataType=new string;
                


                getCommand(line,*tempColName,*tempDataType);
                replaceChars(*tempDataType,',','\0');

                currentTable.tableInsertCol(*tempColName,*tempDataType);

                delete tempColName,tempDataType;

            };
            
        };

        currentFile.close();
}


#endif 
