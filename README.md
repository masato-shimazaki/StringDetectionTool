# string-detection-output-file

This project provides a simple setup for building and debugging a C++ program using Visual Studio Code. Follow the instructions below to compile and build your C++ project.

## Requirements

1. **Visual Studio Code**: Install it from [here](https://code.visualstudio.com/).
2. **C++ Extension for VS Code**: Install the C++ extension (ms-vscode.cpptools) from the Extensions view in VS Code.
3. **GCC Compiler**: Ensure `g++` is installed on your system. For Windows, you can use [MinGW](http://www.mingw.org/). For macOS, you can use [Homebrew](https://brew.sh/) to install `gcc`. For Linux, use your package manager (e.g., `apt` for Ubuntu).

## Setup

1. **Open your project folder** in Visual Studio Code.

2. **Create a simple C++ program**:
   - Create a file named `main.cpp` and add the following code:

     ```cpp
     #include <iostream>

     int main() {
         std::cout << "Hello, World!" << std::endl;
         return 0;
     }
     ```

3. **Configure the build task**:
   - Go to the menu bar and select `Terminal` > `Run Build Task` > `Configure Build Task` > `Create tasks.json file from template` > `Others`.
   - Replace the contents of `tasks.json` with the following:

     ```json
     {
         "version": "2.0.0",
         "tasks": [
             {
                 "label": "build",
                 "type": "shell",
                 "command": "g++",
                 "args": [
                     "-g",
                     "${file}",
                     "-o",
                     "${fileDirname}/${fileBasenameNoExtension}"
                 ],
                 "group": {
                     "kind": "build",
                     "isDefault": true
                 },
                 "problemMatcher": ["$gcc"],
                 "detail": "Generated task for building C++ files."
             }
         ]
     }
     ```

4. **Configure debugging**:
   - Go to the menu bar and select `Run` > `Add Configuration...`.
   - Replace the contents of `launch.json` with the following:

     ```json
     {
         "version": "0.2.0",
         "configurations": [
             {
                 "name": "C++ Launch",
                 "type": "cppdbg",
                 "request": "launch",
                 "targetArchitecture": "x64",
                 "program": "${workspaceRoot}/a.out",
                 "args": [
                     "-o", "${workspaceRoot}/res/out/file.txt",
                     "-i", "${workspaceRoot}/res/txt/basic.txt",
                     "-i", "${workspaceRoot}/res/txt/sample.txt"
                 ],
                 "stopAtEntry": false,
                 "cwd": "${workspaceRoot}",
                 "environment": [],
                 "externalConsole": true,
                 "linux": {
                     "MIMode": "gdb"
                 },
                 "osx": {
                     "MIMode": "lldb"
                 },
                 "windows": {
                     "MIMode": "gdb"
                 }
             }
         ]
     }
     ```

## Compile

To compile your C++ program, press `Command + Shift + B` on macOS or `Ctrl + Shift + B` on Windows/Linux.

## Build and Debug

To build and debug your C++ program, press `F5`.

## Additional Information

- **Building**: The build task uses `g++` to compile your C++ files with debugging information included (`-g` flag).
- **Debugging**: The `launch.json` configuration allows you to debug your program using `gdb`, the GNU debugger.

By following these instructions, you can efficiently compile, build, and debug your C++ programs within Visual Studio Code.
