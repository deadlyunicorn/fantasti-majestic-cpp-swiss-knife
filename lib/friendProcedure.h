
#include <iostream>
#include <vector>

#include "global_Functions.h"
#include "Friend_Objects_Functions.h"

using namespace std;



void friendProcedure(string& userInput){
  string filename;
  
  ofstream friendList;

  bar();
  cout << "Hello and welcome to the Friendlist!!" << endl;
  if (userSaidYesTo("Use an existing file?")){

    while(true){

      string tempFilename=getValidInput("Enter filename");
      
      if ( fileExists ( tempFilename ) ){
        filename=tempFilename;
        break;
      };

      cout << "Cannot find file." << endl;
      if ( userSaidYesTo("Retry?") ){
        continue;
      }
      else{
        break;
      };

    }


  }

  if( filename.size() < 1 ){
    filename=getValidInput("Enter a filename to save your friends into");
  }

  while(true){

    cout << "What do you want to do?" << endl;
    optionBar();

    cout << "1: Add a new friend" << endl;
    cout << "2: See all your friends" << endl;
    cout << "3: Compare the age of two friends" << endl;
    cout << "4: Find out about a friend's Zodiac" << endl;
    optionBar();
    cout << "exit: Go to the home menu" << endl;
    optionBar();

    while (true){
        userInput=getNumberInput();
        if( stoi(userInput) < 1 || stoi( userInput ) > 4 ){
          cout << "Please select one of the options listed above!" << endl;
          continue;
        }
        else{
          break;
        }
    }

    if(userInput=="!!!"){
      break;
    }

    friendList.open(filename,ofstream::out | ofstream::app);


    if(userInput=="1"){ //Add new friend

        Friend* newFriend=new Friend;

        newFriend->setFirstName(getValidInput("Enter friend's name"));
        newFriend->setSurName(getValidInput("Enter friend's surname"));
        
        while (true){
          string tempDay=getValidInput("Enter friend's day of birth. \nFor example if it is the 9th of December 2000, \nyou should write '9'");
          try{
            stoi(tempDay);
            if(stoi(tempDay)>0 && stoi(tempDay)<32){
              newFriend->setBirthDay(stoi(tempDay));
              break;
            }
            else{
              cout << "Not a valid day." << endl;
              waitBeforeContinue();
            }
          }
          catch(...){
            cout << "Please enter a number." << endl;
            waitBeforeContinue();

          }
        };

        while (true){
          string tempMonth=getValidInput("Enter friend's month of birth. \nFor example if it is the 9th of December 2000, \nyou should write '12'");
          try{
            stoi(tempMonth);
            if(stoi(tempMonth)>0 && stoi(tempMonth)<13){
              newFriend->setBirthMonth(stoi(tempMonth));
              break;
            }
            else{
              cout << "Not a valid month." << endl;
              waitBeforeContinue();


            }
            
          }
          catch(...){
            cout << "Please enter a number." << endl;
            waitBeforeContinue();

          }
        };

        while (true){
          string tempYear=getValidInput("Enter friend's year of birth. \nFor example if it is the 9th of December 2000, \nyou should write '2000'");
          //I was actually planning initially to accept 'December' and turn it manually to 12, but this is easier for all parties..
          try{
            stoi(tempYear);
            if(stoi(tempYear)>1900 && stoi(tempYear)<2200){ //Sorry future kids..
              newFriend->setBirthYear(stoi(tempYear));
              break;
            }
            else{
              cout << "Not a valid year." << endl;
              waitBeforeContinue();

            }
            
          }
          catch(...){
            cout << "Please enter a number." << endl;
            waitBeforeContinue();

          }
        };

        cout << "Success!" << endl;
        bar();
        cout << newFriend->generate();
        friendList << newFriend->generate();
        bar();
        
        delete newFriend;
        waitBeforeContinue();


          
      
    }
    else if(userInput=="2"){ //See all friends
      friendListClass::friendList* tempList=new friendListClass::friendList;
      tempList->generateFromFile(filename);
      
      cout << "Here is a list of your friends!" << endl;
      cout << "You have " << tempList->getfriendCount() << " friends." << endl;
      cout << tempList->getFriendNames();
      
      waitBeforeContinue();

      delete tempList;
    }
    else if(userInput=="3"){ //Compare age

    }
    else if(userInput=="4"){ //Friend's Zodiac

    }



    friendList.close();
  }

};


