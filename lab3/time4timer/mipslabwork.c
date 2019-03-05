/* mipslabwork.c

   This file written 2015 by F Lundevall
   Updated 2017-04-21 by F Lundevall

   This file should be changed by YOU! So you must
   add comment(s) here with your name(s) and date(s):

   This file modified 2017-04-31 by Ture Teknolog 

   For copyright and licensing, see file COPYING */

#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "mipslab.h"  /* Declatations for these labs */

int mytime = 0x5957;
volatile int* portE = (volatile int*) 0xbf886110; //initializing pointer for lights


char textstring[] = "text, more text, and even more text!";
timeoutcount = 0;

/* Interrupt Service Routine */
void user_isr( void )
{
  return;
}

/* Lab-specific initialization goes here */
void labinit( void )
{
  volatile int* trisE = (volatile int*) 0xbf886100;  //initializing pointer to control register for light GPIO pin
  *trisE &= ~0xff;    //setting lights as output
  *portE = 0;       //setting value of lights to 0
  TRISD |= 0xfe0;     //setting port d bit 11-5 as input

  T2CON = 0;	//clear timer 2 configurations
  TMR2 = 0;		//set timer value to 0 before start
  PR2 = 0x7a12; //set timer period to 31250
  T2CONSET = 0x8070; //bit 15 turns timer on, bits 4-6 set prescale to 256. 80mhz/256 = 312500. 31250(timer period)/312500 = 0.1, which means timer times out 10 times a second
  return;
}

/* This function is called repetitively from the main program */
void labwork( void )
{
  int buttons = getbtns();
  int switches = getsw();
    if (buttons == 1 || buttons == 3 || buttons == 5 || buttons == 7 ){
      mytime &= 0xff0f;
      mytime = (switches << 4) | mytime;
      
    }

    if (buttons == 2 || buttons == 3 || buttons == 6 || buttons == 7){
      mytime &= 0xf0ff;
      mytime = (switches << 8) | mytime;
    }
    if (buttons == 4 || buttons == 5 || buttons == 6 || buttons == 7){
      mytime &= 0x0fff;
      mytime = (switches << 12) | mytime;
    }

    int time;
    time = IFS(0) & 0x0100;
    if (time != 0){
    	IFSCLR(0) = 0x0100;
    	timeoutcount++;
    }

    if(timeoutcount == 10){
    timeoutcount = 0;
	time2string( textstring, mytime );
  	display_string( 3, textstring );
  	display_update();
  	tick( &mytime );
  	*portE += 1;
  	display_image(96, icon);
}
}
