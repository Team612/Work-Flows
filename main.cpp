//Starting point.
#include <windows.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <thread>
#include "headers/firewall.h"
#include "headers/process.h"
#include "headers/elevate.h"

int readOpen();

int main()
{
    /*
    Main function:
    Elevates to administrator (see elevate.h). Then runs the readOpen() function below.
    */
    return elevateNow(readOpen);
}

int readOpen()
{
    /*
    Summary: Reads the paths.txt file, takes those paths and passes it to process.h, where it'll start those processes.
    First block of code creates a vector of threads.
    Second block of code detects if it can read the file. If not, it'll close.
    Third block of code turns off firewall (see firewall.h), then adds a thread to the vector.
        In that thread, the path gets passed to process.h, where it opens the program and detects if it has closed or not.
        Once it has detected if the programs are closed, it'll close the threads.
    Fourth block of code confirms if all programs are closed and turns on firewall again.
    */


   //First block
    std::string path;
    std::vector <std::thread> threads;
    std::fstream file;


    //Second block
    file.open("paths.txt");
    if (!file)
    {
        std::cout << "error reading file. ending program. press enter to close." << std::endl;
        std::cin.get();
        return -1;
    }
    std::cout << "\nFile read successfully." << std::endl;


    //Third block
    firewallOff(); //See firewall.h
    while(getline(file, path))
    {
        threads.emplace_back(process, path); //See process.h
    }
    for (auto& t: threads){t.join();}


    //Fourth block
    std::cout << "to confirm that all of your programs are closed, press enter." << std::endl;
    std::cin.get();
    firewallOn(); //See firewall.h
    std::cout << "Press enter to close window" << std::endl;
    std::cin.get();
    return 0;
}