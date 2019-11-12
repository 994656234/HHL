/*****************************************************************************
		PIXY AG, CH-5400 Baden, Switzerland, www.pixy.ch
		(C) Copyright 2005, PIXY AG, All Rights Reserved
------------------------------------------------------------------------------
 VERSION MANAGEMENT FILE INFO:
 $File: //lmd/pixy/src/h8/h8.cpp $
 $Revision: #1 $
 $Date: 2005/08/12 $
 $Author: patrick.furrer $
------------------------------------------------------------------------------
 TARGET OS: LINUX 2.4
------------------------------------------------------------------------------
 FILE DESCRIPTION (PURPOSE):
 
 This file implements the class for the H8 access. The class H8 is a singleton
 and can be used for communication with the H8 microcontroller. With this
 class you can get or set some H8 paramters like watchdog, device address,
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

// Include header file for this implementation
#include "h8.h"

// Include files for communication with COM ports
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#ifdef INC90
#include <stdlib.h>
#include "command.h"
#endif

#ifdef QR_ENABLE_LOGS
// Include file for trace modules
#include "tracemodules.h"

BubTraceSourceId(H8);
#endif

// Set the only and one H8 object (singleton) to null.
H8* H8::h8 = 0;

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
void H8::initH8(const char* comPort, bool enable)
{
	if (h8 == 0) {
#ifdef QR_ENABLE_LOGS
		QR_Trace(SInit, ("initH8(): H8 access is %s; COM port: %s", enable ? "enabled" : "disabled", comPort));
#endif
		h8 = new H8(comPort, enable);
		
	} else {
#ifdef QR_ENABLE_LOGS
		QR_Trace(SInit, ("initH8(): H8 access is already initialized!"));
#endif
	}
}

/*!
 * \brief	Get the pointer to the only and one H8 object.
 *
 * This static method returns the pointer to the only and one H8 object (if it exists). The H8
 * must be initialized with the static method initH8() before you get a pointer to the H8!
 *
 * \return	Pointer to the only and one H8 object.
 */
H8* H8::getH8()
{
#ifdef QR_ENABLE_LOGS
	if (h8 == 0) {
		QR_Panic(("getH8(): ATTENTION: The H8 access is not initialized. Probably your application crashes!)"));
	}
#endif
	
	return h8;
}

/*!
 * \brief	Get the device address defined by the power connector.
 *
 * This method gets the device address defined by the power connector.
 *
 * \param	deviceAddress	Pointer for storing the device address.
 *
 * \return	Result of operation (see header file for possible return values).
 */
int H8::getDeviceAddress(int* deviceAddress)
{
	int retVal;
	
	if (enabled) {
		if (fd > 0) {
			// Define H8 command for getting the device address
			QString cmd("\x1B#94\x0D");
			
			// Send H8 command sequence <ESC>#94<CR> for getting the device address
			retVal = sendCommand(cmd);
			
			if (retVal == H8_SUCCESS) {
				QString reportSequence;
				
				// Receive H8 report sequence <ACK><SOH>#94,ADDR<CR>
				retVal = receiveReport(reportSequence);
				
				if (retVal == H8_SUCCESS) {
					// Get the device address from the report sequence
					retVal = getParameter(reportSequence, deviceAddress);
				}
			}
		} else {
			retVal = H8_FILE_ERROR;
		}
		
#ifdef QR_ENABLE_LOGS
		// Trace result of H8 operation
		if (retVal == H8_SUCCESS) {
			QR_Trace(SInit, ("getDeviceAddress(): Device address is %d", *deviceAddress));
		} else {
			QR_Trace(SInit, ("getDeviceAddress(): Get device address failed! (Error: %d)", retVal));
		}
#endif
	} else {
#ifdef QR_ENABLE_LOGS
		QR_Trace(SInit, ("getDeviceAddress(): H8 access is disabled!"));
#endif
		retVal = H8_DISABLED;
	}
	
	return retVal;
}

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
int H8::setWatchdog(unsigned int* timeout)
{
	int retVal;
	
	if (enabled) {
		if (fd > 0) {
			// Value should not be between 0 and 100 milliseconds
			if ((*timeout > 0) && (*timeout < 100)) {
				*timeout = 100;
			}
			
			// Value should not be greater than 60'000 milliseconds
			if (*timeout > 60000) {
				*timeout = 60000;
			}

#ifdef INC90
			if ((retVal = rcv_0_command_1(fd, 19, (int)(*timeout/100))) == NAK) {
				retVal = rcv_0_command_1(fd, 19, (int)(*timeout/100));
			}
			if (stringType == retVal) {
				retVal = H8_SUCCESS;
			}
			else {
				retVal = H8_WRITE_ERROR;
			}
				
#else		
			// Define H8 command for setting the watchdog
			QString cmd = QString("\x1B#19,%1\x0D").arg((int)(*timeout/100));
			
			// Send H8 command <ESC>#19,p<CR> for setting the watchdog
			retVal = sendCommand(cmd);
#endif			
		} else {
			retVal = H8_FILE_ERROR;
		}
		
#ifdef QR_ENABLE_LOGS
		// Trace result of H8 operation
		if (retVal == H8_SUCCESS) {
			if (*timeout == 0) {
				QR_Trace(SInit, ("setWatchdog(): Watchdog is disabled"));
			} else {
				QR_Trace(SInit, ("setWatchdog(): Watchdog is enabled with timeout: %d ms", ((int)(*timeout/100)) * 100));
			}
		} else {
			QR_Trace(SInit, ("setWatchdog(): Set watchdog failed! (Error: %d)", retVal));
		}
#endif
	} else {
#ifdef QR_ENABLE_LOGS
		QR_Trace(SInit, ("setWatchdog(): H8 access is disabled!"));
#endif
		retVal = H8_DISABLED;
	}
	
	return retVal;
}

/*!
 * \brief	Retrigger the watchdog.
 *
 * This method retriggers the watchdog.
 *
 * \return	Result of operation (see header file for possible return values).
 */
int H8::retriggerWatchdog()
{
	int retVal;
	
	if (enabled) {
		if (fd > 0) {
			// Define H8 command for retrigger the watchdog
			QString cmd("\x17");
			
			// Send H8 command for retrigger the watchdog
			retVal = sendCommand(cmd);
		} else {
			retVal = H8_FILE_ERROR;
		}
		
#ifdef QR_ENABLE_LOGS
		// Trace result of H8 operation (only failures!)
		if (retVal != H8_SUCCESS) {
			QR_Trace(SInit, ("retriggerWatchdog(): Retrigger watchdog failed! (Error: %d)", retVal));
		}
#endif
	} else {
#ifdef QR_ENABLE_LOGS
		QR_Trace(SInit, ("retriggerWatchdog(): H8 access is disabled!"));
#endif
		retVal = H8_DISABLED;
	}
	
	return retVal;
}

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
int H8::setMinBrightness(unsigned int minBrightness)
{
	int retVal;
	
	if (enabled) {
		if (fd > 0) {
			// Value should not be greater than 255
			if (minBrightness > 255) {
				minBrightness = 255;
			}
#ifdef INC90	
			if ((retVal = rcv_0_command_1(fd, 12, minBrightness)) == NAK) {
				retVal = rcv_0_command_1(fd, 12, minBrightness);
			}
			if (stringType == retVal) {
				retVal = H8_SUCCESS;
			}
			else {
				retVal = H8_WRITE_ERROR;
			}			
#else
			// Define H8 command for setting the minimum brightness
			QString cmd = QString("!#12,%1\x0D").arg(minBrightness);
			
			// Send H8 command <ESC>#12,p<CR> for setting the minimum brightness
			retVal = sendCommand(cmd);
#endif
		} else {
			retVal = H8_FILE_ERROR;
		}
		
#ifdef QR_ENABLE_LOGS
		// Trace result of H8 operation
		if (retVal == H8_SUCCESS) {
			QR_Trace(SInit, ("setMinBrightness(): Minimum brightness is set to %d", minBrightness));
		} else {
			QR_Trace(SInit, ("setMinBrightness(): Set minimum brightness failed! (Error: %d)", retVal));
		}
#endif
	} else {
#ifdef QR_ENABLE_LOGS
		QR_Trace(SInit, ("setMinBrightness(): H8 access is disabled!"));
#endif
		retVal = H8_DISABLED;
	}
	
	return retVal;
}

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
int H8::setMaxBrightness(unsigned int maxBrightness)
{
	int retVal;
	
	if (enabled) {
		if (fd > 0) {
			// Value should not be greater than 255
			if (maxBrightness > 255) {
				maxBrightness = 255;
			}
#ifdef INC90	
			if ((retVal = rcv_0_command_1(fd, 11, maxBrightness)) == NAK) {
				retVal = rcv_0_command_1(fd, 11, maxBrightness);
			}
			if (stringType == retVal) {
				retVal = H8_SUCCESS;
			}
			else {
				retVal = H8_WRITE_ERROR;
			}				
#else
			// Define H8 command for setting the maximum brightness
			QString cmd = QString("\x1B#11,%1\x0D").arg(maxBrightness);
			
			// Send H8 command <ESC>#11,p<CR> for setting the maximum brightness
			retVal = sendCommand(cmd);
#endif			
		} else {
			retVal = H8_FILE_ERROR;
		}
		
#ifdef QR_ENABLE_LOGS
		// Trace result of H8 operation
		if (retVal == H8_SUCCESS) {
			QR_Trace(SInit, ("setMaxBrightness(): Maximum brightness is set to %d", maxBrightness));
		} else {
			QR_Trace(SInit, ("setMaxBrightness(): Set maximum brightness failed! (Error: %d)", retVal));
		}
#endif
	} else {
#ifdef QR_ENABLE_LOGS
		QR_Trace(SInit, ("setMaxBrightness(): H8 access is disabled!"));
#endif
		retVal = H8_DISABLED;
	}
	
	return retVal;
}

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
int H8::setBrightness(unsigned int brightness)
{
	int retVal;
	
	if (enabled) {
		if (fd > 0) {
			// Value should not be greater than 255
			if (brightness > 255) {
				brightness = 255;
			}
#ifdef INC90
			if ((retVal = rcv_0_command_1(fd, 34, brightness)) == NAK) {
				retVal = rcv_0_command_1(fd, 34, brightness);
			}
			if (stringType == retVal) {
				retVal = H8_SUCCESS;
			}
			else {
				retVal = H8_WRITE_ERROR;
			}			
#else
			// Define H8 command for setting the brightness
			QString cmd = QString("\x1B#34,%1\x0D").arg(brightness);
			
			// Send H8 command <ESC>#34,p<CR> for setting the brightness
			retVal = sendCommand(cmd);
#endif		
		} else {
			retVal = H8_FILE_ERROR;
		}
		
#ifdef QR_ENABLE_LOGS
		// Trace result of H8 operation
		if (retVal == H8_SUCCESS) {
			switch (brightness) {
				case 0:
					QR_Trace(SInit, ("setBrightness(): Automatic brightness"));
					break;
				case 1:
					QR_Trace(SInit, ("setBrightness(): LCD off"));
					break;
				default:
					QR_Trace(SInit, ("setBrightness(): Brightness is set to %d manually", brightness));
			}
		} else {
			QR_Trace(SInit, ("setBrightness(): Set brightness failed! (Error: %d)", retVal));
		}
#endif
	} else {
#ifdef QR_ENABLE_LOGS
		QR_Trace(SInit, ("setBrightness(): H8 access is disabled!"));
#endif
		retVal = H8_DISABLED;
	}
	
	return retVal;
}

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
int H8::setBrightnessOffset(int brightnessOffset)
{
	int retVal;
	
	if (enabled) {
		if (fd > 0) {
			// Value should not be greater than 255
			if (brightnessOffset > 255) {
				brightnessOffset = 255;
			}
			
			// Value should not be less than -255
			if (brightnessOffset < -255) {
				brightnessOffset = -255;
			}
#ifdef INC90
			if ((retVal = rcv_0_command_1(fd, 10, brightnessOffset)) == NAK) {
				retVal = rcv_0_command_1(fd, 10, brightnessOffset);
			}
			if (stringType == retVal) {
				retVal = H8_SUCCESS;
			}
			else {
				retVal = H8_WRITE_ERROR;
			}			
#else
			// Define H8 command for setting the brightness offset
			QString cmd = QString("\x1B#10,%1\x0D").arg(brightnessOffset);
			
			// Send H8 command <ESC>#10,p<CR> for setting the brightness offset
			retVal = sendCommand(cmd);
#endif					
		} else {
			retVal = H8_FILE_ERROR;
		}
		
#ifdef QR_ENABLE_LOGS
		// Trace result of H8 operation
		if (retVal == H8_SUCCESS) {
			QR_Trace(SInit, ("setBrightnessOffset(): Brightness offset is set to %d", brightnessOffset));
		} else {
			QR_Trace(SInit, ("setBrightnessOffset(): Set brightness offset failed! (Error: %d)", retVal));
		}
#endif
	} else {
#ifdef QR_ENABLE_LOGS
		QR_Trace(SInit, ("setBrightnessOffset(): H8 access is disabled!"));
#endif
		retVal = H8_DISABLED;
	}
	
	return retVal;
}

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
int H8::setBrightnessAxisSection(int brightnessAxis)
{
	int retVal;
	
	if (enabled) {
		if (fd > 0) {
			// Value should not be greater than 255
			if (brightnessAxis > 255) {
				brightnessAxis = 255;
			}
			
			// Value should not be less than -255
			if (brightnessAxis < -255) {
				brightnessAxis = -255;
			}
#ifdef INC90
			if ((retVal = rcv_0_command_1(fd, 16, brightnessAxis)) == NAK) {
				retVal = rcv_0_command_1(fd, 16, brightnessAxis);
			}
			if (stringType == retVal) {
				retVal = H8_SUCCESS;
			}
			else {
				retVal = H8_WRITE_ERROR;
			}			
#else
			// Define H8 command for setting the brightness axis section
			QString cmd = QString("\x1B#16,%1\x0D").arg(brightnessAxis);
			
			// Send H8 command <ESC>#16,p<CR> for setting the brightness axis section
			retVal = sendCommand(cmd);
#endif			
		} else {
			retVal = H8_FILE_ERROR;
		}
		
#ifdef QR_ENABLE_LOGS
		// Trace result of H8 operation
		if (retVal == H8_SUCCESS) {
			QR_Trace(SInit, ("setBrightnessAxisSection(): Brightness control axis segment is set to %d", brightnessAxis));
		} else {
			QR_Trace(SInit, ("setBrightnessAxisSection(): Set brightness control axis segment failed! (Error: %d)", retVal));
		}
#endif
	} else {
#ifdef QR_ENABLE_LOGS
		QR_Trace(SInit, ("setBrightnessAxisSection(): H8 access is disabled!"));
#endif
		retVal = H8_DISABLED;
	}
	
	return retVal;
}

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
int H8::setBrightnessPositiveReactionRate(unsigned int posReactionRate)
{
	int retVal;
	
	if (enabled) {
		if (fd > 0) {
			// Value should not be greater than 100
			if (posReactionRate > 100) {
				posReactionRate = 100;
			}
			
			// Value should not be less than 1
			if (posReactionRate < 1) {
				posReactionRate = 1;
			}
#ifdef INC90
			if ((retVal = rcv_0_command_1(fd, 14, posReactionRate)) == NAK) {
				retVal = rcv_0_command_1(fd, 14, posReactionRate);
			}
			if (stringType == retVal) {
				retVal = H8_SUCCESS;
			}
			else {
				retVal = H8_WRITE_ERROR;
			}			
#else
			// Define H8 command for setting the brightness positive reaction rate
			QString cmd = QString("\x1B#14,%1\x0D").arg(posReactionRate);
			
			// Send H8 command <ESC>#14,p<CR> for setting the brightness positive reaction rate
			retVal = sendCommand(cmd);
#endif			
		} else {
			retVal = H8_FILE_ERROR;
		}
		
#ifdef QR_ENABLE_LOGS
		// Trace result of H8 operation
		if (retVal == H8_SUCCESS) {
			QR_Trace(SInit, ("setBrightnessPositiveReactionRate(): Brightness positive reaction rate is set to %d", posReactionRate));
		} else {
			QR_Trace(SInit, ("setBrightnessPositiveReactionRate(): Set brightness positive reaction rate failed! (Error: %d)", retVal));
		}
#endif
	} else {
#ifdef QR_ENABLE_LOGS
		QR_Trace(SInit, ("setBrightnessPositiveReactionRate(): H8 access is disabled!"));
#endif
		retVal = H8_DISABLED;
	}
	
	return retVal;
}

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
int H8::setBrightnessNegativeReactionRate(unsigned int negReactionRate)
{
	int retVal;
	
	if (enabled) {
		if (fd > 0) {
			// Value should not be greater than 100
			if (negReactionRate > 100) {
				negReactionRate = 100;
			}
			
			// Value should not be less than 1
			if (negReactionRate < 1) {
				negReactionRate = 1;
			}
#ifdef INC90
			if ((retVal = rcv_0_command_1(fd, 15, negReactionRate)) == NAK) {
				retVal = rcv_0_command_1(fd, 15, negReactionRate);
			}
			if (stringType == retVal) {
				retVal = H8_SUCCESS;
			}
			else {
				retVal = H8_WRITE_ERROR;
			}			
#else
			// Define H8 command for setting the brightness negative reaction rate
			QString cmd = QString("\x1B#15,%1\x0D").arg(negReactionRate);
			
			// Send H8 command <ESC>#15,p<CR> for setting the brightness negative reaction rate
			retVal = sendCommand(cmd);
#endif				
		} else {
			retVal = H8_FILE_ERROR;
		}
		
#ifdef QR_ENABLE_LOGS
		// Trace result of H8 operation
		if (retVal == H8_SUCCESS) {
			QR_Trace(SInit, ("setBrightnessNegativeReactionRate(): Brightness negative reaction rate is set to %d", negReactionRate));
		} else {
			QR_Trace(SInit, ("setBrightnessNegativeReactionRate(): Set brightness negative reaction rate failed! (Error: %d)", retVal));
		}
#endif
	} else {
#ifdef QR_ENABLE_LOGS
		QR_Trace(SInit, ("setBrightnessNegativeReactionRate(): H8 access is disabled!"));
#endif
		retVal = H8_DISABLED;
	}
	
	return retVal;
}

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
int H8::setupBuzzer(bool powerUpSound, bool buttonClick, bool beep, bool errorBeep)
{
	int retVal;
	
	if (enabled) {
		if (fd > 0) {
#ifdef INC90
			if ((retVal = rcv_0_command_4(fd, 25, powerUpSound, buttonClick, beep, errorBeep)) == NAK) {
				retVal = rcv_0_command_4(fd, 25, powerUpSound, buttonClick, beep, errorBeep);
			}
			if (stringType == retVal) {
				retVal = H8_SUCCESS;
			}
			else {
				retVal = H8_WRITE_ERROR;
			}			
#else
			// Define H8 command for setting the internal buzzer
			QString cmd = QString("\x1B#25,%1,%2,%3,%4\x0D").arg(powerUpSound).arg(buttonClick).arg(beep).arg(errorBeep);
			
			// Send H8 command <ESC>#25,p1,p2,p3,p4<CR> for setting the internal buzzer
			retVal = sendCommand(cmd);
#endif			
		} else {
			retVal = H8_FILE_ERROR;
		}
		
#ifdef QR_ENABLE_LOGS
		// Trace result of H8 operation
		if (retVal == H8_SUCCESS) {
			QR_Trace(SInit, ("setupBuzzer(): Setup buzzer: Power up sound %s; Button click %s; Beep %s; Error beep %s", powerUpSound ? "on" : "off", buttonClick ? "on" : "off", beep ? "on" : "off", errorBeep ? "on" : "off"));
		} else {
			QR_Trace(SInit, ("setupBuzzer(): Setup buzzer failed! (Error: %d)", retVal));
		}
#endif
	} else {
#ifdef QR_ENABLE_LOGS
		QR_Trace(SInit, ("setupBuzzer(): H8 access is disabled!"));
#endif
		retVal = H8_DISABLED;
	}
	
	return retVal;
}

int H8::activBuzzer(unsigned int ifrequency, unsigned int ilength)
{
	int retVal;
	
	if (enabled) {
		if (fd > 0) {
			if (ifrequency < 30) {
				ifrequency = 30;
			}
			else if (ifrequency > 500) {
				ifrequency = 500;
			}
			if (ilength < 1) {
				ilength = 1;
			}
			else if (ilength > 999) {
				ilength = 999;
			}				
#ifdef INC90	
			if ((retVal = rcv_0_command_2(fd, 22, ifrequency, ilength)) == NAK) {
				retVal = rcv_0_command_2(fd, 22, ifrequency, ilength);
			}
			if (stringType == retVal) {
				retVal = H8_SUCCESS;
			}
			else {
				retVal = H8_WRITE_ERROR;
			}			
#else
			// Define H8 command for setting the minimum brightness
			QString cmd = QString("!#22,%1,%2\x0D").arg(ifrequency).arg(ilength);
			
			// Send H8 command <ESC>#12,p<CR> for setting the minimum brightness
			retVal = sendCommand(cmd);
#endif
		} else {
			retVal = H8_FILE_ERROR;
		}
		
	} else {
		retVal = H8_DISABLED;
	}
	
	return retVal;
}


/*!
 * \brief	Get the current LCD brightness.
 *
 * This method gets the current LCD brightness.
 *
 * \param	brightness	Pointer for storing the current LCD brightness.
 *
 * \return	Result of operation (see header file for possible return values).
 */
int H8::getBrightness(int* brightness)
{
	int retVal;
	
	if (enabled) {
		if (fd > 0) {
#ifdef INC90
			char result[100];
			QString result1;
			bool ok;
			if ((retVal = rcv_1_command_0(fd, 82, result)) == NAK) {
				retVal = rcv_1_command_0(fd, 82, result);
			}
			if (stringType == retVal) {
				result1 = result;
				*brightness = result1.toInt(&ok);
				if(ok)
					retVal = H8_SUCCESS;
				else
					retVal = H8_PARAM_ERROR;
			}
			else {
				retVal = H8_READ_ERROR;
			}
#else 			
			// Define H8 command for getting the current LCD brightness
			QString cmd("\x1B#82\x0D");
			
			// Send H8 command sequence <ESC>#82<CR> for getting the brightness
			retVal = sendCommand(cmd);
			
			if (retVal == H8_SUCCESS) {
				QString reportSequence;
				
				// Receive H8 report sequence <ACK><SOH>#82,p<CR>
				retVal = receiveReport(reportSequence);
				
				if (retVal == H8_SUCCESS) {
					// Get the current LCD brightness from the report sequence
					retVal = getParameter(reportSequence, brightness);
				}
			}
#endif
		} else {
			retVal = H8_FILE_ERROR;
		}
		
#ifdef QR_ENABLE_LOGS
		// Trace result of H8 operation
		if (retVal == H8_SUCCESS) {
			QR_Trace(SInit, ("getBrightness(): Current LCD brightness is %d", *brightness));
		} else {
			QR_Trace(SInit, ("getBrightness(): Get current LCD brightness failed! (Error: %d)", retVal));
		}
#endif
	} else {
#ifdef QR_ENABLE_LOGS
		QR_Trace(SInit, ("getBrightness(): H8 access is disabled!"));
#endif
		retVal = H8_DISABLED;
	}
	
	return retVal;
}

/*!
 * \brief	Get the software version of the H8 firmware.
 *
 * This method gets the software version of the H8 firmware.
 *
 * \param	swVersion	Pointer for storing the software version.
 *
 * \return	Result of operation (see header file for possible return values).
 */
int H8::getSwVersion(int* majorSwVersion, int* minorSwVersion)
{
	int retVal;
	
	if (enabled) {
		if (fd > 0) {
#ifdef INC90
			char result[100];
			QString result1, result2;
			bool ok;
			if ((retVal = rcv_1_command_0(fd, 80, result)) == NAK) {
				retVal = rcv_1_command_0(fd, 80, result);
			}			
			if (stringType == retVal) {
				result1 = result;
				if (result1.contains('.') != 0) {
					result2 = result1.left(result1.indexOf('.'));
					*majorSwVersion = result2.toInt(&ok);
					if (ok) {
						*majorSwVersion = *majorSwVersion * 10;
						result1 = result1.remove(0, result1.indexOf('.') + 1);
						if (result1.contains('.') != 0) {
							result2 = result1.left(result1.indexOf('.'));
							*majorSwVersion = *majorSwVersion + result2.toInt(&ok);
							if (ok) {
								result1 = result1.remove(0, result1.indexOf('.') + 1);
								*minorSwVersion = result1.toInt(&ok);
								if (ok) 
									retVal = H8_SUCCESS;
								else
									retVal = H8_PARAM_ERROR;								
							}
							else 
								retVal = H8_PARAM_ERROR;
						}
						else {
							*majorSwVersion = *majorSwVersion + result1.toInt(&ok);
							*minorSwVersion = 0;
							if (ok) {
								retVal = H8_SUCCESS;
							}
							else
								retVal = H8_PARAM_ERROR;
						}
					}
					else 
						retVal = H8_PARAM_ERROR;
				}
				else {
					retVal = H8_PARAM_ERROR;
				}
			}
			else {
				retVal = H8_READ_ERROR;
			}
#else
			// Define H8 command for getting the software version of H8
			QString cmd("\x1B#80\x0D");
			
			// Send H8 command sequence <ESC>#80<CR> for getting the software version of H8
			retVal = sendCommand(cmd);
			
			if (retVal == H8_SUCCESS) {
				QString reportSequence;
				
				// Receive H8 report sequence <ACK><SOH>#80,p<CR>
				retVal = receiveReport(reportSequence);
				
				if (retVal == H8_SUCCESS) {
					// Get the software version of the H8 firmware
					retVal = getParameter(reportSequence, swVersion);
				}
			}
#endif
		} else {
			retVal = H8_FILE_ERROR;
		}
		
#ifdef QR_ENABLE_LOGS
		// Trace result of H8 operation
		if (retVal == H8_SUCCESS) {
			QR_Trace(SInit, ("getSwVersion(): SW version is %d", *swVersion));
		} else {
			QR_Trace(SInit, ("getSwVersion(): Get SW version failed! (Error: %d)", retVal));
		}
#endif
	} else {
#ifdef QR_ENABLE_LOGS
		QR_Trace(SInit, ("getSwVersion(): H8 access is disabled!"));
#endif
		retVal = H8_DISABLED;
	}
	
	return retVal;
}

/*!
 * \brief	Get the board number.
 *
 * This method gets the board number which can be used for hardware identification purposes.
 *
 * \param	boardNumber	Pointer for storing the board number.
 *
 * \return	Result of operation (see header file for possible return values).
 */
int H8::getBoardNumber(int* boardNumber)
{
	int retVal;
	
	if (enabled) {
		if (fd > 0) {

#ifdef INC90
			char result[100];
			QString result1;
			bool ok;
			if ((retVal = rcv_1_command_0(fd, 72, result)) == NAK) {
				retVal = rcv_1_command_0(fd, 72, result);
			}			
			if (stringType == retVal) {
				result1 = result;
				*boardNumber = result1.toInt(&ok);
				if(ok)
					retVal = H8_SUCCESS;
				else
					retVal = H8_PARAM_ERROR;
			}
			else {
				retVal = H8_READ_ERROR;
			}			
#else 
			// Define H8 command for getting the board number
			QString cmd("\x1B#72\x0D");
			
			// Send H8 command sequence <ESC>#72<CR> for getting the board number
			retVal = sendCommand(cmd);
			
			if (retVal == H8_SUCCESS) {
				QString reportSequence;
				
				// Receive H8 report sequence <ACK><SOH>#72,p<CR>
				retVal = receiveReport(reportSequence);
				
				if (retVal == H8_SUCCESS) {
					// Get the board number
					retVal = getParameter(reportSequence, boardNumber);
				}
			}
#endif
		} else {
			retVal = H8_FILE_ERROR;
		}
		
#ifdef QR_ENABLE_LOGS
		// Trace result of H8 operation
		if (retVal == H8_SUCCESS) {
			QR_Trace(SInit, ("getBoardNumber(): Board number is %d", *boardNumber));
		} else {
			QR_Trace(SInit, ("getBoardNumber(): Get board number failed! (Error: %d)", retVal));
		}
#endif
	} else {
#ifdef QR_ENABLE_LOGS
		QR_Trace(SInit, ("getBoardNumber(): H8 access is disabled!"));
#endif
		retVal = H8_DISABLED;
	}
	
	return retVal;
}

/*!
 * \brief	Get the panel type.
 *
 * This method gets the panel type which identifies the softkeys configuration.
 *
 * \param	panelType	Pointer for storing the panel type.
 *
 * \return	Result of operation (see header file for possible return values).
 */
int H8::getPanelType(int* panelType)
{
	int retVal;
	
	if (enabled) {

		if (fd > 0) {
#ifdef INC90
	// No this command in inc90
	retVal = H8_SUCCESS;
	*panelType = 0;
#else
			// Define H8 command for getting the panel type
			QString cmd("\x1B#70\x0D");
			
			// Send H8 command sequence <ESC>#70<CR> for getting the panel type
			retVal = sendCommand(cmd);
			
			if (retVal == H8_SUCCESS) {
				QString reportSequence;
				
				// Receive H8 report sequence <ACK><SOH>#70,p<CR>
				retVal = receiveReport(reportSequence);
				
				if (retVal == H8_SUCCESS) {
					// Get the panel type
					retVal = getParameter(reportSequence, panelType);
				}
			}
#endif
		} else {
			retVal = H8_FILE_ERROR;
		}
		
#ifdef QR_ENABLE_LOGS
		// Trace result of H8 operation
		if (retVal == H8_SUCCESS) {
			QR_Trace(SInit, ("getPanelType(): Panel type is %d", *panelType));
		} else {
			QR_Trace(SInit, ("getPanelType(): Get panel type failed! (Error: %d)", retVal));
		}
#endif
	} else {
#ifdef QR_ENABLE_LOGS
		QR_Trace(SInit, ("getPanelType(): H8 access is disabled!"));
#endif
		retVal = H8_DISABLED;
	}
	
	return retVal;
}

/*!
 * \brief	Get the device inside temperature.
 *
 * This method gets the current device inside temperature.
 *
 * \param	temperature	Pointer for storing the inside temperature.
 *
 * \return	Result of operation (see header file for possible return values).
 */
int H8::getDeviceTemperature(int* temperature)
{
	int retVal;
	
	if (enabled) {
		if (fd > 0) {
#ifdef INC90
			char result[100];
			QString result1;
			bool ok;
			if ((retVal = rcv_1_command_0(fd, 86, result)) == NAK) {
				retVal = rcv_1_command_0(fd, 86, result);
			}
			if (stringType == retVal) {			
				result1 = result;
				if('+' == result1[0] && 'G' == result1[result1.length() - 1]) {
					result1.remove(result1.length() - 1, 1);
					result1.remove(0, 1);
					*temperature = result1.toInt(&ok);
					if(ok)
						retVal = H8_SUCCESS;
					else
						retVal = H8_PARAM_ERROR;
				}
				
			}
			else {
				retVal = H8_READ_ERROR;
			}			
#else 			
			// Define H8 command for getting the device inside temperature
			QString cmd("\x1B#86\x0D");
			
			// Send H8 command sequence <ESC>#86<CR> for getting the device inside temperature
			retVal = sendCommand(cmd);
			
			if (retVal == H8_SUCCESS) {
				QString reportSequence;
				
				// Receive H8 report sequence <ACK><SOH>#86,p<CR>
				retVal = receiveReport(reportSequence);
				
				if (retVal == H8_SUCCESS) {
					// Get the device inside temperature
					retVal = getParameter(reportSequence, temperature);
				}
			}
#endif
		} else {
			retVal = H8_FILE_ERROR;
		}
		
#ifdef QR_ENABLE_LOGS
		// Trace result of H8 operation
		if (retVal == H8_SUCCESS) {
			QR_Trace(SInit, ("getDeviceTemperature(): Device inside temperature is %d", *temperature));
		} else {
			QR_Trace(SInit, ("getDeviceTemperature(): Get device inside temperature failed! (Error: %d)", retVal));
		}
#endif
	} else {
#ifdef QR_ENABLE_LOGS
		QR_Trace(SInit, ("getDeviceTemperature(): H8 access is disabled!"));
#endif
		retVal = H8_DISABLED;
	}
	
	return retVal;
}

int H8::getTemperatureLevel(QString& level)
{
		int retVal;
		
		if (enabled) {
			if (fd > 0) {
	
				char result[100];
				bool ok;
				if ((retVal = rcv_1_command_0(fd, 174, result)) == NAK) {
					retVal = rcv_1_command_0(fd, 174, result);
				}			
				if (stringType == retVal) {
					level = result;
					retVal = H8_SUCCESS;
				}
				else {
					retVal = H8_READ_ERROR;
				}			
			} else {
				retVal = H8_FILE_ERROR;
			}
			
		} else {
			retVal = H8_DISABLED;
		}
		
		return retVal;

}

/*!
 * \brief	Enable or disable the backlight.
 *
 * This method enables or disables the backlight.
 *
 * \param	enable	True for enable the backlight otherwise false.
 *
 * \return	Result of operation (see header file for possible return values).
 */
int H8::enableBacklight(bool enable)
{
	int retVal;

#ifdef INC90
	static int currentBrightness = 200;
#endif
	
	if (enabled) {
		if (fd > 0) {
#ifdef INC90
			if ((retVal = rcv_0_command_1(fd, 2, enable)) == NAK) {
				retVal = rcv_0_command_1(fd, 2, enable);
			}
			if (stringType == retVal) {
				retVal = H8_SUCCESS;
			}
			else {
				retVal = H8_WRITE_ERROR;
			}				
#else
			// Define H8 command for enable/disable the backlight
			QString cmd = QString("\x1B#02,%1\x0D").arg(enable);
			
			// Send H8 command <ESC>#02,p<CR> for enable/disable the backlight
			retVal = sendCommand(cmd);
#endif
		} else {
			retVal = H8_FILE_ERROR;
		}
		
#ifdef QR_ENABLE_LOGS
		// Trace result of H8 operation
		if (retVal == H8_SUCCESS) {
			QR_Trace(SInit, ("enableBacklight(): Backlight is %s", enable ? "ON" : "OFF"));
		} else {
			QR_Trace(SInit, ("enableBacklight(): Enable or disable backlight failed! (Error: %d)", retVal));
		}
#endif
	} else {
#ifdef QR_ENABLE_LOGS
		QR_Trace(SInit, ("enableBacklight(): H8 access is disabled!"));
#endif
		retVal = H8_DISABLED;
	}
	return retVal;
}

/*!
 * \brief	Enable or disable the front panel keys.
 *
 * This method enables or disables the front panel keys.
 *
 * \param	enable	True for enable the front panel keys otherwise false.
 *
 * \return	Result of operation (see header file for possible return values).
 */
int H8::enableFrontPanelKeys(bool enable)
{
	int retVal;
	
	if (enabled) {
		if (fd > 0) {
#ifdef INC90
			if ((retVal = rcv_0_command_1(fd, 20, enable)) == NAK) {
				retVal = rcv_0_command_1(fd, 20, enable);
			}
			if (stringType == retVal) {
				retVal = H8_SUCCESS;
			}
			else {
				retVal = H8_WRITE_ERROR;
			}				
#else
			// Define H8 command for enable/disable the front panel keys
			QString cmd = QString("\x1B#20,%1\x0D").arg(enable);
			
			// Send H8 command <ESC>#20,p<CR> for enable/disable the front panel keys
			retVal = sendCommand(cmd);
#endif		
		} else {
			retVal = H8_FILE_ERROR;
		}
		
#ifdef QR_ENABLE_LOGS
		// Trace result of H8 operation
		if (retVal == H8_SUCCESS) {
			QR_Trace(SInit, ("enableFrontPanelKeys(): Front panel keys are %s", enable ? "ON" : "OFF"));
		} else {
			QR_Trace(SInit, ("enableFrontPanelKeys(): Enable or disable front panel keys failed! (Error: %d)", retVal));
		}
#endif
	} else {
#ifdef QR_ENABLE_LOGS
		QR_Trace(SInit, ("enableFrontPanelKeys(): H8 access is disabled!"));
#endif
		retVal = H8_DISABLED;
	}
	
	return retVal;
}

/*!
 * \brief	Save current settings to H8 EEPROM.
 *
 * This method saves the current settings to H8 EEPROM..
 *
 * \return	Result of operation (see header file for possible return values).
 */
int H8::saveCurrentSettings()
{
	int retVal;
	
	if (enabled) {
		if (fd > 0) {
#ifdef INC90
			if ((retVal = rcv_0_command_0(fd, 50)) == NAK) {
				retVal = rcv_0_command_0(fd, 50);
			}
			if (stringType == retVal) {
				retVal = H8_SUCCESS;
			}
			else {
				retVal = H8_WRITE_ERROR;
			}			
#else
			// Define H8 command for saving the current settings
			QString cmd = QString("\x1B#50\x0D");
			
			// Send H8 command <ESC>#50<CR> for saving the current settings
			retVal = sendCommand(cmd);
#endif
		} else {
			retVal = H8_FILE_ERROR;
		}
		
#ifdef QR_ENABLE_LOGS
		// Trace result of H8 operation
		if (retVal == H8_SUCCESS) {
			QR_Trace(SInit, ("saveCurrentSettings(): Current setting are saved"));
		} else {
			QR_Trace(SInit, ("saveCurrentSettings(): Save current settings failed! (Error: %d)", retVal));
		}
#endif
	} else {
#ifdef QR_ENABLE_LOGS
		QR_Trace(SInit, ("saveCurrentSettings(): H8 access is disabled!"));
#endif
		retVal = H8_DISABLED;
	}
	
	return retVal;
}

/*!
 * \brief	The constructor opens the defined COM port on which the H8 is connected to.
 *
 * The constructor opens the defined COM port (e.g. "/dev/ttyS2") on which the H8 is connected to.
 * After that the current COM options will be stored. This options will be restored after closing
 * the COM port in destructor. After storing the current options, new options are set.
 *
 * \param	comPort	COM port (e.g. "/dev/ttyS2") on which the H8 microcontroller is connected to.
 */
H8::H8(const char* comPort, bool enable)
	: enabled(enable)
{
#ifdef QR_ENABLE_LOGS
	QR_Trace(SInit, ("Constructor of H8 (Access is %s; COM port: %s)", enabled ? "enabled" : "disabled", comPort));
#endif


	if (enabled) {
	#ifdef INC90

		fd = open_port();
		if (fd > 0) {
                     #ifdef QR_ENABLE_LOGS
                     		QR_Trace(SInit, ("Connected to H8 successfully"));
                     #endif			
                     	}
                     	else {
                     #ifdef QR_ENABLE_LOGS
                     		QR_Trace(SInit, ("Cannot connect to H8!!"));
                     #endif
		}
	#else			
		// Open port COM3
		fd = open(comPort, O_RDWR | O_NOCTTY | O_NDELAY);
		
		if (fd > 0) {
		
			fcntl(fd, F_SETFL, O_ASYNC);
			
			// Save the actual port settings
			tcgetattr(fd, &oldOptions);
			
			// Copy the port settings
			newOptions = oldOptions;

			// Set the port speed
			cfsetispeed(&newOptions, B9600);
			cfsetospeed(&newOptions, B9600);
			
			// Enable the receiver and set local mode
			newOptions.c_cflag |= (CLOCAL | CREAD);
			
			// 8N1
			newOptions.c_cflag &= ~PARENB; // no parity
			newOptions.c_cflag &= ~CSTOPB; // one stop bit only
			newOptions.c_cflag &= ~CSIZE;  // mast the character size bits
			newOptions.c_cflag |= CS8;     // select 8 data bits
			
			// Disable hardware flow control
			newOptions.c_cflag &= ~CRTSCTS;
			
			// Disable XON-XOFF protocol
			newOptions.c_iflag &= ~(IXON | IXOFF | IXANY);
			
			newOptions.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG );
			newOptions.c_oflag &= ~OPOST;
			
			// Set the new port settings
			tcsetattr(fd, TCSANOW, &newOptions);
		
			
#ifdef QR_ENABLE_LOGS
			QR_Trace(SInit, ("Connected to H8 successfully"));
#endif
		} else {
#ifdef QR_ENABLE_LOGS
			QR_Trace(SInit, ("Cannot connect to H8!!"));
#endif
		}
	#endif
	} else {
#ifdef QR_ENABLE_LOGS
		QR_Trace(SInit, ("H8 access is disabled!!"));
#endif
	}
}

/*!
 * \brief	The destructor closes the COM port.
 *
 * The destructor restores the old port settings and closes the COM port.
 */
H8::~H8()
{
#ifdef QR_ENABLE_LOGS
	QR_Trace(SInit, ("Destructor of H8"));
#endif

	if (enabled) {
		if (fd > 0) {
	#ifdef INC90
		closePort(fd);
	#else
			// Restore the old port settings
			tcsetattr(fd, TCSANOW, &oldOptions);
			
			// Close port COM3
			close(fd);
	#endif			
	#ifdef QR_ENABLE_LOGS
			QR_Trace(SInit, ("Disconnect from H8"));
	#endif
		} else {
	#ifdef QR_ENABLE_LOGS
			QR_Trace(SInit, ("Cannot disconnect from H8!!"));
	#endif
		}
	} else {
	#ifdef QR_ENABLE_LOGS
		QR_Trace(SInit, ("H8 access is disabled!!"));
	#endif
	}
}

/*!
 * \brief	Send the command sequence to H8 microcontroller.
 *
 * This method sends the command sequence to the H8 microcontroller.
 *
 * \param	commandSequence	H8 command sequence.
 *
 * \return	Result of operation (see header file for possible return values).
 */
int H8::sendCommand(QString& commandSequence)
{
	int retVal;
	
	if (fd > 0) {
        if (write(fd, commandSequence.toLatin1(), commandSequence.length()) != commandSequence.length()) {
			retVal = H8_WRITE_ERROR;
		}
		else
			retVal = H8_SUCCESS;
	} else {
		retVal = H8_FILE_ERROR;
	}
	
	return retVal;
}

/*!
 * \brief	Receive the the report sequence from H8 microcontroller.
 *
 * This method receives the report sequence from the H8 microcontroller.
 *
 * \param	reportSequence	H8 report sequence.
 *
 * \return	Result of operation (see header file for possible return values).
 */
int H8::receiveReport(QString& reportSequence)
{
	int retVal;
	
	if (fd > 0) {
		char ch;
		bool record = false;
		
		while (true) {
			// Read the next character
			read(fd, &ch, 1);
			
			// Is the character a SOH?
			if (ch == '\x01') {
				// This charactar is a SOH. Begin to record the
				// characters until a line feed is detected.
				record = true;
			}
			
			if (record) {
				// Add the character to the report sequence
				reportSequence = reportSequence + ch;
			}
			
			// Is the character a line feed?
			if (ch == '\x0A') {
				// This charactar is a line feed. Stop to record the
				// characters and leave the loop.
				break;
			}
		}
		retVal = H8_SUCCESS;
	} else {
		retVal = H8_FILE_ERROR;
	}
	
	return retVal;
}

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
int H8::getParameter(QString& reportSequence, int* param)
{
	int retVal;
	bool ok;
	
	// Get the start position of the parameter within the report sequence
	int start = reportSequence.indexOf('\x2C') + 1;
	
	// Get the end position of the parameter within the report sequence
	int end = reportSequence.indexOf('\x0A', start);

#ifdef QR_ENABLE_LOGS
	QR_Trace(SInit, ("getParameter(): size is %d \n", reportSequence.length()));
	QR_Trace(SInit, ("getParameter(): reportSequence is %s", reportSequence.ascii()));
#endif

	// Get the parameter from the report sequence as string
	QString strParam = reportSequence.mid(start, end);
	
	// Get the parameter string as number
	*param = strParam.toInt(&ok);
	
	if (ok) {
		retVal = H8_SUCCESS;
	} else {
		// Workaround for device inside temperature
		if (strParam.length() > 1) {
			// Remove the two characters at the end.
			// ('G\n' for device inside temperature)
			strParam = strParam.remove(strParam.length() - 2, 2);
		
			// Get the parameter string as number
			*param = strParam.toInt(&ok);
			
			if (ok) {
				retVal = H8_SUCCESS;
			} else {
#ifdef QR_ENABLE_LOGS
				QR_Trace(SInit, ("getParameter(): Parameter error! Parameter is %s", strParam.ascii()));
#endif
				retVal = H8_PARAM_ERROR;
			}
		} else {
			retVal = H8_PARAM_ERROR;
		}
	}
	
	return retVal;
}
