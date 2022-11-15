// Write a program for file, opening, defining, closing, file modes, file types, writing content into a file.
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
FILE* create(char* s, char* mode){
    FILE* file = fopen(s, mode);                    // Creating a file
    return file;
}
void read(FILE *file){
    char ch;
    printf("Content: ");
    while((ch=fgetc(file))!=EOF) printf("%c",ch);   // Printing contents of file
    printf("\n");
}
void write(FILE *file){
    char s[10000];
    printf("Enter the String: ");
    getchar();
    gets(s);
    fputs(s,file);                                  // Writing into the file
}
int main(){
    char name[10001], mode[3]; 
    printf("Enter the Filename: ");
    scanf("%s",name);
    char *fname = strcat(name,".txt");
    while(1){
        printf("For reading: r\nFor writing: w\nFor continue writing: a\nFor read and write: r+\nFor erase and write: w+\nFor read and write: a+\nTo exit: 0\nEnter the operations: ");
        scanf("%s",mode);
        if(mode[0]=='0') break;                     // End program when user inputs 0
        FILE *file = create(fname, mode);           // Creating file pointer
        if(file == NULL){                           // If file is not present
            printf("File not found");
            break;
        }
        if(strcmp(mode,"r")==0) read(file);         // Read file when mode is r
        else if(strcmp(mode,"w")==0) write(file);   // Create and write file when mode is w
        else if(strcmp(mode,"a")==0) write(file);   // Append writing when mode is a
        else if(strcmp(mode,"r+")==0){              // Reading and writing when mode is r+
            read(file);
            write(file);
        }
        else if(strcmp(mode,"w+")==0){              // Erasing and writing when mode is w+
            read(file);
            write(file);
        }
        else if(strcmp(mode,"a+")==0){              // Reading and writing when mode is a+
            read(file);
            write(file);
        }
        else printf("Invalid Input");
        printf("\n");   
        system("pause");
        fclose(file);                               // Closing file
        //system("cls");
    }                                               
    return 0;
}