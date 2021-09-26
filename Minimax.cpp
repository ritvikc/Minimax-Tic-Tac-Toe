#include "stdarg.h"
#include "string.h"
#include "stdlib.h"
#include <stdio.h>
#include <cstdarg>
#include <cstring>
#include <stdarg.h>

enum eplayer { human, comp, tie, notDone };
int scores[] = { -10, 10, 0, -1 };
eplayer player = human;
char splayer[] = { 'X', 'O' };
char box[11] = { " 123456789" };
bool game_over = false;

//returns result of the game
int result(eplayer a)
{
	//rows
	int x = -16;

	if (box[1] == box[2] && box[2] == box[3])
	{
		x = scores[(box[1] == splayer[comp])];
	}
	if (box[4] == box[5] && box[5] == box[6])
	{
		x = scores[(box[4] == splayer[comp])];
	}

	if (box[7] == box[8] && box[8] == box[9])
	{
		x = scores[(box[7] == splayer[comp])];
	}
	//columns
	if (box[1] == box[4] && box[4] == box[7])
	{
		x = scores[(box[1] == splayer[comp])];
	}
	if (box[2] == box[5] && box[5] == box[8])
	{
		x = scores[(box[2] == splayer[comp])];
	}
	if (box[3] == box[6] && box[6] == box[9])
	{
		x = scores[(box[3] == splayer[comp])];
	}
	//diags
	if (box[1] == box[5] && box[5] == box[9])
	{
		x = scores[(box[1] == splayer[comp])];
	}
	if (box[3] == box[5] && box[5] == box[7])
	{
		x = scores[(box[3] == splayer[comp])];
	}
	if (x != -16)
	{
		if (a == 1)
		{
			return x;
		}
		else
		{
			return -x;
		}
	}

	bool tie_game = true;
	for (int i = 1; i <= 9; i++)
	{
		if (box[i] != splayer[comp] && box[i] != splayer[human])
		{
			tie_game = false;
		}
	}
	if (tie_game)
	{
		return scores[2];
	}
	else {
		return scores[3];
	}
}
// this method displays the board to the user.
void board()
{

	for (int i = 1; i < strlen(box); i++)
	{
		if (i % 3 != 0)
		{
			printf("|%c", box[i]);
		}
		else
		{
			printf("|%c|\n", box[i]);
		}
	}
	printf("\n\n");
}

//simulates user and computer moves
int* simulation(eplayer a)
{
	int x;
	int highest_score = -11;
	int best_move;
	int finalanswer[2] = { 0,0 };
	int *pointer = finalanswer;

	for (int i = 1; i < strlen(box); i++)
	{

		if (box[i] >= '0' && box[i] <= '9') //if empty
		{
			box[i] = splayer[a]; //place down

			if (result(a) == -1) //if game not over
			{
				pointer = simulation((eplayer)!a); //continue game, return result
				x = *pointer; //obtain score (first item of array)
				if (x == 10 || x == 0)
				{
					if (-x > highest_score) 
					{
						best_move = i;
						highest_score = -x;
					}

					box[i] = i + '0'; //remove piece
				}
				else if (x == -10)
				{
					box[i] = i + '0'; //remove piece
					best_move = i;
					finalanswer[0] = -x;
					finalanswer[1] = best_move;
					pointer = finalanswer;
					return pointer; 
				}
			}
			else
			{
				int answer = result(a); //if game is over, return the final stuff
				best_move = i;
				box[i] = i + '0';
				finalanswer[0] = answer;
				finalanswer[1] = best_move;
				pointer = finalanswer;
				return pointer;
			}
		}
	}
	finalanswer[0] = highest_score; //after checking all locations, choose best location
	finalanswer[1] = best_move;
	pointer = finalanswer;
	return pointer;
}
void comp_turn()
{
	int* x;
	x = simulation(comp);
	box[*(x + 1)] = splayer[1];
	printf("Computer move:\n");
	board();
}
void user_turn()
{

	printf("\n Where would you like to go?\n");

	char ch;
	int location;

	while (true)
	{
		ch = getchar();
		if (ch >= '0' && ch <= '9')
		{
			location = ch - '0';
			break;
		}
	}
	if (box[location] == 'X' || box[location] == 'O')
	{
		printf("Unavaible. Pick a different location. \n");
		user_turn();
	}
	box[location] = splayer[player];
	printf("\nYour move:\n");
	board();
}
int main()
{
	printf("\nLet's play Tic-Tac-Toe!\n");
	board();
	while (!game_over)
	{
		(player == human ? user_turn() : comp_turn());
		player = (eplayer)!player;
		if (result(human) != -1)
		{
			game_over = true;
		}
	}
	int a = result(human);

	if (a == -10)
	{
		printf("\nYou lost!");
	}
	else
	{
		printf("Tie!\n");
	}
	scanf("%d", &a);
}
