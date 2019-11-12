/*****************************************************************************
		PIXY AG, CH-5400 Baden, Switzerland, www.pixy.ch
		(C) Copyright 2005, PIXY AG, All Rights Reserved
------------------------------------------------------------------------------
 VERSION MANAGEMENT FILE INFO:
 $File: //lmd/pixy/include/h8.h $
 $Revision: #1 $
 $Date: 2005/08/12 $
 $Author: patrick.furrer $
------------------------------------------------------------------------------
 TARGET OS: LINUX 2.4
------------------------------------------------------------------------------
 FILE DESCRIPTION (PURPOSE):
 
 This header file declares the class for the H8 access. The class H8 is a
 singleton and can be used for communication with the H8 microcontroller. With
 this class you can get or set some H8 paramters like watchdog, device address,
 brightness and so on. The singleton H8 must be initialized with the static
 method initH8() which defines the COM port (e.g. "/dev/ttyS2") before you can
 communicate with the H8 microcontroller.
------------------------------------------------------------------------------
 CONSTRAINTS:
------------------------------------------------------------------------------
 HISTORY

 Date	Step	Who	What
 120805	1	pf	first version
*****************************************************************************/

#ifndef H8_H
#define H8_H

#define INC90

// Include file for struct termios
#include <termios.h>

// Include file for Qt class QString
#include <QString>

// Defines for H8 operation results
#define H8_SUCCESS	0
#define H8_FILE_ERROR	-1
#define H8_WRITE_ERROR	-2
#define H8_READ_ERROR	-3
#define H8_PARAM_ERROR	-4
#define H8_DISABLED	-5

/*!
 * \brief	The class H8 communicates with the H8 microcontroller.
 *
 * The class H8 is a singleton and can be used for communication with the H8 microcontroller. With
 * this class you can get or set some H8 paramters like watchdog, device address, brightness and so
 * on. The singleton H8 must be initialized with the static method initH8() which defines the COM
 * port (e.g. "/dev/ttyS2") before you can communicate with the H8 microcontroller.
 */
class H8
{		
public:
	/*!
	 * \brief	Initialize the H8 access with the defined COM port.
	 *
	 * This static method initializes the H8 access with the defined COM port (e.g. "/dev/ttyS2")
	 * on which the H8 microcontroller is connected to. If the H8 access is already initialized so
	 * the method does nothing. Otherwise the class H8 will be instantiated with the defined COM
	 * port. Initialize the H8 access as early as possible in your application!
	 *
	 * \param	comPort	COM port (e.g. "/dev/ttyS2") on which the H8 microcontroller is connected to.
	 */
	static void initH8(const char* comPort, bool enable = true);
	
	/*!
	 * \brief	Get the pointer to the only and one H8 object.
	 *
	 * This static method returns the pointer to the only and one H8 object (if it exists). The H8
	 * must be initialized with the static method initH8() before you get a pointer to the H8!
	 *
	 * \return	Pointer to the only and one H8 object.
	 */
	static H8* getH8();
	
	/*!
	 * \brief	Get the device address defined by the power connector.
	 *
	 * This method gets the device address defined by the power connector.
	 *
	 * \param	deviceAddress	Pointer for storing the device address.
	 *
	 * \return	Result of operation (see header file for possible return values).
	 */
	int getDeviceAddress(int* deviceAddress);
	 
	/*!
	 * \brief	Set the watchdog with the defined timeout (in milliseconds).
	 *
	 * This method sets the watchdog with the defined timeout (in milliseconds). The following values for
	 * timeout are allowed:
	 *
	 *     0               : Disable watchdog                                           <br>
	 *     100..60000 ms   : Enable watchdog with the defined timeout value             <br>
	 *
	 * Values greater than 60000 ms are set to 60000 ms automatically. Values between 0 and 100 ms are
	 * set to 100 ms. The method parameter timeout will be replaced with the effective timeout which is
	 * used for setting the H8 watchdog.
	 *
	 * \param	timeout	Timeout for watchdog (in milliseconds).
	 *
	 * \return	Result of operation (see header file for possible return values).
	 */
	int setWatchdog(unsigned int* timeout);
	
	/*!
	 * \brief	Retrigger the watchdog.
	 *
	 * This method retriggers the watchdog.
	 *
	 * \return	Result of operation (see header file for possible return values).
	 */
	int retriggerWatchdog();
	
	/*!
	 * \brief	Set the minimum adjustable LCD brightness.
	 *
	 * This method sets the minimum adjustable LCD brightness. The following range is allowed: 0..255.
	 * Values greater than 255 are set to 255 automatically.
	 *
	 * \param	minBrightness	Value for minimum adjustable LCD brightness.
	 *
	 * \return	Result of operation (see header file for possible return values).
	 */
	int setMinBrightness(unsigned int minBrightness);
	
	/*!
	 * \brief	Set the maximum adjustable LCD brightness.
	 *
	 * This method sets the maximum adjustable LCD brightness. The following range is allowed: 0..255.
	 * Values greater than 255 are set to 255 automatically.
	 *
	 * \param	maxBrightness	Value for maximum adjustable LCD brightness.
	 *
	 * \return	Result of operation (see header file for possible return values).
	 */
	int setMaxBrightness(unsigned int maxBrightness);
	
	/*!
	 * \brief	Set the manual or automatic LCD brightness mode.
	 *
	 * This method sets the manual or automatic LCD brightness mode. The following values for brightness
	 * are allowed:
	 *
	 *     0        : Automatic brightness                                              <br>
	 *     1        : LCD off                                                           <br>
	 *     2..255   : Manual brightness                                                 <br>
	 *
	 * Values greater than 255 are set to 255 automatically.
	 *
	 * \param	brightness	Value for LCD brightness.
	 *
	 * \return	Result of operation (see header file for possible return values).
	 */
	int setBrightness(unsigned int brightness);
	
	/*!
	 * \brief	Set the LCD brightness offset.
	 *
	 * This method sets the LCD brightness offset. The valid range is -255..255. Values greater
	 * than 255 are set to 255. Values less than -255 are set to -255.
	 *
	 * \param	brightnessOffset	Value for LCD brightness offset.
	 *
	 * \return	Result of operation (see header file for possible return values).
	 */
	int setBrightnessOffset(int brightnessOffset);
	
	/*!
	 * \brief	Set the LCD brightness control axis segment.
	 *
	 * This method sets the LCD brightness control axis segment. The valid range is -255..255. Values
	 * greater than 255 are set to 255. Values less than -255 are set to -255.
	 *
	 * \param	brightnessAxis	Value for LCD brightness control axis segment.
	 *
	 * \return	Result of operation (see header file for possible return values).
	 */
	int setBrightnessAxisSection(int brightnessAxis);
	
	/*!
	 * \brief	Set the brightness positive reaction rate.
	 *
	 * This method sets the rate at which the backlight reacts to increasing brightness. The valid
	 * range is 1..100 (100 = slowest). Values greater than 100 are set to 100. Values less than 1
	 * are set to 1.
	 *
	 * \param	posReactionRate	Positive reaction rate.
	 *
	 * \return	Result of operation (see header file for possible return values).
	 */
	int setBrightnessPositiveReactionRate(unsigned int posReactionRate);
	
	/*!
	 * \brief	Set the brightness negative reaction rate.
	 *
	 * This method sets the rate at which the backlight reacts to decreasing brightness. The valid
	 * range is 1..100 (100 = slowest). Values greater than 100 are set to 100. Values less than 1
	 * are set to 1.
	 *
	 * \param	negReactionRate	Negative reaction rate.
	 *
	 * \return	Result of operation (see header file for possible return values).
	 */
	int setBrightnessNegativeReactionRate(unsigned int negReactionRate);
	
	/*!
	 * \brief	Setup the internal buzzer.
	 *
	 * This method setups the internal buzzer. This buzzer is used for various system actions like
	 * power up sound, button click, beep and error beep.
	 *
	 * \param	powerUpSound	Flag for power up sound.
	 * \param	buttonClick	Flag for button click.
	 * \param	beep		Flag for beep.
	 * \param	errorBeep	Flag for error beep.
	 *
	 * \return	Result of operation (see header file for possible return values).
	 */
	int setupBuzzer(bool powerUpSound, bool buttonClick, bool beep, bool errorBeep);

	int activBuzzer(unsigned int ifrequency, unsigned int ilength);

	/*!
	 * \brief	Get the current LCD brightness.
	 *
	 * This method gets the current LCD brightness.
	 *
	 * \param	brightness	Pointer for storing the current LCD brightness.
	 *
	 * \return	Result of operation (see header file for possible return values).
	 */
	int getBrightness(int* brightness);
	
	/*!
	 * \brief	Get the software version of the H8 firmware.
	 *
	 * This method gets the software version of the H8 firmware.
	 *
	 * \param	swVersion	Pointer for storing the software version.
	 *
	 * \return	Result of operation (see header file for possible return values).
	 */
	int getSwVersion(int* majorSwVersion, int* minorSwVersion);
	
	/*!
	 * \brief	Get the board number.
	 *
	 * This method gets the board number which can be used for hardware identification purposes.
	 *
	 * \param	boardNumber	Pointer for storing the board number.
	 *
	 * \return	Result of operation (see header file for possible return values).
	 */
	int getBoardNumber(int* boardNumber);
	
	/*!
	 * \brief	Get the panel type.
	 *
	 * This method gets the panel type which identifies the softkeys configuration.
	 *
	 * \param	panelType	Pointer for storing the panel type.
	 *
	 * \return	Result of operation (see header file for possible return values).
	 */
	int getPanelType(int* panelType);
	
	/*!
	 * \brief	Get the device inside temperature.
	 *
	 * This method gets the current device inside temperature.
	 *
	 * \param	temperature	Pointer for storing the inside temperature.
	 *
	 * \return	Result of operation (see header file for possible return values).
	 */
	int getDeviceTemperature(int* temperature);

	int getTemperatureLevel(QString& level);
	
	/*!
	 * \brief	Enable or disable the backlight.
	 *
	 * This method enables or disables the backlight.
	 *
	 * \param	enable	True for enable the backlight otherwise false.
	 *
	 * \return	Result of operation (see header file for possible return values).
	 */
	int enableBacklight(bool enable = true);
	
	/*!
	 * \brief	Enable or disable the front panel keys.
	 *
	 * This method enables or disables the front panel keys.
	 *
	 * \param	enable	True for enable the front panel keys otherwise false.
	 *
	 * \return	Result of operation (see header file for possible return values).
	 */
	int enableFrontPanelKeys(bool enable = true);
	
	/*!
	 * \brief	Save current settings to H8 EEPROM.
	 *
	 * This method saves the current settings to H8 EEPROM..
	 *
	 * \return	Result of operation (see header file for possible return values).
	 */
	int saveCurrentSettings();

private:
	/*!
	 * \brief	The constructor opens the defined COM port on which the H8 is connected to.
	 *
	 * The constructor opens the defined COM port (e.g. "/dev/ttyS2") on which the H8 is connected to.
	 * After that the current COM options will be stored. This options will be restored after closing
	 * the COM port in destructor. After storing the current options, new options are set.
	 *
	 * \param	comPort	COM port (e.g. "/dev/ttyS2") on which the H8 microcontroller is connected to.
	 */
	H8(const char* comPort, bool enable = true);
	
	/*!
	 * \brief	The destructor closes the COM port.
	 *
	 * The destructor restores the old port settings and closes the COM port.
	 */
	~H8();
	
	/*!
	 * \brief	Send the command sequence to H8 microcontroller.
	 *
	 * This method sends the command sequence to the H8 microcontroller.
	 *
	 * \param	commandSequence	H8 command sequence.
	 *
	 * \return	Result of operation (see header file for possible return values).
	 */
	int sendCommand(QString& commandSequence);
	
	/*!
	 * \brief	Receive the the report sequence from H8 microcontroller.
	 *
	 * This method receives the report sequence from the H8 microcontroller.
	 *
	 * \param	reportSequence	H8 report sequence.
	 *
	 * \return	Result of operation (see header file for possible return values).
	 */
	int receiveReport(QString& reportSequence);
	
	/*!
	 * \brief	Get the parameter from the report sequence.
	 *
	 * This method gets the parameter from the report sequence.
	 *
	 * \param	reportSequence	H8 report sequence.
	 * \param	param		Parameter contained in the report sequence.
	 *
	 * \return	Result of operation (see header file for possible return values).
	 */
	int getParameter(QString& reportSequence, int* param);
	
	/*!
	 * \brief	Define the only and one H8 object (singleton).
	 *
	 * This variable defines the only and one H8 object (singleton). This object cannot
	 * instantiated directly. Use the static method initH8() to instantiate an H8 object.
	 */
	static H8* h8;
	
	/*!
	 *
	 */
	bool enabled;
	
	/*!
	 * \brief	Define the file descriptor.
	 *
	 * This variable defines the file descriptor which must be used for file operations to
	 * communicate with the H8 microcontroller.
	 */
	int fd;
	
	/*!
	 * \brief	Define a struct for storing the current COM port settings.
	 *
	 * This variable defines a struct for storing the COM port settings which are set before
	 * the communication with H8 begins.
	 */
	struct termios oldOptions;
	
	/*!
	 * \brief	Define a struct for storing the H8 COM port settings.
	 *
	 * This variable defines a struct for storing the COM port settings used for the communication
	 * with the H8 microcontroller.
	 */
	struct termios newOptions;
};

#endif
