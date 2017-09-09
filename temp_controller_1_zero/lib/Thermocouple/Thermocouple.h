/*------------------------------------------------------------------------
  not much here yet

    ------------------------------------------------------------------------*/
#include "Arduino.h"

#ifndef _THERMOCOUPLE_
#define _THERMOCOUPLE_

class Thermocouple {

 public:

    Thermocouple(uint8_t cs, uint8_t so, uint8_t clock);
    // ~Thermocouple(void);
  uint32_t
        readThermocouple(),
        Temperature();
  void
    begin(void);                            // Prime pins/SPI for output

 private:
   uint8_t
    cs,
    so,
    clock;

    uint32_t
      temperature;
};

#endif // _ADAFRUIT_DOT_STAR_H_
