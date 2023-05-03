#include <SoftwareSerial.h> 
//SoftwareSerial MyBlue(0, 1); // RX | TX 
int flag = 0; 
int LED = 8; 
void setup() 
{   
 Serial.begin(9600); 
 
 Serial.println("Ready to connect\nDefualt password is 1234 or 000"); 
} 
void loop() 
{ 
 if (Serial.available())
 {
  flag = Serial.read();
  Serial.println(flag); 
 }
   
  
 if (flag == 1) 
 { 
   
   Serial.println("LED On"); 
 } 
 else if (flag == 0) 
 { 
   
   Serial.println("LED Off"); 
 }

 delay(500);
}  
