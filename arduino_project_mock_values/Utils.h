//Pins Cell Group A
const int LOADCELL_DOUT_PIN_SM13 = 39; //nao funca
const int LOADCELL_SCK_PIN_SM13 = 38; //nao funca
const int LOADCELL_DOUT_PIN_SM14 = 41;
const int LOADCELL_SCK_PIN_SM14 = 40; //102280
const int LOADCELL_DOUT_PIN_SM15 = 43; //(teve de haver toque em fios)
const int LOADCELL_SCK_PIN_SM15 = 42; //(teve de haver toque em fios) //102280
const int LOADCELL_DOUT_PIN_SM16 = 45;
const int LOADCELL_SCK_PIN_SM16 = 44; //102280


//Pins Cell Group B
const int LOADCELL_DOUT_PIN_SM7 = 12;
const int LOADCELL_SCK_PIN_SM7 = 13;
const int LOADCELL_DOUT_PIN_SM8 = 10; //nao funca
const int LOADCELL_SCK_PIN_SM8 = 11; //nao funca
const int LOADCELL_DOUT_PIN_SM11 = 51;
const int LOADCELL_SCK_PIN_SM11 = 50; //102280
const int LOADCELL_DOUT_PIN_SM12 = 53; 
const int LOADCELL_SCK_PIN_SM12 = 52; //102280



//Pins Cell Group C
const int LOADCELL_DOUT_PIN_SM1 = 8;
const int LOADCELL_SCK_PIN_SM1 = 9;
const int LOADCELL_DOUT_PIN_SM2 = 6;
const int LOADCELL_SCK_PIN_SM2 = 7;
const int LOADCELL_DOUT_PIN_SM3 = 4;
const int LOADCELL_SCK_PIN_SM3 = 5; //49480
const int LOADCELL_DOUT_PIN_SM4 = 4; //nao funca - parte o serial
const int LOADCELL_SCK_PIN_SM4 = 5; //nao funca - parte o serial


//Pins Cell Group D
const int LOADCELL_DOUT_PIN_SM5 = 16; //cabos partidos (funca se mexermos nos fios)
const int LOADCELL_SCK_PIN_SM5 = 17; //cabos partidos (funca se mexermos nos fios)
const int LOADCELL_DOUT_PIN_SM6 = 14; //muito instavel (teve de se mexer nos fios) 
const int LOADCELL_SCK_PIN_SM6 = 15; //muito instavel (teve de se mexer nos fios)
const int LOADCELL_DOUT_PIN_SM9 = 47;
const int LOADCELL_SCK_PIN_SM9 = 46;
const int LOADCELL_DOUT_PIN_SM10 = 49; //nao funca
const int LOADCELL_SCK_PIN_SM10 = 48; //nao funca






//Configs
const int NUMBER_OF_READINGS = 1;

const int NUMBER_OF_CELLS = 16;

//const double CALIBRATION_FACTOR = 102280.f;

const float CALIBRATION_FACTOR_VALUES [] = {102280, 102280, 102280, 102280, 102280, 102280, 102280, 102280, 102280, 102280, 102280, 102280, 102280, 102280, 102280, 102280};
