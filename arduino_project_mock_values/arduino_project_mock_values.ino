#include "PrecisionBalanceLogic.h"
#include <SoftwareSerial.h>


PrecisionBalanceLogic precisionBalanceLogic; //the object which control the system
char incomingValue = 0; //temporary var which saves the values that are received by bluetooth or printed on the serial with keyboard

HX711 cells[NUMBER_OF_CELLS];

double *rawValuesFromCellsArray;

int MOCK_VALUE = 0;

void setup() {
    
  Serial.begin(9600);
  //Serial.println("Serial start!");
    
  //calibrateCells();
}

void loop() {


  if (Serial.available() > 0) {
    incomingValue = Serial.read();
    if(incomingValue == 'T') {
      MOCK_VALUE++;
    }   
  }

  
  /*
  if (Serial.available() > 0) {
    incomingValue = Serial.read();
    if(incomingValue == 't') {
      Serial.println("taring...");
      precisionBalanceLogic.tareCells(cells);
      Serial.println("Tare finished");
    }   
  }


  precisionBalanceLogic.getRawValuesFromCells(&rawValuesFromCellsArray, cells, NUMBER_OF_CELLS);
  
  printRawValuesFromCells(&rawValuesFromCellsArray);

  delete rawValuesFromCellsArray;

  delay(1000);*/

  printDummyRawValuesFromCells();
  delay(1000);
  
}

void calibrateCells()
{

  Serial.println("Calibrating cells");
  
  precisionBalanceLogic.calibrateCell(&cells[0], LOADCELL_DOUT_PIN_SM14, LOADCELL_SCK_PIN_SM14, CALIBRATION_FACTOR_VALUES[0]);
  precisionBalanceLogic.calibrateCell(&cells[1], LOADCELL_DOUT_PIN_SM16, LOADCELL_SCK_PIN_SM16, CALIBRATION_FACTOR_VALUES[1]);
  precisionBalanceLogic.calibrateCell(&cells[2], LOADCELL_DOUT_PIN_SM13, LOADCELL_SCK_PIN_SM13, CALIBRATION_FACTOR_VALUES[2]);
  precisionBalanceLogic.calibrateCell(&cells[3], LOADCELL_DOUT_PIN_SM15, LOADCELL_SCK_PIN_SM15, CALIBRATION_FACTOR_VALUES[3]);

  precisionBalanceLogic.calibrateCell(&cells[4], LOADCELL_DOUT_PIN_SM12, LOADCELL_SCK_PIN_SM12, CALIBRATION_FACTOR_VALUES[4]);
  precisionBalanceLogic.calibrateCell(&cells[5], LOADCELL_DOUT_PIN_SM8, LOADCELL_SCK_PIN_SM8, CALIBRATION_FACTOR_VALUES[5]);
  precisionBalanceLogic.calibrateCell(&cells[6], LOADCELL_DOUT_PIN_SM11, LOADCELL_SCK_PIN_SM11, CALIBRATION_FACTOR_VALUES[6]);
  precisionBalanceLogic.calibrateCell(&cells[7], LOADCELL_DOUT_PIN_SM7, LOADCELL_SCK_PIN_SM7, CALIBRATION_FACTOR_VALUES[7]);

  
  precisionBalanceLogic.calibrateCell(&cells[8], LOADCELL_DOUT_PIN_SM1, LOADCELL_SCK_PIN_SM1, CALIBRATION_FACTOR_VALUES[8]);
  precisionBalanceLogic.calibrateCell(&cells[9], LOADCELL_DOUT_PIN_SM3, LOADCELL_SCK_PIN_SM3, CALIBRATION_FACTOR_VALUES[9]);
  precisionBalanceLogic.calibrateCell(&cells[10], LOADCELL_DOUT_PIN_SM2, LOADCELL_SCK_PIN_SM3, CALIBRATION_FACTOR_VALUES[10]);
  precisionBalanceLogic.calibrateCell(&cells[11], LOADCELL_DOUT_PIN_SM2, LOADCELL_SCK_PIN_SM3, CALIBRATION_FACTOR_VALUES[11]);

  
  precisionBalanceLogic.calibrateCell(&cells[12], LOADCELL_DOUT_PIN_SM9, LOADCELL_SCK_PIN_SM9, CALIBRATION_FACTOR_VALUES[12]);
  precisionBalanceLogic.calibrateCell(&cells[13], LOADCELL_DOUT_PIN_SM6, LOADCELL_SCK_PIN_SM6, CALIBRATION_FACTOR_VALUES[13]);
  precisionBalanceLogic.calibrateCell(&cells[14], LOADCELL_DOUT_PIN_SM10, LOADCELL_SCK_PIN_SM10, CALIBRATION_FACTOR_VALUES[14]);
  precisionBalanceLogic.calibrateCell(&cells[15], LOADCELL_DOUT_PIN_SM5, LOADCELL_SCK_PIN_SM5, CALIBRATION_FACTOR_VALUES[15]);
  
}

void printRawValuesFromCells(double *rawValuesFromCellsArray[])
{
  int i;
  for (i = 0; i < NUMBER_OF_CELLS-1; i = i + 1) {
    Serial.print((*rawValuesFromCellsArray)[i]);
    Serial.print(" ");
  }
  Serial.print((*rawValuesFromCellsArray)[NUMBER_OF_CELLS-1]); //print last value without a blank space at the end
  Serial.print(";");
  Serial.println();
  Serial.println();

}

void printDummyRawValuesFromCells()
{
  int i;
  int MOCK_VALUES [] = {MOCK_VALUE, MOCK_VALUE, MOCK_VALUE, MOCK_VALUE, MOCK_VALUE, MOCK_VALUE, MOCK_VALUE, MOCK_VALUE, MOCK_VALUE, MOCK_VALUE, MOCK_VALUE, MOCK_VALUE, MOCK_VALUE, MOCK_VALUE, MOCK_VALUE, MOCK_VALUE};

  for (i = 0; i < NUMBER_OF_CELLS-1; i = i + 1) {
    Serial.print(MOCK_VALUES[i]);
    Serial.print(" ");
  }
  Serial.println(MOCK_VALUES[NUMBER_OF_CELLS-1]); //print last value without a blank space at the end
  //Serial.println();
  //Serial.println();

}
