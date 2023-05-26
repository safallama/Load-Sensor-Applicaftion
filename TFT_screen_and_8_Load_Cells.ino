//the code is written with the help of different insightful videos, and implemented to adjust to the requirement of the project.
// This is C++ based code written for arduino microcontroller

#include <UTFT.h> //install and include UTFT library
#include <HX711.h> //install and include HX711 library, it is the  ampliphier for the load sensor data. 
#include <URTouch.h> //install and include URTouch library
#include <URTouchCD.h> //install and include URTouchCD library
#include <UTFT_Buttons.h> //install and include UTFT_Buttons library

//Remember each and every library included may not be required, they are all included to make things work just in case. PLease check if you require the library 

// Define the pins for the LCD screen and HX711 load cells
#define TOUCH_ORIENTATION LANDSCAPE
#define HX711_DOUT_1 A15
#define HX711_SCK_1 A14
#define HX711_DOUT_2 A13
#define HX711_SCK_2 A12
#define HX711_DOUT_3 A11
#define HX711_SCK_3 A10
#define HX711_DOUT_4 A9
#define HX711_SCK_4 A8
#define HX711_DOUT_5 A7
#define HX711_SCK_5 A6
#define HX711_DOUT_6 A5
#define HX711_SCK_6 A4
#define HX711_DOUT_7 A3
#define HX711_SCK_7 A2
#define HX711_DOUT_8 A1
#define HX711_SCK_8 A0

int led = 13;
int button1on = 0;
int x, y;

int interval = 1;
unsigned long previousMillis = 0;
int previoussecs = 0;
int currentsecs = 0;

int bg[] = {
  0, 0, 255
};

int fg[] = {
  255, 255, 255
};

UTFT myGLCD(CTE70, 38, 39, 40, 41);  //ITDB50
URTouch myTouch(6, 5, 4, 3, 2);

extern uint8_t BigFont[];
extern uint8_t SevenSegNumFont[];


// Initialize the HX711 library with the correct pins and calibration factor
HX711 Loadcell_1;
HX711 Loadcell_2;
HX711 Loadcell_3;
HX711 Loadcell_4;
HX711 Loadcell_5;
HX711 Loadcell_6;
HX711 Loadcell_7;
HX711 Loadcell_8;

float calibration_factor_1 = 1069.0;
float calibration_factor_2 = 1069.0;
float calibration_factor_3 = 1069.0;
float calibration_factor_4 = 1069.0;
float calibration_factor_5 = 1069.0;
float calibration_factor_6 = 1065.0;
float calibration_factor_7 = 1050.0;
float calibration_factor_8 = 1065.0;


void drawButtons() {
  // put your setup code here, to run once:
  myGLCD.setColor(bg[0], bg[1], bg[2]);
  
  myGLCD.fillRoundRect(10, 10, 260, 155);
  myGLCD.fillRoundRect(270, 10, 520, 155);
  myGLCD.fillRoundRect(530, 10, 780, 155);

  myGLCD.fillRoundRect(10, 165, 260, 310);
  myGLCD.fillRoundRect(270, 165, 520, 310);
  myGLCD.fillRoundRect(530, 165, 780, 310);  

  myGLCD.fillRoundRect(10, 320, 260, 465);
  myGLCD.fillRoundRect(270, 320, 520, 465);
  myGLCD.fillRoundRect(530, 320, 780, 465); 

  myGLCD.setColor(fg[0], fg[1], fg[2]);
  myGLCD.drawRoundRect(10, 10, 260, 155);
  myGLCD.drawRoundRect(270, 10, 520, 155);
  myGLCD.drawRoundRect(530, 10, 780, 155);

  myGLCD.drawRoundRect(10, 165, 260, 310);
  myGLCD.drawRoundRect(270, 165, 520, 310);
  myGLCD.drawRoundRect(530, 165, 780, 310);  

  myGLCD.drawRoundRect(10, 320, 260, 465);
  myGLCD.drawRoundRect(270, 320, 520, 465);
  myGLCD.drawRoundRect(530, 320, 780, 465);

  //myGLCD.print(" Cell 1", 20, 70);
  //myGLCD.print(" Cell 3", 20, 235);
  //myGLCD.print(" Cell 4", 20, 390);

  //myGLCD.print(" Cell 5", 280, 70);
  //myGLCD.print(" Cell 2", 280, 235);
  myGLCD.print(" Touch the one", 280, 390);
  myGLCD.print(" you want!!", 300, 420);


  //myGLCD.print(" Cell 6", 540, 70);
  //myGLCD.print(" Cell 7", 540, 235);
  //myGLCD.print(" Cell 8", 540, 390);

  myGLCD.setBackColor(0, 0, 255);
  myTouch.InitTouch();
  myTouch.setPrecision(PREC_MEDIUM);
}

void setup() {
  // Initialize the LCD screen
  Serial.begin(9600);
  myGLCD.InitLCD();

//Initial Setup
  myGLCD.InitLCD();
  myGLCD.clrScr();

  myTouch.InitTouch();
  myTouch.setPrecision(PREC_MEDIUM);
  
  myGLCD.setFont(BigFont);
  
  myGLCD.setBackColor(0, 0, 255);
  drawButtons();

  // Initialize the HX711 load cells
  Loadcell_1.begin(HX711_DOUT_1, HX711_SCK_1);
  Loadcell_1.set_scale(calibration_factor_1);
  Loadcell_1.tare();

  Loadcell_2.begin(HX711_DOUT_2, HX711_SCK_2);
  Loadcell_2.set_scale(calibration_factor_2);
  Loadcell_2.tare();

  Loadcell_3.begin(HX711_DOUT_3, HX711_SCK_3);
  Loadcell_3.set_scale(calibration_factor_3);
  Loadcell_3.tare();

  Loadcell_4.begin(HX711_DOUT_4, HX711_SCK_4);
  Loadcell_4.set_scale(calibration_factor_4);
  Loadcell_4.tare();

  Loadcell_5.begin(HX711_DOUT_5, HX711_SCK_5);
  Loadcell_5.set_scale(calibration_factor_5);
  Loadcell_5.tare();

  Loadcell_6.begin(HX711_DOUT_6, HX711_SCK_6);
  Loadcell_6.set_scale(calibration_factor_6);
  Loadcell_6.tare();

  Loadcell_7.begin(HX711_DOUT_7, HX711_SCK_7);
  Loadcell_7.set_scale(calibration_factor_7);
  Loadcell_7.tare();

  Loadcell_8.begin(HX711_DOUT_8, HX711_SCK_8);
  Loadcell_8.set_scale(calibration_factor_8);
  Loadcell_8.tare();

}

void loop() {
  // Read the weight from the load cells
  float weight_1 = Loadcell_1.get_units(5);
  float weight_2 = Loadcell_2.get_units(5);
  float weight_3 = Loadcell_3.get_units(5);
  float weight_4 = Loadcell_4.get_units(5);
  float weight_5 = Loadcell_5.get_units(5);
  float weight_6 = Loadcell_6.get_units(5);
  float weight_7 = Loadcell_7.get_units(5);  
  float weight_8 = Loadcell_8.get_units(5);

  // Clear the screen and print the weight on the screen
  myGLCD.printNumF(weight_1, 2, 80, 390, '.', 3);
  myGLCD.printNumF(weight_2, 2, 340, 235, '.', 3);
  myGLCD.printNumF(weight_3, 2, 80, 235, '.', 3);
  myGLCD.printNumF(weight_4, 2, 80, 70, '.', 3);
  myGLCD.printNumF(weight_5, 2, 340, 70, '.', 3);
  myGLCD.printNumF(weight_6, 2, 600, 70, '.', 3);
  myGLCD.printNumF(weight_7, 2, 600, 235, '.', 3);
  myGLCD.printNumF(weight_8, 2, 600, 390, '.', 3);

}

void waitForIt(int x1, int y1, int x2, int y2) {
  myGLCD.setColor(255, 0, 0);
  myGLCD.drawRoundRect(x1, y1, x2, y2);
  while (myTouch.dataAvailable()) {
  }
  delay(20);



  //list all files in the card with date and size

  myGLCD.setColor(fg[0], fg[1], fg[2]);
  myGLCD.drawRoundRect(x1, y1, x2, y2);
}
