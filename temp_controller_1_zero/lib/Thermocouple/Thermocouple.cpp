#include "Thermocouple.h"

Thermocouple::Thermocouple(uint8_t cs1, uint8_t so1, uint8_t clock1){

  cs= cs1;
  so=so1;
  clock= clock1;

  pinMode(cs, OUTPUT);
  pinMode(so, INPUT);
  pinMode(clock, OUTPUT);
  digitalWrite(cs, HIGH);

}

uint32_t Thermocouple::Temperature(){
return temperature;
}
uint32_t Thermocouple::readThermocouple() {

  uint16_t v;
  digitalWrite(cs, LOW);
  delay(1);
  // Read in 16 bits,
  //  15    = 0 always
  //  14..2 = 0.25 degree counts MSB First
  //  2     = 1 if thermocouple is open circuit

  v = shiftIn(so, clock, MSBFIRST);
  v <<= 8;
  v |= shiftIn(so, clock, MSBFIRST);

  digitalWrite(cs, HIGH);
  if (v & 0x4)
  {
    // Bit 2 indicates if the thermocouple is disconnected
    return NAN;
  }

  // The lower three bits (0,1,2) are discarded status bits
  v >>= 3;

  // The remaining bits are the number of 0.25 degree (C) counts
  return

  temperature=v*0.25;

  return temperature;
}
void Thermocouple::begin(){




}
