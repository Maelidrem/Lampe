/*
	This is a library for the SH01
	Digital Touch Sensor

	The board uses I2C for communication.
	
	The board communicates with two I2C devices:
	* 	CAP1296

	Data Sheets:
	CAP1296 - http://www.microchip.com/mymicrochip/filehandler.aspx?ddocname=en566278
*/

#include <xSH01.h>

/*---Public Function---*/
/********************************************************
 	Constructor
*********************************************************/
xSH01::xSH01(void)
{
    CAP1296_I2C_ADDR = 0x28;
    init();
}
 
/********************************************************
 	Deconstructor
*********************************************************/
xSH01::~xSH01(void)
{

}

/********************************************************
 	Default Parameter Set
*********************************************************/
void xSH01::init(void)
{
    // Main Configuration Regsiter
    SH01_CONFIG.MAIN.INT = 0x01;

    // Configure Sensor Sensitivity 
    SH01_CONFIG.SENSITIVITY.DELTA_SENSE = 0x50; // 4x gain
    SH01_CONFIG.SENSITIVITY.BASE_SHIFT = 0x0F;

    // Config Reg 1
    SH01_CONFIG.CONF.MAX_DR_EN = 0x08;
    SH01_CONFIG.CONF.DIS_DIG_NOISE = 0x20;

    // Configure Sensor Inputs
    SH01_CONFIG.CS_CONF.CS_DEFAULT = 0x39;

    // Disable sensor interrupts
    SH01_CONFIG.CS_CONF.CS_INT_DEFAULT = 0x00; 
    SH01_CONFIG.CS_CONF.CS_REPEAT_EN = 0x00; 

    // Configure Multi-touch Enable
    SH01_CONFIG.CS_CONF.MULT_BLK = 0x00;
	SH01_CONFIG.CS_CONF.B_MULT_T = 0x00;

    // Force Touch input calibration
    SH01_CONFIG.CS_CONF.CS_CAL = 0x39;
}

/********************************************************
 	Configure Sensor
*********************************************************/
bool xSH01::begin(void)
{
    uint8_t PROD_ID;
    uint8_t MANU_ID;

    PROD_ID = xCore.read8(CAP1296_I2C_ADDR, CAP1296_REG_PRODID);
    MANU_ID = xCore.read8(CAP1296_I2C_ADDR, CAP1296_REG_MANUID);

    if(!((PROD_ID == 0x69) && (MANU_ID == 0x5D))){
        return false;
    } 
    else 
    {
        xCore.write8(CAP1296_I2C_ADDR, CAP1296_REG_MTCONFIG, (SH01_CONFIG.CS_CONF.B_MULT_T|SH01_CONFIG.CS_CONF.MULT_BLK));
        xCore.write8(CAP1296_I2C_ADDR, CAP1296_REG_SENSITIVITY, (SH01_CONFIG.SENSITIVITY.BASE_SHIFT|SH01_CONFIG.SENSITIVITY.DELTA_SENSE));
        xCore.write8(CAP1296_I2C_ADDR, CAP1296_REG_RPTRATEENABLE, SH01_CONFIG.CS_CONF.CS_REPEAT_EN);
        xCore.write8(CAP1296_I2C_ADDR, CAP1296_REG_CONFIG1, SH01_CONFIG.CONF.MAX_DR_EN|SH01_CONFIG.CONF.DIS_DIG_NOISE);
        xCore.write8(CAP1296_I2C_ADDR, CAP1296_REG_SENSINPUTENABLE, SH01_CONFIG.CS_CONF.CS_DEFAULT);
        xCore.write8(CAP1296_I2C_ADDR, CAP1296_REG_IRQ_ENABLE, SH01_CONFIG.CS_CONF.CS_INT_DEFAULT);
        xCore.write8(CAP1296_I2C_ADDR, CAP1296_REG_CALIBRATE, SH01_CONFIG.CS_CONF.CS_CAL);
        return true;
    }
}

/********************************************************
 	Poll the sensor
*********************************************************/
void xSH01::poll(void)
{
    GENERAL_STATUS = xCore.read8(CAP1296_I2C_ADDR, CAP1296_REG_GENSTAT);
}

/********************************************************
 	Check if button is pressed
*********************************************************/
bool xSH01::touchDetected(void)
{
    if(GENERAL_STATUS & SH01_CONFIG.MAIN.INT)
    {
        return true;
    } 
    else
    {
        return false;
    }
}

/********************************************************
 	Check if triangle is pressed
*********************************************************/
bool xSH01::triangleTouched(void)
{
    uint8_t touch = xCore.read8(CAP1296_I2C_ADDR, CAP1296_REG_SENSTATUS);

    if(touch & TRIANGLE)
    {
        uint8_t REG_MAIN = xCore.read8(CAP1296_I2C_ADDR, CAP1296_REG_MAIN);
        xCore.write8(CAP1296_I2C_ADDR, CAP1296_REG_MAIN, REG_MAIN & ~SH01_CONFIG.MAIN.INT);
        return true;
    }
    else
    {
        return false;
    }
}

/********************************************************
 	Check if triangle is pressed
*********************************************************/
bool xSH01::circleTouched(void)
{
    uint8_t touch = xCore.read8(CAP1296_I2C_ADDR, CAP1296_REG_SENSTATUS);

    if(touch & CIRCLE)
    {
        uint8_t REG_MAIN = xCore.read8(CAP1296_I2C_ADDR, CAP1296_REG_MAIN);
        xCore.write8(CAP1296_I2C_ADDR, CAP1296_REG_MAIN, REG_MAIN & ~SH01_CONFIG.MAIN.INT);
        return true;
    }
    else
    {
        return false;
    }
}

/********************************************************
 	Check if triangle is pressed
*********************************************************/
bool xSH01::squareTouched(void)
{
    uint8_t touch = xCore.read8(CAP1296_I2C_ADDR, CAP1296_REG_SENSTATUS);


    if(touch & SQUARE)
    {
        uint8_t REG_MAIN = xCore.read8(CAP1296_I2C_ADDR, CAP1296_REG_MAIN);
        xCore.write8(CAP1296_I2C_ADDR, CAP1296_REG_MAIN, REG_MAIN & ~SH01_CONFIG.MAIN.INT);
        return true;
    }
    else
    {
        return false;
    }
}


/********************************************************
 	Check if triangle is pressed
*********************************************************/
bool xSH01::crossTouched(void)
{
    uint8_t touch = xCore.read8(CAP1296_I2C_ADDR, CAP1296_REG_SENSTATUS);


    if(touch & CROSS)
    {
        uint8_t REG_MAIN = xCore.read8(CAP1296_I2C_ADDR, CAP1296_REG_MAIN);
        xCore.write8(CAP1296_I2C_ADDR, CAP1296_REG_MAIN, REG_MAIN & ~SH01_CONFIG.MAIN.INT);
        return true;
    }
    else
    {
        return false;
    }
}

/********************************************************
 	Get the touch status registers value
*********************************************************/
uint8_t xSH01::getTouch(void)
{
    uint8_t touch = xCore.read8(CAP1296_I2C_ADDR, CAP1296_REG_SENSTATUS);
    
    uint8_t REG_MAIN = xCore.read8(CAP1296_I2C_ADDR, CAP1296_REG_MAIN);
    xCore.write8(CAP1296_I2C_ADDR, CAP1296_REG_MAIN, REG_MAIN & ~SH01_CONFIG.MAIN.INT);

    return touch;
}

/*---Private Function---*/
/********************************************************
 	Write default configurations to the SH01
*********************************************************/
void xSH01::writeConfigs(void)
{
    xCore.write8(CAP1296_I2C_ADDR, CAP1296_REG_SENSITIVITY, (SH01_CONFIG.SENSITIVITY.BASE_SHIFT|SH01_CONFIG.SENSITIVITY.DELTA_SENSE));
    xCore.write8(CAP1296_I2C_ADDR, CAP1296_REG_SENSINPUTENABLE, SH01_CONFIG.CS_CONF.CS_DEFAULT);
    xCore.write8(CAP1296_I2C_ADDR, CAP1296_REG_IRQ_ENABLE, SH01_CONFIG.CS_CONF.CS_INT_DEFAULT);
    xCore.write8(CAP1296_I2C_ADDR, CAP1296_REG_RPTRATEENABLE, SH01_CONFIG.CS_CONF.CS_REPEAT_EN);
    xCore.write8(CAP1296_I2C_ADDR, CAP1296_REG_MTCONFIG, (SH01_CONFIG.CS_CONF.B_MULT_T|SH01_CONFIG.CS_CONF.MULT_BLK));
    xCore.write8(CAP1296_I2C_ADDR, CAP1296_REG_CALIBRATE, SH01_CONFIG.CS_CONF.CS_CAL);    
}





