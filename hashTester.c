#include <stdio.h>
#include <stdint.h>
#include <string.h>

uint32_t hashFunc(char *key, size_t len)
{
    uint32_t hash = 5381;
    int c;

    while (c = *key++)
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash;
}

int main()
{
    char *string = "Harsh";
    printf("%s", string);
    printf("hash is : %u", hashFunc(string, strlen(string)));

    return 0;
}
