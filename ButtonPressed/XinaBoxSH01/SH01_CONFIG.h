/*
	This is a library for the SH01
	Digital Touch Sensor

	The board uses I2C for communication.
	
	The board communicates with two I2C devices:
	* 	CAP1296

	Data Sheets:
	CAP1296 - http://www.microchip.com/mymicrochip/filehandler.aspx?ddocname=en566278
*/

#ifndef SH01_CONFIG_h
#define SH01_CONFIG_h

// MAIN CONTROL REGISTER
struct MAIN_CONF_REG {
	uint8_t GAIN;
	uint8_t	STBY;
	uint8_t DSLEEP;
	uint8_t C_GAIN;
	uint8_t COMBO;
	uint8_t INT;
};

// SENSITIVITY CONTROL REGISTER
struct SENSITIVITY_CTRL_REG {
	uint8_t DELTA_SENSE;
	uint8_t BASE_SHIFT;
};

// CONFIGURATION REGISTERS
struct CONF_REG {
	uint8_t TIMEOUT;
	uint8_t DIS_DIG_NOISE;
	uint8_t DIS_ANA_NOISE;
	uint8_t MAX_DR_EN;
	uint8_t BC_OUT_REACEL;
	uint8_t BLK_PWR_CTRL;
	uint8_t BC_OUT_INT;
	uint8_t SHOW_RF_NOISE;
	uint8_t DIS_RF_NOISE;
	uint8_t ACAL_FAIL_INT;
	uint8_t INT_REL_n;
};

// CONFIGURATION OF SENSOR INPUTS
struct SENSOR_INPUT_CONF {
	// SENSOR INPUT ENABLE REGISTER
	uint8_t CS_DEFAULT;

	// SENSOR INPUT CONFIGURATION REGISTER 1 
	uint8_t MAX_DURATION;
	uint8_t RPT_RATE;

	// SENSOR INPUT CONFIGURATION REGISTER 2
	uint8_t M_PRESS;

	// AVERAGING AND SAMPLING CONFIGURATION REGISTER
	uint8_t AVG;
	uint8_t SAMP_TIME;
	uint8_t CYCLE_TIME;

	// CALIBRATION ACTIVATE AND STATUS REGISTER
	uint8_t CS_CAL;

	// INTERRUPT ENABLE REGISTER	
	uint8_t CS_INT_DEFAULT;

	// REPEAT RATE ENABLE REGISTER
	uint8_t CS_REPEAT_EN;

	// SIGNAL GUARD ENABLE REGISTER
	uint8_t SIGNAL_GUARD_EN;

	// MULTIPLE TOUCH CONFIGURATION REGISTER
	uint8_t MULT_BLK;
	uint8_t B_MULT_T;

	// MULTIPLE TOUCH PATTERN CONFIGURATION REGISTER
	uint8_t MTP_EN = 0x80;
	uint8_t CS_PTRN;

	// SENSOR INPUT NOISE THRESHOLD REGISTER
	uint8_t CS_BN_TH;

	// STANDBY CHANNEL REGISTER
	uint8_t CS_STBY_EN;

	// STANDBY CHANNEL REGISTER
	uint8_t AVG_SUM_EN = 0x80;
	uint8_t STBY_AVG;
	uint8_t STBY_SAMP_TIME;
	uint8_t STBY_CY_TIME;

	// STANDBY SENSITIVITY REGISTER
	uint8_t STBY_SENSE;

	// CALIBRATION SENSITIVITY CONFIGURATION REGISTERS
	uint8_t CALSEN1;
	uint8_t CALSEN4;
	uint8_t CALSEN5;
	uint8_t CALSEN6;
};

struct structSH01 {
	MAIN_CONF_REG MAIN;
	SENSITIVITY_CTRL_REG SENSITIVITY;
	CONF_REG CONF;
	SENSOR_INPUT_CONF CS_CONF;
};

#endif