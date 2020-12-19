#include <windows.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "firewall.h"
#include "process.h"

int main()
{
    std::fstream file;
 
    file.open("paths.txt");
    if (!file)
    {
        firewallOn();
    }
    std::cout << "\nFile read successfully." << std::endl;

    std::vector <std::string> paths;

    std::string path;
    while(getline(file, path))
    {
        paths.push_back(path);
    }

    for(std::string path: paths)
    {
        firewallOff();
        LPCTSTR lp=(LPCTSTR)path.c_str();
        process(lp);
    }

    firewallOn();
    std::cout << "Press enter to close window" << std::endl;
    std::cin.get();
}