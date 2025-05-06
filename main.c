#include <stdio.h>
#include "Ff.h"
int main(){
    int input_number;
    do {
        printf("-------\n");
        printf("  |    |\n");
        printf("  O    |\n");
        printf(" /|\\   |\n");
        printf(" / \\   |\n");
        printf("       |\n");
        printf("-------\n");
        printf("Welcome to the Hanged Man game!\n");
        meniu();
        printf("Enter your choice: ");
        scanf("%d", &input_number);
        getchar();

        switch (input_number) {
        case 1:
            play_hangman();
            break;
        case 2:
            number_3();
            break;
        case 3:
            number_4();
            break;
        case 4:
            number_5();
            break;
        case 5:
            display_history();
            break;
        case 0:
            printf("Exiting program. Goodbye!\n");
            break;
        default:
            printf("Invalid choice. Please try again.\n");

        }

    } while (input_number != 0);

    return 0;
}