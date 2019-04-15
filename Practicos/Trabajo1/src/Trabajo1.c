/*
===============================================================================
 Name        : Trabajo1.c
 Author      : $(author)
 Version     :
 Copyright   : $(copyright)
 Description : main definition
===============================================================================
*/

#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif

#include <cr_section_macros.h>

//Declaramos Punteros PUERTO 0
unsigned int volatile *const FIO0DIR = (unsigned int*)0x2009C000;
unsigned int volatile *const FIO0SET = (unsigned int*)0x2009C018;
unsigned int volatile *const FIO0CLR = (unsigned int*)0x2009c01c;
unsigned int volatile *const FIO0PIN = (unsigned int*)0x2009c014;
// Declaramos Punteros PUERTO 2
unsigned int volatile *const FIO2DIR = (unsigned int*)0x2009C040;
unsigned int volatile *const FIO2SET = (unsigned int*)0x2009C058;
unsigned int volatile *const FIO2PIN = (unsigned int*)0x2009c054;

//Declaramos Punteros PUERTO 3
unsigned int volatile *const FIO3DIR = (unsigned int*)0x2009C060;
unsigned int volatile *const FIO3CLR = (unsigned int*)0x2009c07c;
unsigned int volatile *const FIO3SET = (unsigned int*)0x2009C078;
int main(void) {
	volatile static int i = 0 ;
    //Definimos las salidas
//*FIO0DIR|=(1<<22); //LED Rojo como salida
*FIO3DIR|=(1<<26); //LED Verde como salida
	//Definimos las entradas
*FIO2DIR|=(0<<10);  //SW2 como Entrada

    while(1) {
       if (*FIO2PIN&(1<<10))
    	   *FIO3CLR=(1<<26);
       else
    	   *FIO3SET = (1<<26);

    }
    return 0 ;
}
