#include <iostream>
#include <vector>
#include <fstream>
#include "global_Functions.h"

using namespace std;

class Friend{
  private:
    string firstName;
    string surName;
    int birthDay;
    int birthMonth;
    int birthYear;
  public:
    void setFirstName(string firstName){
      this->firstName=firstName;
    }
    void setSurName(string surName){
      this->surName=surName;
    }
    void setBirthDay(int birthDay){
      this->birthDay=birthDay;
    }
    void setBirthMonth(int birthMonth){
      this->birthMonth=birthMonth;
    }
    void setBirthYear(int birthYear){
      this->birthYear=birthYear;
    }
    string generate(){
      string temp;

      temp="FRIEND ENTRY";
      temp+=("\nName: "+firstName);
      temp+=("\nSurname: "+surName);
      temp+=("\nYear: "+to_string(birthYear));
      temp+=("\nMonth: "+to_string(birthMonth));
      temp+=("\nDay: "+to_string(birthDay));
      temp+="\nEND OF FRIEND ENTRY\n\n";

      return temp;
    }
    string DisplayInfo(){
      string temp;

      temp="";
      temp+=("Name: "+firstName);
      temp+=("\nSurname: "+surName);
      temp+=("\nYear: "+to_string(birthYear));
      temp+=("\nMonth: "+to_string(birthMonth));
      temp+=("\nDay: "+to_string(birthDay));

      return temp;
    }
    string getName(){
      return (firstName + " " +surName);
    }
    int getBirthday(){
      return birthDay;
    }
    int getMonth(){
      return birthMonth;
    }
    int getYear(){
      return birthYear;
    }
    Friend operator-(Friend& friendRef){
          Friend tempObj;
          tempObj.setFirstName(" ");
          tempObj.setSurName(" ");

          int temp,temp2;
          temp=friendRef.getBirthday()-this->getBirthday();
          if (temp < 0){
            temp2=30-temp;
          }
          else {
            temp2=temp;
          }
          tempObj.setBirthDay(temp2);
          
          if (temp<0){
            temp=friendRef.getMonth()-this->getMonth()-1;
          }
          else {
            temp=friendRef.getMonth()-this->getMonth();
          }

          tempObj.setBirthMonth(temp);

          if (temp<0){
            temp2=12-(temp);
          }
          else{
            temp2=temp;
          }

          tempObj.setBirthMonth(temp2);
          if (temp<0){
            temp=friendRef.getYear()-this->getYear()-1;
          }
          else {
            temp=friendRef.getYear()-this->getYear();
          }
          temp2=temp;
          tempObj.setBirthYear(temp2);
          
          return tempObj;
          
    };
};

namespace friendListClass{

class friendList{

    private:

        vector<Friend> friendList;

    public:

        void addFriend(const Friend& friendObj ){

            friendList.push_back( friendObj );

        }

        string getFriendNames(){
            string output = "";
            for ( int i=0 ;    i < friendList.size()    ; i++ ){

                output += to_string(i+1)+". " + friendList[i].getName() + "\n" ;
                
            }
            return output;
        }

        int getfriendCount (){
            return friendList.size();
        }

        void generateFromFile( string& filename );

        Friend getFriendNum(int i){
          return friendList[i];
        }


};

}


void friendListClass::friendList::generateFromFile(string& filename){
        
        Friend currentFriend;

        ifstream currentFile(filename);
        
        if (!currentFile){

            cout << "Error! File disappeared." << endl;

            return;
        
        }


        string line; //line we are currently reading from file
        bool foundFriend=false;
        

        
        string phrase="FRIEND ENTRY";  //(#phrase)
        int FriendSearchLength=phrase.length(); //(#phrase)

        while(getline(currentFile,line)){

            
            int FriendSearchIndex=line.find(phrase);
            

            if( FriendSearchIndex != string::npos ){ //When a 'CREATE Friend' query is found

                int FriendIndex =  this->friendList.size(); //get current vector size - list items. 


                foundFriend = true;
            }

            if( foundFriend ){

                if( line.find("END OF FRIEND ENTRY") != string::npos ){  //In case we find the end of the entry
                    this->addFriend(currentFriend);  // Submit the Friend  -----  void addFriend( sqlFriend& Friend ){
                    foundFriend=false;
                    continue;
                }
                
                
                
                string* tempProperty = new string;
                string* tempValue = new string;

                getCommand(line,*tempProperty,*tempValue);

                if (*tempProperty=="Name:"){ //I spent like an hour debugging because I initially was equallying the values to e.g. 'Name' not 'Name:', but this is not .find() :(..
                  currentFriend.setFirstName(*tempValue);
                }
                else if (*tempProperty=="Surname:"){
                  currentFriend.setSurName(*tempValue);
                }
                else if (*tempProperty=="Year:"){
                  currentFriend.setBirthYear(stoi(*tempValue));
                }
                else if (*tempProperty=="Month:"){
                  currentFriend.setBirthMonth(stoi(*tempValue));
                }
                else if (*tempProperty=="Day:"){
                  currentFriend.setBirthDay(stoi(*tempValue));
                }


                delete tempProperty,tempValue;

            };
            
        };

        currentFile.close();
}
