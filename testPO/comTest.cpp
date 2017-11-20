/*
 * comTest.cpp
 *
 *  Created on: 18 ���. 2017 �.
 *      Author: shestakov.aa
 */

#include "comTest.h"
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
#include <Input.h>
#include "PWR.h"

//namespace std
//{

extern Pwr Pwrrr;
extern Input Inputs;
//�����
const char out[4] = "out";
const char adc[4] = "adc";
const char gps[4] = "gps";
const char pwr[4] = "pwr";
//��������� ������
ParamOut ParamOutTab[] =
{
 {1, GPIO_PORTL_BASE, GPIO_PIN_1, 0}, // PL1 - out1
 {2, GPIO_PORTL_BASE, GPIO_PIN_2, 0}, //PL2 - out2
 {3, GPIO_PORTL_BASE, GPIO_PIN_3, 0},     //PL3 - out3
 {4, GPIO_PORTL_BASE, GPIO_PIN_0, 0},
 {5, GPIO_PORTL_BASE, GPIO_PIN_4, 0},
 {6, GPIO_PORTL_BASE, GPIO_PIN_5, 0},
 {7, GPIO_PORTM_BASE, GPIO_PIN_0, 0},
 {8, GPIO_PORTM_BASE, GPIO_PIN_1, 0},
 {9, GPIO_PORTM_BASE, GPIO_PIN_2, 0},
 {10, GPIO_PORTM_BASE, GPIO_PIN_3, 0},
 {11, GPIO_PORTM_BASE, GPIO_PIN_4, 0}

};

comTest::comTest()
{
    // TODO Auto-generated constructor stub
    count = 0;
}

void comTest::SendMess(){
    UARTprintf("OPA-OPA");

}



void comTest::ReadMess(char c){
    mess[count] = c;
    count++;
    if (c == 0x0A) ParserMess();
    if (count==99) count=0;
}

void comTest::ParserMess(){

    //ParamOutTab[1].name = GetNumber(mess+3);

    //char *istr;
    if (strstr(mess, out)==NULL){
        //UARTprintf("Mimo\n");

    } else {

        ParserOut();
        for (uint8_t var = 0;  var < sizeof(ParamOutTab)/sizeof(ParamOut); var++) {
            if (CurentOut.name == ParamOutTab[var].name){
                CurentOut.port = ParamOutTab[var].port;
                CurentOut.pin = ParamOutTab[var].pin;
                PopalOut = true;
                break;
            }
            else {
                PopalOut = false;

            }
        }

        if (PopalOut == true){
            if (CurentOut.state == 1){
                GPIOPinWrite(CurentOut.port, CurentOut.pin, CurentOut.pin);
            }
            else {
                GPIOPinWrite(CurentOut.port, CurentOut.pin, 0);
            }
            UARTprintf("OK, Out%d - %d\n",CurentOut.name, CurentOut.state);
        } else {
            UARTprintf("Mimo\n");
        }


    }

    if (strstr(mess, adc)==NULL){
           //UARTprintf("Mimo\n");

    } else {
        if (mess[5]=='?'){
            Inputs.AdcSend(mess[3]);
        }   else {
            Inputs.AdcOn(mess[3], mess[5]);

        }

    }



    if (strstr(mess, gps)==NULL){

    } else {

    }

    //������ pwr
    if (strstr(mess, pwr)==NULL){

    } else {
        Pwrrr.ParserPwr(mess);

        //UARTprintf("pwr\n");
    }


    ClearMess();
}

void comTest::ClearMess(){
    for (int i=0; i<100; i++){
        mess[i] = 0x00;
    }
    count = 0;
}

void comTest::ParserOut(){
    uint8_t number = 0;
    char *ch = mess+3;

    for (uint8_t i =0; i < 3; i++){
        if (*ch!=':'){
            if((*ch>='0')&&(*ch<='9')){
               number = number*10;
               number = number + (uint8_t)(*ch - 0x30);
            }else {

            }

        }
        if (*ch==':'){
            break;
        }
        *ch++;
    }
    CurentOut.name = number;
    *ch++;
    if((*ch>='0')&&(*ch<='9')){
        CurentOut.state = (uint8_t)(*ch-0x30);
    } else {
        CurentOut.state = 0;
    }


}
//}

