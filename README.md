Creating a .exe file that 
1) turns off firewall 
2) opens up selected app
3) turns on firewall again once it detects that those apps are closed out.

Instructions:
1) create a text file in the same directory as the exe called paths.txt.
2) Paste your path into the paths.txt file. DO IT IN THIS FORMAT:
    a) NO QUOTES!
    b) Use "/" instead of "\" or "\\."

Current issues:

Future plans:
1) I'll see what I can do with JSON files.
2) Better firewall using Windows API
3) Nice interface?

Code walkthrough:

main.cpp is the starting point where everything is run. main.cpp also has the readOpen() function that reads the paths.txt file and passes it into process.h. It also turns on and off the firewall.

elevate.h elevates to administrator privileges, then runs the readOpen() function in main.cpp.

firewall.h has functions to turn firewall on and off.

process.h has the function to open an app. It then detects if that app is closed. when it closes, it returns to readOpen.