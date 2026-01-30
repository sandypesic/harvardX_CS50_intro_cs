// Implements linear search for strings (standard C)

#include <stdio.h>
#include <string.h>

int main(void)
{
    // An array of strings
    char *strings[] = {
        "battleship",
        "boot",
        "cannon",
        "iron",
        "thimble",
        "top hat"
    };

    // Buffer for user input
    char s[100];

    // Prompt user
    printf("String: ");
    if (fgets(s, sizeof(s), stdin) == NULL)
    {
        return 1;
    }

    // Remove trailing newline from fgets
    s[strcspn(s, "\n")] = '\0';

    // Linear search
    for (int i = 0; i < 6; i++)
    {
        if (strcmp(strings[i], s) == 0)
        {
            printf("Found\n");
            return 0;
        }
    }

    printf("Not found\n");
    return 1;
}