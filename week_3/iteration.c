// Draws a pyramid using recursion (standard C)

#include <stdio.h>

void draw(int n);

int main(void)
{
    int height;

    // Prompt user for height
    printf("Height: ");
    scanf("%d", &height);

    // Draw pyramid
    draw(height);

    return 0;
}

void draw(int n)
{
    // Base case
    if (n <= 0)
    {
        return;
    }

    // Recursive call
    draw(n - 1);

    // Draw one row of width n
    for (int i = 0; i < n; i++)
    {
        printf("#");
    }
    printf("\n");
}