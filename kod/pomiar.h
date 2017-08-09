/*
 * pomiar.h
 *
 * Created: 18.10.2016 18:43:11
 *  Author: LPA1
 */ 


#ifndef POMIAR_H_
#define POMIAR_H_

#define INVERS 5

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <stddef.h>
#include "hd44780.h"




 short kali_obrot;
 float des_vl;
 float des_vr;
 short kalibracja;
 short turn2(short direction);
 int16_t mouse_dir_x(short dir);
 int16_t mouse_dir_y(short dir);
 int16_t mierz (void);
 void kalibruj(void);
 void kalibruj_poczatek(void);
 void kalibruj_ruchy(void);
 uint8_t kal_count;
 uint8_t mierz_count;
 uint8_t  pomiartable[4][5];
 uint8_t LDprog=1000;
 uint8_t RDprog=1000;
 uint8_t RFprog=1000;
 uint8_t LFprog=1000;
 
 #endif