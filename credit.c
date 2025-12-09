#include <stdio.h>

int main(void)
{
    long long card;
    printf("Number: ");
    scanf("%lld", &card);

    int sum = 0;
    int digit_count = 0;

    long long temp = card;

    while (temp > 0)
    {
        int digit = temp % 10;

        if (digit_count % 2 == 1)
        {
            int prod = digit * 2;
            sum += (prod / 10) + (prod % 10);
        }
        else
        {
            sum += digit;
        }

        temp /= 10;
        digit_count++;
    }

    int valid = (sum % 10 == 0);

    long long start = card;
    while (start >= 100)
        start /= 10;

    int first = start / 10;
    int first_two = start;

    if (valid)
    {
        if (digit_count == 15 && (first_two == 34 || first_two == 37))
            printf("AMEX\n");
        else if (digit_count == 16 && (first_two >= 51 && first_two <= 55))
            printf("MASTERCARD\n");
        else if ((digit_count == 13 || digit_count == 16) && first == 4)
            printf("VISA\n");
        else
            printf("INVALID\n");
    }
    else
    {
        printf("INVALID\n");
    }

    return 0;
}