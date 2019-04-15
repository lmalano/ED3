/*
===============================================================================
 Name        : Trabajo3.c
 Authors     : Leandro Malano y Sergio Figueroa
 Version     : 1.00
 Copyright   : $(copyright)
 Description : Interrupcion externa por EINT0 que incrementa un contador de 00 a 99 a mostrar en sendos displays de 7 segmentos
===============================================================================
*/

#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif

#include <cr_section_macros.h>

//Declaramos Punteros PUERTO 0
unsigned int volatile *const FIO0DIR = (unsigned int*)0x2009C000;
unsigned int volatile *const FIO0SET0 = (unsigned int*)0x2009C018; // bit 0 a 7 puerto 0
unsigned int volatile *const FIO0SET1 = (unsigned int*)0x2009C019; // bit 8 a 15 puerto 0
unsigned int volatile *const FIO0CLR = (unsigned int*)0x2009c01c;  // En principio no usado
unsigned int volatile *const FIO0PIN = (unsigned int*)0x2009c014; // no usado en este practico
unsigned int volatile *const FIO0MASK = (unsigned int*)0x2009C010;
// Declaramos Punteros PUERTO 2
unsigned int volatile *const FIO2DIR = (unsigned int*)0x2009C040;
unsigned int volatile *const FIO2SET = (unsigned int*)0x2009C058; //En principio no usado
unsigned int volatile *const FIO2PIN = (unsigned int*)0x2009c054; //En principio no usado

//Declaramos Punteros PUERTO 3
unsigned int volatile *const FIO3DIR = (unsigned int*)0x2009C060; //En principio no usado
unsigned int volatile *const FIO3CLR = (unsigned int*)0x2009c07c; //En principio no usado
unsigned int volatile *const FIO3SET = (unsigned int*)0x2009C078; //En principio no usado

// Declaramos punteros a los registros PINSEL0, PINSEL1 que controlan
// la parte baja y alta del puerto 0, respectivamente
unsigned int volatile *const PINSEL0 = (unsigned int*)0x4002C000;
unsigned int volatile *const PINSEL1 = (unsigned int*)0x4002C004;

// Declaramos punteros al registro PINSEL4, que controla la parte baja
// del puerto 2
unsigned int volatile *const PINSEL4 = (unsigned int*)0x4002C000;

// Declaramos puntero INTERRUPCIONES ISER0
unsigned int volatile *const ISER0 = (unsigned int*)0xE000E100;

// Declaramos puntero para encender perifericos PCONP
unsigned int volatile *const PCONP =(unsigned int*)0x400FC0C4;

// Declaramos puntero a EXTMODE: Para seleccionar la interrupcion por flanco
unsigned int volatile *const EXTMODE = (unsigned int*)0x400FC148;

// Declaramos puntero a EXTPOLAR: Para seleccionar que sea por flanco bajo
unsigned int volatile *const EXTPOLAR = (unsigned int*)0x400FC14C;

// Declaramos puntero a EXTINT: para limpiar la interrupcion
unsigned int volatile *const EXTINT = (unsigned int*)0x400FC140;

// Declaramos un contador0 y un contador1 para cada display
// Contador1 se incrementa una vez por cada 10 veces se incrementa contador0
// Contador0 se incrementa por cada interrupcion EINT0 y se reinicia despues de alcanzar el valor 9 decimal
		int contador0 = 0;
		int contador1 = 0;
// Valor0 y Valor1 son los valores que guardan los resultados de la tabla en la posicion[contadorY]
		int valor0 =0;
        int valor1 =0;
int main(void) {

	// configuramos puerto 0 como salida
	*FIO0DIR=0xFF;

	//Configuramos P2.10 como interrupcion externa
	*PINSEL4 |=(1<<20);

	//Pongo en '1' el bit 0 del registro EXTMODE para que la interrupcion EINT0
	// Sea por flanco
	*EXTMODE|= (1<<0); //El registro EXTPOLAR no hace falta configurar porque por defecto es bajo

	//Bajo bandera antes de empezar
	 *EXTINT|=(1<<0);

	//Habilitamos interrupcion por EINT-0
	*ISER0 |= (1<<18);





	// declaro vector para representar valores,uno en binario y otro en hexadecimal
	uint32_t tablabin[10] = {00111111, 00000011, 01011011, 01001111, 01100110, 01101100, 01111101, 00000111, 01111111, 01100111};
	unsigned char tablahex[10] = {0x0, 0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8, 0x9};


    // Force the counter to be placed into memory
    volatile static int i = 0 ;
    // Enter an infinite loop, just incrementing a counter
    // envio la representacion del numero en el contador mediante la consulta en la tabla


    while (i)
    {
    	 valor0=tablabin[contador0];
    	 valor1=tablabin[contador1];
    	*FIO0SET0 =  valor0;
    	*FIO0SET1 = valor1;
    	i++;
    }

    return 0;
}

void EINT0_IRQHandler(void)
{
	contador0++;
	if (contador0==10)
	{
		contador0=0;//unidad
		contador1++;//decena
	}

	//ANTI-REBOTE nivel bajo
	 while(!(*FIO2PIN&(1<<10)))
	 {
	 }

	 *EXTINT|=(1<<0); //Bajo bandera


}
