#include <stdio.h>

int get_positive_int(void);
void meow(int n);

int main(void)
{
    int n = get_positive_int();
    meow(n);
}

// Get number of meows
int get_positive_int(void)
{
    int n;

    do
    {
        printf("Number: ");
        int result = scanf("%d", &n);

        // Clear invalid input from buffer
        if (result != 1)
        {
            n = 0; // force the loop to continue
            int c;
            while ((c = getchar()) != '\n' && c != EOF); // discard bad input
        }

    } while (n < 1);

    return n;
}

// Meow some number of times
void meow(int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("meow\n");
    }
}