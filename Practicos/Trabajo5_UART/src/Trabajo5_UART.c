/*
===============================================================================
 Name        : Trabajo5_UART.c
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

void Delay(void);
void Enviar (char k);


unsigned int volatile *const PCONP = (unsigned int) 0X400FC0C4;
unsigned int volatile *const LCR = (unsigned int) 0X4009C00C;
unsigned int volatile *const DLL = (unsigned int) 0X4009C000;
unsigned int volatile *const DLM = (unsigned int) 0X4009C004;
unsigned int volatile *const PINSEL0 = (unsigned int) 0X4002C000;
unsigned int volatile *const THR = (unsigned int) 0X4009C000;
unsigned int volatile *const RBR = (unsigned int) 0X4009C000;
unsigned int volatile *const IER = (unsigned int) 0X4009C004;
unsigned int volatile *const ISER = (unsigned int) 0XE000E100;



int main(void) {

    *PCONP |= (1 << 25); //ENCENDEMOS EL PERIFERICO
    *LCR |= (1 << 0); // PARA UNA LONGITUD DEL MENSAJE DE 8 BITS
    *LCR |= (1 << 1); // CONFIGURO LOS BITS 0 Y 1

    *LCR |= (1 << 7); //PARA ACCEDER A DLL Y DLM

    //CONFIGURACION DE TASA DE TRANSMISION A 9600
    *DLL = 162;
    *DLM = 0;


    *LCR &= ~(1 << 7); //YA CONFIGURADO, DESHABILITO EL ACCESO

    *IER |= (1 << 0); //HABILITO INTERR. DE RECEPCION

    *ISER |= (1 << 8);

    *PINSEL0 |= (1 << 1); //HABILITO TX3
    *PINSEL0 |= (1 << 3); //HABILITO RX3

    while(1){
    Delay();

    }
    return 0 ;
}

void Delay(void){
	for (int i=0; i <1000000; i++){}
}
void Enviar (char k){
	*THR=k;
}
void UART3_IRQHandler(void){
	char k;
	k=*RBR;
	Enviar(k);
}
