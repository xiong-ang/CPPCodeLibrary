// GetProcessName.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<Windows.h>
#include<string.h>
#include<iostream>


int _tmain(int argc, _TCHAR* argv[])
{
	TCHAR szFileName[MAX_PATH + 1];
	if (0 == GetModuleFileName(NULL, szFileName, MAX_PATH) || nullptr == szFileName)
	{
		std::cout << "ERROR" << std::endl;
	}
	else
	{
		std::wcout << szFileName << std::endl;
	}

	return 0;
}

