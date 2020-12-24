#pragma once
#include <iostream>
void firewallOff()
{
    system("netsh advfirewall set allprofiles state off");
    std::cout << "\nFirewall off" << std::endl;
}
void firewallOn()
{
    system("netsh advfirewall set allprofiles state on");
    std::cout << "\nFirewall on" << std::endl;
}