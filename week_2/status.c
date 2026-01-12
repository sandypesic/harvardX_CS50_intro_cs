#include <stdio.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Missing command-line argument\n");
        return 1;  // return nonzero value to indicate error
    }

    printf("hello, %s\n", argv[1]);
    return 0;      // return 0 indicates success
}
