/********************************************************************
 *
 *                			 Stepper Motor Driver
 *
 ********************************************************************
 *
 * Author               Date        Comment
 ********************************************************************
 * Phillip Pickett     11.4.12		Initial Release
 ********************************************************************/

#include <p18f4550.h>
#include <delays.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <timers.h>
#include "typedefs.h"


#pragma udata
void getAD(char, char *);
unsigned char buffer[8];
unsigned int delay1;
int i;


extern void _startup (void);        // See c018i.c in your C18 compiler dir

#pragma code _RESET_INTERRUPT_VECTOR = 0x000800
void _reset (void) {
	_asm 
	goto _startup 
	_endasm
}



#pragma code
void main(void) {

	TRISDbits.TRISD2 = 0; //pin d2 output, output 1
	TRISDbits.TRISD3 = 0; //pin d3 output, output 2
	TRISCbits.TRISC6 = 0; //pin c6 output, output 3
	TRISCbits.TRISC7 = 0; //pin c7 output, output 4
/*
   	TRISAbits.TRISA0 = 1;         //pin A0 input, 1 pot
   	TRISAbits.TRISA1 = 1;         //pin A1 input, 2 pot
	TRISAbits.TRISA2 = 1;         //pin A2 input, 3 pot
	TRISAbits.TRISA3 = 1;         //pin A3 input, 4 pot


   	ADCON0 = 0x01;                // AD Control Register 1: Enable (turn on ADC)
  	ADCON2 = 0x3C;                // AD Control Register 2: 20 TAD (accuracy), FOSC 4 (freq/4)
  	ADCON2bits.ADFM = 1;          // ADC result right justified
*/
    while(1) { 
/*
       	for (i = 0; i < 4; i++) {
        	getAD(i, buffer+2*i);
       	}

      	delay1 = (buffer[1]*256 + buffer[0])/5;   
*/

		//Coil 1 = C7 & D3
		//Coil 2 = D2 & C6






		/*
		Wave Drive
		************************************************************************************
           |--|--|--|--|--|--|--|--|--|--|--|
		1	---|           |---|               
    	0	   |-----------|   |------------		Coil 1 - Pin A

		1	   |---|           |---|          
		0	---|   |-----------|   |--------		Coil 2 - Pin A

		1	       |---|           |---|   
		0	-------|   |-----------|   |----		Coil 1 - Pin B

 		1	           |---|           |---|
		0	-----------|   |-----------|   |		Coil 2 - Pin B

		***********************************************************************************
		*/

		LATDbits.LATD2 = 1;
		LATDbits.LATD3 = 0;
		LATCbits.LATC6 = 0;
		LATCbits.LATC7 = 0;

		Delay10KTCYx(10);

		LATDbits.LATD2 = 0;
		LATDbits.LATD3 = 1;
		LATCbits.LATC6 = 0;
		LATCbits.LATC7 = 0;

		Delay10KTCYx(10);

		LATDbits.LATD2 = 0;
		LATDbits.LATD3 = 0;
		LATCbits.LATC6 = 1;
		LATCbits.LATC7 = 0;

		Delay10KTCYx(10);

		LATDbits.LATD2 = 0;
		LATDbits.LATD3 = 0;
		LATCbits.LATC6 = 0;
		LATCbits.LATC7 = 1;

		Delay10KTCYx(10);

   		/************************************************************************************/

	
		/*
		Full Step Drive
		************************************************************************************
           |--|--|--|--|--|--|--|--|--|--|--|
		1	-----|     |-----|     |-----|           
    	0	     |-----|     |-----|     |--		Coil 1 - Pin A

		1	  |-----|     |-----|     |-----    
		0	--|     |-----|     |-----|				Coil 2 - Pin A

		1	     |-----|     |-----|     |--
		0	-----|     |-----|     |-----|			Coil 1 - Pin B

 		1	--|     |-----|     |-----|    
		0	  |-----|     |-----|     |-----		Coil 2 - Pin B

		***********************************************************************************
		*/
/*
		LATDbits.LATD2 = 1;
		LATDbits.LATD3 = 0;
		LATCbits.LATC6 = 0;
		LATCbits.LATC7 = 1;

		Delay10KTCYx(10);

		LATDbits.LATD2 = 1;
		LATDbits.LATD3 = 1;
		LATCbits.LATC6 = 0;
		LATCbits.LATC7 = 0;

		Delay10KTCYx(10);

		LATDbits.LATD2 = 0;
		LATDbits.LATD3 = 1;
		LATCbits.LATC6 = 1;
		LATCbits.LATC7 = 0;

		Delay10KTCYx(10);

		LATDbits.LATD2 = 0;
		LATDbits.LATD3 = 0;
		LATCbits.LATC6 = 1;
		LATCbits.LATC7 = 1;

		Delay10KTCYx(10);
*/
   		/************************************************************************************/


		/*
		Half Step Drive - Needs to be tested
		************************************************************************************
           |--|--|--|--|--|--|--|--|--|--|--|--|--|--|--|--|--|--|
		1	--------|              |--------|              |-----
    	0	        |--------------|        |--------------|			Coil 1 - Pin A

		1	     |--------|              |--------|       
		0	-----|        |--------------|        |--------------		Coil 2 - Pin A

		1	           |--------|              |--------|     
		0	-----------|        |--------------|        |--------		Coil 1 - Pin B

 		1	--|              |--------|              |--------|    
		0	  |--------------|        |--------------|        |--		Coil 2 - Pin B

		***********************************************************************************
		*/

/*
		LATDbits.LATD2 = 1;
		LATDbits.LATD3 = 0;
		LATCbits.LATC6 = 0;
		LATCbits.LATC7 = 1;

		Delay10KTCYx(5);

		LATDbits.LATD2 = 1;
		LATDbits.LATD3 = 0;
		LATCbits.LATC6 = 0;
		LATCbits.LATC7 = 0;

		Delay10KTCYx(5);

		LATDbits.LATD2 = 1;
		LATDbits.LATD3 = 1;
		LATCbits.LATC6 = 0;
		LATCbits.LATC7 = 0;

		Delay10KTCYx(5);

		LATDbits.LATD2 = 0;
		LATDbits.LATD3 = 1;
		LATCbits.LATC6 = 0;
		LATCbits.LATC7 = 0;

		Delay10KTCYx(5);

		LATDbits.LATD2 = 0;
		LATDbits.LATD3 = 1;
		LATCbits.LATC6 = 1;
		LATCbits.LATC7 = 0;

		Delay10KTCYx(5);

		LATDbits.LATD2 = 0;
		LATDbits.LATD3 = 0;
		LATCbits.LATC6 = 1;
		LATCbits.LATC7 = 0;

		Delay10KTCYx(5);

		LATDbits.LATD2 = 0;
		LATDbits.LATD3 = 0;
		LATCbits.LATC6 = 1;
		LATCbits.LATC7 = 1;

		Delay10KTCYx(5);

		LATDbits.LATD2 = 0;
		LATDbits.LATD3 = 0;
		LATCbits.LATC6 = 0;
		LATCbits.LATC7 = 1;

		Delay10KTCYx(5);
*/
   		/************************************************************************************/


		/*
		Microstepping
		************************************************************************************
		*/

	}
}	



void getAD(char channel, char * buffer) {
   ADCON0 &= 0b11000011;         
   ADCON0 |= channel << 2;               
   ADCON0bits.GO = 1;   

   while (ADCON0bits.NOT_DONE);        
   buffer[0] = ADRESL;                   
   buffer[1] = ADRESH;
}