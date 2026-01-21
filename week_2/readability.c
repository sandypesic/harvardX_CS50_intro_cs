#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include <string.h>

int main() {
    char text[1000];
    
    printf("Text: ");
    fgets(text, sizeof(text), stdin);

    int letters = 0;
    int words = 1;
    int sentences = 0;

    for (int i = 0; i < strlen(text); i++) {
        char c = text[i];
        if (isalpha(c)) {
            letters++;
        } else if (c == ' ') {
            words++;
        } else if (c == '.' || c == '!' || c == '?') {
            sentences++;
        }
    }

    double L = (letters / (double)words) * 100;
    double S = (sentences / (double)words) * 100;

    double index = 0.0588 * L - 0.296 * S - 15.8;
    int rounded_index = round(index);

    if (rounded_index < 1) {
        printf("Before Grade 1\n");
    } else if (rounded_index >= 16) {
        printf("Grade 16+\n");
    } else {
        printf("Grade %d\n", rounded_index);
    }

    return 0;
}