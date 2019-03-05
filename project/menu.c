#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "mipslab.h"  

int menu(void){
	char string1[] = "Single Game";
	char string2[] = "BO3";
	char string3[] = "BO5";
	char token1[] = "*Single Game";
	char token2[] = "*BO3";
	char token3[] = "*BO5";
	int token = 1;
	int select = 0;

	while(select == 0){
		delay(300);
		if(getselect() == 1){
			select = token;
		}
		if(getincrement() == 1){
			if (token < 3){
				token++;
			}
			else{
				token = 1;
			}
		}
		if(token == 1){
			display_string(0, "TicTacToe");
			display_string(1, token1);
			display_string(2, string2);
			display_string(3, string3);
			display_update();		
		}
		else if(token == 2){
			display_string(0, "TicTacToe");
			display_string(1, string1);
			display_string(2, token2);
			display_string(3, string3);
			display_update();		

		}

		else {
			display_string(0, "TicTacToe");
			display_string(1, string1);
			display_string(2, string2);
			display_string(3, token3);
			display_update();		

		}


	}
	


return select;
}