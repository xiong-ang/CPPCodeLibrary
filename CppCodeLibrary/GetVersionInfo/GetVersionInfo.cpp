// GetMsiInfo.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <Windows.h>
#include <atlbase.h>
#include <atlsecurity.h>
#include <Msi.h>
#include <iostream>


#pragma comment(lib,"version.lib")
BOOL GetVersionByFile(CString fileName, LPVOID* lppVersionData)
{
	//Get Version Lenght
	DWORD dwHandle;
	DWORD dwVersionLen = GetFileVersionInfoSize(fileName.GetBuffer(MAX_PATH), &dwHandle);
	fileName.ReleaseBuffer();

	if (dwVersionLen && (NULL != (*lppVersionData = malloc(dwVersionLen))))
		return GetFileVersionInfo(fileName.GetBuffer(MAX_PATH), dwHandle, dwVersionLen, *lppVersionData);

	return FALSE;
}


int _tmain(int argc, _TCHAR* argv[])
{
	LPVOID lpVersionData;
	if (GetVersionByFile(_T("C:\\Program Files (x86)\\Google\\Chrome\\Application\\chrome.exe"), &lpVersionData))
	{
		void *lpVersionBuf;
		UINT uiBufLen;
		if (VerQueryValue(lpVersionData, _T("\\StringFileInfo\\040904b0\\ProductVersion"), &lpVersionBuf, &uiBufLen) && uiBufLen>0)
		{
			CString csVersion((LPTSTR)lpVersionBuf);
			std::wcout << csVersion.GetString() << std::endl;
		}
	}

	if (lpVersionData)
	{
		free(lpVersionData);
		lpVersionData = NULL;
	}

	return 0;
}
