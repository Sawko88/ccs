/*
 * Input.h
 *
 *  Created on: 20 окт. 2017 г.
 *      Author: shestakov.aa
 */
#include <stdint.h>
#include <stdbool.h>

#ifndef INPUT_H_
#define INPUT_H_

//namespace std
//{

struct InputState{
    uint8_t name;
    uint32_t port;
    uint8_t pin;
    uint32_t old_state;
    uint32_t mid_state;
    uint32_t new_state;

};

struct AdcState{
    char name;
    bool on;
    uint8_t koeficent;
    uint32_t adc;

};

class Input
{
public:
    Input();
    void ReadInputs(void);
    bool ready ;
    void ReadAdc(void);
    void AdcOn(char, char);
    void AdcSend(char);


private:
    uint32_t pui32ADC0Value[8];
    uint8_t AdcCount;
    uint32_t inputState;
};

//} /* namespace std */

#endif /* INPUT_H_ */
