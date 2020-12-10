#include <iostream>
void firewallOff()
{
    system("netsh advfirewall set allprofiles state off");
}
void firewallOn()
{
    system("netsh advfirewall set allprofiles state on");
}