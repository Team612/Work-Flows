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
    return elevateNow(readOpen);
}

int readOpen()
{
    std::vector <std::string> paths;
    std::string path;
    std::vector <std::thread> threads;
    std::fstream file;

    file.open("paths.txt");
    if (!file)
    {
        std::cout << "error reading file. ending program. press enter to close." << std::endl;
        std::cin.get();
        return -1;
    }

    std::cout << "\nFile read successfully." << std::endl;
    firewallOff();

    while(getline(file, path))
    {
        paths.push_back(path);
        threads.emplace_back(process, path);
    }

    for (auto& t: threads){t.join();}

    std::cout << "to confirm that all of your programs are closed, press enter." << std::endl;
    std::cin.get();

    firewallOn();
    std::cout << "Press enter to close window" << std::endl;
    std::cin.get();
    return 0;
}