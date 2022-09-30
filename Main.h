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
	void Write(PBYTE addr, PBYTE val, PBYTE size = nullptr);
	void Read(PBYTE addr, PBYTE val, PBYTE size = nullptr);
	char* ProcessName;
	int ProcessID;
	uintptr_t GetModuleBaseAddress(char* mod_name);
private:
	int GetProcID();
	HANDLE GetHandleToProcess();
};

