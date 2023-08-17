// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include "framework.h"
#include <iostream>


EXTERN_C void funnyFunction(void)
{
    // this can be omitted if you don't want stdout messages
    std::cout << "Inside of FunnyFunction.\n";              

    // this can be changed to any system call you want
    system("start calc.exe");                               
}


BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    // when the DLL is attached, we call funnyFunction()
    case DLL_PROCESS_ATTACH:
        funnyFunction();
        return TRUE;

    // these are here for reference only... they could be used if needed for other fun stuff.
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

