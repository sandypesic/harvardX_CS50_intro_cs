#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    
    char *key = argv[1];

    if (strlen(key) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    for (int i = 0; i < 26; i++)
    {
        if (!isalpha(key[i]))
        {
            printf("Usage: ./substitution key\n");
            return 1;
        }
    }

    for (int i = 0; i < 26; i++)
    {
        for (int j = i + 1; j < 26; j++)
        {
            if (toupper(key[i]) == toupper(key[j]))
            {
                printf("Usage: ./substitution key\n");
                return 1;
            }
        }
    }

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
        if (isupper(c))
            printf("%c", toupper(key[c - 'A']));
        else if (islower(c))
            printf("%c", tolower(key[c - 'a']));
        else
            printf("%c", c);
    }
    printf("\n");

    return 0;
}