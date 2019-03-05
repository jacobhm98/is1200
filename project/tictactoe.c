#include <stdint.h>
#include <pic32mx.h>
#include "mipslab.h"
#include <stdio.h>
#include <string.h>

//initializing global variables that define the playing board, and specifies which slots we wish to change throughout the game
char line1[] = "____|____|____";
char line2[] = "____|____|____";
char line3[] = "    |    |    ";
char *a1 = &line1[2];
char *a2 = &line2[2];
char *a3 = &line3[2];
char *b1 = &line1[7];
char *b2 = &line2[7];
char *b3 = &line3[7];
char *c1 = &line1[12];
char *c2 = &line2[12];
char *c3 = &line3[12];
int xPos = 1;
int yPos = 1;
int counter = 1;



int game_control(int gamemode){
	int player1 = gamemode;
	int player2 = gamemode;

	while(player1 != 0 && player2 != 0){
		int gameWinner = single_game(player1, player2, gamemode);
		if (gameWinner == 1){
			player1--;
			clear();
			display_string(1, "P1");
			display_update();
			delay(5000);
		}
		if(gameWinner == 2){
			player2--;
			clear();
			display_string(1, "P2");
			display_update();
			delay(5000);
		}
		else if(checkWin() == 3){
			player1--;
			player2--;
			clear();
			display_string(1, "Drawn Game");
			display_update();
			delay(5000);

		}
		resetBoard();
	}
	clear();
	if(player1 == 0 && player2 == 0){
		display_string(0, "Draw");
	}
	else if(player2 == 0){
		display_string(0, "player2 wins");
	}
	else if(player1 == 0){
		display_string(0, "player1 wins");
	}
	display_update();


}


int single_game(int player1, int player2, int gamemode){
	display_string(0, "");
	display_string(1, line1);
	display_string(2, line2);
	display_string(3, line3);
	display_update();
	
	int winner = 0;
	while(winner == 0){
		selectSquare();
		winner = checkWin();

	}
	

	
	if(winner == 1){
		return 1;
	}
	if(winner == 2){
		return 2;
	}
	if(winner == 3){
		return 3;
	}

}

/*
TicTacToe helper functions
*/

void resetBoard(){
	*a1 = '_';
	*a2 = '_';
	*a3 = ' ';
	*b1 = '_';
	*b2 = '_';
	*b3 = ' ';
	*c1 = '_';
	*c2 = '_';
	*c3 = ' ';
	
	display_string(0, "");
	display_string(1, line1);
	display_string(2, line2);
	display_string(3, line3);
	display_update();

}
void clear(){
	display_string(0, "");
	display_string(1, "");
	display_string(2, "");
	display_string(3, "");
	display_update();

}

/*
a method that checks if the board has been won, returns 1 for player1 win,
2 for player2 win, 0 for an unfinished game and 3 for a draw
*/
int checkWin(){
	char mark;
	if (*b2 != '_' && *b2 == *b3 && *b2 == *b1){
		mark = *b2;
	}
	if(*b2 != '_' && *b2 == *a2 && *b2 == *c2){
		mark = *b2;
	}
	if (*b2 != '_' && *b2 == *c3 && *b2 == *a1){
		mark = *b2;
	}
	if (*b2 != '_' && *b2 == *a3 && *b2 == *c1){
		mark = *b2;
	}
	if (*a1 != '_' && *a1 == *a2 && *a1 == *a3){
		mark = *a1;
	}
	if (*a1 != '_' && *a1 == *c1 && *a1 == *b1){
		mark = *a1;
	}
	if (*c3 != '_' && *c3 == *c2 && *c3 == *c1){
		mark = *c3;
	}
	if (*c3 != '_' && *c3 == *c2 && *c3 == *c1){
		mark = *c3;
	}
	if(getMarked(a1) == 1 && getMarked(a2) == 1 && getMarked(a3) == 1 && getMarked(b1) == 1 && getMarked(b2) == 1
	&& getMarked(b3) == 1 && getMarked(c1) && getMarked(c2) == 1 && getMarked(c3) == 1){
		return 3;
	}
	if (mark == 'X'){
		return 1;
	}
	else if (mark == 'O'){
		return 2;
	}
	else {return 0;}
}
// a function that accepts a square and returns 1 if occupied, and 0 if free
int getMarked(char* square){
	int returnValue;
	if (*square == '_' || *square == ' '){
		returnValue = 0;
	}
	else{
		returnValue = 1;
	}
	return returnValue;
}

//a function that allows you to select a square using button 4 and the switches
void selectSquare(){
	int select = 0;
	char nextMark;

	if ((counter % 2) != 0){
		nextMark = 'X';
	}
	else{
		nextMark = 'O';
	}
	while(select == 0){
		select = getselect();
		makeBlink(nextMark);
	}
		char *square = getPos();
		if(*square != 'X' && *square != 'O'){ 
			*square = nextMark;
			counter++;
	}
}

//a function that reads the value of the x and y positions, and translates it into the corresponding square. x and y are controlled by switches.
char* getPos(){
	char *square;
	if (xPos == 1){
			if (yPos == 1){
				square = a1;
			}
			if (yPos == 2){
				square = a2;
			}
			if (yPos == 3){
				square = a3;
			}

		}
		if (xPos == 2){
			if (yPos == 1){
				square = b1;
			}
			if (yPos == 2){
				square = b2;
			}
			if (yPos == 3){
				square = b3;
			}

		}
		if (xPos == 3){
			if (yPos == 1){
				square = c1;
			}
			if (yPos == 2){
				square = c2;
			}
			if (yPos == 3){
				square = c3;
			}

		}

	return square;
}

//a function that displays a blinking version of the next players character until an appropriate square is chosen
void makeBlink(char mark){
	char* square = getPos();
	char oldMark = *square;
	if (oldMark == '_' || ' '){
		*square = mark;
		display_string(1, line1);
		display_string(2, line2);
		display_string(3, line3);
		display_update();
		delay(200);
		*square = oldMark;
		display_string(1, line1);
		display_string(2, line2);
		display_string(3, line3);
		display_update();
		delay(200);
	}
}


	
