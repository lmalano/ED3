/*
===============================================================================
 Name        : Trabajo2_TIMER.c
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

// Declaramos puntero INTERRUPCIONES ISER0
unsigned int volatile *const ISER0 = (unsigned int*)0xE000E100;

// Declaramos puntero para encender perifericos PCONP
unsigned int volatile *const PCONP =(unsigned int*)0x400FC0C4;

//Declaramos punteros para manejar el Timer0
unsigned int volatile *const T0IR = (unsigned int*)0x40004000; // bit de interrupcion (flag)
unsigned int volatile *const T0TCR = (unsigned int*)0x40004004; //registro del TCR, sirve para controlar las funciones del timer counter
unsigned int volatile *const T0PR = (unsigned int*)0x4000400C; //Preescaler register, cuando el preescaler counter alcanza el valor almacenado aca, se incrementa el TC (TimerCounter)
unsigned int volatile *const T0MCR = (unsigned int*)0x40004014; //Match control register
unsigned int volatile *const T0MR0 = (unsigned int*)0x40004018; //Match Register 0
unsigned int volatile *const T0MR1 = (unsigned int*)0x4000401C; //Match Register 1
unsigned int volatile *const PCLKSEL0 = (unsigned int*)0x400FC1A8; //PCLKSEL0 elije el periferico al que le asigna el clock



int main(void) {

    //Configuro las salidas del RGB
	*FIO3DIR|=(1<<26); //LED Azul como salida
	*FIO3DIR|=(1<<25); //LED Verde como salida

	//Habilito las interrupciones para el timer0
	*ISER0|=(1<<1); // Habilito las interrupciones por timer0

	//Enciendo el periferico TMR0
	*PCONP|=(1<<1); //Enciendo el timer0

	*PCLKSEL0|=(1<<2); // Habilito el clock para el timer0
	*PCLKSEL0|=(1<<3);

	//Configuracion del Timer0
	*T0PR = 0; //Al poner el Preescaler igual a 0, el timer counter se incrementara con cada pulso de clock
	*T0MR0 = 25000000; // Cargo un valor al MR0
	*T0MR1 = 50000000; // Cargo un valor al MR1

	//Configuracion del MCR
	*T0MCR|=(1<<0); // Se genera una interrupcion cuando el MR0 se matchea con el TC (timer counter)
	*T0MCR|=(1<<3); // Se genera una interrupcion cuando el MR1 se matchea con el TC (timer counter)
	*T0MCR|=(1<<4); // Se reinicia el TC cuando el MR1 se matchea con el.

    // INICIO EL TIMER COUNTER DEL TIMER 0
	*T0TCR|=(1<<0);
    volatile static int i = 0 ;
    // Enter an infinite loop, just incrementing a counter

    return 0 ;
}
void TIMER0_IRQHandler (void)
{
	if (*T0IR&= 1)
	{   *FIO3SET=(1<<26); // Apago el LED Azul del RGB
		*FIO3CLR=(1<<25); //Prendo el LED Verde del RGB
			}
	else if (*T0IR&=(1<<1))
	{   *FIO3SET=(1<<25); // Apago el LED VERDE del RGB
		*FIO3CLR=(1<<26); //Prendo el LED AZUL del RGB
	}
}
