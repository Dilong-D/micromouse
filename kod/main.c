/*
 * micromouse.c
 *
 * Created: 2016.10.15 02:30
 * Author : Dominik Markowski, Mateusz Wasala, Jan Zyczkowski, Piotr Papiez, Artur Hadasz
 */ 

#define  F_CPU    32000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <avr/pgmspace.h>
#include <stddef.h>
#include "hd44780.h"
#include "libs.h"
#include "gyro.h"
#include "pid.h"
#include "pos_dir_enc.h"
#include "algorithms.h"
#include "pomiar.h"
#include "real_alg.h"
#include "NewControl.h"
#include "bluetooth.h"
#include "rightHand.h"

/*
Opis portów
port	funkcja		
D0	-	PWM	MOTOR R
D1	-	INPUT MOTOR 2 R
D2	-	INPUT MOTOR 1 R
D3	-	PWM	MOTOR L
D4	-	INPUT 2 MOTOR L
D5	-	INPUT 1	MOTOR L
C0	-	enkoder MOTOR L
C1	-	enkoder	MOTOR L
F0	-	enkoder MOTOR R
F1	-	enkoder	MOTOR R
E4,E5,E6,E7	-	dioda IR
B0-B4	-	fototranzystory
C3-C7-	lcd
*/

float regV_P =6;
float regV_I =2;//4.5;
float regV_D =0.48;//1.1;
//int16_t aktualna_V_8=0;
//int16_t target_S=0;

float regT_P = 6;
float regT_I = 2;
float regT_D = 0.48;
//int16_t aktualna_T_8=0;
int indTcc1=0;
int pred_ch[4];
int roznica_ch[4];
int roznica=0;
int pred=0;
int k=2000;
int pomiar=0;
int wyslij=0;
int tabsend[1000];
int pomiary[4][5];
// Interrupt Service Routine for handling the ADC conversion complete interrupt
ISR(ADCB_CH0_vect) {
	adc_result_LD = ADCB.CH0RES;
}
ISR(ADCB_CH1_vect) {
	adc_result_LF = ADCB.CH1RES;
}
ISR(ADCB_CH2_vect) {
	adc_result_RF = ADCB.CH2RES;
}
ISR(ADCB_CH3_vect) {
	adc_result_RD = ADCB.CH3RES;
}
//Przerwanie przycisk dol
ISR(PORTF_INT0_vect){
		
}
//Przerwanie przycisk gora
ISR(PORTF_INT1_vect){	
	_delay_ms(500);
	rotateAngle(PI/2);
}

ISR(ACA_AC0_vect){
	PORTF_OUTTGL=PIN7_bm;

}

int16_t roznica_czujnikow;
int refR=0;
int refL=0;
ISR(TCD1_OVF_vect){
	pomiarr=adcPomiar_RD();
	pomiarl=adcPomiar_LD();
	pomiarfr=adcPomiar_RF();
	pomiarfl=adcPomiar_LF();
	
	
	int i,j;
	for(i=4;i>0;i--)
	   for(j=0;j<4;j++)
	       pomiary[j][i]=pomiary[j][i-1];
	
	pomiary[0][0]  =pomiarr;
	pomiary[1][0]  =pomiarl;
	pomiary[2][0]  =pomiarfr;
	pomiary[3][0]  =pomiarfl;
	
	stan_T = JAZDA;
	
	
	if(((pomiarr)>100)&&((pomiarl)>100))
		{
			roznica_czujnikow=pomiarl-pomiarr;
			refR=pomiarr;
			refL=pomiarl;
		}
	else if ((pomiarr>100)&&(pomiarl<100) && (pomiarfl+pomiarfr<800))
	    {
			roznica_czujnikow=refR-pomiarr;
		}
	
	else if ((pomiarr<100)&&(pomiarl>100) && (pomiarfl+pomiarfr<800))	
		{
			roznica_czujnikow=-refL+pomiarl;
		}
	else 
	{ 
		roznica_czujnikow=0;
	}
	
	
	
	if(flaga_czuj==1)
	{
		if(roznica_czujnikow>0)
		    {
			docelowa_T_8=-10;//roznica_czujnikow/parametrp; minus skreca w lewo
			target_T=lookup(roznica_czujnikow)*(aktualna_V_8/30)*537.6;
		    }
		else if (roznica_czujnikow<0)
		    {
			docelowa_T_8=10;//roznica_czujnikow/parametrp;
			target_T=lookup(roznica_czujnikow)*(aktualna_V_8/30)*537.6;
		    }
			else
			 {
				 docelowa_T_8=0;
				 target_T=0;
			 }
	}
	
}
		
	int enkl_send=0;
	int enkr_send=0;
ISR(TCC1_OVF_vect){
	//odczyt enkoderow
	enkl = L_ENKODER;
	enkr = R_ENKODER;
	L_ENKODER=0;
	R_ENKODER=0;
	enkl = - enkl;
	if(enkl > 30000)
		enkl = enkl -65536;
	if(enkr > 30000)
		enkr =enkr- 65536;
	//predkosc i roznica
	roznica=enkl-enkr;
	pred=enkl+enkr;
	
	go(regV_P,regV_I,regV_D,pred, regT_P, regT_I, regT_D, roznica,enkl,enkr);
	
	
	////pozycja
	par=get_params_enc(enkl,enkr,par);
}

ISR(OSC_OSCF_vect) {									// przerwanie w razie awarii oscylatora
	OSC.XOSCFAIL	|=	OSC_XOSCFDIF_bm;				// kasowanie flagi przerwania
	//LcdClear();
	//Lcd("Awaria!");
	_delay_ms(1000);
}







int main(void) {

	prestartSetUp();
	rightHandStart();
	
}

