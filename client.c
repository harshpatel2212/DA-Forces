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

void send_file(FILE *fp, int sockfd)
{
    int n;
    char data[SIZE] = {0};

    while (fgets(data, SIZE, fp) != NULL)
    {
        if (send(sockfd, data, sizeof(data), 0) == -1)
        {
            printf("[-]Error in sending file.");
            exit(1);
        }
        bzero(data, SIZE);
    }
}

int main(int argc, char *argv[])
{
    int ret;
    FILE *fp;
    char *filename = (char *)malloc(sizeof(char) * (100));
    char buffer[SIZE];
    int sockfd;
    struct sockaddr_in server_addr;

    if (atoi(argv[1]) == 0)
    {
        filename = "dummy.txt";
        fp = fopen(filename, "w");
        int success;
        success = fputs("PATH\n", fp);
        success = fputs(argv[2], fp);
        if (success == EOF)
        {
            printf("[-]Error in writing to file.");
            exit(1);
        }
        fclose(fp);
    }
    else if (atoi(argv[1]) == 1)
    {
        strcpy(filename, argv[2]);
        puts(filename);
    }
    else
    {
        filename = "dummy.txt";
        fp = fopen(filename, "w");
        int success = fputs("EXIT", fp);
        if (success == EOF)
        {
            printf("[-]Error in writing to file.");
            exit(1);
        }
        fclose(fp);
    }

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

    ret = connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
    if (ret == -1)
    {
        printf("[-]Error in socket");
        exit(1);
    }
    printf("[+]Connected to Server.\n");

    // Opening file to send
    fp = fopen(filename, "r");
    if (fp == NULL)
    {
        printf("[-]Error in reading file.");
        exit(1);
    }

    send_file(fp, sockfd);
    fclose(fp);
    printf("[+]File data sent successfully.\n");
    printf("[+]Closing the connection.\n");
    close(sockfd);
    free(filename);
    return 0;
}
