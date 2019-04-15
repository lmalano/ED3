/*
===============================================================================
 Name        : Trabajo4_ADC.c
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

// declaramos puntero a fio0pin
unsigned int volatile *const fio0pin = (unsigned int*)0x2009C014;

// declaramos puntero a fio3pin
unsigned int volatile *const fio3pin = (unsigned int*)0x2009C074;


// declaramos puntero a pinmode1
unsigned int volatile *const pinmode1 = (unsigned int*)0x4002C044;

//declaramos puntero a pinsel1
unsigned int volatile *const pinsel1 = (unsigned int*) 0x4002C004;

// declaramos puntero a fio0dir
unsigned int volatile *const fio0dir = (unsigned int*)0x2009C000;

// declaramos puntero a fio3dir
unsigned int volatile *const fio3dir = (unsigned int*)0x2009C060;

// declaramos puntero a pinmode7
unsigned int volatile *const pinmode7 = (unsigned int*) 0x4002C05C;

// Declaramos puntero INTERRUPCIONES ISER0
unsigned int volatile *const iser0 = (unsigned int*)0xE000E100;

// Declaramos puntero para encender perifericos PCONP
unsigned int volatile *const pconp =(unsigned int*)0x400FC0C4;

// Declaramos puntero para ad0inten
unsigned int volatile *const ad0inten =(unsigned int*)0x4003400C;


// Declaramos puntero para ad0cr
unsigned int volatile *const ad0cr =(unsigned int*)0x40034000;

// Declaramos puntero para addr0
unsigned int volatile *const addr0 =(unsigned int*)0x40034010;




int main(void) {

	// Inicio de las configuraciones
	*pinsel1|=(1<<14);
	*pinmode1|=(1<<12);
	*pinmode7|=(1<<19);
	*fio0dir|=(1<<22);
	*fio3dir|=(1<<25);
	*iser0|=(1<<22);
	*pconp|=(1<<12); //alimentacion para el adc
	*ad0inten |= 1; //generar una interrupcion para el canal 0
	*ad0cr |= 0x00210101; // conversion por canal 0, divisor por 2 (queda 12.5 MHz)
	                     //modo burst
	// fin de las configuraciones

	while (1)
	{

	}

	return 0 ;
}

void ADC_IRQHandler(void)
{
	int aux =((*addr0& (0xfff<<4))>>4);
	if (aux <2048)
	{
		*fio0pin|=(1<<22); //apago el led rojo
		*fio3pin&=!(1<<25); //enciendo led verde o &=~
	}
	else
	{
		*fio3pin|=(1<<25); //apago led verde
		*fio0pin&=!(1<<22); //enciendo el led rojo
	}
}
