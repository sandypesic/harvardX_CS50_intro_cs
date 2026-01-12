#include <stdio.h>

// Constant
#define N 3

// Prototype
float average(int length, int array[]);

int main(void)
{
    int scores[N];

    // Get scores
    for (int i = 0; i < N; i++)
    {
        printf("Score %d: ", i + 1);
        scanf("%d", &scores[i]);
    }

    // Print average
    printf("Average: %.2f\n", average(N, scores));

    return 0;
}

float average(int length, int array[])
{
    int sum = 0;
    for (int i = 0; i < length; i++)
    {
        sum += array[i];
    }
    return sum / (float) length;  // cast to float for decimal average
}
