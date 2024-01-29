#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define MAX_TRIES 6

void drawHangman(int wrongGuesses) {
    switch (wrongGuesses) {
        case 0:
            printf("  ___\n");
            printf(" |       |\n");
            printf(" |\n");
            printf(" |\n");
            printf(" |\n");
            printf(" |\n");
            break;
        case 1:
            printf("  ___\n");
            printf(" |       |\n");
            printf(" |       O\n");
            printf(" |\n");
            printf(" |\n");
            printf(" |\n");
            break;
        case 2:
            printf("  ___\n");
            printf(" |       |\n");
            printf(" |       O\n");
            printf(" |       |\n");
            printf(" |\n");
            printf(" |\n");
            break;
        case 3:
            printf("  ___\n");
            printf(" |       |\n");
            printf(" |       O\n");
            printf(" |      /|\n");
            printf(" |\n");
            printf(" |\n");
            break;
        case 4:
            printf("  ___\n");
            printf(" |       |\n");
            printf(" |       O\n");
            printf(" |      /|\\\n");
            printf(" |\n");
            printf(" |\n");
            break;
        case 5:
            printf("  ___\n");
            printf(" |       |\n");
            printf(" |       O\n");
            printf(" |      /|\\\n");
            printf(" |      /\n");
            printf(" |\n");
            break;
        case 6:
            printf("  ___\n");
            printf(" |       |\n");
            printf(" |       O\n");
            printf(" |      /|\\\n");
            printf(" |      / \\\n");
            printf(" |\n");
            break;
        default:
            break;
    }
}

void displayWord(char secretWord[], char guessedLetters[]) {
    int i, j;
    int wordLength = strlen(secretWord);

    printf("Secret Word: ");
    for (i = 0; i < wordLength; i++) {
        int found = 0;
        for (j = 0; j < strlen(guessedLetters); j++) {
            if (secretWord[i] == guessedLetters[j]) {
                found = 1;
                break;
            }
        }
        if (found) {
            printf("%c ", secretWord[i]);
        } else {
            printf("_ ");
        }
    }
    printf("\n");
}

int isGameOver(char secretWord[], char guessedLetters[]) {
    int i;
    int wordLength = strlen(secretWord);

    for (i = 0; i < wordLength; i++) {
        int found = 0;
        for (int j = 0; j < strlen(guessedLetters); j++) {
            if (secretWord[i] == guessedLetters[j]) {
                found = 1;
                break;
            }
        }
        if (!found) {
            return 0;
        }
    }

    return 1;
}

int main() {
    char words[][15] = {"hangman", "computer", "keyboard", "software"};
    int wordCount = sizeof(words) / sizeof(words[0]);

    srand(time(NULL));

    int randomIndex = rand() % wordCount;
    char secretWord[15];
    strcpy(secretWord, words[randomIndex]);

    char guessedLetters[26];
    int tries = 0;

    printf("Welcome to Hangman!\n");

    while (tries < MAX_TRIES) {
        char guess;
        printf("\nTries left: %d\n", MAX_TRIES - tries);
        printf("Guessed letters: %s\n", guessedLetters);
        displayWord(secretWord, guessedLetters);
        drawHangman(tries);
        printf("Enter a letter: ");
        scanf(" %c", &guess);

        int alreadyGuessed = 0;
        for (int i = 0; i < strlen(guessedLetters); i++) {
            if (guess == guessedLetters[i]) {
                alreadyGuessed = 1;
                break;
            }
        }

        if (alreadyGuessed) {
            printf("You already guessed that letter. Try again.\n");
            continue;
        }

        guessedLetters[strlen(guessedLetters)] = guess;
        guessedLetters[strlen(guessedLetters) + 1] = '\0';

        int found = 0;
        for (int i = 0; i < strlen(secretWord); i++) {
            if (guess == secretWord[i]) {
                found = 1;
                break;
            }
        }

        if (found) {
            printf("Correct!\n");
        } else {
            printf("Incorrect.\n");
            tries++;
        }

        if (isGameOver(secretWord, guessedLetters)) {
            printf("\nCongratulations! You guessed the word: %s\n", secretWord);
            return 0;
        }
    }
    drawHangman(tries);
    if (tries == MAX_TRIES) {
        printf("\nSorry, you ran out of tries. The correct word was: %s\n", secretWord);
    }

    return 0;
}