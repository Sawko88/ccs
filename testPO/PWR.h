/*
 * PWR.h
 *
 *  Created on: 20 но€б. 2017 г.
 *      Author: shestakov.aa
 */
#include <stdint.h>
#include <stdbool.h>

#ifndef PWR_H_
#define PWR_H_

//namespace std
//{

struct pwrParam{
    uint8_t name;
    uint32_t portOn;
    uint8_t pinOn;
    uint8_t stateOn;
    uint32_t portCS;
    uint8_t pinCS;
    uint8_t stateV;
};

class Pwr
{
public:
    Pwr();
    void ParserPwr(char *bufPwr);
};

//}
#endif /* PWR_H_ */
