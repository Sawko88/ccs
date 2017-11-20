/*
 * Input.cpp
 *
 *  Created on: 20 ���. 2017 �.
 *      Author: shestakov.aa
 */

#include "Input.h"
#include <stdint.h>
#include <stdbool.h>
#include "driverlib/pin_map.h"
#include "driverlib/gpio.h"
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "utils/uartstdio.h"
#include <string.h>
#include "driverlib/adc.h"

//namespace std
//{


#define TIMERADC 10

InputState InputStateTab[] = {
   {1, GPIO_PORTH_BASE, GPIO_PIN_1, 0,0,0}, //input1
   {2, GPIO_PORTH_BASE, GPIO_PIN_2, 0,0,0}, // input 2
   {3, GPIO_PORTH_BASE, GPIO_PIN_3, 0,0,0}, // input3
   {4, GPIO_PORTH_BASE, GPIO_PIN_0, 0,0,0},
   {5, GPIO_PORTK_BASE, GPIO_PIN_2, 0,0,0},
   {6, GPIO_PORTK_BASE, GPIO_PIN_3, 0,0,0},
   {7, GPIO_PORTK_BASE, GPIO_PIN_4, 0,0,0},
   {8, GPIO_PORTK_BASE, GPIO_PIN_5, 0,0,0},
   {9, GPIO_PORTK_BASE, GPIO_PIN_6, 0,0,0},
   {10, GPIO_PORTK_BASE, GPIO_PIN_7, 0,0,0},
   {11, GPIO_PORTA_BASE, GPIO_PIN_2, 0,0,0},
   {12, GPIO_PORTA_BASE, GPIO_PIN_3, 0,0,0},
   {13, GPIO_PORTA_BASE, GPIO_PIN_4, 0,0,0},
   {14, GPIO_PORTA_BASE, GPIO_PIN_5, 0,0,0},
   {15, GPIO_PORTB_BASE, GPIO_PIN_2, 0,0,0},
   {16, GPIO_PORTB_BASE, GPIO_PIN_3, 0,0,0},
   {17, GPIO_PORTD_BASE, GPIO_PIN_0, 0,0,0},
   {18, GPIO_PORTD_BASE, GPIO_PIN_6, 0,0,0}
};

AdcState AdcStateTab[]={
   {'1', false, 6, 0},//�������� �������
   {'2', false, 1, 0},
   {'3', false, 1, 0},
   {'4', false, 1, 0},
   {'5', false, 1, 0},
   {'6', false, 1, 0}
};



uint32_t inputStateNew =0;

Input::Input()
{
    // TODO Auto-generated constructor stub
    ready = false;
    AdcCount = 0;
    inputState =0;
}

void Input::ReadInputs(){


    inputStateNew  = 0;
    for(uint8_t var=0; var<sizeof(InputStateTab)/sizeof(InputState); var++)
    {
        if((GPIOPinRead(InputStateTab[var].port, InputStateTab[var].pin))&&InputStateTab[var].pin){
            InputStateTab[var].new_state = 1;
        } else {
            InputStateTab[var].new_state = 0;
        }


        if (InputStateTab[var].old_state != InputStateTab[var].new_state)
        {
            if (InputStateTab[var].mid_state != InputStateTab[var].new_state){
                InputStateTab[var].mid_state = InputStateTab[var].new_state;
            } else {
                InputStateTab[var].old_state = InputStateTab[var].new_state;

                UARTprintf("Inp%d=%d\n", InputStateTab[var].name, InputStateTab[var].old_state);
            }
        } else {
            InputStateTab[var].mid_state = InputStateTab[var].old_state;
        }
        inputStateNew = inputStateNew + (InputStateTab[var].old_state<<InputStateTab[var].name);
    }
    if (inputState != inputStateNew){
        inputState = inputStateNew;
        UARTprintf("InpAll:%d\n",inputState);
    }

}

void Input::ReadAdc(){
    AdcCount++;
    if(AdcCount>TIMERADC)
    {
        ADCProcessorTrigger(ADC0_BASE, 0);
        while(!ADCIntStatus(ADC0_BASE, 0, false)){}
        ADCIntClear(ADC0_BASE, 0);
        ADCSequenceDataGet(ADC0_BASE, 0, pui32ADC0Value);
        for (uint8_t i = 0; i<sizeof(AdcStateTab)/sizeof(AdcState); i++){
            AdcStateTab[i].adc = (pui32ADC0Value[i]*3350/4096)*AdcStateTab[i].koeficent;
            if (AdcStateTab[i].on){

               UARTprintf("ADC%c=%d\n", AdcStateTab[i].name, AdcStateTab[i].adc);
            }
        }
        AdcCount=0;
    }
}

void Input::AdcOn(char ch, char state){
    for(uint8_t i = 0; i<sizeof(AdcStateTab)/sizeof(AdcState); i++){
        if (AdcStateTab[i].name == ch) {
            if (state == '1'){
                AdcStateTab[i].on = true;
            }else {
                AdcStateTab[i].on = false;
            }
            UARTprintf("ADC%c:%d-OK\n",ch,AdcStateTab[i].on);
            break;
        }
    }

}

void Input::AdcSend(char ch){
    for(uint8_t i = 0; i<sizeof(AdcStateTab)/sizeof(AdcState); i++){
        if (AdcStateTab[i].name == ch) {
            UARTprintf("ADC%c=%d, OK\n", AdcStateTab[i].name, AdcStateTab[i].adc);
        }
    }
}

//} /* namespace std */
//
