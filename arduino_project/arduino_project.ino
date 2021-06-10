#include "PrecisionBalanceLogic.h"

PrecisionBalanceLogic precisionBalanceLogic; //the object which control the system

HX711 scales[NUMBER_OF_CELLS];

void setup() {
  Serial.begin(9600);

  calibrateCells();
}

void loop() {

  if(Serial.available())
  {
    char temp = Serial.read();
    if(temp == 't' || temp == 'T') {
      Serial.println("taring...");
      scales[0].tare();
      Serial.println("Tare finished");
    }
   
  }

  Serial.print("getRawValuesFromCells: ");
  double *rawValuesFromCellsArray;
  
  precisionBalanceLogic.getRawValuesFromCells(&rawValuesFromCellsArray, scales, NUMBER_OF_CELLS);
  
  int i;
  for (i = 0; i < NUMBER_OF_CELLS; i = i + 1) {
    Serial.print(" ");
    Serial.print(rawValuesFromCellsArray[i]);
  }

  Serial.println();


  
    
  scales[0].power_down();             // put the ADC in sleep mode
  delay(1000);
  scales[0].power_up();
  
}



void calibrateCells()
{

  precisionBalanceLogic.calibrateCell(&scales[0], LOADCELL_DOUT_PIN_SM1, LOADCELL_SCK_PIN_SM1);
  precisionBalanceLogic.calibrateCell(&scales[1], LOADCELL_DOUT_PIN_SM2, LOADCELL_SCK_PIN_SM2);
  precisionBalanceLogic.calibrateCell(&scales[2], LOADCELL_DOUT_PIN_SM3, LOADCELL_SCK_PIN_SM3);
  precisionBalanceLogic.calibrateCell(&scales[3], LOADCELL_DOUT_PIN_SM4, LOADCELL_SCK_PIN_SM4);
  
}
