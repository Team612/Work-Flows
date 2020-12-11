#include <windows.h>
#include "firewall.h"
#include <iostream>

int main()
{
    firewallOff();
    HANDLE hProcess;
    HANDLE hThread;

    STARTUPINFO si;
    PROCESS_INFORMATION pi;

    DWORD dwProcessID =0;
    DWORD dwThreadID=0;

    ZeroMemory( &si, sizeof(si) );
    //si.cb = sizeof(si);
    ZeroMemory( &pi, sizeof(pi) );

    // Start the child process.
    bool process;

    process = CreateProcess( 
        TEXT("C:/Users/Myrrh's SurfacePro/AppData/Local/Programs/Microsoft VS Code/Code.exe"),   //App name
        NULL,           // Command Line
        NULL,           // Process handle not inheritable
        NULL,           // Thread handle not inheritable
        FALSE,          // Set handle inheritance to FALSE
        0,              // No creation flags
        NULL,           // Use parent's environment block
        NULL,           // Use parent's starting directory 
        &si,            // Pointer to STARTUPINFO structure
        &pi )           // Pointer to PROCESS_INFORMATION structure
    ;
    DWORD dwCode;

    while (true)
    {
        if(GetExitCodeProcess(pi.hProcess, &dwCode))
        {
            if (dwCode != 0) {firewallOff();}
            else {break;}
        }
        else {firewallOn(); break;}   
    }
    std::cout << "ended process" << std::endl;

    // Wait until child process exits.
    WaitForSingleObject( pi.hProcess, INFINITE );

    // Close process and thread handles. 
    CloseHandle( pi.hProcess );
    CloseHandle( pi.hThread );
    firewallOn();
    std::cout << "Press enter to close window" << std::endl;
    std::cin.get();
}