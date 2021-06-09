#include "PrecisionBalanceLogic.h"

PrecisionBalanceLogic precisionBalanceLogic; //the object which control the system

void setup() {
  Serial.begin(9600);

}

void loop() {

//  if (precisionBalanceLogic.getCell(0).is_ready()) {
//    Serial.print("HX711 SM1 reading: ");
//    Serial.println(precisionBalanceLogic.getCell(0).read());
//
//  } else {
//    Serial.println("HX711 SM1 not found.");
//  }
//
//  if (precisionBalanceLogic.getCell(1).is_ready()) {
//    Serial.print("HX711 SM2 reading: ");
//    Serial.println(precisionBalanceLogic.getCell(1).read());
//
//  } else {
//    Serial.println("HX711 SM2 not found.");
//  }
//
//
//  Serial.print("getMeanValuesFromCellGroup A : ");
//  double meanValueA = precisionBalanceLogic.getMeanValuesFromCellGroup('A');
//  Serial.println(meanValueA);
//
//  Serial.print("getMeanValuesFromCellGroup B : ");
//  Serial.println(precisionBalanceLogic.getMeanValuesFromCellGroup('B'));


  if(Serial.available())
  {
    char input = Serial.read();

    Serial.print("input : ");
    Serial.println(input);

    if(input == 't' || input == 'T') {
      for (int i = 0; i < 4; i++) {
        precisionBalanceLogic.getCell(i).tare();
      }
    }

    
  }


  Serial.print("getRawValuesFromCells: ");
  double *rawValuesFromCellsArray;
  
  precisionBalanceLogic.getRawValuesFromCells(&rawValuesFromCellsArray, NUMBER_OF_CELLS);
  
  int i;
  for (i = 0; i < NUMBER_OF_CELLS; i = i + 1) {
    Serial.print(" ");
    Serial.print(rawValuesFromCellsArray[i]);
    
  }

  Serial.println();

  delay(1000);
  
}
