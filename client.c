#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define SIZE 1024

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
    char *ip = "127.0.0.1";
    int port = 8080;
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
        int success = fputs(fp, "EXIT");
        if (success == EOF)
        {
            printf("[-]Error in writing to file.");
            exit(1);
        }
    }
    else if (atoi(argv[1]) == 1)
    {
        *filename = argv[2];
    }
    else
    {
        filename = "dummy.txt";
        fp = fopen(filename, "w");
        int success = fputs(fp, argv[2]);
        if (success == EOF)
        {
            printf("[-]Error in writing to file.");
            exit(1);
        }
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
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = inet_addr(ip);

    ret = connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
    if (ret == -1)
    {
        printf("[-]Error in socket");
        exit(1);
    }
    printf("[+]Connected to Server.\n");

    fp = fopen(filename, "r");
    if (fp == NULL)
    {
        printf("[-]Error in reading file.");
        exit(1);
    }

    send_file(fp, sockfd);
    printf("[+]File data sent successfully.\n");
    printf("[+]Closing the connection.\n");
    close(sockfd);
    fclose(fp);
    free(filename);
    return 0;
}