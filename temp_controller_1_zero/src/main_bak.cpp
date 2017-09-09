// #include "Arduino.h"
// #include <NeoPatterns.h>
// #include <Adafruit_DotStar.h>
// #include <Thermocouple.h>
// #include <PID_v1.h>
// #include <SPI.h>         // COMMENT OUT THIS LINE FOR GEMMA OR TRINKET
// #include <avdweb_SAMDtimer.h>
//
// //for Protoboard
// //Sample using LiquidCrystal I2C library
// #include <Wire.h>
// #include <LiquidCrystal_I2C.h>
//
// /********************************************
// DEfine pin config
// ************************************************/
// #define NUMPIXELS 144 // Number of LEDs in strip
// #define DATAPIN    4
// #define CLOCKPIN   5
// #define PIN_INPUT 0
// #define PIN_OUTPUT 3
//
//
// /********************************************
// Define Variables for current controllerDirection
// ************************************************/
//
// unsigned char channel_1 = 7;    // Output to Opto Triac pin, channel 1
// unsigned char channel_2 = 6;    // Output to Opto Triac pin, channel 2
// unsigned char dimming;      // Dimming level (0-100)
// unsigned char i;
// unsigned char flag=0;
// unsigned int counter = 0;
// // Period in microseconds
// unsigned int period = 10000;
// // duty cycle in %
// double dutyCycle = 25.0;
// // time delay in miliseconds
// uint32_t timeDelay = 1000;
// uint64_t startTime;
//
// /* Valid PWM outs:
//   Timer3: channel 0 on D2 or D10, channel 1 on D5 or D12
//   Timer4: channel 0 on SDA or A1, channel 2 on SCL or A2
//   Timer5: channel 0 on MOSI, channel 1 on SCK
// */
//
// const byte timer3Pin= 5; // timer3 16bit has 2 pins: 5 12
// const byte timer4Pin= 16; // timer4 16bit has 2 pins: SCL(21) or A2(16)
// const byte timer5Pin= 24; // timer3 16bit has 1 pin: SCK(24)
//
// //Setting up PID controller
// // Define Variables we'll be connecting to
// double Setpoint, Input, Output;
// //Specify the links and initial tuning parameters
// double Kp=0.7, Ki=0, Kd=0;
//
//
// /********************************************
// Define Functions for interrupts
// ************************************************/
// void StickComplete();
// void readThermocouple();
// void zero_crosss_int() ;
// double triacDutyCycle(double dCycle);
//
// /********************************************
// Constructors
// ************************************************/
// // NeoPatterns Stick(NUMPIXELS,DATAPIN, CLOCKPIN, DOTSTAR_BRG, &StickComplete);
// Thermocouple Thermo1(12,10,13);
// // set the LCD address to 0x20 (8574) for a 16 chars and 2 line display
// LiquidCrystal_I2C lcd_8574(0x20,16,2);
// PID myPID(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);
//
// /********************************************
// Setup Section
// ************************************************/
// void setup() {
//
//   // Define Global Variables
//   // const int oneSecInUsec = 1000000;   // A second in mirco second unit.
//   // int time = 1000000; // time is used to read from thermometer
//   Setpoint= 50;
//   Input=Thermo1.Temperature();
//   startTime = millis();
//
//   // setup current controller
//   pinMode(channel_1, OUTPUT);// Set AC Load pin as output
//   pinMode(channel_2, OUTPUT);// Set AC Load pin as output
//   attachInterrupt(3, zero_crosss_int, RISING);
//   flag=1;
//   dimming=50;  //percentage of off time
//
//   // Start PWM
//   // SAMDtimer(byte timerNr, tc_counter_size countersize, byte pin, unsigned period_us, int pulseWidth_us=-1, bool timerEnable=1);
//   // starts with period of 10 000uS and default duty cycle of 50%
//   SAMDtimer timer3 = SAMDtimer(3, TC_COUNTER_SIZE_16BIT, timer3Pin, 1e4);
//
//
//   // Start PID
//   myPID.SetOutputLimits(0.0, 100.0);
//   myPID.SetMode(AUTOMATIC);
//
//   // Initialize all the pixelStrips
//   // Stick.begin();
//   // Stick.RainbowCycle(1);
//
//   Serial.begin(115200);
// }
//
// void loop() {
//
//       // Stick.Update();
//
//
//
//
//
//       if ((millis() - startTime) >= timeDelay)
//       { //time to shift the Relay Window
//         startTime = millis();
//         readThermocouple();
//         Serial.print(Thermo1.Temperature());
//         Serial.println('c');
//         Serial.println(Output);
//       }
//       // if ( timeDelay < (millis() - startTime))
//       // { //time to shift the Relay Window
//       //
//       //   Serial.println("waiting");
//       // }
//       // if (Output < millis() - startTime) digitalWrite(RELAY_PIN, HIGH);
//       // else digitalWrite(RELAY_PIN, LOW);
//       // Serial.println(millis() - startTime);
//       // delay(10);
// }
//
// //------------------------------------------------------------
// //Completion Routines - get called on completion of a pattern
// //------------------------------------------------------------
//
// // Call back functions
// void StickComplete()
// {
//     // Stick.Reverse();
// }
//
// void readThermocouple()   // callback function when interrupt is asserted
// {
//   Thermo1.readThermocouple();  // use NOT operator to invert toggle value
//
// }
//
// double triacDutyCycle(double dCycle)
// {
//   if ((dCycle >= 100.1) || (dCycle <= -0.1))
//   {
//   Serial.println("Duty cycle is out of bounds. expected between 0.0 and 100.0. Value is:");
//   Serial.println(dCycle);
//   }
// return (100.0 - dCycle);
// }
//
// void zero_crosss_int()  // function to be fired at the zero crossing to dim the light
// {
//   Input=Thermo1.Temperature();
//   myPID.Compute();
//
//   // CurieTimerOne.pwmStart(channel_1, Output, period);
//
//   // CurieTimerOne.pwm(channel_1, Output);
//   if (flag==1)
//   {
//     // CurieTimerOne.restart();
//     flag=0;
//   }
//   // Serial.println("duty cycle");
//   // Serial.println(Output);
//
//   // Firing angle calculation : 1 full 50Hz wave =1/50=20ms
//   // Every zerocrossing : (50Hz)-> 10ms (1/2 Cycle) For 60Hz (1/2 Cycle) => 8.33ms
//   // 10ms=10000us
//
//   // int dimtime = (100*dimming);    // For 60Hz =>83
//   // delayMicroseconds(dimtime);    // Off cycle
//
//   // if (flag==0xFF)
//   //  {
//     // digitalWrite(channel_1, HIGH);   // triac firing
//     // delayMicroseconds(10);         // triac On propogation delay (for 60Hz use 8.33)
//     // digitalWrite(channel_1, LOW);    // triac Off
//   //  }
//   //
//   // else
//   //  {
//   //   digitalWrite(channel_2, HIGH);   // triac firing
//   //   delayMicroseconds(10);         // triac On propogation delay (for 60Hz use 8.33)
//   //   digitalWrite(channel_2, LOW);    // triac Off
//   //  }
//
//
//
// }
