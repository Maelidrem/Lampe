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

enum Mode
{
  OFF,
  ALL,
  BLINK,
  WHITE,
  SWITCH,
};

enum BlinkState
{
  GREEN,
  RED,
  BLUE,
};

bool ledState[4];
short smoothTimer[4];
bool switchedState[4];
bool buttonState[4];
int duration;
Mode modeCorrespondance[4];

BlinkState currentBlinkState;
Mode currentMode;

void setup() 
{
  //Start I2C com at 115200 bauds
  Serial.begin(115200);
  Wire.begin();
  // Set D03,D05,D06,D09 I/O in output state
  pinMode(WHITE_LED_PIN, OUTPUT);
  pinMode(BLUE_LED_PIN, OUTPUT);
  pinMode(GREEN_LED_PIN, OUTPUT);
  pinMode(RED_LED_PIN, OUTPUT);

  duration = 0;
  currentBlinkState = GREEN;
  currentMode = OFF;
  
  for (int i = 0; i < 4; i++)
  {
    ledState[i] = false;
    switchedState[i] = false;
    buttonState[i] = false;
  }
  
  modeCorrespondance[TRIANGLE_INDEX] = SWITCH;
  modeCorrespondance[CIRCLE_INDEX] = ALL;
  modeCorrespondance[CROSS_INDEX] = WHITE;
  modeCorrespondance[SQUARE_INDEX] = BLINK;   
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

bool CheckPressed(int buttonIndex)
{
    if (CheckTouched(buttonIndex))
    {
      smoothTimer[buttonIndex] ++;
      if(smoothTimer[buttonIndex] > 10 && !buttonState[buttonIndex])
      {
        buttonState[buttonIndex] = true;
        return true;
      }
    }
    else
    {     
        buttonState[buttonIndex] = false;
        smoothTimer[buttonIndex] = 0;
    }

    return false;
}

void UpdateBlinkState() 
{
    duration++;
    if (duration > 25)
    {
      duration = 0;
      switch(currentBlinkState)
      {
        case RED:
          currentBlinkState = GREEN;
          break;
        case GREEN:
          currentBlinkState = BLUE;
          break;
        case BLUE:
          currentBlinkState = RED;
          break;
      }
    }
}

void UpdateBlinkStateOnButtonPress() 
{
  switch(currentBlinkState)
  {
    case RED:
      currentBlinkState = GREEN;
      break;
    case GREEN:
      currentBlinkState = BLUE;
      break;
    case BLUE:
    currentBlinkState = RED;
    break;
  }
}
 
void SetLedStatesUsingBlinkState()
{
    switch(currentBlinkState)
    {
      case RED:
         ledState[RED_INDEX] = 1;
         ledState[GREEN_INDEX] = 0;
         ledState[BLUE_INDEX] = 0;
         ledState[WHITE_INDEX] = 0;
         break;    
      case GREEN:
         ledState[RED_INDEX] = 0;
         ledState[GREEN_INDEX] = 1;
         ledState[BLUE_INDEX] = 0;
         ledState[WHITE_INDEX] = 0;
         break;
      case BLUE:
         ledState[RED_INDEX] = 0;
         ledState[GREEN_INDEX] = 0;
         ledState[BLUE_INDEX] = 1;
         ledState[WHITE_INDEX] = 0;
         break;   
    }  
}

void SetMode(Mode mode)
{
    currentMode = currentMode == mode ? OFF: mode;
}


void loop() {
  SH01.poll();
  for (int i = 0; i < 4; i++)
  {
    if (CheckPressed(i))
    {
      SetMode(modeCorrespondance[i]);
      if (i == TRIANGLE_INDEX)
      {
        UpdateBlinkStateOnButtonPress();
      }
    }
  }

  switch(currentMode)
  {
    case ALL:
      ledState[RED_INDEX] = 1;
      ledState[GREEN_INDEX] = 1;
      ledState[BLUE_INDEX] = 1;
      ledState[WHITE_INDEX] = 1;
      break;
    case OFF:
      ledState[RED_INDEX] = 0;
      ledState[GREEN_INDEX] = 0;
      ledState[BLUE_INDEX] = 0;
      ledState[WHITE_INDEX] = 0;
      break;
    case BLINK:
      UpdateBlinkState();
      SetLedStatesUsingBlinkState();
      break;
    case WHITE:
      ledState[RED_INDEX] = 0;
      ledState[GREEN_INDEX] = 0;
      ledState[BLUE_INDEX] = 0;
      ledState[WHITE_INDEX] = 1;
      break;
    case SWITCH:
      SetLedStatesUsingBlinkState();
      break;
  }
  
  // Display led in function of state leds
  digitalWrite(WHITE_LED_PIN, ledState[WHITE_INDEX]);
  digitalWrite(BLUE_LED_PIN, ledState[BLUE_INDEX]);
  digitalWrite(GREEN_LED_PIN, ledState[GREEN_INDEX]);
  digitalWrite(RED_LED_PIN, ledState[RED_INDEX]);
  
  delay(10);
}
