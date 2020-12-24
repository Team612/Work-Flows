//Come here from main.cpp. This code elevates to administrator and then runs the rest of the code.
//I admit, I copied this code from the internet lol. Here it is: https://www.cplusplus.com/forum/windows/101207/
//This file is a bit messy. I might split it up into two files?

#include <Windows.h>

BOOL IsRunAsAdministrator();

int elevateNow(int (*func)())
{
    /*
    The first block of code checks if it's running as admin.
    If not, it'll call elevateNow() again in the second block of code, but as admin. If it's already as an admin, see line 15. 
        Uses a bit of recursion (i.e. calling a function within itself.)
    When it calls elevateNow(), it'll see that it's running as an admin, so it'll skip the second block of code.
    In the third block of code, it'll run a function, in this case, the readOpen() function in main.cpp.
        If the file is not found, it'll return -1 and end the program. If it's there, it'll run and return 0.
    */

   //First block
    int x; //for running readOpen().
	BOOL bAlreadyRunningAsAdministrator = FALSE;
	bAlreadyRunningAsAdministrator = IsRunAsAdministrator();


    //Second block.
	if(!bAlreadyRunningAsAdministrator)
	{
        x = 0;
		char szPath[MAX_PATH];
		if (GetModuleFileNameA(NULL, szPath, ARRAYSIZE(szPath)))
		{

			SHELLEXECUTEINFOA sei = { sizeof(sei) };

			//sei.lpVerb = convertCharArrayToLPCWSTR("runas");
			//sei.lpFile = convertCharArrayToLPCWSTR(szPath);
			sei.lpVerb = const_cast<LPCSTR>("runas");
			sei.lpFile = const_cast<LPCSTR>(szPath);
			sei.hwnd = NULL;
			sei.nShow = SW_NORMAL;

			if (!ShellExecuteExA(&sei))
			{
				DWORD dwError = GetLastError();
				CreateThread(0,0,(LPTHREAD_START_ROUTINE)elevateNow,0,0,0); //Recursion.
	       	}
		}
	}


    //Third block.
    else
    {
        x = (*func)(); //See main.cpp
    }
    return x;
}

BOOL IsRunAsAdministrator()
{
    /*
    Checks if it's running as an admin. I have no idea what's going on here. I just copied the code from the internet.
    It just works.
    Trust me :)
    */
    BOOL fIsRunAsAdmin = FALSE;
    DWORD dwError = ERROR_SUCCESS;
    PSID pAdministratorsGroup = NULL;

    SID_IDENTIFIER_AUTHORITY NtAuthority = SECURITY_NT_AUTHORITY;
    if (!AllocateAndInitializeSid(
        &NtAuthority, 
        2, 
        SECURITY_BUILTIN_DOMAIN_RID, 
        DOMAIN_ALIAS_RID_ADMINS, 
        0, 0, 0, 0, 0, 0, 
        &pAdministratorsGroup))
    {
        dwError = GetLastError();
        goto Cleanup;
    }

    if (!CheckTokenMembership(NULL, pAdministratorsGroup, &fIsRunAsAdmin))
    {
        dwError = GetLastError();
        goto Cleanup;
    }

Cleanup:

    if (pAdministratorsGroup)
    {
        FreeSid(pAdministratorsGroup);
        pAdministratorsGroup = NULL;
    }

    if (ERROR_SUCCESS != dwError)
    {
        throw dwError;
    }

    return fIsRunAsAdmin;
}