/*
* Author: Huy Nguyen
* Kevin Bacon Game
* Version 1
* 
* This Driver is used to run the program by creating a
* BaconGenerator object and calling the
* Execute() method
*
* The required input will be a valid .txt file that 
* contains properly formatted texts in order for the
* program to run accurately
*
*/
#include <iostream>
#include "BaconGenerator.h"


int main(int argc, char* argv[])
{
    if (argv[1] == nullptr)
    {
        cout << "No file found" << endl;
    }
    else
    {
        BaconGenerator BG;
        BG.Execute(argv[1]);
    }
    return 0;
}
