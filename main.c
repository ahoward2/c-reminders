#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define LISTFILE "/tmp/list.txt"
#define MAX_DESCRIPTION_SIZE 27

int main(int argc, char *argv[]){
    FILE *fp;
    char buff[MAX_DESCRIPTION_SIZE];    

    if (strncmp(argv[1], "show", 4) == 0){
        
        fp = fopen(LISTFILE, "r");
        if (fp == NULL) {
            perror("Error opening file");
            return(-1);
        }
        int counter = 1;
        while (1) {
            fgets(buff, MAX_DESCRIPTION_SIZE, (FILE*)fp);
            if ( feof(fp) ) {
                break;
            }
            printf("%i: %s", counter,  buff);
            counter++;
        }
        fclose(fp);

    } else if (strncmp(argv[1], "add", 3) == 0) { 
      
        char buff[MAX_DESCRIPTION_SIZE]; 
        printf("Enter description for new item (Limit %i): ", MAX_DESCRIPTION_SIZE - 2);
        fgets(buff, MAX_DESCRIPTION_SIZE, stdin);
        
        int counter = 0;
        int found_new_line = 0;
        while (counter < MAX_DESCRIPTION_SIZE) {
            if (strncmp(&buff[counter], "\n", 2) == 0) {
                found_new_line = 1;
                break;
            }
            if (counter == (MAX_DESCRIPTION_SIZE - 1) && found_new_line == 0) {
                // swap end char with new line char
                strncpy(&buff[MAX_DESCRIPTION_SIZE - 2], "\n", 2);
            }
            counter++;
        }

        fp = fopen(LISTFILE, "a");
        fputs(buff, fp);
        fclose(fp);
        printf("New item successfully added to list. \n");

    } else if (strncmp(argv[1], "rm", 2) == 0) {

        printf("remove from list of items \n");

        // TODO: Need implementation for removing individual items from storage
    
    } else if (strncmp(argv[1], "dl", 2) == 0) {  

        remove(LISTFILE);
        printf("List successfully deleted. \n");

    } else if (strncmp(argv[1], "db", 2) == 0) {
       
       printf("Useful command for debugging");
       // USE THIS TO DEBUG

    } else {

        fprintf(stderr, "Invalid arg passed.\n");
        return(-1);

    }

    return 0;
}

