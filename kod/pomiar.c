/*
 * pomiar.c
 *
 * Created: 18.10.2016 18:42:49
 *  Author: LPA1
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <avr/pgmspace.h>
#include "pomiar.h"
#include "algorithms.h"
#include "libs.h"
#include "pos_dir_enc.h"
#include "NewControl.h"
 
	
short turn2(short direction){
	
		if(direction == RIGHT){
			switch(mouse_dir_real){
				case UP:
				return RIGHT;
				
				case DOWN:
				return LEFT;
				
				case RIGHT:
				return DOWN;
				
				case LEFT:
				return UP;
			}
		}
		if(direction == LEFT){
			switch(mouse_dir_real){
				case UP:
				return LEFT;
				
				case DOWN:
				return RIGHT;
				
				case RIGHT:
				return UP;
				
				case LEFT:
				return DOWN;
			}
		}
        if(direction == INVERS){
			switch(mouse_dir_real){
				case UP:
				return DOWN;
				
				case DOWN:
				return UP;
				
				case RIGHT:
				return LEFT;
				
				case LEFT:
				return RIGHT;
			}
		}
}

	int16_t mouse_dir_x(short dir) //  zapisuje jaka wartosc trzeba otrzymac by miec wartosc komorki przed
	{
		if(dir == RIGHT)
			return (1);
		if(dir == LEFT)
			return (-1);
		if(dir == UP)
			return (0);
		if(dir == DOWN)
			return (0);
			

	}
	int16_t mouse_dir_y(short dir)
	{
		if(dir == RIGHT)
			return (0);
		if(dir == LEFT)
			return (0);
		if(dir == UP)
			return (1);
		if(dir == DOWN)
			return (-1);
		

	}
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	 
		
		
		
	
	
	
	
		
		
        int16_t mierz ()
		// 1  - dobry pomiar
		// 0  - brak pomiaru
		// -1 - blad

		{
	
		int16_t discaverdcounter=0; // zlicza czy pole juz jest discaverd (przy discaverdcounter==3)
		 int16_t debRF;
		 int16_t debLF;
		 int16_t debRD;
		 int16_t debLD;
		
		
		if (adcPomiar_LD()<LDprog) pomiartable[mierz_count][0]=0 //zapis do tabeli pomiarow
		else pomiartable[mierz_count][0]=1;
		if (adcPomiar_RD()<RDprog) pomiartable[mierz_count][1]=0
		else pomiartable[mierz_count][1]=1;
		if (adcPomiar_LF()<LFprog) pomiartable[mierz_count][2]=0
		else pomiartable[mierz_count][2]=1;
		if (adcPomiar_RF()<RFprog) pomiartable[mierz_count][3]=0
		else pomiartable[mierz_count][3]=1;
		
		//debLD=adcPomiar_LD();//debancer(adcPomiar_LD(),adcPomiar_LD(),adcPomiar_LD());  // pomiar LD
		//debRD=adcPomiar_RD();///debancer(adcPomiar_RD(),adcPomiar_RD(),adcPomiar_RD());  // pomiar RD
		//debRF=adcPomiar_RF();//debancer(adcPomiar_RF(),adcPomiar_RF(),adcPomiar_RF());  // pomiar RF
		//debLF=adcPomiar_LF();//debancer(adcPomiar_LF(),adcPomiar_LF(),adcPomiar_LF());  // pomiar LF
		
	    mierz_count++;
		
		if (mierz_count==5)
		{ 
			//trzeba dopisac sprawdzanie czy jest wiecej 0 czy jedynek. Mozna nie robic tabeli tylko zmienna ktora bedziemy inkrementowali
			
			
			mierz_count=0;
			
			
			if(((debLF!=0)&&(debRF!=0))&&(discovered[labposx_real+mouse_dir_x( mouse_dir_real)][labposy_real+mouse_dir_y( mouse_dir_real)]==0))
			{
			

			//------------------------------------------------------------------------------------------------------------------------------------------RD	
			if(debRD==-1) 
			return (-1);
			else if(debRD==0)
		
				{
				//if(labyrinth[labposx_real+mouse_dir_x( mouse_dir_real)][labposy_real+mouse_dir_y( mouse_dir_real)]&turn(RIGHT)==turn(RIGHT))
				// ;
				// else
					 {	 
						labyrinth[labposx_real+mouse_dir_x( mouse_dir_real)][labposy_real+mouse_dir_y( mouse_dir_real)]&=(~turn2(RIGHT));
					
						discaverdcounter++;
					 }
				}
			
		
		
			else if(debRD==1) 
			 {   //if(labyrinth[labposx_real+mouse_dir_x( mouse_dir_real)][labposy_real+mouse_dir_y( mouse_dir_real)]&turn2(RIGHT)==turn2(RIGHT))
				 //;
				 //else
				 {
				 
			 
					labyrinth[labposx_real+mouse_dir_x( mouse_dir_real)][labposy_real+mouse_dir_y( mouse_dir_real)]|=turn2(RIGHT);    
					discaverdcounter++;
						 
				}			 
			 }
		
		
		
			//------------------------------------------------------------------------------------------------------------------------------------------RF i LF
		
		
		
		
		
				if(((debRF==-1)||(debRF==-1))|| (debRF!=debLF))
				return (-1);
				else if(debRF==0)
				{
					// if(labyrinth[labposx_real][labposy_real]&mouse_dir_real)
					// ;
					// else
				
					labyrinth[labposx_real][labposy_real]&=(~mouse_dir_real);
				
				}
			
				else if(debRF==1)
				{// if(labyrinth[labposx_real+mouse_dir_x( mouse_dir_real)][labposy_real+mouse_dir_x( mouse_dir_real)]&mouse_dir_real)
					// ;
					// else
				
					labyrinth[labposx_real+mouse_dir_x( mouse_dir_real)][labposy_real+mouse_dir_y( mouse_dir_real)]&=(~mouse_dir_real);
					discaverdcounter++;
			
				
				
				}
				else if(debRF==2) 
				{// if(labyrinth[labposx_real+mouse_dir_x( mouse_dir_real)][labposy_real+mouse_dir_x( mouse_dir_real)47]&mouse_dir_real)
					// ;
					// else
			
					labyrinth[labposx_real+mouse_dir_x( mouse_dir_real)][labposy_real+mouse_dir_y( mouse_dir_real)]|=(mouse_dir_real);
					discaverdcounter++;
				
				}
			
			/*
			//------------------------------------------------------------------------------------------------------------------------------------------LF
		
		
		

			if(debLF==-1) ;
			//return (-1)
			else if(debLF==0)
			
						{
							// if(labyrinth[labposx_real][labposy_real]&mouse_dir_real)
							// ;
							// else
			
						labyrinth[labposx_real][labposy_real]&=(~mouse_dir_real);
						discovered[labposx_real][labposy_real]=1;
						discaverdcounter++;
					
						}
			
			else if(debLF==1)
			{// if(labyrinth[labposx_real+mouse_dir_x( mouse_dir_real)][labposy_real+mouse_dir_x( mouse_dir_real)]&mouse_dir_real)
				// ;
				// else
			
				labyrinth[labposx_real+mouse_dir_x( mouse_dir_real)][labposy_real+mouse_dir_y( mouse_dir_real)]&=(~mouse_dir_real);
				discaverdcounter++;
			
			
			} 
			else if(debLF==2) ;
				{// if(labyrinth[labposx_real+mouse_dir_x( mouse_dir_real)][labposy_real+mouse_dir_x( mouse_dir_real)47]&mouse_dir_real)
					// ;
					// else
				
					labyrinth[labposx_real+mouse_dir_x( mouse_dir_real)][labposy_real+mouse_dir_y( mouse_dir_real)]&=(mouse_dir_real);
					discaverdcounter++;
				
				}
	   
	   
	   
		   */
				//------------------------------------------------------------------------------------------------------------------------------------------LD
			if(debLD==-1) 
			return (-1);
			else if(debLD==0)
			{
				// if(labyrinth[labposx_real+mouse_dir_x( mouse_dir_real)][labposy_real+mouse_dir_y( mouse_dir_real)]&turn(LEFT)==turn(LEFT))
				// ;
				// else
				{
					labyrinth[labposx_real+mouse_dir_x( mouse_dir_real)][labposy_real+mouse_dir_y( mouse_dir_real)]&=(~turn2(LEFT));
					discaverdcounter++;
				
				}
			}
		
			else if(debLD==1)
			{  // if(labyrinth[labposx_real+mouse_dir_x( mouse_dir_real)][labposy_real+mouse_dir_y( mouse_dir_real)]&turn2(LEFT)==turn2(LEFT))
				//;
			//	else
				//{
				
				
					labyrinth[labposx_real+mouse_dir_x( mouse_dir_real)][labposy_real+mouse_dir_y( mouse_dir_real)]|=(turn2(LEFT));
				
					discaverdcounter++;
				
			}
			}
			else
		
		
			{   
				/*
		 		LcdDec (discovered[0][1]);
		 		Lcd(" ");
		 		LcdDec (discovered[1][1]);
		 		Lcd("  ");
		 		LcdDec (labyrinth[0][1]);
		 		Lcd(" ");
		 		LcdDec (labyrinth[1][1]);
		 	
		 		Lcd2;
		 		LcdDec (discovered[0][0]);
		 		Lcd(" ");
		 		LcdDec (discovered[1][0]);
		 		Lcd("  ");
		 		LcdDec (labyrinth[0][0]);
		 		Lcd(" ");
		 		LcdDec (labyrinth[1][0]);
		 		_delay_ms(1000);
			 *//*
			 Lcd2;
			 Lcd("pomiar niepotrzebny ");*/
			 return 0;
		 
			}
		
					if (discaverdcounter==3)
							if(discovered[labposx_real+mouse_dir_x( mouse_dir_real)][labposy_real+mouse_dir_y( mouse_dir_real)]==0)
								{labyrinth[labposx_real+mouse_dir_x( mouse_dir_real)][labposy_real+mouse_dir_y( mouse_dir_real)]|= turn2(INVERS) ;
								new_wall_discovered=1;
								discovered[labposx_real+mouse_dir_x( mouse_dir_real)][labposy_real+mouse_dir_y( mouse_dir_real)]=1;
						        return 1;
								}
		  }
	           return 1;
	   
				
return(-1);

	}
	

void kalibruj_ruchy(void)
{
	des_vl=-0.5;
	des_vr=-0.5;
	
	_delay_ms(22220);
	
	des_vl=0;
	des_vr=0;
	
	switch (mouse_dir_real)
	{
		case UP:
		par.posy=labposy_real*180+45;
		forward(par.posy+43);
		
		break;
		
		case DOWN:
		
		par.posy=labposy_real*180+135;
		forward(par.posy-43);
		break;
		
		case RIGHT:
		par.posx =labposx_real*180+45;
		forward(par.posx+43);
		break;
		
		case LEFT:
		par.posx =labposx_real*180+135;
		forward(par.posx-43);
		break;
	}
	
	
	
	if (((labyrinth[labposx_real][labposy_real]&turn2(RIGHT))==0))
	{rotateAngle(-PI/2);
		mouse_dir_real=turn2(LEFT);
		kali_obrot=1;
	}
	
	else
	{rotateAngle(PI/2);
		mouse_dir_real=turn2(RIGHT);
		kali_obrot=2;
	}
	
	
	
	des_vl=-0.5;
	des_vr=-0.5;
	_delay_ms(22220);
	des_vl=0;
	des_vr=0;
	
	switch (mouse_dir_real)
	{
		case UP:
		par.posy=labposy_real*180+45;
		forward(par.posy+43);
		
		break;
		
		case DOWN:
		
		par.posy=labposy_real*180+135;
		forward(par.posy-43);
		break;
		
		case RIGHT:
		par.posx =labposx_real*180+45;
		forward(par.posx+43);
		break;
		
		case LEFT:
		par.posx =labposx_real*180+135;
		forward(par.posx-43);
		break;
	}
	
	kal_count=0;
	
	
	
	switch (mouse_dir_real)
	{
		case UP:
		par.dir=0;
		break;
		
		case DOWN:
		par.dir=PI;
		break;
		
		case RIGHT:
		par.dir=PI/2;
		break;
		
		case LEFT:
		par.dir=3*PI/2;
		break;
	}
	
	
}

void kalibruj_poczatek(void)
{
	short debRF=debancer(adcPomiar_RF(),adcPomiar_RF(),adcPomiar_RF());  // pomiar RF
	_delay_ms(1);
	short	 debLF=debancer(adcPomiar_LF(),adcPomiar_LF(),adcPomiar_LF());  // pomiar LF
	_delay_ms(1);
	
	if(((debRF==-1)||(debRF==-1))|| (debRF!=debLF))
	;//return (-1);
	
	else
	if(debRF==0)
	labyrinth[0][0]&=(~UP);
	
	_delay_ms(1000);
	
	des_vl=-0.5;
	des_vr=-0.5;
	_delay_ms(201);
	des_vl=0;
	des_vr=0;
	
	_delay_ms(201);
	par.posy=43;
	forward(par.posy+30);
	rotateAngle(PI/2);

	debRF=debancer(adcPomiar_RF(),adcPomiar_RF(),adcPomiar_RF());  // pomiar RF
	_delay_ms(1);
	debLF=debancer(adcPomiar_LF(),adcPomiar_LF(),adcPomiar_LF());  // pomiar LF
	_delay_ms(1);

	if(((debRF==-1)||(debRF==-1))|| (debRF!=debLF))
	;//return (-1);
	else if(debRF==0)
	labyrinth[0][0]&=(~RIGHT);


	discovered[0][0]=1;
	des_vl=-0.5;
	des_vr=-0.5;
	
	_delay_ms(201);
	des_vl=0;
	des_vr=0;
	
	_delay_ms(201);
	par.posx =43;
	par.dir=3*PI/2;
	L_ENKODER = 0;
	R_ENKODER = 0;
	forward(par.posx+30);
	
	
	
	kal_count = 0;
	
}


void kalibruj(void)
{
	if ((kal_count > 2) &&   (((labyrinth[labposx_real][labposy_real]&UP)==0)||((labyrinth[labposx_real][labposy_real]&DOWN)==0))  &&   (((labyrinth[labposx_real][labposy_real]&LEFT)==0)||((labyrinth[labposx_real][labposy_real]&RIGHT)==0))  )
	{
		
		if ((labyrinth[labposx_real][labposy_real]&turn2(INVERS))==0)
		{
			kalibruj_ruchy();
			if (kali_obrot==1)
			{
				rotateAngle(PI/2);
				mouse_dir_real=turn2(RIGHT);
			}
			
			
			else
			{
				
				
				rotateAngle(-PI/2);
				mouse_dir_real=turn2(LEFT);
			}
		}
		
		else if ((labyrinth[labposx_real][labposy_real]&turn2(RIGHT))==0)
		{rotateAngle(-PI/2);
			mouse_dir_real=turn2(LEFT);
			kalibruj_ruchy();
			rotateAngle(-PI);
			mouse_dir_real=turn2(INVERS);
		}
		
		else
		{rotateAngle(PI/2);
			mouse_dir_real=turn2(RIGHT);
			kalibruj_ruchy();
			rotateAngle(-PI);
			mouse_dir_real=turn2(INVERS);
		}
		
		
		
		
	}
	
}