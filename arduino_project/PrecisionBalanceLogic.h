#ifndef PrecisionBalanceLogic_h
#define PrecisionBalanceLogic_h

#include "HX711.h"
#include "Utils.h"
  
class PrecisionBalanceLogic
{
  
  public:
    PrecisionBalanceLogic();
    double getMeanValuesFromCellGroup(char group);
    void getRawValuesFromCells(double *rawValuesFromCellsArray[], HX711 scales[], int numberOfCells);
    void calibrateCell(HX711 *cell, int loadcellDoutPin, int loadCellSckPin);
    


    
  private:
    /*
     * private vars
     * 
     */

//    double maximumDistanceWaterTank;
    
    
    /*
     * Private methods
     */
//    double getFoodTankDistance();
    
    
    
};

#endif
