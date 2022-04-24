#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    system("cls");
    FILE* ptr;
    printf("Welcome To DA_Forces\n\n"
    
            "Select the appropriate choice from following\n\n"
            
            "1) Enter 0 for User\n"
            "2) Enter 1 for Admin\n\n");

    int  choice_1;
    scanf("%d", &choice_1);
    system("cls");
    if(choice_1 == 0)
    {
        printf("Select the appropriate choice from following\n\n"
            
            "1) Enter 0 for Login\n"
            "2) Enter 1 for Signup\n\n");

        int choice_2;
        scanf("%d", &choice_2);

        system("cls");

        if(choice_2 == 0)
        {
            char us_id[50], password[50];
            printf("Username : ");
            scanf("%s", us_id);
            printf("Password : ");
            scanf("%s", password);
            ptr = fopen("users_data.txt", "r");
            char temp[50];
            while(fscanf(ptr, "%s", temp)!=EOF)
            {
                printf("\n%s", temp);
                if(strcmp(temp, us_id) == 0)
                {
                    fscanf(ptr, "%s", temp);
                    printf("\n%s", temp);
                    if(strcmp(temp, password) == 0)
                    {
                        printf("\n\nSucessfully Login");
                        break;
                    }
                    else
                    {
                        printf("\n\nWrong Password");
                    }
                }
            }
            fclose(ptr);
            //confirm Username and password from file
        }
        else
        {
            char us_id[50], password[50];
            printf("Username : ");
            scanf("%s", us_id);
            printf("Password : ");
            scanf("%s", password);
            //confirm password
            //username already exists
            ptr = fopen("users_data.txt", "r");
            for(int i=0;i != EOF; i++)
            {
                char temp[50];
                fscanf(ptr, "%s", temp);
                if(strcmp(temp, us_id) == 0)
                {
                    fscanf(ptr, "%s", temp);
                    if(temp == password)
                    {
                        printf("Username already exists\n\n");
                        break;
                    }
                }
            }
            fclose(ptr);
            //Add username and password in file
            ptr = fopen("users_data.txt", "a");
            fprintf(ptr, "%s %s\n", us_id, password);
            fclose(ptr);
        }
    }

    return 0;
}