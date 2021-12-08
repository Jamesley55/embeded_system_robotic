#ifndef PROJET_H
#define PROJET_H
#define __DELAY_BACKWARD_COMPATIBLE__
#define TEST_MODE_ACTIVATE false
#define ETAT_MAX 5
#define DEBOUNCE 30
#define TEMPS_DEMARAGE 2000
#define AFFICHUER_DDR DDRC
#define AFFICHUER_PORT PORTC
#define LED_CATHODE PB0
#define LED_ANODE PB1
#define INTERUPT PD2
#define POUSSOIR PD3
#define PRESCALER_1024 1024
#define N 2
#define PERIODE_PAR_SECONDE 10
#define DEMO_DDR DDRC   
#define DEMO_PORT PORTC 
#define DISTANCE_LIMIT 12
#define SUIVRE_LIGNE_BUFFER 30
#define BUFFER_COUNT 100
#define FROLE_MUR_COUNT 70
#define RECULER_DELAY 1000

#include <avr/io.h>
#include <util/delay.h>
#include <led.h>
#include <sonore.h>
#include <distance.h>
#include <Conducteur.h>
#include <can.h>
#include <minuterie.h>
#include <avr/interrupt.h>
#include <distance.h>
#include <lcm_so1602dtr_m_fw.h>
#include <stdlib.h>
#include <lcm_so1602dtr_m_fw.h>
#include <customprocs.h>
#include "musique.cpp"
#include "segementBD.cpp"
#include "segementCBGHF.cpp"
#include "segementFED.cpp"
#include "segementFinal.cpp"
#include "test.cpp"
#endif