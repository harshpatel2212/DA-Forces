#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define SIZE 1024
#define PORT 4444

void write_file(int sockfd, char *fname)
{
    int n;
    FILE *fp;
    printf("%s\n", fname);
    char *filename = (char *)malloc(sizeof(char) * (strlen(fname) + 1));
    filename = fname;
    char buffer[SIZE];

    fp = fopen(filename, "w");
    while (1)
    {
        n = recv(sockfd, buffer, SIZE, 0);
        if (n <= 0)
        {
            printf("[-]Error in Writing file.\n");
        }
        fprintf(fp, "%s", buffer);
        bzero(buffer, SIZE);
    }
    fclose(fp);
    free(filename);
    return;
}

int main(int argc, char *argv[])
{
    int ret;
    int sockfd, new_sock;
    struct sockaddr_in server_addr, new_addr;
    socklen_t addr_size;
    char buffer[SIZE];
    char *filename = (char *)malloc(sizeof(char) * (100));

    pid_t childPid;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        printf("[-]Error in socket");
        exit(1);
    }
    printf("[+]Server socket created successfully.\n");

    memset(&server_addr, '\0', sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    ret = bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
    if (ret < 0)
    {
        printf("[-]Error in bind");
        exit(1);
    }
    printf("[+]Binding successfull.\n");

    if (listen(sockfd, 10) == 0)
    {
        printf("[+]Listening....\n");
    }
    else
    {
        printf("[-]Error in listening");
        exit(1);
    }
    while (1)
    {
        addr_size = sizeof(new_addr);
        new_sock = accept(sockfd, (struct sockaddr *)&new_addr, &addr_size);
        if (new_sock < 0)
        {
            printf("[-]Error in accept");
            exit(1);
        }
        printf("Connection accepted from %s : %d\n", inet_ntoa(new_addr.sin_addr), ntohs(new_addr.sin_port));
        childPid = fork();
        if (childPid == 0)
        {
            close(sockfd);
            while (1)
            {
                int n;
                n = recv(new_sock, buffer, SIZE, 0);
                if (n <= 0)
                {
                    printf("[-]Error in Reading file.\n");
                }
                if (strcmp(buffer, "EXIT") == 0)
                {
                    printf("Disconnected accepted from %s : %d\n", inet_ntoa(new_addr.sin_addr), ntohs(new_addr.sin_port));
                    close(new_sock);

                    // Exit needs to send data where it needs to rm all files and display the verdict. returning pid and ppid
                    break;
                }
                else if (strcmp(buffer, "PATH") == 0)
                {
                    strcpy(filename, buffer);
                }
                else
                {
                    write_file(new_sock, filename);
					printf("[+]Data written in the file successfully.\n");
                }
                bzero(buffer, sizeof(buffer));
            }
        }
    }
    return 0;
}
