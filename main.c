#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define LISTFILE "/tmp/list.txt"
#define MAX_DESCRIPTION_SIZE 27
#define MAX_REMINDERS 4

struct reminder {
    char description[MAX_DESCRIPTION_SIZE];
};

struct reminder reminders[MAX_REMINDERS] = {{0}}; 

int save_storage(FILE *fp) {

    fp = fopen(LISTFILE, "w");
    if (fp == NULL) {
        perror("Error opening file");
        return(-1);
    };

    int counter = 0;
    
    while(1) {
        if (counter == MAX_REMINDERS) {
            break;
        };
        if (strncmp(reminders[counter].description, "", 1) == 0) {
            break;
        };   
        fputs(reminders[counter].description, fp);
        counter++;
    };
    fclose(fp);
    printf("Successfully saved reminders.\n");
    return(0);

};

int load_storage(FILE *fp) {
    
    fp = fopen(LISTFILE, "r");
    if (fp == NULL) {
        perror("Error opening file");
        return(-1);
    };
    int counter = 0;
    while (1) {
        if (counter == MAX_REMINDERS) {
            break;
        }
        fgets(reminders[counter].description, MAX_DESCRIPTION_SIZE, (FILE*)fp);
        if ( feof(fp) ) {
            break;
        }
        counter++;
    }
    fclose(fp);
    printf("Load file into memory.\n");
    return(0);
    
};

int main(int argc, char *argv[]){
    FILE *fp;
    char buff[MAX_DESCRIPTION_SIZE];

    if (strncmp(argv[1], "show", 4) == 0){
        
        int lf = load_storage(fp);
        if (lf == -1) {
            return (-1);
        }
        int counter = 0;
        while (counter < MAX_REMINDERS) {
            if (strncmp(reminders[counter].description, "", 1) == 0) {
                break;
            }
            printf("%i: %s", counter + 1, reminders[counter].description);
            counter++;
        }

    } else if (strncmp(argv[1], "add", 3) == 0) { 
     
        int lf = load_storage(fp);
        if (lf == -1) {
            return (-1);
        }

        printf("Enter description for new item (Limit %i): ", MAX_DESCRIPTION_SIZE - 2);
        fgets(buff, MAX_DESCRIPTION_SIZE, stdin);
        
        int counter = 0;
        int found_new_line = 0;
        while (counter < MAX_DESCRIPTION_SIZE) {
            if (strncmp(&buff[counter], "\n", 2) == 0) {
                found_new_line = 1;
                break;
            };
            if (counter == (MAX_DESCRIPTION_SIZE - 1) && found_new_line == 0) {
                // swap end char with new line char
                strncpy(&buff[MAX_DESCRIPTION_SIZE - 2], "\n", 2);
            };
            counter++;
        };
        
        counter = 0;
        while (counter < MAX_REMINDERS) {
            if (strncmp(reminders[counter].description, "", 1) == 0) {
                strncpy(reminders[counter].description, buff, MAX_DESCRIPTION_SIZE);
                save_storage(fp);
                break;
            };
            counter++;
        }

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

