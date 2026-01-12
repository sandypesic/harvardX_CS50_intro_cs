#include <stdio.h>

int main(void)
{
    int height;
    int c;

    do
    {
        printf("Height (1-8): ");
        if (scanf("%d", &height) != 1)
        {
            height = 0;
            while ((c = getchar()) != '\n' && c != EOF) ;
        }
    } while (height < 1 || height > 8);

    for (int r = 1; r <= height; r++)
    {
        for (int s = 0; s < height - r; s++)
            putchar(' ');

        for (int h = 0; h < r; h++)
            putchar('#');

        putchar(' ');
        putchar(' ');

        for (int h = 0; h < r; h++)
            putchar('#');

        putchar('\n');
    }

    return 0;
}