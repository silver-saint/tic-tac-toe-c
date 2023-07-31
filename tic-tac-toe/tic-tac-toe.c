
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define LOWER_CASE_O 111
#define LOWER_CASE_X 120
#define TO_UPPER(X) (X-= 32)
#define ROWS 3
#define COLUMNS 3
#define TRUE 1

typedef struct
{
	int playerRow;
	int playerCol;
	char input;
} player;

typedef struct
{
	int aiRow;
	int aiCol;
	char input;
} ai;

char take_input()
{
	char current, prev;
	int counter = 0;

	while ((current = getchar()) != '\n') {
		prev = current;
		++counter;
	}

	return counter == 1 ? prev : -1;
}

void printBoard(char board[ROWS][COLUMNS])
{
	printf(" %c | %c | %c ", board[0][0], board[0][1], board[0][2]);
	printf("\n---|---|---\n");
	printf(" %c | %c | %c ", board[1][0], board[1][1], board[1][2]);
	printf("\n---|---|---\n");
	printf(" %c | %c | %c ", board[2][0], board[2][1], board[2][2]);
	printf("\n");
}

int main()
{
	char board[ROWS][COLUMNS] = { {' ',' ',' '}, {' ',' ', ' '}, {' ',' ',' '} };
	int takenSlots[ROWS][COLUMNS] = { {0,0,0},{0,0,0}, {0,0,0} };
	int colSize = sizeof(board[0]) / sizeof(board[0][0]);
	int rowSize = sizeof(board) / sizeof(board[0]);
	player player;
	ai ai;
	char isOver = 0;
	printf("Which symbol would you use? X or O\n");
	player.input = take_input();
	while ((player.input != 'X' && player.input != 'O') && (player.input != 'x' && player.input != 'o'))
	{
		printf("Invalid input, please try again.\n");
		player.input = take_input();
	}
	if (player.input == LOWER_CASE_X || player.input == LOWER_CASE_O)
	{
		TO_UPPER(player.input);
	}

	switch (player.input)
	{
	case 'X': ai.input = 'O';
		break;
	case 'O': ai.input = 'X';
		break;
	}
	printf("AI Picks: %c\n", ai.input);
	while (!isOver)
	{
		srand((unsigned int)(time(0)));
		ai.aiCol = rand() % 3;
		ai.aiRow = rand() % 3;
		printf("Please enter the spot where you'd like to place the character\nChoose an Row between 1 and 3.\n");
		player.playerRow = (take_input() - '0') - 1;
		printf("Please enter the spot where you'd like to place the character\nChoose an Col between 1 and 3.\n");
		player.playerCol = (take_input() - '0') - 1;
		while ((player.playerRow < 0) || (player.playerRow > 2) && (player.playerCol < 0) || (player.playerCol > 2)) // array consistency.
		{
			printf("Invalid row and or column please try again.\n");
			printf("Please enter the spot where you'd like to place the character\nChoose an Row between 1 and 3.\n");
			player.playerRow = (take_input() - '0') - 1;
			printf("Please enter the spot where you'd like to place the character\nChoose an Col between 1 and 3.\n");
			player.playerCol = (take_input() - '0') - 1;
		}

		for (size_t rowIdx = 0; rowIdx < rowSize; ++rowIdx)
		{
			for (size_t colIdx = 0; colIdx < colSize; ++colIdx)
			{
				if ((player.playerRow == rowIdx) && (player.playerCol == colIdx) && (takenSlots[player.playerRow][player.playerCol] != TRUE))
				{
					board[player.playerRow][player.playerCol] = player.input;
					takenSlots[player.playerRow][player.playerRow] = TRUE;
				}


			}
		}

		printBoard(board);
	}
}

