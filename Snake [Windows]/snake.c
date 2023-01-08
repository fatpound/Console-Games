/*******************************************************************************/
/*                                                                             */
/*              :::::::                                                        */
/*            :+:    :+:                                                       */
/*           +:+                                                               */
/*          +#+                                                                */
/*         +#+                                                                 */
/*        #+#     #+#                                                          */
/*   snake.########                                                            */
/*                                                                             */
/*                                                                             */
/*   By: fatpound                                                              */
/*                                                                             */
/*   Created: 19/02/2022 00:17:19 by fatpound                                  */
/*   Updated: 08/01/2023 13:57:46 by fatpound                                  */
/*                                                                             */
/*******************************************************************************/

#pragma warning(disable:6031)
#pragma warning(disable:6385)
#pragma warning(disable:6386)

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <windows.h>

#define SWAP(x, y) (x == y ? 0 : (x ^= y ^= x ^= y))

#define UP    'w'
#define DOWN  's'
#define RIGHT 'd'
#define LEFT  'a'

#define WIN   'n'
#define END   0x1b // ESC (Terminate)

#define MAX_SIZE   15

#define RED        4
#define BLUE       1
#define YELLOW     6
#define GREEN      2
#define GRAY       8
#define CYAN       11
#define PURPLE     13
#define WHITE      15
#define L_RED      12
#define L_BLUE     3
#define L_YELLOW   14
#define L_GREEN    10
#define NBLUE      9

#define SET_COLOR(x) (SetConsoleTextAttribute(h, x))

char* credits       = "\nProgrammed by fatpound (2022-2023)\n";
char* error_codes[] =
{
    "You need to start the game with parameter(s)!\n", // 0x0
    "Too many parameters!\n",                          // 0x1
    "Syntax error on 1st parameter!\n",                // 0x2
    "Syntax error on 2nd parameter!\n",                // 0x3
    "Syntax error on both parameters!\n",              // 0x4
    "Board is too small!\n",                           // 0x5
    "Out of memory!\n"                                 // 0x6
};

int head[2];
int tail[2];
int apple[2];

int limits[2];

int** board = NULL;

int score = 0;
int hitapple = 0;
int gameover = 0;

char k = RIGHT;
char lastmove = RIGHT;

void IncreaseNumbers()
{
    for (int i = 0; i < limits[0]; i++)
    {
        for (int j = 0; j < limits[1]; j++)
        {
            if (board[i][j] > 1)
            {
                board[i][j]++;
            }
        }
    }
}

void HeadLocation()
{
    for (int i = 0; i < limits[0]; i++)
    {
        for (int j = 0; j < limits[1]; j++)
        {
            if (board[i][j] == 1)
            {
                head[0] = i;
                head[1] = j;

                return;
            }
        }
    }
}

void TailLocation()
{
    int greatest = 0;

    for (int i = 0; i < limits[0]; i++)
    {
        for (int j = 0; j < limits[1]; j++)
        {
            if (board[i][j] > greatest)
            {
                tail[0] = i;
                tail[1] = j;

                greatest = board[i][j];
            }
        }
    }
}

void PlaceApple()
{
    do
    {
        apple[0] = rand() % limits[0];
        apple[1] = rand() % limits[1];
    }
    while (board[apple[0]][apple[1]] > 0);

    board[apple[0]][apple[1]] = -1;
}

void SwapHead()
{
    switch (k)
    {
        case UP:    {SWAP(board[head[0]][head[1]], board[head[0] == 0 ? limits[0] - 1 : head[0] - 1][head[1]]); break;}
        case DOWN:  {SWAP(board[head[0]][head[1]], board[head[0] == limits[0] - 1 ? 0 : head[0] + 1][head[1]]); break;}
        case LEFT:  {SWAP(board[head[0]][head[1]], board[head[0]][head[1] == 0 ? limits[1] - 1 : head[1] - 1]); break;}
        case RIGHT: {SWAP(board[head[0]][head[1]], board[head[0]][head[1] == limits[1] - 1 ? 0 : head[1] + 1]); break;}
        default: break;
    }
}

void MoveBoard()
{
    if ((k == UP    && board[(head[0] - 1 + limits[0]) % limits[0]][head[1]] == -1) ||
        (k == DOWN  && board[(head[0] + 1)             % limits[0]][head[1]] == -1) ||
        (k == LEFT  && board[head[0]][(head[1] - 1 + limits[1]) % limits[1]] == -1) ||
        (k == RIGHT && board[head[0]][(head[1] + 1)             % limits[1]] == -1))
    {
        hitapple = 1;

        score++;

        board[apple[0]][apple[1]] = 1;
        board[head[0]][head[1]] = 0;

        IncreaseNumbers();

        board[head[0]][head[1]] = 2;

        if (score != (limits[0] * limits[1] - 2))
        {
            PlaceApple();
        }
        else
        {
            k = WIN;
        }

        hitapple = !hitapple;

        return;
    }

    SwapHead();
    TailLocation();
    IncreaseNumbers();

    board[head[0]][head[1]] = 2;
    board[tail[0]][tail[1]] = 0;
}

void BoardLogic()
{
    HeadLocation();

    if ((k == UP    && board[(head[0] - 1 + limits[0]) % limits[0]][head[1]] > 1) ||
        (k == DOWN  && board[(head[0] + 1)             % limits[0]][head[1]] > 1) ||
        (k == LEFT  && board[head[0]][(head[1] - 1 + limits[1]) % limits[1]] > 1) ||
        (k == RIGHT && board[head[0]][(head[1] + 1)             % limits[1]] > 1))
    {
        gameover = TRUE;
        return;
    }

    MoveBoard();
}

void DrawBoard(HANDLE h, WORD wOldColorAttrs)
{
    if (gameover == 1 || k == END)
        return;

    system("CLS");

    for (int i = 0; i < limits[0] + 2; i++)
    {
        for (int j = 0; j < limits[1] + 2; j++)
        {
            if (i == 0 || j == 0 || i == limits[0] + 1 || j == limits[1] + 1)
            {
                printf("#");
            }
            else
            {
                switch (board[i - 1][j - 1])
                {
                    case -1:
                    {
                        printf("*");
                        break;
                    }

                    case 0:
                    {
                        printf(" ");
                        break;
                    }

                    case 1:
                    {
                        printf("X");
                        break;
                    }

                    default:
                    {
                        printf("O");
                        break;
                    }
                }
            }
        }

        printf("\n");
    }

    SET_COLOR(GREEN);
    printf("\nScore : %d", score);
    SET_COLOR(wOldColorAttrs);
}

int main(int argc, char** argv)
{
    if (argc == 1 || argc > 3)
    {
        printf(error_codes[argc == 1 ? 0x0 : 0x1]);
        printf(credits);

        _getch();
        exit(argc == 1 ? 0x0 : 0x1);
    }

    if (argc == 2 && atoi(argv[1]) == FALSE)
    {
        printf(error_codes[0x2]);
        printf(credits);

        _getch();
        exit(0x2);
    }

    if (argc == 3 && atoi(argv[2]) == FALSE)
    {
        printf(error_codes[atoi(argv[1]) == FALSE ? 0x4 : 0x3]);
        printf(credits);

        _getch();
        exit(atoi(argv[1]) == FALSE ? 0x4 : 0x3);
    }

    if (atoi(argv[1]) < 2 || atoi(argv[1 + (argc == 3)]) < 2)
    {
        printf(error_codes[0x5]);
        printf(credits);

        _getch();
        exit(0x5);
    }

    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
    GetConsoleScreenBufferInfo(h, &csbiInfo);
    WORD wOldColorAttrs = csbiInfo.wAttributes;
    
    // Setting board limits
    limits[0] = atoi(argv[1])               > MAX_SIZE ? MAX_SIZE : atoi(argv[1]);
    limits[1] = atoi(argv[1 + (argc == 3)]) > MAX_SIZE ? MAX_SIZE : atoi(argv[1 + (argc == 3)]);

    // Allocating memory for the game board
    board = (int**) malloc(sizeof(int*) * limits[0]);

    if (board == NULL)
    {
        printf(error_codes[0x6]);
        printf(credits);

        _getch();
        exit(0x6);
    }

    for (int i = 0; i < limits[0]; i++)
    {
        board[i] = (int*) malloc(sizeof(int) * limits[1]);

        if (board[i] == NULL)
        {
            printf(error_codes[0x6]);
            printf(credits);

            _getch();
            exit(0x6);
        }
    }

    // Resetting board
    for (int i = 0; i < limits[0]; i++)
    {
        for (int j = 0; j < limits[1]; j++)
        {
            board[i][j] = 0;
        }
    }

    // Placing snake's head 'X'
    board[0][1] = 1;

    // Placing snake's first 'O'
    board[0][0] = 2;

    unsigned int tim = (unsigned int) time(0);
    
    srand(tim);

    PlaceApple();
    DrawBoard(h, wOldColorAttrs);

    // Game loop
    do
    {
        do
        {
            k = tolower((int)_getch());
        }
        while ((k == LEFT && lastmove == RIGHT) || (k == RIGHT && lastmove == LEFT) || (k == UP && lastmove == DOWN) || (k == DOWN && lastmove == UP));

        if (k == END)
        {
            DrawBoard(h, wOldColorAttrs);
            break;
        }

        lastmove = k;

        if (k == UP || k == DOWN || k == LEFT || k == RIGHT)
        {
            BoardLogic();
            DrawBoard(h, wOldColorAttrs);
        }
    }
    while (!gameover && k != WIN);

    printf("\n\nGame %s!%s", k == END ? "Terminated" : (k == WIN ? "Ended" : "Over"), credits);
    // printf("\nSeed : %llu", tim);

    return !_getch();
}