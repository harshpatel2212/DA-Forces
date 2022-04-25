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

// PWD shell scripting to do.
char *PROJECTPATH, *ADMINPATH, *USERSPATH;

#define MAXUSERSIZE 100
void userLogin(char *username, char *password, FILE *fp, int flag);

typedef struct usersDataBase
{
    int id;
    char name[50];
    char password[50];
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
            // char *uname, *pass;
            // while (fscanf(ptr, "%s %s", uname, pass) != EOF)
            // {
            //     printf("%s\n", uname);
            //     printf("%s\n", pass);
            //     if (strcmp(uname, us_id) == 0)
            //     {
            //         if (strcmp(pass, password) == 0)
            //         {
            //             printf("\nSucessfully Login\n");
            //             userLogin(us_id, password, ptr, 0);
            //             break;
            //         }
            //         else
            //         {
            //             printf("\nWrong Password\n");
            //         }
            //     }
            // }

            // Working Fine. So Problem is in fscanf() or reading a string.
            char buffer;
            while ((buffer = fgetc(ptr)) != EOF)
            {
                printf("%c", buffer);
            }
            printf("\n");
            userLogin(us_id, "1", ptr, 1);
            fclose(ptr);
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
            printf("%s\n", ADMINPATH);
            printf("%s\n", path);
            FILE *ptr = fopen(path, "r");
            if (ptr == NULL)
            {
                printf("Error in opening file\n");
                exit(1);
            }
            char *uname, *pass;
            while (fscanf(ptr, "%s %s", uname, pass) != EOF)
            {
                if (strcmp(uname, us_id) == 0)
                {
                    printf("\nUsername already exists\n");
                    printf("Choose a unique Username\n\n");
                    goto username;
                }
            }
            fclose(ptr);
        confirmPassword:
            printf("Password : ");
            scanf("%s", password);
            printf("Confirm Password : ");
            scanf("%s", confmPass);
            if (strcmp(password, confmPass) == 0)
            {
                FILE *ptr = fopen(path, "a");
                fprintf(ptr, "%s %s\n", us_id, password);
                fclose(ptr);
                printf("\n\nSucessfully Signup\n");
                users[number_of_users].id = number_of_users;
                strncpy(users[number_of_users].name, us_id, 50);
                users[number_of_users].name[49] = '\0';
                strncpy(users[number_of_users].password, password, 50);
                users[number_of_users].password[49] = '\0';
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

void userLogin(char *username, char *password, FILE *fp, int flag)
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
}