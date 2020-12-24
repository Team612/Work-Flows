#include <Windows.h>

BOOL IsRunAsAdministrator();

int elevateNow(int (*func)())
{
    int x;
	BOOL bAlreadyRunningAsAdministrator = FALSE;
	bAlreadyRunningAsAdministrator = IsRunAsAdministrator();
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
				CreateThread(0,0,(LPTHREAD_START_ROUTINE)elevateNow,0,0,0);
	       	}
		}
	}
    else
    {
        x = (*func)();
    }
    return x;
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