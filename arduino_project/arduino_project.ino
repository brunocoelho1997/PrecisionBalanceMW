#include "PrecisionBalanceLogic.h"

PrecisionBalanceLogic precisionBalanceLogic; //the object which control the system
char incomingValue = 0; //temporary var which saves the values that are received by bluetooth or printed on the serial with keyboard

HX711 cells[NUMBER_OF_CELLS];

void setup() {
  Serial.begin(9600);

  calibrateCells();
}

void loop() {


  if (Serial.available() > 0) {
    incomingValue = Serial.read();
    if(incomingValue == 't' || incomingValue == 'T') {
      Serial.println("taring...");
      precisionBalanceLogic.tareCells(cells);
      Serial.println("Tare finished");
    }
    else
    {
      Serial.print("Input: ");
      Serial.println(incomingValue);
    }
   
  }

  Serial.print("getRawValuesFromCells: ");
  double *rawValuesFromCellsArray;
  
  precisionBalanceLogic.getRawValuesFromCells(&rawValuesFromCellsArray, cells, NUMBER_OF_CELLS);
  
  int i;
  for (i = 0; i < NUMBER_OF_CELLS; i = i + 1) {
    Serial.print(" ");
    Serial.print(rawValuesFromCellsArray[i]);
  }

  Serial.println();

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
  
}
