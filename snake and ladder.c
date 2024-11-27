#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define BOARD_SIZE 100

// Function prototypes
void printBoard(int playerPos);
int rollDice();
int checkPosition(int pos);

int main() {
    srand(time(0));
    int playerPos = 1;
    char choice;

    printf("Welcome to Snake and Ladder Game!\n");
    printf("Press 'r' to roll the dice, 'q' to quit:\n");

    while (playerPos < BOARD_SIZE) {
        printf("Your current position: %d\n", playerPos);
        printf("Enter your choice: ");
        scanf(" %c", &choice);

        if (choice == 'r') {
            int diceRoll = rollDice();
            printf("You rolled a %d!\n", diceRoll);
            playerPos += diceRoll;

            if (playerPos > BOARD_SIZE) {
                playerPos -= diceRoll;
                printf("Roll exceeds board size, stay at position: %d\n", playerPos);
            } else {
                playerPos = checkPosition(playerPos);
                printf("Your new position: %d\n", playerPos);
            }
            
            printBoard(playerPos);
        } else if (choice == 'q') {
            printf("Thank you for playing!\n");
            break;
        } else {
            printf("Invalid choice. Try again.\n");
        }
    }

    if (playerPos == BOARD_SIZE) {
        printf("Congratulations! You've reached the end!\n");
    }

    return 0;
}

void printBoard(int playerPos) {
    for (int i = 1; i <= BOARD_SIZE; i++) {
        if (i == playerPos) {
            printf("[P] ");
        } else {
            printf("[%d] ", i);
        }

        if (i % 10 == 0) {
            printf("\n");
        }
    }
}

int rollDice() {
    return (rand() % 6) + 1;
}

int checkPosition(int pos) {
    // Define ladders: {start, end}
    int ladders[][2] = {
        {4, 14},
        {9, 31},
        {20, 38},
        {28, 84},
        {40, 59},
        {51, 67},
        {63, 81},
        {71, 91}
    };

    // Define snakes: {start, end}
    int snakes[][2] = {
        {17, 7},
        {54, 34},
        {62, 19},
        {64, 60},
        {87, 24},
        {93, 73},
        {95, 75},
        {99, 78}
    };

    for (int i = 0; i < sizeof(ladders) / sizeof(ladders[0]); i++) {
        if (pos == ladders[i][0]) {
            printf("Ladder! Climb up from %d to %d.\n", ladders[i][0], ladders[i][1]);
            return ladders[i][1];
        }
    }

    for (int i = 0; i < sizeof(snakes) / sizeof(snakes[0]); i++) {
        if (pos == snakes[i][0]) {
            printf("Snake! Slide down from %d to %d.\n", snakes[i][0], snakes[i][1]);
            return snakes[i][1];
        }
    }

    return pos;
}