#include <stdio.h>

int main(void)
{
    long dollars = 1;
    char c;

    while (1) // infinite loop
    {
        printf("Here's $%li. Double it and give to next person? ", dollars);
        scanf(" %c", &c); // space before %c skips leftover newline

        if (c == 'y' || c == 'Y') // handle uppercase as well
        {
            dollars *= 2;
        }
        else
        {
            break;
        }
    }

    printf("Here's $%li.\n", dollars);

    return 0;
}
