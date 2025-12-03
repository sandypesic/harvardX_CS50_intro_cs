#include <stdio.h>

int main(void)
{
    char c;

    // Prompt user to agree
    printf("Do you agree? ");
    scanf(" %c", &c);

    // Check whether agreed
    if (c == 'Y' || c == 'y')
    {
        printf("Agreed.\n");
    }
    else if (c == 'N' || c == 'n')
    {
        printf("Not agreed.\n");
    }
    else
    {
        printf("Invalid input.\n");
    }

    return 0;
}
