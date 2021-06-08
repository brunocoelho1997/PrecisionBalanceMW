#include "PrecisionBalanceLogic.h"

  HX711 scales[8];

  PrecisionBalanceLogic::PrecisionBalanceLogic(){    
    //Cell Group A
    scales[0].begin(LOADCELL_DOUT_PIN_SM1, LOADCELL_SCK_PIN_SM1);
    scales[1].begin(LOADCELL_DOUT_PIN_SM2, LOADCELL_SCK_PIN_SM2);
    scales[2].begin(LOADCELL_DOUT_PIN_SM3, LOADCELL_SCK_PIN_SM3);
    scales[3].begin(LOADCELL_DOUT_PIN_SM4, LOADCELL_SCK_PIN_SM4);
  
    //Cell Group B
    scales[4].begin(LOADCELL_DOUT_PIN_SM13, LOADCELL_SCK_PIN_SM13);
    scales[5].begin(LOADCELL_DOUT_PIN_SM14, LOADCELL_SCK_PIN_SM14);
    scales[6].begin(LOADCELL_DOUT_PIN_SM15, LOADCELL_SCK_PIN_SM15);
    scales[7].begin(LOADCELL_DOUT_PIN_SM16, LOADCELL_SCK_PIN_SM16);

  }


  HX711 PrecisionBalanceLogic::getCell(int index)
  {
    return scales[index];
  }
  
  double PrecisionBalanceLogic::getMeanValuesFromCellGroup(char group)
  {
    double weight;

    switch(group) {
      case 'A':
        weight = scales[0].get_units(NUMBER_OF_READINGS);
        weight += scales[1].get_units(NUMBER_OF_READINGS);
        weight += scales[2].get_units(NUMBER_OF_READINGS);
        weight += scales[3].get_units(NUMBER_OF_READINGS);
        break;
        
      case 'B':
        weight = scales[4].get_units(NUMBER_OF_READINGS);
        weight += scales[5].get_units(NUMBER_OF_READINGS);
        weight += scales[6].get_units(NUMBER_OF_READINGS);
        weight += scales[7].get_units(NUMBER_OF_READINGS);
        break;      
    }

    return weight/4;
    
  }
  
