#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <errno.h>
#include <time.h>

char board[10];

void resetBoard(void);
void drawBoard(void);
int checkwin(void);
int computerMove(int level);
int getNumber(void);
int getLevel(void);
char getPlayAgain(void);

int main(void) {
    char playAgain = 'y';

    srand((unsigned int)time(NULL));

    while (playAgain == 'y') {
        int result = -1;

        resetBoard();
        int level = getLevel();

        while (result == -1) {
            drawBoard();

            int choice = getNumber();

            if (choice == -1) {
                printf("\nInput band ho gaya. Game khatam.\n");
                return 0;
            }

            if (choice == 0) {
                printf("Are pagal, is game mein 0 use nahi karna hai! Sahi se khelo.\n");
                continue;
            }

            if (board[choice] != '0' + choice) {
                printf("Sahi se dekho, ye number ho chuka hai. Ab dusra number enter karo aur dimag se khelo!\n");
                continue;
            }

            /* Tumhari chaal */
            board[choice] = 'X';
            result = checkwin();

            if (result != -1) {
                break;
            }

            /* Computer ki chaal */
            choice = computerMove(level);

            if (choice == 0) {
                result = 0;
                break;
            }

            board[choice] = 'O';
            printf("Computer ne box %d chuna.\n", choice);

            result = checkwin();
        }

        drawBoard();

        if (result == 1) {
            printf("Mai jeet gaya!\n");
        } else if (result == 2) {
            printf("Jao, jaakar seekh ke aao!\n");
        } else {
            printf("Game draw ho gaya!\n");
        }

        playAgain = getPlayAgain();
    }

    printf("Khelne ke liye dhanyavaad!\n");
    return 0;
}

void resetBoard(void) {
    board[0] = 'o';

    for (int i = 1; i <= 9; i++) {
        board[i] = '0' + i;
    }
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

/* 1 = tum jeete, 2 = computer jeeta, 0 = draw, -1 = game jaari */
int checkwin(void) {
    int lines[8][3] = {
        {1, 2, 3}, {4, 5, 6}, {7, 8, 9},
        {1, 4, 7}, {2, 5, 8}, {3, 6, 9},
        {1, 5, 9}, {3, 5, 7}
    };

    for (int i = 0; i < 8; i++) {
        int a = lines[i][0];
        int b = lines[i][1];
        int c = lines[i][2];

        if (board[a] == board[b] && board[b] == board[c]) {
            return board[a] == 'X' ? 1 : 2;
        }
    }

    for (int i = 1; i <= 9; i++) {
        if (board[i] == '0' + i) {
            return -1;
        }
    }

    return 0;
}

/* Level 1 = Easy, Level 2 = Hard */
int computerMove(int level) {
    int i;

    if (level == 1) {
        /* Easy: random khaali box chunta hai. */
        int emptyBoxes[9];
        int count = 0;

        for (i = 1; i <= 9; i++) {
            if (board[i] == '0' + i) {
                emptyBoxes[count] = i;
                count++;
            }
        }

        if (count == 0) {
            return 0;
        }

        return emptyBoxes[rand() % count];
    }

    /* Hard: computer apni jeetne wali chaal dekhta hai. */
    for (i = 1; i <= 9; i++) {
        if (board[i] == '0' + i) {
            board[i] = 'O';

            if (checkwin() == 2) {
                board[i] = '0' + i;
                return i;
            }

            board[i] = '0' + i;
        }
    }

    /* Hard: tumhari jeetne wali chaal rokta hai. */
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

    /* Center khaali ho to center lega. */
    if (board[5] == '5') {
        return 5;
    }

    /* Warna khaali corner lega. */
    {
        int corners[] = {1, 3, 7, 9};

        for (i = 0; i < 4; i++) {
            int box = corners[i];

            if (board[box] == '0' + box) {
                return box;
            }
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

int getNumber(void) {
    char line[100];

    while (1) {
        char *start;
        char *end;
        long number;

        printf("Tum (X), khaali box ka number chuno (1-9): ");

        if (fgets(line, sizeof(line), stdin) == NULL) {
            return -1;
        }

        start = line;

        while (isspace((unsigned char)*start)) {
            start++;
        }

        errno = 0;
        number = strtol(start, &end, 10);

        /* Input number nahi hai, jaise a ya # */
        if (start == end || errno == ERANGE) {
            printf("Are pagal, sirf number ka hi use karna hai!\n");
            continue;
        }

        while (isspace((unsigned char)*end)) {
            end++;
        }

        /* Number ke saath extra character ho, jaise 5a */
        if (*end != '\0') {
            printf("Are pagal, sirf number ka hi use karna hai!\n");
            continue;
        }

        if (number == 0) {
            return 0;
        }

        /* 10, 25, 55 jaise numbers */
        if (number < 1 || number > 9) {
            printf("Sirf 1 se 9 ke number use karo.\n");
            continue;
        }

        return (int)number;
    }
}

int getLevel(void) {
    char line[100];

    while (1) {
        char *start;
        char *end;
        long level;

        printf("\nLevel chuno:\n");
        printf("1. Easy\n");
        printf("2. Hard\n");
        printf("Apna level likho (1 ya 2): ");

        if (fgets(line, sizeof(line), stdin) == NULL) {
            return 1;
        }

        start = line;

        while (isspace((unsigned char)*start)) {
            start++;
        }

        errno = 0;
        level = strtol(start, &end, 10);

        if (start == end || errno == ERANGE) {
            printf("Kripya 1 (Easy) ya 2 (Hard) chuno.\n");
            continue;
        }

        while (isspace((unsigned char)*end)) {
            end++;
        }

        if (*end != '\0' || (level != 1 && level != 2)) {
            printf("Kripya 1 (Easy) ya 2 (Hard) chuno.\n");
            continue;
        }

        if (level == 1) {
            printf("Easy level chuna. Computer random chaal chalega.\n");
        } else {
            printf("Hard level chuna. Computer jeetne aur tumhe rokne ki koshish karega.\n");
        }

        return (int)level;
    }
}

char getPlayAgain(void) {
    char line[100];

    while (1) {
        printf("\nKya fir se khelna hai? (y/n): ");

        if (fgets(line, sizeof(line), stdin) == NULL) {
            return 'n';
        }

        char answer = (char)tolower((unsigned char)line[0]);

        if (answer == 'y' || answer == 'n') {
            return answer;
        }

        printf("Sirf y (haan) ya n (nahi) likho.\n");
    }
}