#include <windows.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <thread>
#include "firewall.h"
#include "process.h"

int main()
{
    std::vector <std::string> paths;
    std::string path;
    std::vector <std::thread> threads;
    std::fstream file;

    file.open("paths.txt");
    if (!file)
    {
        std::cout << "error reading file. ending program." << std::endl;
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

    firewallOn();
    std::cout << "Press enter to close window" << std::endl;
    std::cin.get();
}