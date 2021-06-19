//Pins Cell Group A
const int LOADCELL_DOUT_PIN_SM1 = 8;
const int LOADCELL_SCK_PIN_SM1 = 9;
const int LOADCELL_DOUT_PIN_SM2 = 6;
const int LOADCELL_SCK_PIN_SM2 = 7;
const int LOADCELL_DOUT_PIN_SM3 = 4;
const int LOADCELL_SCK_PIN_SM3 = 5;
const int LOADCELL_DOUT_PIN_SM4 = 2;
const int LOADCELL_SCK_PIN_SM4 = 3;

//Pins Cell Group B
const int LOADCELL_DOUT_PIN_SM13 = 10;
const int LOADCELL_SCK_PIN_SM13 = 11;
const int LOADCELL_DOUT_PIN_SM14 = 4;
const int LOADCELL_SCK_PIN_SM14 = 5;
const int LOADCELL_DOUT_PIN_SM15 = 6;
const int LOADCELL_SCK_PIN_SM15 = 7;
const int LOADCELL_DOUT_PIN_SM16 = 8;
const int LOADCELL_SCK_PIN_SM16 = 9;



//Configs
const int NUMBER_OF_READINGS = 2;

const int NUMBER_OF_CELLS = 16;
const int NUMBER_OF_RAW_VALUES = 17; //16 cells plus 1 index to indicate if is to export values or not

const double CALIBRATION_FACTOR = 2280.f;
