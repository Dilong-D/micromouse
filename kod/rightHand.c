/*
 * rightHand.c
 *
 * Created: 27.07.2017 17:55:22
 *  Author: dmark
 */ 

 #include "algorithms.h"
 #include <avr/io.h>
 #include <avr/interrupt.h>
 #include <util/delay.h>
 #include <avr/pgmspace.h>
 #include <stddef.h>
 #include "hd44780.h"
 #include "libs.h"
 #include "gyro.h"
 #include "pomiar.h"
 #include "pid.h"
 #include "pos_dir_enc.h"
 #include "NewControl.h"
 #include "rightHand.h"
 #define  F_CPU 32000000UL

void rightHandStart(){
	flaga_czuj=0;
	moves_flags = 0;
	_delay_ms(500);
	forward(40);
	_delay_ms(1000);
	float pos_id=0;
	while(1)
	{
		
		if(pomiarl<50){
			PORTF_OUTCLR=PIN5_bm;
			PORTF_OUTSET=PIN6_bm;
			forward(180);
			rotateAngle(pos_id-par.dir+PI/2);
			pos_id=pos_id+PI/2;
			if(pos_id>PI)
			pos_id=pos_id-2*PI;

		}
		else
		{
			if(pomiarfl+pomiarfr<1000){
				PORTF_OUTCLR=PIN6_bm;
				PORTF_OUTSET=PIN5_bm;
				forward(180);
			}
			else{
				PORTF_OUTCLR=PIN6_bm;
				PORTF_OUTCLR=PIN5_bm;
				rotateAngle(pos_id-par.dir-PI/2);
				pos_id=pos_id-PI/2;
				if(pos_id<-PI)
				pos_id=pos_id+2*PI;
				
			}
		}
		_delay_ms(1);
		
	}
	
	
	
}