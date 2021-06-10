#include "PrecisionBalanceLogic.h"


  PrecisionBalanceLogic::PrecisionBalanceLogic(){    
    
    
  }

  

  void PrecisionBalanceLogic::getRawValuesFromCells(double *rawValuesFromCellsArray[], HX711 scales[], int numberOfCells)
  {
    *rawValuesFromCellsArray = new double[numberOfCells];
    (*rawValuesFromCellsArray)[0] = scales[0].get_units(NUMBER_OF_READINGS);
    (*rawValuesFromCellsArray)[1] = scales[1].get_units(NUMBER_OF_READINGS);
    (*rawValuesFromCellsArray)[2] = scales[3].get_units(NUMBER_OF_READINGS);
    (*rawValuesFromCellsArray)[3] = scales[3].get_units(NUMBER_OF_READINGS);
  }

  void PrecisionBalanceLogic::calibrateCell(HX711 *cell, int loadcellDoutPin, int loadCellSckPin)
  {
    cell->begin(loadcellDoutPin, loadCellSckPin);
    cell->set_scale(CALIBRATION_FACTOR);
    cell->tare();
  }



  //unused method
//  double PrecisionBalanceLogic::getMeanValuesFromCellGroup(char group)
//  {
//    double weight;
//
//    switch(group) {
//      case 'A':
//        weight = scales[0].get_units(NUMBER_OF_READINGS);
//        weight += scales[1].get_units(NUMBER_OF_READINGS);
//        weight += scales[2].get_units(NUMBER_OF_READINGS);
//        weight += scales[3].get_units(NUMBER_OF_READINGS);
//        break;
//        
//      case 'B':
//        weight = scales[4].get_units(NUMBER_OF_READINGS);
//        weight += scales[5].get_units(NUMBER_OF_READINGS);
//        weight += scales[6].get_units(NUMBER_OF_READINGS);
//        weight += scales[7].get_units(NUMBER_OF_READINGS);
//        break;      
//    }
//
//    return weight/4;
//    
//  }
  
