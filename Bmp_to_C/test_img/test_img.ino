
#include <SPI.h>
#include <TFT_eSPI.h>

char * txt = "OI   menina,   boa  tarde . . . OI   menina,   boa  tarde . . .";

TFT_eSPI tft = TFT_eSPI();


#include <JPEGDecoder.h>

#define minimum(a,b)     (((a) < (b)) ? (a) : (b))

// Include the sketch header file that contains the image stored as an array of bytes
// More than one image array could be stored in each header file.
#include "val.h"


uint32_t icount = 0;



void setup() {
  Serial.begin(115200);
  tft.begin();

  tft.setSwapBytes(true);
  tft.setRotation(0);  // portrait
  tft.fillScreen(TFT_BLACK);
  tft.pushImage(0,0,160,128,val);
  
}

int offset = 0;
void loop() {
  //tft.setTextColor(TFT_MAGENTA);
  tft.setCursor(0,190);
  tft.drawString(txt+offset, 0, 190, 4);

  offset = offset + 1;
  if(offset >= (  strlen(txt)/2    ) )offset = 0;
  
  delay(400);
}
