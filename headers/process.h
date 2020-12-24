/*
Thread is passed into here.
Opens the app's path. For example, if i wanna open the Driver's Station, it'll pass the path to Driver's Station
    and open it up.
Once it detects that the user has closed that app, it'll stop the thread.
Copied from Win32 API: 
    https://docs.microsoft.com/en-us/windows/win32/procthread/creating-processes
NOTE: has to change the path into an LPCTSTR cause the Win32 API IS SUPER JANK MY GOD AAAA
*/

#include <iostream>
#include <Windows.h>

void process(std::string path)
{
    LPCTSTR lp=(LPCTSTR)path.c_str();
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

    std::cout << "creating process for " << path << std::endl;

    process = CreateProcess( 
        lp,   //App name
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
            if (dwCode == 0) {break;}
        }
        else {break;}   
    }
    std::cout << "ended process for " << path << std::endl;

    // Wait until child process exits.
    WaitForSingleObject( pi.hProcess, INFINITE );

    // Close process and thread handles. 
    CloseHandle( pi.hProcess );
    CloseHandle( pi.hThread );    
}