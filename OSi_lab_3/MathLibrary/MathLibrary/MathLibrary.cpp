// MathLibrary.cpp : Defines the exported functions for the DLL.
#include "pch.h" // use stdafx.h in Visual Studio 2017 and earlier
#include <utility>
#include <limits.h>
#include "MathLibrary.h"

void ReplaceString(char* lpOrigStr, char* lpReplStr)
{

	SIZE_T dwRead = 0;
	char* lpData;
	SYSTEM_INFO si;
	MEMORY_BASIC_INFORMATION mbi;

	int origLen = strlen(lpOrigStr);
	int replLen = strlen(lpReplStr);

	DWORD pid = GetCurrentProcessId();
	HANDLE hProcess = OpenProcess(PROCESS_VM_READ | 
		PROCESS_TRUST_LABEL_SECURITY_INFORMATION | 
		PROCESS_VM_WRITE | 
		PROCESS_QUERY_INFORMATION, 
		FALSE, pid);

	GetSystemInfo(&si);
	ZeroMemory(&mbi, sizeof(mbi));

	for (char* lpAdress = (char*)si.lpMinimumApplicationAddress;
		lpAdress <= si.lpMaximumApplicationAddress;
		lpAdress += mbi.RegionSize) {
		if (!VirtualQueryEx(hProcess, lpAdress, &mbi, sizeof(mbi))) {
			continue;
		}
		if (!((mbi.State == MEM_COMMIT) && (mbi.AllocationProtect == PAGE_READWRITE))) {
			continue;
		}
		lpData = (char*)GlobalAlloc(GMEM_FIXED, mbi.RegionSize);
		if (lpData == NULL)
			continue;
		ZeroMemory(lpData, mbi.RegionSize);
		dwRead = 0;
		lpAdress = (char*) mbi.BaseAddress;
		if (!ReadProcessMemory(hProcess, lpAdress, lpData, mbi.RegionSize, &dwRead)) {
			GlobalFree(lpData);
			continue;
		}
		for (int i = 0; i < (dwRead - origLen); ++i)
		{
			if (memcmp(lpOrigStr, &lpData[i], origLen) == 0)
			{
				char* ref = lpAdress + i;
				for (int j = 0; j < replLen; j++) {
					ref[j] = lpReplStr[j];
				}
				ref[replLen] = 0;
			}
		}
		GlobalFree(lpData);
	}
}