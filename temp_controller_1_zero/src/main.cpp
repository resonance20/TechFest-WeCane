#include "Arduino.h"
#include <SPI.h>
#include <avdweb_SAMDtimer.h>
#include "wiring_private.h" // pinPeripheral() function
#include "../lib/Adafruit_DRV2605/Adafruit_DRV2605.cpp"

//for Protoboard
//Sample using LiquidCrystal I2C library
#include <Wire.h>
#include <LiquidCrystal_I2C.h>


/********************************************
Define pin config
************************************************/
#define NUMPIXELS 144 // Number of LEDs in strip
#define DATAPIN    4
#define CLOCKPIN   5
#define PIN_Temp1 0
#define PIN_OUTPUT 3
#define Red 11
#define Green 12
unsigned char channel_1 = 7;    // Output to Opto Triac pin, channel 1
unsigned char channel_2 = 6;    // Output to Opto Triac pin, channel 2
// Valid PWM outs:
// Timer3: channel 0 on D2 or D10, channel 1 on D5 or D12
// Timer4: channel 0 on SDA or A1, channel 2 on SCL or A2
// Timer5: channel 0 on MOSI, channel 1 on SCK
const byte timer3Pin= 5; // timer3 16bit has 2 pins: 5 12
const byte timer4Pin= 16; // timer4 16bit has 2 pins: SCL(21) or A2(16)
const byte timer5Pin= 24; // timer5 16bit has 1 pin: SCK(24)
// (uint8_t cs1, uint8_t so1, uint8_t clock1)


// SCK on D5 (SERCOM2.3), MISO on D3 (SERCOM2.1) and MOSI on D4 (SERCOM2.0)

int thermo1CLK = 4;
int thermo1SO = 3;
int thermo1CS = 2;

int thermo2CLK = 7;
int thermo2SO = 6;
int thermo2CS = 5;

// For the Proto board
#define btnRIGHT  0
#define btnUP     1
#define btnDOWN   2
#define btnLEFT   3
#define btnSELECT 4
#define btnNONE   5

/********************************************
Define Variables for current controllerDirection
************************************************/
// define some values used by the panel and buttons
int lcd_key     = 0;
int adc_key_in  = 0;
int brightness = 0;

// unsigned char flag=0;
// Period in microseconds
unsigned int period = 10000;
// duty cycle in %
double dutyCycle1 = 25.0;
double dutyCycle2= dutyCycle1;

// time delay in miliseconds
uint32_t timeDelay = 1000;
uint64_t startTime;


uint8_t effect = 52;

/********************************************
Define Functions for interrupts
************************************************/
void StickComplete();
void readThermocouple();
void zero_crosss_int() ;
double triacdutyCycle1(double dCycle);
int read_LCD_buttons();
void buttonSet(int lcd_key);

/********************************************
Constructors
************************************************/
// SAMDtimer timer3 = SAMDtimer(3, TC_COUNTER_SIZE_16BIT, timer3Pin, 1e4);
// SAMDtimer timer4 = SAMDtimer(3, TC_COUNTER_SIZE_16BIT, timer3Pin, 1e4);

// set the LCD address to 0x20 (8574) for a 16 chars and 2 line display
// LiquidCrystal_I2C lcd_8574(0x20,16,2);
Adafruit_DRV2605 drv;

// adress of haptic motor driver
// 0x5A

/********************************************
Setup Section
************************************************/
void setup() {
  //init LCD on 8574
  // lcd_8574.begin();
  // lcd_8574.backlight();

  // Red LED on the Protoboard
  // pinMode(Red,OUTPUT);
  // Green LED on the Protoboard
  // pinMode(Green,OUTPUT);
  // digitalWrite(10,LOW);

  // LCD Init Settings
  // lcd_8574.setBacklight(HIGH);  //write to LCD on PCF8574
  // lcd_8574.setCursor(0,0);
  // lcd_8574.print("Back in business"); // print a simple message to LCD on PCF8574
  // lcd_8574.setCursor(0,1);
  // lcd_8574.print("Neves");  // print a simple message to LCD on PCF8574

  // start PWM at default 50hz
  // timer3.setPulseWidth(50*period);

  // vibration driver setup
  drv.begin();
  drv.selectLibrary(1);
  // I2C trigger by sending 'go' command
  // default, internal trigger when sending GO command
  drv.setMode(DRV2605_MODE_INTTRIG);

  // timer4.setPulseWidth(50*period);

  // do this first, for Reasons
//  SPI1.begin();
  // Assign pins 3, 4, 5 to SERCOM & SERCOM_ALT
  // int thermo1SO = 3;
  // int thermoSI = 4;
  // int thermo1CLK = 5;
  // int thermo1CS = 6;

  //pinPeripheral(thermo1SO, PIO_SERCOM_ALT);
  //pinPeripheral(thermoSI, PIO_SERCOM_ALT);
  //pinPeripheral(thermo1CLK, PIO_SERCOM);

  // Define Global Variables
  // const int oneSecInUsec = 1000000;   // A second in mirco second unit.
  // int time = 1000000; // time is used to read from thermometer


  startTime = millis();

  Serial.begin(115200);
}

void loop() {


  // Serial.print("Effect #"); Serial.println(effect);

  // set the effect to play
  drv.setWaveform(0, effect);  // play effect
  // drv.setWaveform(1, 0);       // end waveform

  // play the effect!
  drv.go();

  // wait a bit
  // delay(2000);

  // effect++;
  if (effect > 117) effect = 1;

  Serial.print("Effect #"); Serial.println(effect);

// Stick.Update();
// digitalWrite(Red,HIGH);
// digitalWrite(Green,LOW);
buttonSet(read_LCD_buttons());  // read the buttons
      if ((millis() - startTime) >= timeDelay)
      { //time to read the temperature
        startTime = millis();
        readThermocouple();
        // lcd_8574.clear();
        // lcd_8574.setCursor(0,0);
        // lcd_8574.print("Effect ");
        // lcd_8574.setCursor(9,0);
        // lcd_8574.print(effect);
        //
        // lcd_8574.setCursor(0,1);
        // lcd_8574.print("Temp2");
        // lcd_8574.setCursor(9,1);
        // lcd_8574.print("nothing");

        // Serial.print(Thermo1.Temperature());
        // Serial.println('c');
        // Serial.println(Output);
      }


}

/********************************************
Functions are writen here
************************************************/

int read_LCD_buttons()
{
 adc_key_in = analogRead(0);      // read the value from the sensor
 if (adc_key_in > 1000) return btnNONE; // this is the 1st option for speed reasons: it will be the most likely result
 // For V1.1 us this threshold
 if (adc_key_in < 50)   return btnRIGHT;
 if (adc_key_in < 250)  return btnUP;
 if (adc_key_in < 450)  return btnDOWN;
 if (adc_key_in < 650)  return btnLEFT;
 if (adc_key_in < 850)  return btnSELECT;
 return btnNONE;  // when all others fail, return this...
}


// Call back functions
void StickComplete()
{
    // Stick.Reverse();
}

void readThermocouple()   // callback function when interrupt is asserted
{

}

void zero_crosss_int()  // function to be fired at the zero crossing to dim the light
{
  /*****************************************************************************
  Firing angle calculation : 1 full 50Hz wave =1/50=20ms
  Every zerocrossing : (50Hz)-> 10ms (1/2 Cycle) For 60Hz (1/2 Cycle) => 8.33ms
  10ms=10000us

  int dimtime = (100*dimming);    // For 60Hz =>83
  delayMicroseconds(dimtime);    // Off cycle
  *****************************************************************************/

  // timer3.setPulseWidth(dutyCycle1*period);
  // timer4.setPulseWidth(dutyCycle2*period);
}

void buttonSet(int lcd_key)
 {

   switch (lcd_key)               // depending on which button was pushed, we perform an action
   {
     case btnRIGHT:
       {


       break;
       }
     case btnLEFT:
       {


       break;
       }
     case btnUP:
       {
      //  lcd_8574.print("BTN = UP     ");
      //  lcd_8574.clear();

      // lcd_8574.setCursor(0,0);
      // lcd_8574.print("Setpoint at");
      // lcd_8574.setCursor(0,1);
      // lcd_8574.print("nothing");
       break;
       }
     case btnDOWN:
       {
        //  lcd_8574.clear();
         //
        //  lcd_8574.setCursor(0,0);
        //  lcd_8574.print("Setpoint at");
        //  lcd_8574.setCursor(0,1);
        //  lcd_8574.print("nothing");
       break;
       }
     case btnSELECT:
       {
      //  lcd_8574.print("BTN = SELECT  ");

       break;
       }
       case btnNONE:
       {
      //  lcd_8574.print("BTN = NONE    ");

       break;
       }
   }
 }
