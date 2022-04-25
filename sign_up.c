#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <errno.h>
#include <signal.h>
#include <stdint.h>

#define MAXUSERSIZE 100

char *PROJECTPATH, *ADMINPATH, *USERSPATH;

// void userLogin(char *username, char *password, FILE *fp, int flag);
void userLogin(char *username, uint32_t password, FILE *fp, int flag);
uint32_t hashFunc(char *key, size_t len);

typedef struct usersDataBase
{
    int id;
    char name[50];
    uint32_t password;
    DIR *dir_ptr;
} user;

int main()
{
    PROJECTPATH = (char *)malloc(sizeof(char) * 100);
    ADMINPATH = (char *)malloc(sizeof(char) * 100);
    USERSPATH = (char *)malloc(sizeof(char) * 100);
    PROJECTPATH = getenv("PWD");
    strcpy(ADMINPATH, PROJECTPATH);
    strcat(ADMINPATH, "/Admin");
    strcpy(USERSPATH, PROJECTPATH);
    strcat(USERSPATH, "/Users");
    int number_of_users = 0;
    user users[MAXUSERSIZE];

launch:
    printf("Welcome To DA_Forces\n\n"

           "Select the appropriate choice from following\n\n"

           "1) Enter 0 for User\n"
           "2) Enter 1 for Admin\n\n");

    int choice_1;
    scanf("%d", &choice_1);
    system("clear");
    if (choice_1 == 0)
    {
        printf("Select the appropriate choice from following\n\n"

               "1) Enter 0 for Login\n"
               "2) Enter 1 for Signup\n\n");

        int choice_2;
        scanf("%d", &choice_2);
        printf("%d", choice_2);

        system("clear");

        if (choice_2 == 0)
        {
            char us_id[50], password[50];
            printf("Username : ");
            scanf("%s", us_id);
            printf("Password : ");
            scanf("%s", password);
            char *path = (char *)malloc(sizeof(char) * 100);
            strcpy(path, ADMINPATH);
            strcat(path, "/users_data.txt");
            printf("%s\n", ADMINPATH);
            printf("%s\n", path);
            FILE *ptr = fopen(path, "r");
            if (ptr == NULL)
            {
                printf("Error in opening file\n");
                exit(1);
            }
            char *uname;
            uname = (char *)malloc(sizeof(char) * 50);
            uint32_t pass;
            // Working Fine. So Problem is in fscanf() or reading a string.
            while (fscanf(ptr, "%s", uname) != EOF)
            {
                fscanf(ptr, "%u", &pass);
                printf("%s\n", uname);
                printf("%u\n", pass);
                printf("%u\n", hashFunc(password, strlen(password)));
                if (strcmp(uname, us_id) == 0)
                {
                    printf("in\n");
                    if (pass == hashFunc(password, strlen(password)))
                    {
                        printf("\nSucessfully Login\n");
                        fclose(ptr);
                        free(path);
                        userLogin(us_id, pass, ptr, 0);
                        break;
                    }
                    else
                    {
                        printf("\nWrong Password\n");
                        free(path);
                    }
                }
            }

            // Working Fine. So Problem is in fscanf() or reading a string.
            // char buffer;
            // while ((buffer = fgetc(ptr)) != EOF)
            // {
            //     printf("%c", buffer);
            // }
            // printf("\n");
            // userLogin(us_id, 223152475, ptr, 1);
            // fclose(ptr);
        }
        else
        {
            char us_id[50], password[50], confmPass[50];
        username:
            printf("Username : ");
            scanf("%s", us_id);
            printf("%s\n", us_id);

            char *path = (char *)malloc(sizeof(char) * 100);
            strcpy(path, ADMINPATH);
            strcat(path, "/users_data.txt");
            printf("%s\n", ADMINPATH);
            printf("%s\n", path);
            FILE *ptr = fopen(path, "r");
            if (ptr == NULL)
            {
                printf("Error in opening file\n");
                exit(1);
            }
            char *uname;
            uname = (char *)malloc(sizeof(char) * 50);
            uint32_t pass;
            int flag = 0;
            while (flag != EOF)
            {
                fscanf(ptr, "%s", uname);
                printf("%s\n", us_id);
                printf("%s\n", uname);
                if (strcmp(uname, us_id) == 0)
                {
                    printf("Username already exists\n\n");
                    fclose(ptr);
                    free(uname);
                    free(path);
                    goto username;
                }
                flag = fscanf(ptr, "%u", &pass);
                printf("%u\n", pass);
                printf("%u\n", hashFunc(password, strlen(password)));
            }
        confirmPassword:
            printf("Password : ");
            scanf("%s", password);
            printf("Confirm Password : ");
            scanf("%s", confmPass);
            if (strcmp(password, confmPass) == 0)
            {
                FILE *ptr = fopen(path, "a");
                fprintf(ptr, "%s %u\n", us_id, hashFunc(password, strlen(password)));
                fclose(ptr);
                printf("\n\nSucessfully Signup\n");
                users[number_of_users].id = number_of_users;
                strncpy(users[number_of_users].name, us_id, 50);
                users[number_of_users].name[49] = '\0';
                users[number_of_users].password = hashFunc(password, strlen(password));
                // users[number_of_users].password[49] = '\0';
                number_of_users++;
                system("clear");
            }
            else
            {
                printf("\n\nPassword and Confirm Password doesn't match\n\n");
                goto confirmPassword;
            }
            goto launch;
        }
    }
    else
    {
        printf("Select the appropriate choice from following\n\n"

               "1) Enter 0 for Shut-Down System\n"
               "2) Enter 1 for Adding Question\n\n");

        int choice_3;
        scanf("%d", &choice_3);

        system("clear");
        if (choice_3)
        {
            // Add Question
        }
        else
        {
            // Shut-Down System
            printf("\nShutting Down System...\n\n");
            sleep(1);
            exit(0);
        }
    }
    return 0;
}

// void userLogin(char *username, char *password, FILE *fp, int flag)
void userLogin(char *username, uint32_t password, FILE *fp, int flag)
{
    char *folderPath = (char *)malloc(sizeof(char) * 100);
    strcpy(folderPath, USERSPATH);
    strcat(folderPath, "/");
    strcat(folderPath, username);
    if (flag)
    {
        printf("%s\n", folderPath);
        mode_t mode = 0777;
        // mkdir(folderPath, mode);
    }
    free(folderPath);
    printf("Select the appropriate choice from following\n\n"

           "1) Enter 0 for Solve Question\n"
           "2) Enter 1 for Exit\n\n");

    int choice;
    scanf("%d", &choice);
    system("clear");
    if (choice == 0)
    {
        char *questionsPath = (char *)malloc(sizeof(char) * 100);
        strcpy(questionsPath, ADMINPATH);
        strcat(questionsPath, "/Questions");
        DIR *dir;
        dir = opendir(questionsPath);
        if (dir == NULL)
        {
            fprintf(fp, "Error: Directory not found\n");
            printf("Error: Directory not found\n");
            return;
        }
        else
        {
        display:;
            struct dirent *entry;
            int index = 1;
            while ((entry = readdir(dir)) != NULL)
            {
                if (entry->d_name[0] != '.')
                {
                    printf("%d :- %s\n", index, entry->d_name);
                    index++;
                }
            }
            closedir(dir);
            printf("Select the appropriate choice from following\n\n"

                   "1) Enter Question Number\n"
                   "2) Enter -1 for Exit\n\n");
            int choice;
            scanf("%d", &choice);
            if (choice == -1)
            {
                printf("\n\nExiting...\n\n");
                free(questionsPath);
                sleep(1);
                exit(0);
            }
            else
            {
                // Read Question.
                char *question = (char *)malloc(sizeof(char) * 100);
                strcpy(question, questionsPath);

                dir = opendir(questionsPath);
                struct dirent *ques;
                while ((ques = readdir(dir)) != NULL)
                {
                    if (ques->d_name[0] - '0' != choice)
                    {
                        continue;
                    }
                    else
                    {
                        strcat(question, "/");
                        strcat(question, ques->d_name);
                        strcat(question, "/description.txt");
                        break;
                    }
                }
                closedir(dir);
                printf("%s\n", question);
                FILE *ptr = fopen(question, "r");
                if (ptr == NULL)
                {
                    printf("Error in opening file\n");
                    exit(1);
                }
                char buffer;
                while ((buffer = fgetc(ptr)) != EOF)
                {
                    printf("%c", buffer);
                }
                printf("\n");
                fclose(ptr);

                printf("Select the appropriate choice from following\n\n"

                       "1) Enter 0 for Submit Question\n"
                       "2) Enter 1 to go back\n\n");

                int choice;
                scanf("%d", &choice);
                if (choice == 0)
                {
                    // Open Gedit. Save file and then call the tester.
                    // fork exec wait signal handling all here.
                    printf("Success...");
                }
                else
                {
                    free(question);
                    goto display;
                }
            }
        }
    }
    else
    {
        printf("\n\nExiting...\n\n");
        sleep(1);
        exit(0);
    }
}

uint32_t hashFunc(char *key, size_t len)
{
    uint32_t hash = 5381;
    int c;

    while (c = *key++)
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash;
}
