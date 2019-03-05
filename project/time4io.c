#include <stdint.h>
#include <pic32mx.h>
#include "mipslab.h" 

int getsw( void ){

	int SW = (PORTD >> 8) & 0x000F;

	return SW;
}

int getbtns(void){

	int BTN = (PORTD >> 5) & 0x0007;

	return BTN;
}
int getselect(void){
	int select = (PORTD >> 7) & 0x01;
	return select;
}

int getincrement(void){
	int increment = (PORTD >> 6) & 0x01;
	return increment;
}