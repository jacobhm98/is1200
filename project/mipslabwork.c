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




/* Interrupt Service Routine */
void user_isr( void )
{
  if (((IFS(0) >> 7) & 1) == 1){
   decrementXPos();
    IFSCLR(0) = 0x80;
  }

  if (((IFS(0) >> 11) & 1) == 1){
    incrementXPos();
    IFSCLR(0) = 0x800;
  }
  
  if (((IFS(0) >> 15) & 1) == 1){
    decrementYPos();
    IFSCLR(0) = 0x8000;
  }

  if (((IFS(0) >> 19) & 1) == 1){
    incrementYPos();
    IFSCLR(0) = 0x80000;
  }
}
void incrementXPos(){
  if(xPos < 3){
    xPos++;
  }
  else {
    xPos = 1;
  }
}
void decrementXPos(){
   if(xPos > 1){
    xPos--;
  }
  else {
    xPos = 3;
  }
}

void incrementYPos(){
  if(yPos < 3){
    yPos++;
  }
  else {
    yPos = 1;
  }
}
void decrementYPos(){
  if(yPos > 1){
    yPos--;
  }
  else{
    yPos = 3;

  }
}
  




/* Lab-specific initialization goes here */
void labinit( void )
{
  TRISD |= 0xfe0;     //setting port d bit 11-5 as input
  IECSET(0) = 0x88880;  //enable interrupt for int1 bit 7, int2 bit 11, int3 bit 15, and int4 bit 19
  IPCSET(1) = 0x1C000000;
  IPCSET(2) = 0x1C000000; //set priority of switch 2 to 111
  IPCSET(3) = 0x1C000000;
  IPCSET(4) = 0x1C000000;
  enable_interrupt(); //call labwork.s to enable interrupts globally
  return;
}

/* This function is called repetitively from the main program */
void labwork( void )
{
  
  
}

