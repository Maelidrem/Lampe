/*****************************************************************************
    This is an example for the xCHIP SH01

    This examples read data from a SH01 Capacitive Touch Buttons

    You can buy this device on our store!
    -----> https://xinabox.cc/products/SH01/

    The sensors communicates over the I2C Bus
*****************************************************************************/

#include <xCore.h>
#include <xSH01.h>

#define WHITE_LED_PIN 3
#define BLUE_LED_PIN 5
#define GREEN_LED_PIN 6
#define RED_LED_PIN 9

#define WHITE_INDEX 0
#define BLUE_INDEX 1
#define GREEN_INDEX 2
#define RED_INDEX 3

#define TRIANGLE_INDEX 0
#define SQUARE_INDEX 1
#define CROSS_INDEX 2
#define CIRCLE_INDEX 3

xSH01 SH01;

bool ledState[4];
// Timer pour eviter les rebonds humain (#Lolo)
short smoothTimer[4];
bool switchedState[4];
void setup() {
  //Start I2C com at 115200 bauds
  Serial.begin(115200);
  Wire.begin();
  // Set D03,D05,D06,D09 I/O in output state
  pinMode(WHITE_LED_PIN, OUTPUT);
  pinMode(BLUE_LED_PIN, OUTPUT);
  pinMode(GREEN_LED_PIN, OUTPUT);
  pinMode(RED_LED_PIN, OUTPUT);

  for (int i = 0; i < 4; i++)
  {
    ledState[i] = false;
    switchedState[i] = false;
  }
}

bool CheckTouched(int buttonIndex)
{
  if (SH01.touchDetected()) 
  {
    switch(buttonIndex)
    {
      case TRIANGLE_INDEX:
        return SH01.triangleTouched();      
      case SQUARE_INDEX:
        return SH01.squareTouched();      
      case CROSS_INDEX:
        return SH01.crossTouched();      
      case CIRCLE_INDEX:
        return SH01.circleTouched();    
      default:
        return false;
    }
  }

  return false;
}

short GetLedIndexForButtonIndex(short buttonIndex)
{
    switch(buttonIndex)
    {
      case TRIANGLE_INDEX:
        return WHITE_INDEX;      
      case SQUARE_INDEX:
        return BLUE_INDEX;      
      case CROSS_INDEX:
        return GREEN_INDEX;     
      case CIRCLE_INDEX:
        return RED_INDEX;     
      default:
        return -1;
    }

    return -1;
}

void SetStateForEnlightening(int buttonIndex)
{
    short ledIndex = GetLedIndexForButtonIndex(buttonIndex);
    if (CheckTouched(buttonIndex))
    {
      smoothTimer[buttonIndex] ++;
      if(smoothTimer[buttonIndex] > 10 && !switchedState[ledIndex])
      {
        switchedState[ledIndex] = true;
        ledState[ledIndex] = !ledState[ledIndex];
      }
    }
    else
    {     
        switchedState[ledIndex] = false;
        smoothTimer[buttonIndex] = 0;
    }
}

void loop() {
  SH01.poll();
  for (int i = 0; i < 4; i++)
  {
    SetStateForEnlightening(i);
  }
  
  if (SH01.touchDetected()) 
  {
    // Display led in function of state leds
    digitalWrite(WHITE_LED_PIN, ledState[WHITE_INDEX]);
    digitalWrite(BLUE_LED_PIN, ledState[BLUE_INDEX]);
    digitalWrite(GREEN_LED_PIN, ledState[GREEN_INDEX]);
    digitalWrite(RED_LED_PIN, ledState[RED_INDEX]);
  }
  
  delay(10);
}
