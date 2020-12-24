#include <Windows.h>

BOOL IsRunAsAdministrator();

void elevateNow(void (*func)())
{
	BOOL bAlreadyRunningAsAdministrator = FALSE;
	bAlreadyRunningAsAdministrator = IsRunAsAdministrator();
	if(!bAlreadyRunningAsAdministrator)
	{
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
				//if (dwError == ERROR_CANCELLED)
				//Annoys you to Elevate it LOL
				CreateThread(0,0,(LPTHREAD_START_ROUTINE)elevateNow,0,0,0);
	       	}
		}
	}
    else
    {
        (*func)();
    }
}

BOOL IsRunAsAdministrator()
{
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



/*LPCWSTR convertCharArrayToLPCWSTR(const char* charArray)
{
    wchar_t* wString=new wchar_t[4096];
    MultiByteToWideChar(CP_ACP, 0, charArray, -1, wString, 4096);
	LPCWSTR wchar = const_cast<LPCWSTR>(wString);
    return wchar;
}*/