// Capitalizes a copy of a string without memory errors

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    // Allocate memory for input string
    char *s = malloc(1024);
    if (s == NULL)
    {
        return 1;
    }

    // Get string from user
    printf("s: ");
    if (fgets(s, 1024, stdin) == NULL)
    {
        free(s);
        return 1;
    }

    // Remove trailing newline, if any
    s[strcspn(s, "\n")] = '\0';

    // Allocate memory for copy
    char *t = malloc(strlen(s) + 1);
    if (t == NULL)
    {
        free(s);
        return 1;
    }

    // Copy string
    strcpy(t, s);

    // Capitalize first character
    if (strlen(t) > 0)
    {
        t[0] = toupper(t[0]);
    }

    // Print strings
    printf("s: %s\n", s);
    printf("t: %s\n", t);

    // Free memory
    free(s);
    free(t);

    return 0;
}