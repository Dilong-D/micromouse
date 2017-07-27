/*
 * NewControl.h
 *
 * Created: 2016-12-16 19:15:35
 *  Author: Pawel
 */ 
#ifndef __NEWCONTROL_H_
#define __NEWCONTROL_H_

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <stddef.h>
#include "hd44780.h"
int16_t aktualna_T_8;
int16_t target_S;
int16_t regT_aktE;
int16_t regV_aktE;
int16_t reg_newPWML;
int16_t reg_newPWMP;
int16_t sum;
int16_t sum2;
int16_t aktualna_V_8;
int16_t deb;
int16_t docelowa_V_8;
int16_t target_T;
int flag_T;
int16_t docelowa_T_8;
int stan_T;
int stan;

int16_t pomiarr;
int16_t pomiarl;
int16_t pomiarfr;
int16_t pomiarfl;
int32_t enkl;
int32_t enkr;

//flagi oznaczajace, �e jest aktualnie w stanie ruchu - jedzie naprz�d lub si� obraca.
uint8_t moves_flags;
#define MOVES_FORWARD 0x1;
#define ROTATES 0x2;

int flaga_czuj;



enum stany{JAZDA,KONIEC,HAMOWANIE};

void go(float regV_P,float regV_I,float regV_D, int16_t suma_akt, float regT_P,float regT_I,float regT_D,int16_t roznica_akt, int32_t enkl, int32_t enkr);
void reg(float regV_P,float regV_I,float regV_D, int16_t suma_akt, float regT_P,float regT_I,float regT_D, int16_t roznica_akt);
void profiler( int32_t enkl,int32_t enkr);
void profiler_k();
void right(float angle);
void left(float angle);
void forward(int16_t dist);
void backwardv2(int16_t dist);
int lookup(int roznicaczujnikow);
void rotateAngle(float angle);
void stabilizacja_kata(void);
void prestartSetUp();
#endif