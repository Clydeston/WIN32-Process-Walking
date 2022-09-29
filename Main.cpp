#include "Main.h"
#pragma warning(disable : 4996)

void GameInfo::GetProcessInfo() {
	GetProcID();
}

uintptr_t GameInfo::GetModuleBaseAddress(char* mod_name) {
	uintptr_t base_address = 0;
	// gets snapshot of all modules loaded into process
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, this->ProcessID);

	// checking if snapshot is valid
	if (hSnapshot != INVALID_HANDLE_VALUE) {
		// module struct 
		MODULEENTRY32 module_struct;

		// size of structure to be set to avoid issues
		module_struct.dwSize = sizeof(PROCESSENTRY32);

		// valid first module check
		if (!Module32First(hSnapshot, &module_struct))
			// exit if not valid
			return 0;

		// iterating through processes
		do {
			HANDLE hMod;

			// wchar_t to char type conversion
			char mod_name_conversion[256];
			sprintf(mod_name_conversion, "%ws", module_struct.szModule);

			// checking process name
			if (strcmp(mod_name, mod_name_conversion) == 0) {
				base_address = (uintptr_t)module_struct.modBaseAddr;
				break;
			}
		} while (Module32Next(hSnapshot, &module_struct));

		CloseHandle(hSnapshot);
		return base_address;

	}
}

int GameInfo::GetProcID() {
	int proc_id = 0;
	// gets snapshot of all processes
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

	// checking if snapshot is valid
	if (hSnapshot != INVALID_HANDLE_VALUE) {
		// module struct 
		PROCESSENTRY32 process_struct;

		// size of structure to be set to avoid issues
		process_struct.dwSize = sizeof(PROCESSENTRY32);

		// iterate through processes in snapshot to find correct module
		// valid first process check
		if (!Process32First(hSnapshot, &process_struct))
			return 0;
		// iterating through processes
		do {
			HANDLE hProc;
			//_tprintf(TEXT("\nPROCESS NAME:  %s"), process_struct.szExeFile);

			// wchar_t to char type conversion
			char proc_name_conversion[256];
			sprintf(proc_name_conversion, "%ws", process_struct.szExeFile);

			// checking process name
			if (strcmp(this->ProcessName, output) == 0) {
				this->ProcessID = process_struct.th32ProcessID;
				break;
			}

		} while (Process32Next(hSnapshot, &process_struct));

		CloseHandle(hSnapshot);
		return proc_id;

	}
}
