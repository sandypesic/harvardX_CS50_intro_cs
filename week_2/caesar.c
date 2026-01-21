#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    
    for (int i = 0; i < strlen(argv[1]); i++)
    {
        if (!isdigit(argv[1][i]))
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
    }

    int k = atoi(argv[1]);
    k = k % 26;

    char text[1000];
    printf("plaintext:  ");
    fgets(text, sizeof(text), stdin);

    int len = strlen(text);
    if (len > 0 && text[len - 1] == '\n')
    {
        text[len - 1] = '\0';
    }

    printf("ciphertext: ");
    for (int i = 0; i < strlen(text); i++)
    {
        char c = text[i];
        char rotated;

        if (islower(c))
            rotated = ((c - 'a') + k) % 26 + 'a';
        else if (isupper(c))
            rotated = ((c - 'A') + k % 26 + 'A');
        else
            rotated = c;

        printf("%c", rotated);
    }
    printf("\n");

    return 0;
}