//http://www.rinkydinkelectronics.com/t_imageconverter565.php
#include <SPI.h>
#include <TFT_eSPI.h>
//TFT 135x240

char txt []  = "C A R P E D I E M . . .\0";
char txt2 [100] ;
TFT_eSPI tft = TFT_eSPI();


#include <JPEGDecoder.h>

#define minimum(a,b)     (((a) < (b)) ? (a) : (b))

// Include the sketch header file that contains the image stored as an array of bytes
// More than one image array could be stored in each header file.
#include "cdm2.h"
#include "cdm.h"


uint32_t icount = 0;



void setup() {
  Serial.begin(115200);
  tft.begin();

  tft.setSwapBytes(true);
  tft.setRotation(0); 
  tft.fillScreen(TFT_BLACK);
  tft.setRotation(1);
  tft.pushImage(150,27,80,80,cdm2);

}

int offset = 0;
void loop() {
  
 
  
  tft.pushImage(150,27,80,80,cdm2);
  
  sprintf(txt2,txt);
  txt2[offset + 1] = '-';
  txt2[offset + 2] = '_';
  txt2[offset + 3] = '\0';
  tft.setCursor(0,0);
  tft.drawString(txt2 , 0, 55, 4);
  
  delay(200);
  
  offset = offset + 1;
  if(offset >= (  strlen(txt)   ) ){
    offset = 0;
    tft.fillScreen(TFT_BLACK);
  }
  
  
}
