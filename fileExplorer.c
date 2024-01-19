#include <stdio.h>
#include <dirent.h>
#include <unistd.h>
#include <limits.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>

// Function prototype
int getDir(char *dir);
int makeFile(FILE *file);
void ls();
int strcmp();
void printCommands();

void printCommands(){
    printf("1. Display all commands\n");
    printf("2. Display current directory\n");
    printf("3. Make a new file\n");
    printf("4. List all files\n");
    printf("5. Exit\n");
}

int main() {
    FILE *fptr;
    char cwd[FILENAME_MAX]; //4096
    int choice;
    printCommands();


    while (1) {
        // Get user input
        printf("Enter your choice: ");
        scanf("%d", &choice);
        if (choice == 1)
        {
            printf("\n");
            printCommands();
            printf("\n");
        } else if (choice == 2) {
            printf("\n");
            getDir(cwd);
            printf("\n");
        } else if (choice == 3) {
            printf("\n");
            makeFile(fptr);
            printf("\n");
        } else if (choice == 4) {
            printf("\n");
            ls();
            printf("\n");
        } else if (choice == 5) {
            printf("Exiting program\n");
            return 0;
        } else {
            printf("Invalid choice. Please enter a valid option.\n");
        }
    }

    return 0;
}

    int getDir(char *dir){
        if (getcwd(dir, FILENAME_MAX) != NULL) {
       printf("Current working dir: %s\n", dir);
        } else {
       perror("getcwd() error");
       return 1;
        }
        return 0;
    }

    int makeFile(FILE *file){
        char fileName[100];
        printf("Enter a name for the file: ");
        scanf("%99s", fileName);
        file = fopen(fileName, "w");

        if (file == NULL) {
            printf("Error creating the file.\n");
            return 1; // Exit the program with an error code
        }

        fclose(file);
        printf("File '%s' created successfully.\n", fileName);

        return 0;
    }


void ls(){
    DIR *directory;
    struct dirent *entry;

    // Open the directory
    directory = opendir(".");

    // Check if the directory was successfully opened
    if (directory == NULL) {
        perror("Unable to open directory");
        return;
    }

    // Arrays to store folder and file names
    char **folders = NULL;
    char **files = NULL;
    int folderCount = 0;
    int fileCount = 0;

    // Read directory entries
    while ((entry = readdir(directory)) != NULL) {
        // Skip entries for "." and ".."
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        // Get the full path of the entry
        char fullpath[PATH_MAX];
        snprintf(fullpath, sizeof(fullpath), "%s/%s", ".", entry->d_name);

        // Get information about the entry
        struct stat statbuf;
        if (stat(fullpath, &statbuf) == -1) {
            perror("Unable to get file status");
            continue;
        }

        // Collect folder and file names
        if (S_ISDIR(statbuf.st_mode)) {
            // Directory
            folders = realloc(folders, (folderCount + 1) * sizeof(char *));
            folders[folderCount] = strdup(entry->d_name);
            folderCount++;
        } else {
            // File
            files = realloc(files, (fileCount + 1) * sizeof(char *));
            files[fileCount] = strdup(entry->d_name);
            fileCount++;
        }

    }

        // Close the directory
        closedir(directory);

        // Print folders
        for (int i = 0; i < folderCount; i++) {
            printf("\033[1;34m%s\033[0m   ", folders[i]);
            free(folders[i]);
        }
        free(folders);

        // Print files
        for (int i = 0; i < fileCount; i++) {
            printf("\033[1;32m%s\033[0m   ", files[i]);
            free(files[i]);
        }
        free(files);

        printf("\n");
    }   

