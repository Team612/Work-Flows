#pragma once
#include <iostream>
void firewallOff()
{
    system("netsh advfirewall set allprofiles state off");
    std::cout << "Firewall off" << std::endl;
}
void firewallOn()
{
    system("netsh advfirewall set allprofiles state on");
    std::cout << "Firewall on" << std::endl;
}