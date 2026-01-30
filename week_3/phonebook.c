// Implements a phone book with structs (standard C)

#include <stdio.h>
#include <string.h>

typedef struct
{
    char *name;
    char *number;
} person;

int main(void)
{
    person people[3];

    people[0].name = "Yuliia";
    people[0].number = "+1-617-495-1000";

    people[1].name = "David";
    people[1].number = "+1-617-495-1000";

    people[2].name = "John";
    people[2].number = "+1-949-468-2750";

    // Buffer for user input
    char name[100];

    // Prompt user
    printf("Name: ");
    if (fgets(name, sizeof(name), stdin) == NULL)
    {
        return 1;
    }

    // Remove trailing newline
    name[strcspn(name, "\n")] = '\0';

    // Search for name
    for (int i = 0; i < 3; i++)
    {
        if (strcmp(people[i].name, name) == 0)
        {
            printf("Found %s\n", people[i].number);
            return 0;
        }
    }

    printf("Not found\n");
    return 1;
}