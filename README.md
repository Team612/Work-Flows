Creating a .exe file that 
1) turns off firewall 
2) opens up the Driver's Station and other apps
3) turns on firewall again once it detects that those apps are closed out.

Current issues:
1) Preferred method of firewall isn't working. I prefer to use the Windows API method in firewall.cpp instead of the "system" command in firewall2.cpp. Idk why.
2) Can currently open an app, but can't detect when it closes. Still figuring that out.

Future stuff:
1) Adding an option for users to add a program to open instead of forcing them to edit the code and rebuild it.
2) Nice interface?