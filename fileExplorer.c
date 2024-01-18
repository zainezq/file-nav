#include <stdio.h>
//#define _DEFAULT_SOURCE
#include <dirent.h>
#include <unistd.h>
#include <limits.h>
#define NORMAL_COLOR  "\x1B[0m"
#define GREEN  "\x1B[32m"
#define BLUE  "\x1B[34m"

// Function prototype
int getDir(char *dir);
int makeFile(FILE *file);
int listFiles();
int isSpecialDirectory(const char *name);
int strcmp();

int main(){
    FILE *fptr;
    char cwd[FILENAME_MAX]; //4096
    int choice;
    while (1)
    {
        printf("1. Display current directory\n");
        printf("2. Make a new file\n");
        printf("3. List all files\n");
        printf("4. Exit\n");
        // Get user input
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice){
            case 1:
                printf("\n");
                getDir(cwd);
                printf("\n");
                break;
            case 2:
                printf("\n");
                makeFile(fptr);
                printf("\n");
                break;
            case 3:
                printf("\n");
                listFiles();
                printf("\n");

                break;
            case 4:
                printf("Exiting program\n");
                return 0;
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


        int listFiles() {
          DIR * d;
          struct dirent * dir;
          d = opendir(".");
          if (d) {
            while ((dir = readdir(d)) != NULL) {

              if (dir -> d_type != DT_DIR) // if the type is not directory just print it with blue color
                printf("%s%s\n", BLUE, dir -> d_name);

            }
            closedir(d);

          }
          return 0;

        }


