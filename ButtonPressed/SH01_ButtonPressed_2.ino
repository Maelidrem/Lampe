/*****************************************************************************
    This is an example for the xCHIP SH01

    This examples read data from a SH01 Capacitive Touch Buttons

    You can buy this device on our store!
    -----> https://xinabox.cc/products/SH01/

    The sensors communicates over the I2C Bus
*****************************************************************************/

#include <xCore.h>
#include <xSH01.h>

#define WHITE_LED 3
#define BLUE_LED 5
#define GREEN_LED 6
#define RED_LED 9

xSH01 SH01;

bool ledState[4];
// Timer pour eviter les rebonds humain (#Lolo)
short smoothTimer[4];
void setup() {
  //Start I2C com at 115200 bauds
  Serial.begin(115200);
  Wire.begin();
  // Set D03,D05,D06,D09 I/O in output state
  pinMode(3, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(9, OUTPUT);

  for (int i = 0; i < 4; i++)
  {
    ledState[i] = false;
  }
}

 
void loop() {
  SH01.poll();

  // Detect change of states
  if (SH01.touchDetected()) {
    if (SH01.triangleTouched() && SH01.triangleTouched() != ledState[0])
    {      
      smoothTimer[0] ++;
      if(smoothTimer[0] > 10) {
        smoothTimer[0] = 0;
        ledState[0] = !ledState[0];
      }
    }

    if (SH01.squareTouched() && smoothTimer[1] > 10) {        
      ledState[1] = !ledState[1];
    }

    if (SH01.crossTouched() && smoothTimer[2] > 10 ) {
      ledState[2] = !ledState[2];
    }

    if (SH01.circleTouched() && smoothTimer[3] > 10) {
      ledState[3] = !ledState[3];
    }

    // Display led in function of state leds
    digitalWrite(WHITE_LED, ledState[0]);
    digitalWrite(BLUE_LED, ledState[1]);
    digitalWrite(GREEN_LED, ledState[2]);
    digitalWrite(RED_LED, ledState[3]);
    delay(1);
  }
}
