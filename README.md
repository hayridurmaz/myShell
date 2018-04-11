# Hello World! myShell
This is a brand new shell for Linux. It has capability to execute commands threaded.
## Compalation:
It is enough to execute ./compile file. If it is not executable, execute Command: chmod +x compile 

## Usage:
- Shell has 2 options of mode; 1. interactive mode or 2. batch mode. If you execute ./myShell without any argumants, program will start in interactive mode.
- Otherwise, you can add an argument of batch file path and name! like: ./myShell /batch/fie/path/and/name.txt
- If commands are splited by | , they will be executed sequentally. If commands are splited by ';', those will be executed threaded.
