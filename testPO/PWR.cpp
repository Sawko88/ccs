/*
 * PWR.cpp
 *
 *  Created on: 20 ����. 2017 �.
 *      Author: shestakov.aa
 */

#include "PWR.h"
#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "utils/uartstdio.h"
#include <string.h>
#include <string>
#include <stdlib.h>
#include "driverlib/pin_map.h"
#include "driverlib/gpio.h"

//namespace std
//{
pwrParam pwrParamTab[]=
{
 {1,GPIO_PORTD_BASE,GPIO_PIN_4,0, GPIO_PORTB_BASE,GPIO_PIN_4,6}

};

Pwr::Pwr(){

}

void Pwr::ParserPwr(char *bufPwr){

    UARTprintf("pwr%d-OK\r\n",bufPwr[3]);
}

//}
