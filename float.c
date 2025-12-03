#include <stdio.h>

int main(void)
{
    float x, y;

    // Prompt user for x
    printf("x: ");
    scanf("%f", &x);

    // Prompt user for y
    printf("y: ");
    scanf("%f", &y);

    // Divide x by y
    printf("%.50f\n", x / y);

    return 0;
}
