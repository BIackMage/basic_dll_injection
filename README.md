# Project Title

## Overview
This project consists of two parts written in C++ using Microsoft Visual Studio. The first part is a dynamic-link library (DLL) that serves to initiate a system call to run `calc.exe` 
when invoked by an external application. The second part is a DLL injector that facilitates the injection of the aforementioned DLL into a target binary.

## Part 1: DLL - Function and System Call
The DLL's primary function is to provide the following capabilities:

- Print a message to the standard output, indicating its successful operation.  This is optional and can be removed prior to compilation.
- Trigger a system call to launch `calc.exe` (Windows Calculator) when executed by an external application.

## Part 2: DLL Injector - Injecting the DLL into a Target Binary
The DLL injector's purpose is to inject the previously mentioned DLL into a target binary (currently set to "Notepad.exe"). 
The injection process involves the following steps:

1. Find the process ID (PID) of the target executable if it is currently running.
2. Open a handle to the target process.
3. Allocate memory within the target process's address space.
4. Write the path of the DLL to the allocated memory.
5. Create a handle to `Kernel32.dll` to locate and invoke the `LoadLibraryA` function.
6. Use the `CreateRemoteThread` function to initiate a remote thread within the target process.
7. Pass the address of `LoadLibraryA` and the DLL's location as parameters to the remote thread.
8. The `LoadLibraryA` function will execute the DLL within the target process, effectively injecting it as a new thread.

## Project Structure
- `yt_tutorial_dll/`: Contains the source code and build files for the first part of the project (DLL with system call and print statement).
- `yt_tutorial_app/`: Contains the source code and build files for the second part of the project (DLL injector).

## Getting Started
To compile and run the project, follow these steps:

1. Open the `yt_tutorial_dll/` folder in Microsoft Visual Studio.
2. Build the project to generate the DLL.
3. Open the `yt_tutorial_app/` folder in Microsoft Visual Studio.
4. Build the DLL injector project.
5. Run the injector executable, specifying the target binary and DLL path.

## Usage
1. Execute the target binary.
2. Compile and run the injector to inject the DLL into the target binary.
4. Observe the DLL's behavior, which includes printing a message and invoking `calc.exe` as a system call.

## License
This project is licensed under the [MIT License](LICENSE).

## Video Tutorials for this project
Part 1 - Creating a basic DLL and launcher application: https://youtu.be/dLksA_bbHP8
Part 2 - Modifing the DLL and creating an injection application: https://youtu.be/zUtAhKk1sL8
