# Simple File Management Program

This program is a basic command-line file management tool written in C. It provides several options for interacting with files and directories in the current working directory. The program includes functionalities such as displaying the current directory, creating new files, listing all files, removing files, and displaying the content of a file.

## Features
- **Display Current Directory**: Shows the current working directory.

- **Make a New File**: Allows the user to create a new file in the current directory.

- **List All Files**: Lists all files and folders in the current directory.

- **Remove a File**: Enables the user to delete a file from the current directory.

- **Display a File**: Shows the content of a selected file.

- **Exit**: Exits the program.

## How to Use
1. Run the program:
    - Compile using: `gcc fileExplorer.c -o fileExplorer`
    - Execution: `./fileExplorer `
2. Choose an option by entering the corresponding number.
3. Follow the prompts and instructions for each selected option.
4. After executing a command, the program will ask if you want to exit. Enter `1` to exit or `0` to continue using the program.


## Note
- This program assumes a Unix-like environment due to the use of certain system calls and ANSI escape codes.
- File operations may require appropriate permissions, and deleting files is irreversible.

Feel free to explore and use this program for basic file management tasks!