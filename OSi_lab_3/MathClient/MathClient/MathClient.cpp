// MathClient.cpp : Client app for MathLibrary DLL.
#include "pch.h" //Uncomment for Visual Studio 2017 and earlier
#include <iostream>
#include "MathClient.h"
#include <string.h>
#include <tchar.h>

using namespace std;

#define ORIGINAL "Old string for replace"
#define REPLACESTRING "ReplaceString"
LPCTSTR DLL_PATH = L"MathLibrary";
LPCTSTR DLL_PATH_INJ = L"F:\\Курс_3_Семестр_1\\ОСиСП\\OSi_lab_3\\MathLibrary\\Debug\\MathLibrary.dll";
char ORIGINAL_STR[] = ORIGINAL;
char REPLACEMENT_STR[] = "New beautiful string";

int main()
{
	const char str[] = ORIGINAL;
	int act;
	cout << "It was: " << ORIGINAL << endl << endl;
	cout << "1 - Static import; 2 - Dynamic import; 3 - Injection library;" << endl;
	cin >> act;
	switch (act)
	{
	case 1:
		StaticImport();
		break;
	case 2:
		DynamicImport();
		break;
	case 3:
		InjectionImport();
		break;
	default:
		break;
	}
	cout << endl <<	
		"It is: " << str << endl;
}

void StaticImport() {
	ReplaceString(ORIGINAL_STR, REPLACEMENT_STR);
}

typedef void (*PFN_ReplaceString)(char*, char*);

void DynamicImport() {
	HINSTANCE hdll = LoadLibrary(DLL_PATH);
	if (hdll != NULL)
	{
		PFN_ReplaceString pReplaceString = (PFN_ReplaceString)GetProcAddress(hdll, REPLACESTRING);
		(pReplaceString)(ORIGINAL_STR, REPLACEMENT_STR);
	}
}

void InjectionImport() {
	DWORD pid = GetCurrentProcessId();
	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
	if (hProcess == INVALID_HANDLE_VALUE) {
		return;
	}
	void* loc = VirtualAllocEx(hProcess, 0, MAX_PATH, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
	if (!loc) {
		return;
	}
	WriteProcessMemory(hProcess, loc, DLL_PATH_INJ, _tcslen(DLL_PATH_INJ) + 1, 0);
	HANDLE hThread = CreateRemoteThread(hProcess, 0, 0, (LPTHREAD_START_ROUTINE)LoadLibrary, loc, 0, 0);
	if (hThread) {
		CloseHandle(hThread);
	}
	if (hProcess) {
		CloseHandle(hProcess);
	}
}
