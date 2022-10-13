#pragma once
#include <Windows.h>
#include <TlHelp32.h>
#include <iostream>
#include <tchar.h>
#include <wchar.h>

class GameInfo {
public:
	HANDLE hProc;
	void GetProcessInfo();
	char* ProcessName;
	int ProcessID;
	uintptr_t GetModuleBaseAddress(char* mod_name);
private:
	int GetProcID();
	HANDLE GetHandleToProcess();
};

