#include "../SQL_Objects.h"


sqlTable getTableFromFile();

string verifyDatatype(string&,string&);

class selectQuery{
    private:
        vector<string> tableToQuery; //could be "Tables to query"
        vector<string> selection;
        string whereCondition;
        string groupBy;
        string havingCondition;
        string orderBy;
    public:
        void addTableToQuery(string table){
            tableToQuery.push_back(table);
        };
        void clearSelection(){
            this->selection.clear();
        }
        void addSelection(string table){
            selection.push_back(table);
        };
        void setWhereCondition(string where){
            whereCondition=where;
        };
        void setGroupBy(string column){
            groupBy=column;
        };
        void setHaving(string having){
            havingCondition=having;
        }
        void setOrderBy(string column){
            orderBy=column;
        }
        vector<string> getTableToQuery(){
            return tableToQuery;
        }
        vector<string> getSelection(){
            return selection;
        };
        string getWhereCondition(){
            return whereCondition;
        };
        string getGroupBy(){///comment
            return groupBy;
        };
        string getHaving(){
            return havingCondition;
        }
        string getOrderBy(){
            return orderBy;
        }
        void showSelection(){
            cout << "Submitted columns" << endl;
            optionBar();
            for (int i=0;i<selection.size();i++){
                cout << i+1 << ". " << selection[i] << endl;
            }
        }
        string getQuery(){
            string output;
            output="SELECT "+selection[0];
            for (int i=1; i < selection.size() ; i++ ){
                output=output+", "+selection[i];
            }
            output=output+"\nFROM "+tableToQuery[0];
            for (int i=1; i < tableToQuery.size() ; i++ ){
                output=output+", "+tableToQuery[i];
            }
            if(whereCondition.size()>0){
                output=output+"\nWHERE "+whereCondition;
            }
            if(groupBy.size()>0){
                output=output+"\nGROUP BY "+groupBy;
            }
            if(havingCondition.size()>0){
                output=output+"\nHAVING "+havingCondition;
            }
            if(orderBy.size()>0){
                output=output+"\nORDER BY "+orderBy;
            }
            output=output+";\n";
            return output;
        }

};

class insertQuery{
    private:
        string tableToQuery;
        vector<string> values;
    public:
        void setTableToQuery(string table){
            tableToQuery=table;
        }
        void insertValue(string value){
            values.push_back(value);
        }
        string getQuery(){
            string output;
            output="INSERT INTO " + tableToQuery + " VALUES(";
            for (int i = 0 ; i < values.size() ; i ++){
                output = output + values[i];
                if ( i != values.size()-1 ){
                    output = output + ", ";
                }
            }
            output =  output + ");" ;
            return output;
        }
};

class deleteQuery{
    protected:
        string table;
        string condition;
    public:
        void setTable(string table){
            this->table=table;
        }
        string getTable(){
            return table;
        }
        void setCondition(string condition){
        this->condition=condition;
        }
        string getCondition(){
            return condition;
        }
        string getQuery();
            

};

class updateQuery:public deleteQuery{
    private:
        string updateArguments;

    public:
        void setUpdateArguments(string arguments){
            this->updateArguments=arguments;
        }
        
        string getUpdateArguments(){
            return updateArguments;
        }
        string getQuery();
        
        
};

string deleteQuery::getQuery(){
    string output;
    output="DELETE FROM " + table;
    if(condition.size()>0){
        output+=" \nWHERE " + condition;
    }
    output+=";\n";
    return output;
}

string updateQuery::getQuery(){
    string output;
    output="UPDATE " + table;
    output+=" \nSET "+ updateArguments;
    if(condition.size()>0){
        output+=" \nWHERE " + condition;
    }
    output+=";\n";
    return output;
}

sqlTable getTableFromFile(){

    string filename;
    sqlTableList tempTableList;

    do{
        cout << "Enter filename" << endl;
        cout << ": ";
        getline ( cin , filename );

        tempTableList.generateFromFile(filename);

        if ( tempTableList.getTableCount() > 0 ){
            
            cout << "Found tables!!" << endl;
            tempTableList.showTables();
            waitBeforeContinue();

            do{
                    string tempInput;
                    int i;
                    
                    cout << endl << "Use table No.";
                    cin >> tempInput;

                try{
                    i=stoi(tempInput);
                    i=i-1; //Setting the actual list item.

                }
                catch(...){
                    cout << "Invalid Input." << endl;
                    continue;
                }

                if( i >= 0 &&  i < tempTableList.getTableCount() ){ //2 tables => [0,1]
                    
                    return tempTableList.getTable(i);

                }
                else{

                    cout << "Invalid Input." << endl;

                }

            }while(true);

            break;

        }
        else if ( filename == "exit" ){
            break;
        }
        else{
            cout << "No tables found." << endl;
            optionBar();
            cout << "Type 'exit' to go back." << endl;
            waitBeforeContinue();
        }

    }while (true);

    
    throw 101;
};
// string filename="goodfilename";
    // sqlTableList listA;
    // listA.generateFromFile(filename);
    // listA.getTableNames();
    // listA.showTables();

string verifyDatatype(string& userInput, string& datatype){

     do{
        cout << ":";
        getline(std::cin,userInput);

        if (userInput == "NULL"){
            return "NULL";
        }
        else if ( datatype.find("CHAR(") != string::npos ){ //This also covers the case type is VARCHAR 
            int inputLength;

            if ( datatype.find(")") == string::npos ){
                inputLength = 250;
            }
            else {
                int start = datatype.find("(")+1; //start after the '('
                int end = datatype.find(")");

                string charCountString;
                
                for ( int i=start; i<end ; i++ ){
                    charCountString.push_back(datatype[i]);
                };
                try{
                    inputLength=stoi(charCountString);
                }
                catch(...){
                    inputLength=250;
                }
                if (userInput.length() <= inputLength){
                    
                    userInput.insert(userInput.begin(), '\'');
                    userInput.push_back('\'');
                    return userInput;
                }
                else{
                    cout << "Invalid Input (check string length)."<<endl;
                }



            }
        }
        else if (  datatype.find("BOOL") != string::npos ){
            if ( userInput == "TRUE" || userInput == "FALSE" || userInput == "True" || userInput == "true" || userInput == "False" || userInput == "false"){
                return userInput;
            }
            else {
                cout << "Invalid Input."<<endl;
            }
        }
        else if (  datatype.find("INT") != string::npos ){

            int i;
            try{
                i=stoi(userInput);
                return userInput;
            }
            catch(...){
                cout << "Invalid Input."<<endl;
            }
        }
        else if (  datatype.find("FLOAT") != string::npos ){
            float i;
            try{
                i=stof(userInput);
                return userInput;
            }
            catch(...){
                cout << "Invalid Input."<<endl;
            }
        }
        else if (  datatype.find("DATE") != string::npos ){ // YYYY-MM-DD
            
            int i;
            for ( i=0 ; i < 10 ; i++){

                int num;
                
                if( i==4 || i==7 ){
                    if ( userInput[i] != '-' ){
                        cout << "Invalid input" << endl;
                        break;
                        
                    }
                    else{continue;}
                }

                if ( isdigit(userInput[i]) ){
                    if( i==0 ){ //Checking if we input a year correctly
                        if( userInput[i]=='1' && userInput[1]=='9' ){
                            i++;
                            continue;
                        }
                        else if ( 
                            userInput[i]=='2' 
                            && ( userInput[1]=='0' || userInput[1]=='1' ) 
                            ){

                            if ( userInput[1]=='0' ){continue;}
                            else if ( userInput[2] - '0' > 5){
                                break;
                            }
                            else if( userInput[2] - '0' == 5 ){
                                if (userInput[3] - '0' > 5){
                                    break;
                                }
                                else { i=3; }
                            };
                        }
                        else{
                            break;
                        }
                    }
                    else if( i==5 ){
                        if ( userInput[i] - '0' == 0 || userInput[i] - '0' == 1 ){
                            if ( userInput[i] - '0' == 1 ){
                                if ( userInput[6] - '0' > 2 ){
                                    break;
                                }
                                else{
                                    i=6;
                                }
                            }
                            else{
                                if( userInput[6] - '0' == 0 ) {
                                    break;
                                }
                                else{ i=6;}
                            }
                            
                        }
                        else { break; }
                    }
                    else if( i==8 ){
                        if ( ((userInput[8] - '0')*10 + userInput[9] - '0') == 0 || ((userInput[8] - '0')*10 + userInput[9] - '0') > 31){
                            break;
                        }
                        else {i=9;}
                    }
                    // continue; Don't remember why I put this here.. However I am too afraid to completely remove.
                }
                else { break;}
            };

            if(i==10){
                userInput.insert(userInput.begin(), '\'');
                userInput.push_back('\'');
                return userInput;
            }
            else{
                cout << "Be sure you set a date between 1901-2155." << endl;
                cout << "Format is YYYY-MM-DD" << endl;
            }
        }

        else if (  datatype.find("YEAR") != string::npos ){ //1901-2155

            int year;
            try{
                year = stoi( userInput );
            }
            catch(...){
                cout << "Invalid Input." << endl;
            }

            if (year > 1900 & year < 2156){
                cout << "Success." << endl;
                // return userInput;
            }
            else{cout << "Year must be between 1901-2155" << endl;}
        }
    }while(true);
}