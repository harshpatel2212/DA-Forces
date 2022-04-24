#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <conio.h>
#include <windows.h>
#include <process.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <errno.h>
#include <signal.h>

// PWD shell scripting to do.
#define PROJECTPATH scanf("%s\n", system("cat >1 pwd"));
#define ADMINPATH strcat(PROJECTPATH, "\\Admin");
#define USERSPATH strcat(PROJECTPATH, "\\Users");

#define MAXUSERSIZE 100

typedef struct usersDataBase
{
    int id;
    char name[50];
    char password[50];
    DIR *dir_ptr;
} user;

int main()
{
    int number_of_users = 0;
    user users[MAXUSERSIZE];
    system("cls");
    FILE *ptr;
launch:
    printf("Welcome To DA_Forces\n\n"

           "Select the appropriate choice from following\n\n"

           "1) Enter 0 for User\n"
           "2) Enter 1 for Admin\n\n");

    int choice_1;
    scanf("%d", &choice_1);
    system("cls");
    if (choice_1 == 0)
    {
        printf("Select the appropriate choice from following\n\n"

               "1) Enter 0 for Login\n"
               "2) Enter 1 for Signup\n\n");

        int choice_2;
        scanf("%d", &choice_2);

        system("cls");

        if (choice_2 == 0)
        {
            char us_id[50], password[50];
            printf("Username : ");
            scanf("%s", us_id);
            printf("Password : ");
            scanf("%s", password);
            ptr = fopen("users_data.txt", "r");
            char temp[50];
            while (fscanf(ptr, "%s", temp) != EOF)
            {
                if (strcmp(temp, us_id) == 0)
                {
                    fscanf(ptr, "%s", temp);
                    if (strcmp(temp, password) == 0)
                    {
                        printf("\nSucessfully Login");
                        break;
                    }
                    else
                    {
                        printf("\nWrong Password");
                    }
                }
            }
            fclose(ptr);
        }
        else
        {
            char us_id[50], password[50], confmPass[50];
        username:
            printf("Username : ");
            scanf("%s", us_id);
            ptr = fopen("users_data.txt", "r");
            for (int i = 0; i < MAXUSERSIZE; i++)
            {
                char temp[50];
                fscanf(ptr, "%s", temp);
                if (strcmp(temp, us_id) == 0)
                {
                    printf("Username already exists\n\n");
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
                ptr = fopen("users_data.txt", "a");
                fprintf(ptr, "%s %s\n", us_id, password);
                fclose(ptr);
                printf("\n\nSucessfully Signup\n");
                users[number_of_users].id = number_of_users;
                strncpy(users[number_of_users].name, us_id, 50);
                users[number_of_users].name[49] = '\0';
                strncpy(users[number_of_users].password, password, 50);
                users[number_of_users].password[49] = '\0';
                number_of_users++;
                system("cls");
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

        system("cls");
        if (choice_3)
        {
            // Add Question
        }
        else
        {
            // Shut-Down System
            printf("\nShutting Down System...\n\n");
            Sleep(1000);
            exit(0);
        }
    }
    return 0;
}