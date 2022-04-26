#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>
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

        system("clear");

        // Login
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
            FILE *ptr = fopen(path, "r");
            if (ptr == NULL)
            {
                printf("Error in opening file\n");
                free(path);
                exit(1);
            }
            char *uname;
            uname = (char *)malloc(sizeof(char) * 50);
            uint32_t pass;
            // Working Fine. So Problem is in fscanf() or reading a string.
            while (fscanf(ptr, "%s", uname) != EOF)
            {
                fscanf(ptr, "%u", &pass);
                if (strcmp(uname, us_id) == 0)
                {
                    if (pass == hashFunc(password, strlen(password)))
                    {
                        printf("\nSucessfully Login\n");
                        fclose(ptr);
                        userLogin(us_id, pass, ptr, 0);
                    }
                    else
                    {
                        printf("\nWrong Password\n");
                    }
                }
            }
            free(path);
            free(uname);
            goto launch;
        }
        else
        {
            char us_id[50], password[50], confmPass[50];
        username:
            printf("Username : ");
            scanf("%s", us_id);

            char *path = (char *)malloc(sizeof(char) * 100);
            strcpy(path, ADMINPATH);
            strcat(path, "/users_data.txt");
            FILE *ptr = fopen(path, "r");
            if (ptr == NULL)
            {
                printf("Error in opening file\n");
                free(path);
                exit(1);
            }
            char *uname;
            uname = (char *)malloc(sizeof(char) * 50);
            uint32_t pass;
            int flag = 0;
            while (flag != EOF)
            {
                fscanf(ptr, "%s", uname);
                if (strcmp(uname, us_id) == 0)
                {
                    printf("Username already exists\n\n");
                    fclose(ptr);
                    free(uname);
                    free(path);
                    goto username;
                }
                flag = fscanf(ptr, "%u", &pass);
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
                system("clear");
                userLogin(us_id, hashFunc(password, strlen(password)), ptr, 1);
            }
            else
            {
                printf("\n\nPassword and Confirm Password doesn't match\n\n");
                goto confirmPassword;
            }
            free(path);
            free(uname);
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
    strcpy(folderPath, ADMINPATH);
    strcat(folderPath, "/users/");
    strcat(folderPath, username);
    if (flag)
    {
        printf("%s\n", folderPath);
        mode_t mode = 0777;
        mkdir(folderPath, mode);
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
                char *cmd;
                cmd = (char *)malloc(sizeof(char) * 100);
                strcpy(cmd, "ls Admin/users/");
                strcat(cmd, username);
                strcat(cmd, "/");
                strcat(cmd, ques->d_name);
                if (system(cmd) != 0)
                {
                    char *cmd2;
                    cmd2 = (char *)malloc(sizeof(char) * 100);
                    strcpy(cmd2, "mkdir Admin/users/");
                    strcat(cmd2, username);
                    strcat(cmd2, "/");
                    strcat(cmd2, ques->d_name);
                    system(cmd2);
                    free(cmd2);
                }
                free(cmd);
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
                free(questionsPath);
                free(question);
                
                printf("Select the appropriate choice from following\n\n"

                       "1) Enter 0 to Code\n"
                       "2) Enter 1 to go back\n\n");

                int choice;
                scanf("%d", &choice);
                if (choice == 0)
                {
                    system("touch Users/submission.c; chmod 755 Users/submission.c; gedit Users/submission.c");
                    printf("Select the appropriate choice from following\n\n"

                           "1) Enter 0 for Submit Code\n"
                           "2) Enter 1 to Cancel\n\n");
                    int choice;
                    scanf("%d", &choice);
                    if (choice == 0)
                    {
                        char *cmd;
                        cmd = (char *)malloc(sizeof(char) * 100);
                        printf("%s\n", cmd);
                        strcpy(cmd, "mv Users/submission.c Admin/users/");
                        strcat(cmd, username);
                        strcat(cmd, "/");
                        strcat(cmd, ques->d_name);
                        printf("%s\n", cmd);
                        system(cmd);
                        free(cmd);

                        // System Testing.
                        cmd = (char *)malloc(sizeof(char) * 100);
                        printf("%s\n", cmd);
                        strcpy(cmd, "Admin/runQuestion.sh ");
                        strcat(cmd, ques->d_name);
                        strcat(cmd, " ");
                        strcat(cmd, username);
                        system(cmd);
                        printf("%s\n", cmd);
                        free(cmd);

                        // Display Verdict.txt
                        FILE *ptr = fopen("verdict.txt", "r");
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
                        system("rm verdict.txt");
                    }
                    else
                    {
                        system("rm Users/submission.*");
                    }
                }
                else
                {
                    goto display;
                }
            }
        }
    }
    else
    {
        printf("\n\nExiting...\n\n");
        free(PROJECTPATH);
        free(ADMINPATH);
        free(USERSPATH);
        free(username);
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
