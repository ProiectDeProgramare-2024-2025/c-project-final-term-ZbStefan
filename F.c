#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Ff.h"
#include <ctype.h>
#include <time.h>

typedef struct {
    char name[50];
    int score;
} data;

void meniu() {
    printf("\033[34m===== Greetings =====\n");
    printf("\n");
    printf("\033[33m===== MENU =====\n");
    printf("1. If you want to play \033[32mHANGMAN\033[33m, enter the number 1!\n");
    printf("2. If you want to see the \033[32mLEADERBOARD\033[33m, enter the number 2!\n");
    printf("3. If you want to learn the \033[32mRULES\033[33m, enter the number 3!\n");
    printf("4. If you want to \033[32mADD\033[33m a word, enter the number 4!\n");
    printf("5. If you want to see \033[32mGAME HISTORY\033[33m, enter the number 5!\n");
    printf("0. If you want to \033[31mEXIT\033[33m, enter the number 0!\n");
    printf("\033[0m\n");
}

int compareScores(const void *a, const void *b) {
    return ((data *)b)->score - ((data *)a)->score;
}

void read_leaderboard() {
    FILE *file = fopen("leaderboard.txt", "r");
    data leaderboard[100];
    int count = 0;

    printf("\n\033[34m===== LEADERBOARD =====\033[0m\n");
    printf("\033[33mRank  Player             Score\033[0m\n");
    printf("\033[33m------------------------------\033[0m\n");

    if (!file) {
        printf("\033[31mNo leaderboard data found :( \033[0m\n");
        return;
    }

    while (fscanf(file, "%s %d", leaderboard[count].name, &leaderboard[count].score) == 2) {
        count++;
    }
    fclose(file);

    if (count == 0) {
        printf("\033[31mLeaderboard is empty.\033[0m\n");
        return;
    }

    qsort(leaderboard, count, sizeof(data), compareScores);

    for (int i = 0; i < count; i++) {
        printf("\033[0m%-5d \033[32m%-18s\033[0m \033[32m%d\033[0m\n", i + 1, leaderboard[i].name, leaderboard[i].score);
    }
}


int number_3() {
    int back;
    read_leaderboard();
    printf("\nPress 1 to return to the menu, or 0 to exit:\n");
    scanf("%d", &back);
    while (getchar() != '\n');

    if (back == 1) {
        system("cls");
        meniu();
    } else if (back == 0) {
        printf("\033[31mGoodbye for now. I will be waiting for you!\033[0m\n");
        exit(0);
    } else {
        printf("\033[31mInvalid option.\033[0m\n");
    }

    return 0;
}

int number_4() {
    int back;
    printf("\033[34mHangman Rules:\033[0m\n");
    printf("\033[33m1. Objective: Guess the word before running out of attempts.\033[0m\n");
    printf("2. Guessing: Guess one letter at a time.\n");
    printf("\033[33m3. Incorrect Guesses: Wrong guesses add to the 'hangman' drawing.\033[0m\n");
    printf("\033[33m4. Attempts: You have 6 wrong guesses before losing.\033[0m\n");
    printf("\033[33m5. Win: Guess all the letters correctly.\033[0m\n");
    printf("\033[33m6. Lose: Run out of attempts without guessing the word.\033[0m\n");
    printf("\nPress 1 to return to the menu, or 0 to exit:\n");

    scanf("%d", &back);
    while (getchar() != '\n');

    if (back == 1) {
        system("cls");
        meniu();
    } else if (back == 0) {
        printf("\033[31mGoodbye for now. I will be waiting for you!\033[0m\n");
        exit(0);
    } else {
        printf("\033[31mInvalid option.\033[0m\n");
    }

    return 0;
}

int number_5(){
    char newName[50];
    printf("\033[33mEnter the new word: \033[0m");
    fgets(newName, sizeof(newName), stdin);
    newName[strcspn(newName, "\n")] = '\0';

    FILE *wordFile = fopen("words.txt", "a");
    if (wordFile == NULL) {
        printf("\033[31mError opening file :(\033[0m\n");
    } else {
        fprintf(wordFile, "%s\n", newName);
        fclose(wordFile);
        printf("\033[32mIt worked! The word '%s' has been added.\033[0m\n", newName);
    }
    return 0;
}

void display_game_tries(int tries)
{
    printf("-------\n");
    printf("  |    |\n");

    switch (tries)
    {
    case 0:
        printf("       |\n");
        printf("       |\n");
        printf("       |\n");
        printf("       |\n");
        break;
    case 1:
        printf("\033[31m  O    |\033[0m\n");
        printf("       |\n");
        printf("       |\n");
        printf("       |\n");
        break;
    case 2:
        printf("\033[31m  O    |\033[0m\n");
        printf("  |    |\n");
        printf("       |\n");
        printf("       |\n");
        break;
    case 3:
        printf("\033[31m  O    |\033[0m\n");
        printf(" /|    |\n");
        printf("       |\n");
        printf("       |\n");
        break;
    case 4:
        printf("\033[31m  O    |\033[0m\n");
        printf(" /|\\   |\n");
        printf("       |\n");
        printf("       |\n");
        break;
    case 5:
        printf("\033[31m  O    |\033[0m\n");
        printf(" /|\\   |\n");
        printf(" /     |\n");
        printf("       |\n");
        break;
    case 6:
        printf("\033[31m  O    |\033[0m\n");
        printf(" /|\\   |\n");
        printf(" / \\   |\n");
        printf("       |\n");
        break;
    }
    printf("-------\n");
}

void play_hangman()
{
    char word[50], guess, display[50];
    char used[100] = {0};
    int wrong = 0, correct = 0;

    FILE *file = fopen("words.txt", "r");
    if (!file) {
        printf("\033[31mError: words.txt not found.\033[0m\n");
        return;
    }

    char words[100][50];
    int count = 0;
    while (fgets(words[count], sizeof(words[0]), file)) {
        words[count][strcspn(words[count], "\n")] = '\0';
        count++;
    }
    fclose(file);

    if (count == 0) {
        printf("\033[31mNo words in file.\033[0m\n");
        return;
    }

    srand(time(NULL));
    strcpy(word, words[rand() % count]);
    int len = strlen(word);

    for (int i = 0; i < len; i++) display[i] = '_';
    display[len] = '\0';

    while (wrong < 6 && correct < len) {
        system("cls");
        display_game_tries(wrong);
        printf("Word: %s\n", display);
        printf("Guess a letter: ");
        scanf(" %c", &guess);
        guess = tolower(guess);

        int found = 0;
        for (int i = 0; i < len; i++) {
            if (tolower(word[i]) == guess && display[i] == '_') {
                display[i] = word[i];
                correct++;
                found = 1;
            }
        }

        if (found) {
            printf("\033[32mCorrect guess!\033[0m\n");
        } else {
            wrong++;
            printf("\033[31mWrong guess!\033[0m\n");
        }
    }

    system("cls");
    display_game_tries(wrong);

    if (correct == len) {
        printf("\033[32mYou won! The word was: %s\033[0m\n", word);
    } else {
        printf("\033[31mGame over! The word was: %s\033[0m\n", word);
    }

    char name[50];
    printf("\033[33mEnter your name: \033[0m");
    scanf(" %[^\n]", name);

    int score;

    if (correct == len) {
        score = 100 - wrong * 10;
    } else {
        score = 0;
    }

    FILE *lb = fopen("leaderboard.txt", "a");
    if (lb) {
        fprintf(lb, "%s %d\n", name, score);
        fclose(lb);
    } else {
        printf("Error opening leaderboard file.\n");
    }

    FILE *hist = fopen("history.txt", "a");
    if (hist) {
        char result[10];
        if (correct == len) {
            strcpy(result, "WIN");
        } else {
            strcpy(result, "LOSE");
        }
        fprintf(hist, "%s %s %s %d\n", result, name, word, score);
        fclose(hist);
    }

    printf("\033[32mScore saved: %d\033[0m\n", score);
}


void display_history() {
    char playerName[50];
    printf("\033[33mEnter the player's name to view their history: \033[0m");
    scanf(" %[^\n]", playerName);

    FILE *file = fopen("history.txt", "r");
    if (!file) {
        printf("\033[31mNo history data found.\033[0m\n");
        return;
    }

    char line[256];
    int found = 0;

    printf("\n\033[34m===== GAME HISTORY FOR %s =====\033[0m\n", playerName);
    printf("\033[33mResult                      Player        Word\033[0m\n");
    printf("\033[33m--------------------------------------------------\033[0m\n");

    while (fgets(line, sizeof(line), file)) {
        if (strstr(line, playerName) != NULL) {
            printf("%s", line);
            found = 1;
        }
    }

    fclose(file);

    if (!found) {
        printf("\033[31mNo history found for player '%s'.\033[0m\n", playerName);
    }
}
