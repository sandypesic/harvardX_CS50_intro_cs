// Saves names and numbers to a CSV file

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    // Open CSV file
    FILE *file = fopen("phonebook.csv", "a");
    if (file == NULL)
    {
        return 1;
    }

    // Allocate memory for name and number
    char name[1024];
    char number[1024];

    // Get name
    printf("Name: ");
    if (fgets(name, sizeof(name), stdin) == NULL)
    {
        fclose(file);
        return 1;
    }

    // Get number
    printf("Number: ");
    if (fgets(number, sizeof(number), stdin) == NULL)
    {
        fclose(file);
        return 1;
    }

    // Remove trailing newlines
    name[strcspn(name, "\n")] = '\0';
    number[strcspn(number, "\n")] = '\0';

    // Print to file
    fprintf(file, "%s,%s\n", name, number);

    // Close file
    fclose(file);

    return 0;
}
