#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main(void)
{
    char s[100];  // buffer for input (max 99 chars + null terminator)

    printf("Before: ");
    fgets(s, sizeof(s), stdin);

    // Remove newline if present
    size_t len = strlen(s);
    if (len > 0 && s[len - 1] == '\n')
    {
        s[len - 1] = '\0';
        len--;
    }

    printf("After:  ");
    for (int i = 0; i < len; i++)
    {
        printf("%c", toupper(s[i]));
    }
    printf("\n");

    return 0;
}
