#ifndef PrecisionBalanceLogic_h
#define PrecisionBalanceLogic_h

#include <SoftwareSerial.h>
#include "HX711.h"
#include "Utils.h"

class PrecisionBalanceLogic
{
  
  public:
    PrecisionBalanceLogic();
    double getMeanValuesFromCellGroup(char group);
    HX711 getCell(int index);
    void getRawValuesFromCells(double *rawValuesFromCellsArray[], int numberOfCells);
    
    
//    double getFoodTankState();
    
        
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
