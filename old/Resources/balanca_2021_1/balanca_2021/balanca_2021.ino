#include <SoftwareSerial.h>
#include "HX711.h"
#define calibration_factor -102900 //This value is obtained using the SparkFun_HX711_Calibration sketch
const int DOUT1 = 8;
const int CLK1 = 9;
const int DOUT2 =6;
const int CLK2 = 7;
const int DOUT3 = 5;
const int CLK3 = 4;
const int DOUT4 = 3;
const int CLK4 = 2;

HX711 scale1;
HX711 scale2;
HX711 scale3;
HX711 scale4;

float total=0;
float c1=0;
float c2=0;
float c3=0;
float c4=0;
float distance =100;

SoftwareSerial portOne(0, 1); // software serial #1: RX = digital pin 0, TX = digital pin 1

void setup() {
  
  Serial.begin(9600); // Open serial communications and wait for port to open:

    portOne.begin(9600); // Start each software serial port
    scale1.begin(DOUT1, CLK1);
    scale1.set_scale(calibration_factor); //This value is obtained by using the SparkFun_HX711_Calibration sketch
    //scale1.tare();
    scale2.begin(DOUT2, CLK2);
    scale2.set_scale(calibration_factor);
    //scale2.tare();
    scale3.begin(DOUT3, CLK3);
    scale3.set_scale(calibration_factor);
   // scale3.tare();
    scale4.begin(DOUT4, CLK4);
    scale4.set_scale(calibration_factor);
    //scale4.tare();
    //Assuming there is no weight on the scale at start up, reset the scale to 0
    
}

void loop() {
  float myArray[6]={c1,c2,c3,c4,total,distance};
  int i;
 
  portOne.listen();
  
  if (scale1.wait_ready_retry(10)) {
      c1=(scale1.get_units());
      portOne.print("Celula 1: ");
      portOne.println(scale1.get_units(), 1);
        
  } else {
    portOne.println("HX711-1 not found.");
  }
    if (scale2.wait_ready_retry(10)) {
      c2=(scale2.get_units());
      portOne.print("Celula 2: ");
      portOne.println(scale2.get_units(), 1);
        
  } else {
    portOne.println("HX711-2 not found.");
 }
    if (scale3.wait_ready_retry(10)) {
      c3=(scale3.get_units());
      portOne.print("Celula 3: "); 
      portOne.println(scale3.get_units(), 1);
      
  } else {
    portOne.println("HX711-3 not found.");
  }

  if (scale4.wait_ready_retry(10)) {
      c4=(scale4.get_units());
      portOne.print("Celula 4: ");
      portOne.println(scale4.get_units(), 1);
      
  } else {
    portOne.println("HX711-4 not found.");
    c4=0;
  }
  total=(c1+c2+c3+c4);
  distance=100;
  
  
    for (i = 0; i < 6; i = i + 1) {
      Serial.print(" ");
      Serial.print(myArray[i]);
      
    }

  if(Serial.available())
  {
    char temp = Serial.read();

    Serial.print("\n serial input: ");
    Serial.println(temp);

    
    
//    if(temp == 't' || temp == 'T')
//
//    for (int i = 1; i <= 4; i++) {
//      switch (i) {
//            case 1:
//              //scale1.tare();
//              break;
//            case 2:
//              //scale2.tare();
//              break;
//            case 3:
//              //scale3.tare();
//              break;
//            case 4:
//              scale4.tare();
//              break;
//          }
//   
//    }
  }

  if(portOne.available())
  {
    while (portOne.available() > 0) {

    char temp = portOne.read();
  
  
    Serial.print("\n bluetooth input: ");
    Serial.println(temp);
      
  //    for (int i = 0; i <= 4; i++) {
  //      switch (i) {
  //            case 1:
  //              scale1.tare();
  //              break;
  //            case 2:
  //              scale2.tare();
  //              break;
  //            case 3:
  //              scale3.tare();
  //              break;
  //            case 4:
  //              scale4.tare();
  //              break;
  //          }
  //      }
    }
  
    // blank line to separate data from the two ports:
    Serial.println();
  } else {
    Serial.println("portOne not available");
  }
  

delay(500);

}
