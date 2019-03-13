/*
	This is a library for the SH01
	Digital Touch Sensor

	The board uses I2C for communication.
	
	The board communicates with two I2C devices:
	* 	CAP1296

	Data Sheets:
	CAP1296 - http://www.microchip.com/mymicrochip/filehandler.aspx?ddocname=en566278
*/

#ifndef xSH01_h
#define xSH01_h

// Include File Headers
#include <xCore.h>
#include <SH01_CONFIG.h>

/* CAP1296 register addresses */
#define CAP1296_REG_MAIN 				0x00      	//Main Control
#define CAP1296_REG_GENSTAT 			0x02		//General Status
#define CAP1296_REG_SENSTATUS 			0x03		//Sensor Input Status (where touches on the inputs are stored)
#define CAP1296_REG_NOISEFLAG 			0x0A		//Noise Flag Status
#define CAP1296_REG_SENS_IN_DEL_COUNT1 	0X10		//Sensor Input 1 Delta Count
#define CAP1296_REG_SENS_IN_DEL_COUNT2 	0X11		//Sensor Input 2 Delta Count
#define CAP1296_REG_SENS_IN_DEL_COUNT3 	0X12		//Sensor Input 3 Delta Count
#define CAP1296_REG_SENS_IN_DEL_COUNT4 	0X13		//Sensor Input 4 Delta Count
#define CAP1296_REG_SENS_IN_DEL_COUNT5 	0X14		//Sensor Input 5 Delta Count
#define CAP1296_REG_SENS_IN_DEL_COUNT6 	0X15		//Sensor Input 6 Delta Count
#define CAP1296_REG_SENSITIVITY			0x1F		//Sensitivity Control
#define CAP1296_REG_CONFIG1 			0x20		//Configuration 1 (General) (Configuration 2 is 0x44)	
#define CAP1296_REG_SENSINPUTENABLE		0x21		//Sensor Input Enable
#define CAP1296_REG_SENSINPUTCONFIG1	0x22		//Sensor Input Configuration 1
#define CAP1296_REG_SENSINPUTCONFIG2	0x23		//Sensor Input Configuration 2
#define CAP1296_REG_AVGSAMPCONFIG		0x24		//Averaging and Sampling Configuration
#define CAP1296_REG_CALIBRATE 			0x26		//Calibration Activate and Status
#define CAP1296_REG_IRQ_ENABLE 			0x27		//Interrupt Enable
#define CAP1296_REG_RPTRATEENABLE 		0x28		//Repeat Rate Enable
#define CAP1296_REG_SGENABLE 			0x29		//Signal Guard Enable
#define CAP1296_REG_MTCONFIG 			0x2A		//Multiple Touch Configuration
#define CAP1296_REG_MTPATTERNCONFIG		0x2B		//Multiple Touch Pattern Configuration
#define CAP1296_REG_MTPATTERN			0x2D		//Multiple Touch Pattern
#define CAP1296_REG_BASECOUNTOUTOFLIMIT 0x2E		//Base Count Out of Limit
#define CAP1296_REG_RECALCONFIG			0x2F		//Recalibration Configuration
#define CAP1296_REG_SENSINPUTTHRES1		0x30		//Sensor Input 1 Threshold
#define CAP1296_REG_SENSINPUTTHRES2		0x31		//Sensor Input 2 Threshold
#define CAP1296_REG_SENSINPUTTHRES3		0x32		//Sensor Input 3 Threshold
#define CAP1296_REG_SENSINPUTTHRES4		0x33		//Sensor Input 4 Threshold
#define CAP1296_REG_SENSINPUTTHRES5		0x34		//Sensor Input 5 Threshold
#define CAP1296_REG_SENSINPUTTHRES6		0x35		//Sensor Input 6 Threshold
#define CAP1296_REG_SENSINPUTNOISTHRES	0x38		//Sensor Input Noise Threshold

/* CAP1296 standby configuration registers addresses */
#define CAP1296_REG_CONF_STANDBYCHNL	0x40		//Standby Channel
#define CAP1296_REG_CONF_STANDBYCFG 	0x41		//Standby Configuration
#define CAP1296_REG_CONF_STANDBYSENS	0x42		//Standby Sensitivity
#define CAP1296_REG_CONF_STANDBYTHRES	0x43		//Standby Threshold
#define CAP1296_REG_CONF_CONFIG2 		0x44		//Configuration 2 (Configuration 1 is 0x20)

/* CAP1296 Base count registers addresses */
#define CAP1296_REG_SENS_IN_BCOUNT1 	0x50		//Sensor Input 1 Base Count
#define CAP1296_REG_SENS_IN_BCOUNT2 	0x51		//Sensor Input 2 Base Count
#define CAP1296_REG_SENS_IN_BCOUNT3 	0x52		//Sensor Input 3 Base Count
#define CAP1296_REG_SENS_IN_BCOUNT4 	0x53		//Sensor Input 4 Base Count
#define CAP1296_REG_SENS_IN_BCOUNT5 	0x54		//Sensor Input 5 Base Count
#define CAP1296_REG_SENS_IN_BCOUNT6 	0x55		//Sensor Input 6 Base Count

/* CAP1296 Power button registers addresses */
#define CAP1296_REG_PWRBT				0x60		//Power Button
#define CAP1296_REG_PWRBTCONFIG			0x61		//Power Button Configuration

/* CAP1296 Calibration sensitivity configuration registers addresses */
#define CAP1296_REG_CALIBSENSCONFIG1	0x80		//Calibration Sensitivity Configuration 1
#define CAP1296_REG_CALIBSENSCONFIG2	0x81		//Calibration Sensitivity Configuration 2

/* CAP1296 Calibration registers addresses */
#define CAP1296_REG_SENSINPUTCALIB1		0xB1		//Sensor Input 1 Calibration
#define CAP1296_REG_SENSINPUTCALIB2		0xB2		//Sensor Input 2 Calibration
#define CAP1296_REG_SENSINPUTCALIB3		0xB3		//Sensor Input 3 Calibration
#define CAP1296_REG_SENSINPUTCALIB4		0xB4		//Sensor Input 4 Calibration
#define CAP1296_REG_SENSINPUTCALIB5		0xB5		//Sensor Input 5 Calibration
#define CAP1296_REG_SENSINPUTCALIB6		0xB6		//Sensor Input 6 Calibration
#define CAP1296_REG_SENSINPUTCALIBLSB1	0xB9		//Sensor Input Calibration LSB 1
#define CAP1296_REG_SENSINPUTCALIBLSB2	0xBA		//Sensor Input Calibration LSB 2

/* CAP1296 ID registers addresses */
#define CAP1296_REG_PRODID 				0xFD		//Product ID (default 0x69)
#define CAP1296_REG_MANUID 				0xFE		//Manufacturer ID (default 0x5D)

#define TRIANGLE	0x01
#define	CIRCLE	0x20
#define	SQUARE	0x10
#define CROSS	0x08

class xSH01: public xCoreClass
{
	public:
	    /**
		* Constructor
		*/	
	    xSH01();

	    /**
		* Deconstructor
		*/		    
	    ~xSH01();

		/**
		* Class stucture for setup
		*/		
		structSH01 SH01_CONFIG;

		/**
		* Default configuration of CAP1296
		*/
		void init(void);

		/*
		* Runs the setup of the sensor. 
		* Call this in setup(), before reading any sensor data.
		*
		* @return true if setup was successful.
		*/	
	    bool begin(void);

		/*
		* Call this in loop(), checks if any botton is pressed.
		*
		* @return none, 
		*/			
		void poll(void);

		/*
		* Call this in loop(), checks if any botton is pressed.
		*
		* @return true, if button press was detected.
		*/	
	    bool touchDetected(void);

		bool triangleTouched(void);

		bool squareTouched(void);

		bool circleTouched(void);

		bool crossTouched(void);

		uint8_t getTouch(void);
		
	private:

		void writeConfigs(void);

		uint8_t GENERAL_STATUS;

		uint8_t CAP1296_I2C_ADDR;

};

#endif