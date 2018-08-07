// GetMsiInfo.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <Windows.h>
#include <atlbase.h>
#include <atlsecurity.h>
#include <Msi.h>
#include <iostream>

/*
How to get product name and code:
	1.Get ProductCode:
		wmic product where "Name like '%Word%'" get Name, Version, IdentifyingNumber
	2.Get UpgradeCode by ProductCode:
		gwmi -Query "SELECT Value FROM Win32_Property WHERE Property='UpgradeCode' AND ProductCode='{YourGuid}'" | Format-Table Value

	OR:

	-------------------------------------------------------------------------------------------------------------------
	From:https://stackoverflow.com/questions/46637094/how-can-i-find-the-upgrade-code-for-an-installed-msi-file/46637095#46637095
	-------------------------------------------------------------------------------------------------------------------
	$wmipackages = Get-WmiObject -Class win32_product
	$wmiproperties = gwmi -Query "SELECT ProductCode,Value FROM Win32_Property WHERE Property='UpgradeCode'"
	$packageinfo = New-Object System.Data.Datatable
	[void]$packageinfo.Columns.Add("Name")
	[void]$packageinfo.Columns.Add("ProductCode")
	[void]$packageinfo.Columns.Add("UpgradeCode")

	foreach ($package in $wmipackages)
	{
	$foundupgradecode = $false # Assume no upgrade code is found

	foreach ($property in $wmiproperties) {

	if ($package.IdentifyingNumber -eq $property.ProductCode) {
	[void]$packageinfo.Rows.Add($package.Name,$package.IdentifyingNumber, $property.Value)
	$foundupgradecode = $true
	break
	}
	}

	if(-Not ($foundupgradecode)) {
	# No upgrade code found, add product code to list
	[void]$packageinfo.Rows.Add($package.Name,$package.IdentifyingNumber, "")
	}

	}

	$packageinfo | Format-table ProductCode, UpgradeCode, Name

	# Enable the following line to export to CSV (good for annotation). Set full path in quotes
	# $packageinfo | Export-Csv "[YourFullWriteablePath]\MsiInfo.csv"

	# copy this line as well
	-------------------------------------------------------------------------------------------------------------------
	
	OR:
	
	#Get Product code
	#https://stackoverflow.com/questions/29937568/how-can-i-find-the-product-guid-of-an-installed-msi-setup
	get-wmiobject Win32_Product | Format-Table IdentifyingNumber, Name, LocalPackage -AutoSize     

	#Get Upgrade code
	#https://stackoverflow.com/questions/46637094/how-can-i-find-the-upgrade-code-for-an-installed-msi-file/46637095#46637095
	gwmi -Query "SELECT ProductCode,Value FROM Win32_Property WHERE Property='UpgradeCode'" | Format-Table ProductCode,Value
*/

#pragma comment(lib,"msi.lib")

/*
{B57097EF-5F38-348C-8081-4D0F0B78757E}  {17D9044E-94D3-31EF-8894-4A971FF62BA7}
*/

int _tmain(int argc, _TCHAR* argv[])
{
	CString strProductUpgradeCode = _T("{17D9044E-94D3-31EF-8894-4A971FF62BA7}");
	DWORD dwProductIndex = 0;
	LPTSTR lpszProductCode = new TCHAR[50];
	
	MsiEnumRelatedProducts(strProductUpgradeCode, 0, dwProductIndex, lpszProductCode);
	//MsiGetProductCode(strProductUpgradeCode, lpszProductCode);

	//LPTSTR lpszProductCode = _T("{B57097EF-5F38-348C-8081-4D0F0B78757E}");
	DWORD dwBufferSize = MAX_PATH;
	//Get Product Name
	CString strProductName = "";
	MsiGetProductInfo(lpszProductCode, INSTALLPROPERTY_PRODUCTNAME, strProductName.GetBuffer(dwBufferSize), &dwBufferSize);
	std::wcout << strProductName.GetString() << std::endl;
	strProductName.ReleaseBuffer();

	//Get Version String
	CString strVersion = "";
	dwBufferSize = MAX_PATH;
	MsiGetProductInfo(lpszProductCode, INSTALLPROPERTY_VERSIONSTRING, strVersion.GetBuffer(dwBufferSize), &dwBufferSize);
	std::wcout << strVersion.GetString() << std::endl;
	strVersion.ReleaseBuffer();

	return 0;
}
