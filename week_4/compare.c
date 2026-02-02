// Prints two strings' addresses

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    // Allocate space for strings
    char *s = malloc(100);
    char *t = malloc(100);

    if (s == NULL || t == NULL)
    {
        return 1;
    }

    // Get two strings
    printf("s: ");
    fgets(s, 100, stdin);

    printf("t: ");
    fgets(t, 100, stdin);

    // Print strings' addresses
    printf("%p\n", (void *) s);
    printf("%p\n", (void *) t);

    // Free memory
    free(s);
    free(t);

    return 0;
}