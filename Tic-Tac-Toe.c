#include <stdio.h>

char board[10] = {'o', '1', '2', '3', '4', '5', '6', '7', '8', '9'};

int checkwin(void);
void drawBoard(void);
int computerMove(void);

int main(void) {
    int choice;
    int result = -1;

    while (result == -1) {
        drawBoard();

        /* Tumhari chaal */
        printf("Tum (X), ek khaali number chuno (1-9): ");

        if (scanf("%d", &choice) != 1) {
            printf("Kripya 1 se 9 ke beech ka number dalo.\n");
            return 1;
        }

        if (choice < 1 || choice > 9 || board[choice] != '0' + choice) {
            printf("Galat chaal! Khaali box ka number chuno.\n");
            continue;
        }

        board[choice] = 'X';
        result = checkwin();

        if (result != -1) {
            break;
        }

        /* Computer ki chaal */
        choice = computerMove();

        if (choice == 0) {
            result = 0;
            break;
        }

        board[choice] = 'O';
        printf("Computer ne box %d chuna.\n", choice);

        result = checkwin();

        if (result == 1) {
            result = 2;  /* Computer jeeta */
        }
    }

    drawBoard();

    if (result == 1) {
        printf("Mai jeet gaya!\n");
    } else if (result == 2) {
        printf("Jao, jaakar seekh ke aao!\n");
    } else {
        printf("Game draw ho gaya!\n");
    }

    return 0;
}

int computerMove(void) {
    int i;

    /* Computer apni jeetne wali chaal dekhta hai. */
    for (i = 1; i <= 9; i++) {
        if (board[i] == '0' + i) {
            board[i] = 'O';

            if (checkwin() == 1) {
                board[i] = '0' + i;
                return i;
            }

            board[i] = '0' + i;
        }
    }

    /* Computer tumhari jeetne wali chaal rokta hai. */
    for (i = 1; i <= 9; i++) {
        if (board[i] == '0' + i) {
            board[i] = 'X';

            if (checkwin() == 1) {
                board[i] = '0' + i;
                return i;
            }

            board[i] = '0' + i;
        }
    }

    /* Center khaali ho to computer center lega. */
    if (board[5] == '5') {
        return 5;
    }

    /* Warna khaali corner lega. */
    int corners[] = {1, 3, 7, 9};

    for (i = 0; i < 4; i++) {
        int box = corners[i];

        if (board[box] == '0' + box) {
            return box;
        }
    }

    /* Aakhir mein koi bhi khaali box lega. */
    for (i = 1; i <= 9; i++) {
        if (board[i] == '0' + i) {
            return i;
        }
    }

    return 0;
}

int checkwin(void) {
    if (board[1] == board[2] && board[2] == board[3]) return 1;
    if (board[4] == board[5] && board[5] == board[6]) return 1;
    if (board[7] == board[8] && board[8] == board[9]) return 1;

    if (board[1] == board[4] && board[4] == board[7]) return 1;
    if (board[2] == board[5] && board[5] == board[8]) return 1;
    if (board[3] == board[6] && board[6] == board[9]) return 1;

    if (board[1] == board[5] && board[5] == board[9]) return 1;
    if (board[3] == board[5] && board[5] == board[7]) return 1;

    /* Agar koi khaali box hai, game jaari rahega. */
    for (int i = 1; i <= 9; i++) {
        if (board[i] == '0' + i) {
            return -1;
        }
    }

    return 0; /* Sab boxes bhar gaye: draw */
}

void drawBoard(void) {
    printf("\n=== TIC TAC TOE ===\n");
    printf("Tum (X)  -  Computer (O)\n\n");

    printf("     %c | %c | %c\n", board[1], board[2], board[3]);
    printf("    ---+---+---\n");
    printf("     %c | %c | %c\n", board[4], board[5], board[6]);
    printf("    ---+---+---\n");
    printf("     %c | %c | %c\n\n", board[7], board[8], board[9]);
}