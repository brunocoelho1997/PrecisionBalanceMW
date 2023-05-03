#include "PrecisionBalanceLogic.h"
#include <SoftwareSerial.h>


/*
 * 
 * To compile this code it's necessary to remove Bluetooth module Tx Rx connection.
 * The default password of the HC-06 it's 1234
 * To connect the Android and the Arduino they have to be paired
 * If the bluetooth module isn't removed, the program will not compile.android
 */

PrecisionBalanceLogic precisionBalanceLogic; //the object which control the system
char incomingValue = 0; //temporary var which saves the values that are received by bluetooth or printed on the serial with keyboard

HX711 cells[NUMBER_OF_CELLS];

double *rawValuesFromCellsArray;
  
void setup() {
    
  Serial.begin(9600);
  Serial.println("Serial start!");
    
  calibrateCells();
}

void loop() {

  if (Serial.available() > 0) {
    incomingValue = Serial.read();
    if(incomingValue == 't') {
      Serial.println("taring...");
      precisionBalanceLogic.tareCells(cells);
      Serial.println("Tare finished");
    }
    else if(incomingValue == 'e') {

      rawValuesFromCellsArray[16] = 1; //to indicate that raw cells data WILL BE exported (it's not necessary reset this value... since it will exist a new read and the values will be replaced)
      
      printRawValuesFromCells(&rawValuesFromCellsArray);

    }
//    else
//    {
//      Serial.print("Input: ");
//      Serial.println(incomingValue);
//    }
   
  }

  precisionBalanceLogic.getRawValuesFromCells(&rawValuesFromCellsArray, cells, NUMBER_OF_CELLS);
  
  printRawValuesFromCells(&rawValuesFromCellsArray);

  delete rawValuesFromCellsArray;

  //cells[0].power_down();
  delay(1000);
  //cells[0].power_up();
  
}



void calibrateCells()
{

  precisionBalanceLogic.calibrateCell(&cells[0], LOADCELL_DOUT_PIN_SM1, LOADCELL_SCK_PIN_SM1);
  precisionBalanceLogic.calibrateCell(&cells[1], LOADCELL_DOUT_PIN_SM2, LOADCELL_SCK_PIN_SM2);
  precisionBalanceLogic.calibrateCell(&cells[2], LOADCELL_DOUT_PIN_SM3, LOADCELL_SCK_PIN_SM3);
  precisionBalanceLogic.calibrateCell(&cells[3], LOADCELL_DOUT_PIN_SM4, LOADCELL_SCK_PIN_SM4);

  precisionBalanceLogic.calibrateCell(&cells[4], LOADCELL_DOUT_PIN_SM1, LOADCELL_SCK_PIN_SM1);
  precisionBalanceLogic.calibrateCell(&cells[5], LOADCELL_DOUT_PIN_SM2, LOADCELL_SCK_PIN_SM2);
  precisionBalanceLogic.calibrateCell(&cells[6], LOADCELL_DOUT_PIN_SM3, LOADCELL_SCK_PIN_SM3);
  precisionBalanceLogic.calibrateCell(&cells[7], LOADCELL_DOUT_PIN_SM4, LOADCELL_SCK_PIN_SM4);

  
  precisionBalanceLogic.calibrateCell(&cells[8], LOADCELL_DOUT_PIN_SM1, LOADCELL_SCK_PIN_SM1);
  precisionBalanceLogic.calibrateCell(&cells[9], LOADCELL_DOUT_PIN_SM2, LOADCELL_SCK_PIN_SM2);
  precisionBalanceLogic.calibrateCell(&cells[10], LOADCELL_DOUT_PIN_SM3, LOADCELL_SCK_PIN_SM3);
  precisionBalanceLogic.calibrateCell(&cells[11], LOADCELL_DOUT_PIN_SM4, LOADCELL_SCK_PIN_SM4);

  
  precisionBalanceLogic.calibrateCell(&cells[12], LOADCELL_DOUT_PIN_SM1, LOADCELL_SCK_PIN_SM1);
  precisionBalanceLogic.calibrateCell(&cells[13], LOADCELL_DOUT_PIN_SM2, LOADCELL_SCK_PIN_SM2);
  precisionBalanceLogic.calibrateCell(&cells[14], LOADCELL_DOUT_PIN_SM3, LOADCELL_SCK_PIN_SM3);
  precisionBalanceLogic.calibrateCell(&cells[15], LOADCELL_DOUT_PIN_SM4, LOADCELL_SCK_PIN_SM4);
  
}

void printRawValuesFromCells(double *rawValuesFromCellsArray[])
{
  int i;
  for (i = 0; i < NUMBER_OF_RAW_VALUES-1; i = i + 1) {
    Serial.print((*rawValuesFromCellsArray)[i]);
    Serial.print(" ");
  }
    Serial.print((*rawValuesFromCellsArray)[NUMBER_OF_RAW_VALUES-1]); //print last value without a blank space at the end
  Serial.print(";");
  Serial.println();
  Serial.println();

}
