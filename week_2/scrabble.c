#include <stdio.h>
#include <ctype.h>
#include <string.h>

int compute_score(char word[]) {
    int score = 0;
    for (int i = 0; i < strlen(word); i++) {
        char c = toupper(word[i]);
        switch (c) {
            case 'A': case 'E': case 'I': case 'L': case 'N': 
            case 'O': case 'R': case 'S': case 'T': case 'U':
                score += 1; break;
            case 'D': case 'G':
                score += 2; break;
            case 'B': case 'C': case 'M': case 'P':
                score += 3; break;
            case 'F': case 'H': case 'V': case 'W': case 'Y':
                score += 4; break;
            case 'K':
                score += 5; break;
            case 'J': case 'X':
                score += 8; break;
            case 'Q': case 'Z':
                score += 10; break;
            default:
                score += 0;
        }
    }
    return score;
}

int main() {
    char player1_word[100];
    char player2_word[100];

    printf("Player 1: ");
    scanf("%s", player1_word);

    printf("Player 2: ");
    scanf("%s", player2_word);

    int score1 = compute_score(player1_word);
    int score2 = compute_score(player2_word);

    if (score1 > score2) {
        printf("Player 1 wins!\n");
    } else if (score2 > score1) {
        printf("Player 2 wins!\n");
    } else {
        printf("Tie!\n");
    }

    return 0;
}