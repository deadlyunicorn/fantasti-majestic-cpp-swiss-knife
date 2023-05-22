
#include <iostream>
#include <fstream>
#include <cstdio>
#include "lib/global_Functions.h"
#include "lib/main_Process.h"

void mainProcess();


using namespace std;

int main(){

    bar(); //Aesthetic - cout of a line bar
    cout << "---Type 'help' for help" <<endl;
    bar();

    mainProcess();
    
    return 0;
}

