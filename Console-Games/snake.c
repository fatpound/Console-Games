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
/*   Updated: 04/12/2022 13:49:51 by fatpound with unsignedbuntu               */
/*                                                                             */
/*******************************************************************************/

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#define SWAP(x, y) (x == y ? 0 : (x ^= y ^= x ^= y))

#define UP    'w'
#define DOWN  's'
#define RIGHT 'd'
#define LEFT  'a'

#define WIN   'n'
#define END   0x1b // ESC (Terminate)

#define MAX_SIZE 15

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

int i, j, temp[2];

int tail[2], head[2];
int table_limits[2];
int snake[MAX_SIZE][MAX_SIZE]; // Game Board

int score = 0, hitapple = 0, gameover = 0;
char k = LEFT, lastmove = LEFT;

void IncreaseNumbers()
{
	for (i = 0; i < table_limits[0]; i++)
	{
		for (j = 0; j < table_limits[1]; j++)
		{
			if (snake[i][j] > 1)
			{
				snake[i][j]++;
			}
		}
	}
}

void LowerTheCase()
{
	if (k == UP - 32 || k == DOWN - 32 || k == LEFT - 32 || k == RIGHT - 32)
	{
		k += 32;
	}
}

void HeadLocation()
{
	for (i = 0; i < table_limits[0]; i++)
	{
		for (j = 0; j < table_limits[1]; j++)
		{
			if (snake[i][j] == 1)
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

	for (i = 0; i < table_limits[0]; i++)
	{
		for (j = 0; j < table_limits[1]; j++)
		{
			if (snake[i][j] > greatest)
			{
				greatest = snake[tail[0] = i][tail[1] = j];
			}
		}
	}
}

void PlaceApple()
{
	while (snake[temp[0]][temp[1]] > 0)
	{
		temp[0] = rand() % table_limits[0];
		temp[1] = rand() % table_limits[1];
	}

	snake[temp[0]][temp[1]] = -1;
}

void SwapHead()
{
	if (k == UP)    SWAP(snake[head[0]][head[1]], snake[(head[0] == 0 ? table_limits[0] : head[0]) - 1][head[1]]);
	if (k == DOWN)  SWAP(snake[head[0]][head[1]], snake[head[0] == table_limits[0] - 1 ? 0 : (head[0] + 1)][head[1]]);
	if (k == LEFT)  SWAP(snake[head[0]][head[1]], snake[head[0]][(head[1] == 0 ? table_limits[1] : head[1]) - 1]);
	if (k == RIGHT) SWAP(snake[head[0]][head[1]], snake[head[0]][head[1] == table_limits[1] - 1 ? 0 : (head[1] + 1)]);
}

void MoveBoard()
{
	if ((k == UP && snake[head[0] - 1][head[1]] == -1) || (k == DOWN && snake[head[0] + 1][head[1]] == -1) || (k == LEFT && snake[head[0]][head[1] - 1] == -1) || (k == RIGHT && snake[head[0]][head[1] + 1] == -1))
	{
		hitapple = 1;
	}

	if (hitapple)
	{
		score++;

		snake[temp[0]][temp[1]] = 1;
		snake[head[0]][head[1]] = 0;

		IncreaseNumbers();

		snake[head[0]][head[1]] = 2;

		if (score != (table_limits[0] * table_limits[1] - 2))
		{
			PlaceApple();
		}
		else
		{
			k = WIN;
		}

		hitapple = !hitapple;
	}
	else
	{
		SwapHead();
		TailLocation();
		IncreaseNumbers();

		snake[head[0]][head[1]] = 2;
		snake[tail[0]][tail[1]] = 0;
	}
}

void BoardLogic()
{
	HeadLocation();

	if ((k == UP && (head[0] > 0) && snake[head[0] - 1][head[1]] > 1) || (k == DOWN && (head[0] < table_limits[0] - 1) && snake[head[0] + 1][head[1]] > 1) || (k == LEFT && (head[1] > 0) && snake[head[0]][head[1] - 1] > 1) || (k == RIGHT && (head[1] < table_limits[1] - 1) && snake[head[0]][head[1] + 1] > 1))
	{
		gameover = 1;
	}

	if (!gameover)
	{
		MoveBoard();
	}
}

void DrawBoard(HANDLE h, WORD wOldColorAttrs)
{
	if (!gameover && k != END)
	{
		for (system("CLS"), i = 0; i < table_limits[0] + 2; i++)
		{
			for (j = 0; j < table_limits[1] + 2; j++)
			{
				SetConsoleTextAttribute(h, (snake[i - 1][j - 1] == 1) ? 1 : ((snake[i - 1][j - 1]) ? (((snake[i - 1][j - 1]) == -1) ? 11 : wOldColorAttrs) : 1));

				printf("%c%s", (i == 0 || j == 0 || i == table_limits[0] + 1 || j == table_limits[1] + 1) ? (SET_COLOR(4), '#') : (snake[i - 1][j - 1] == 1 ? 'X' : (snake[i - 1][j - 1] ? (snake[i - 1][j - 1] == -1 ? 42 : 'O') : 32)), j == table_limits[1] + 1 ? "\n" : "");
			}
		}

		SET_COLOR(GREEN);
		printf("\nSCORE : %d", score);
	}

	SetConsoleTextAttribute(h, wOldColorAttrs);
}

int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		printf("You need to start the game with parameter(s)!\n\nCopright %c fatpound (2022)", 184);

		_getch();
		exit(EXIT_FAILURE);
	}

	if (argc > 3)
	{
		printf("Too many parameters!\n\nCopright %c fatpound (2022)", 184);

		_getch();
		exit(EXIT_FAILURE);
	}

	if (!atoi(argv[1]) || (argc == 3 && !atoi(argv[2])))
	{
		printf("Syntax error on %s parameter%s!\n\nCopright %c fatpound (2022)", !atoi(argv[1]) && (argc == 3 && !atoi(argv[2])) ? "both" : (!atoi(argv[1]) ? "1st" : "2nd"), !atoi(argv[1]) && (argc == 3 && !atoi(argv[2])) ? "s" : "", 184);

		_getch();
		exit(EXIT_FAILURE);
	}

	if ((atoi(argv[1]) * (argc == 2 ? atoi(argv[1]) : atoi(argv[2]))) < 3)
	{
		printf("So tiny board!\n\nCopright %c fatpound (2022)", 184);

		_getch();
		exit(EXIT_FAILURE);
	}

	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
	GetConsoleScreenBufferInfo(h, &csbiInfo);
	WORD wOldColorAttrs = csbiInfo.wAttributes;

	// Setting board limits
	table_limits[0] = atoi(argv[1]) > MAX_SIZE ? MAX_SIZE : atoi(argv[1]);
	table_limits[1] = atoi(argv[argc == 2 ? 1 : 2]) > MAX_SIZE ? MAX_SIZE : atoi(argv[argc == 2 ? 1 : 2]);

	// Board preparation
	for (i = 0; i < table_limits[0]; i++)
	{
		for (j = 0; j < table_limits[1]; j++)
		{
			snake[i][j] = 0;
		}
	}

	// Placing snake's head  'X'
	snake[table_limits[1] == 1][table_limits[1] - 1 - (table_limits[1] != 1)] = 1;

	// Placing snake's first 'O'
	snake[0][table_limits[1] - 1] = 2;

	unsigned int tim = time(NULL);

	srand(tim);

	temp[0] = rand() % table_limits[0];
	temp[1] = rand() % table_limits[1];

	PlaceApple();
	DrawBoard(h, wOldColorAttrs);

	// Game Loop
	while (!gameover && k != WIN)
	{
		k = _getch();
		LowerTheCase();

		while ((k == LEFT && lastmove == RIGHT) || (k == RIGHT && lastmove == LEFT) || (k == UP && lastmove == DOWN) || (k == DOWN && lastmove == UP))
		{
			k = _getch();
			LowerTheCase();
		}

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

	printf("\n\nGame %s!\n\nCopyright %c fatpound (2022)", k == END ? "Terminated" : (k == WIN ? "Ended" : "Over"), 184);
	// printf("\nSeed : %u", tim);

	return !_getch();
}