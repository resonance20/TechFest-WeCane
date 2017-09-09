// /** MAX6675 Thermocouple Reader Example Code
//  *
//  *  This is so simple a library would be silly!
//  *
//  *  6675 Module   ==>   Arduino
//  *    CS          ==>     D10
//  *    SO          ==>     D12
//  *    SCK         ==>     D13
//  *    Vcc         ==>     Vcc (5v OK)
//  *    Gnd         ==>     Gnd
//  *
//  *  You can change the pin assignments below, any pins you want are fine.
//  *
//  *  Upload coade and open your Serial terminal at 9600 to see the temperature
//  *    printed every 1.5 seconds.  That's all!
//  *
//  */
//
// #include <SPI.h>
//
// #define MAX6675_CS   10
// #define MAX6675_SO   12
// #define MAX6675_SCK  13
//
// unsigned char channel_1 = 7;    // Output to Opto Triac pin, channel 1
// unsigned char channel_2 = 6;    // Output to Opto Triac pin, channel 2
// unsigned char dimming = 3;      // Dimming level (0-100)
// unsigned char i;
// unsigned char flag=0;
// unsigned int counter = 0;
//
//
// void setup() {
//   // put your setup code here, to run once:
//   pinMode(channel_1, OUTPUT);// Set AC Load pin as output
//   pinMode(channel_2, OUTPUT);// Set AC Load pin as output
//   attachInterrupt(digitalPinToInterrupt(3), zero_crosss_int, RISING);
//   pinMode(MAX6675_CS, OUTPUT);
//   pinMode(MAX6675_SO, INPUT);
//   pinMode(MAX6675_SCK, OUTPUT);
//   flag=1;
//   dimming=70;  //percentage of off time
//
//   Serial.begin(9600);
//
// }
//
// void zero_crosss_int()  // function to be fired at the zero crossing to dim the light
// {
//   // Firing angle calculation : 1 full 50Hz wave =1/50=20ms
//   // Every zerocrossing : (50Hz)-> 10ms (1/2 Cycle) For 60Hz (1/2 Cycle) => 8.33ms
//   // 10ms=10000us
//
//   int dimtime = (100*dimming);    // For 60Hz =>83
//   delayMicroseconds(dimtime);    // Off cycle
//
//   if (flag==0xFF)
//    {
//     digitalWrite(channel_1, HIGH);   // triac firing
//     delayMicroseconds(10);         // triac On propogation delay (for 60Hz use 8.33)
//     digitalWrite(channel_1, LOW);    // triac Off
//    }
//
//   else
//    {
//     digitalWrite(channel_2, HIGH);   // triac firing
//     delayMicroseconds(10);         // triac On propogation delay (for 60Hz use 8.33)
//     digitalWrite(channel_2, LOW);    // triac Off
//    }
//
// }
//
//
//
// void loop() {
// //  counter = counter +1;
//
// Serial.println(pulseIn(8, HIGH));
//          for (i=85;i>5;i--)
//          {
//            dimming=i;
//            delay(20);
//          }
//
//           for (i=5;i<85;i++)
//          {
//            dimming=i;
//            delay(20);
//          }
//
//           //flag=~flag;
//
// // put your main code here, to run repeatedly:
// //if (counter > 10000)
// //{
// //Serial.print(readThermocouple());
// //Serial.println('c');
// //counter = 0;
// //}
//
// //delay(500);
//
// }
