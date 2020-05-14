# PSIPro Version 1.6 - Released May 13th 2020

## Author
Written by Neil Hutchison

## Thanks
Main sequence transitions by Krijn Schaap, based on his PSI sketch.  Many thanks Krijn.

Pattern Timing Tuning by Malcolm MacKenzie

Thanks to Malcolm (Maxstang) for the boards, support, testing and encouragement.

## Version History

    *  Version 1.6 - 14th May 2020
         * Fixes for the Valid PSI address checks in the T command
         *  Check for a valid pattern number, and ignore if the pattern does not match a known pattern.
              Continue running the current pattern with the current timings.

    *  Version 1.5 - 13th May 2020
         * Added a check in the T command processing to prevent settig the global timing parameters
           if the command is not addressed to a PSI (address 0,4,5)

    *  Version 1.3 - 21st April 2020
         * Minor fix for timing in Imperial March.

    *  Version 1.2 -  16th April 2020
	 * Correct comment typos
	 * Always on was actually only on for 17 min. Changed to +4 hrs.
	 * Change Star Wars Intro
		
	*  Version 1.1 - 13th April 2020
     * Fixed a bug in the Rebel pattern where it would blink the first time a timing command was given
	    Subsequent calls to Rebel with timing supplied worked
     * Explicitly check in Fade Out and Lightsaber Battle for a timing parameter supplied and ignore it
     * All CRGB:White changed to CRGB:Grey to reduce power consumption of the panel
     * Max Brightness allowed upped to 200 from 175
     * Renamed the Sketch to match the git repo

     *  Version 1.0 - 11th April 2020
	* Added 3Pyy command to set brightness without saving to EEPROM
	* Limit the Max LED Brightness to 175 to preserve the LED Life.
   
    * Version 0.99_5 - 10th April 2020
	* Renamed USB_DEBUG to USB_SERIAL

    * Version 0.99_4 - 9th April 2020
        * Fixed the Command line setting for per pattern timeout that was added
            * Timings over 32 seconds did not work
            * To set the pattern as "always On" Set the timing parameter to 256 which will
            * run the pattern for 16 hours - I'll call that good enough for always on!
         *  Added Firmware Average for the POT readings.  This works around the issue of not 
             having a capacitor on the POT.

    *  Version 0.98 - 8th April 2020
       *  Added the ability for each sequence to run for a given time.
           * Rather than try to set the time a pattern runs for by setting the loops, you can
           * specify the total time the pattern should run for.  To disable the total run time
           * and use a set number of loops, set the run time parameter to 0.
       *  Added the ability to set the command duration in seconds via the command.
           * This only applies to T commands.  
           * Send the command using 0Tx|y where |y is optional.  y is in seconds.

    *  Version 0.97 - 7th April 2020
        *  Added ability to set Disco Ball and VU Meter on indefinitely.
            * Mode 13 is the new Always on Disco Ball
            * Mode 12 is the timed Disco Ball 
            * Mode 92 is VU Meter (always on) to match Logic commanding
            * Mode 21 is VU Meter timed
        *  Restored the fast switch between USB Serial and Tx/Rx Pin Serial

    *  Version 0.96 - 5th April 2020
        *  Added address checking for T commands
        *  0 is all
        *  4 is Front PSI
        *  5 is rear PSI as taken from Marc's Teeces command guide.

        * Address field is interpreted as follows:
            * 0 - global address, all displays that support the command are set
            * 1 - TFLD (Top Front Logic Dislay)
            * 2 - BFLD (Bottom Front Logic Display)
            * 3 - RLD  (Rear Logic Display)
            * 4 - Front PSI
            * 5 - Rear PSI
            * 6 - Front Holo (not implemented here)
            * 7 - Rear Holo  (not implemented here)
            * 8 - Top Holo   (not implemented here)

    *  Version 0.9.5 - 5th April 2020
        *  Star Wars scrolling text sequence added
        *  Minor bug fixes

    *  Version 0.94 - 4th April 2020
        *  Comments cleanup and clarification
        *  More timing tweaks
        *  Work around added for serial difficulties with non Sparkfun Pro Micro

    *  Version 0.93 - 1st April 2020 (Happy April Fools Day!)
        *  Code cleanup, and code size reduction
        *  Timing tweaks from Malcolm for various sequences.
        *  Updated JawaLite To support A, D and P (P used to change always on mode)
        *  T1 (Swipe) is now the default sequence, as MarcDuino sends 0T1 on startup.
        *  Added the ability to set the default pattern in the config.h  
        *      Note that MarcDuino will send 0T1, so whatever is in Mode 1 will be the starting pattern.
        *      After that point when a sequence completes, it will restore the "defaultPattern" 
        *      as defined in config.h
        *  EEPROM Support added to store various global settings:
        *      alwaysOn config
        *      Internal or External POT use
        *      Internal brightness setting if using Internal Brightness value (1P1 was sent)
        *  Fixed a bug in the VU Meter Sequence.

    *  Version 0.8 - 31st March 2020
        *  Added Lightsaber Battle animation
        *  Added Pulse for rear logic dsiplay on T9
        *  Updated JawaLite Commanding on Serial to be 0Txx format
        *  Added the ability to change the serial port by defining USB_DEBUG.  
        *    Uncomment #define USB_DEBUG for serial communications using Tx and Rx (removed again)
        *  Set the default behavior for unrecognized commands to just keep running the swipe pattern.
        *  Configuration data moved to config.h rather than being scattered.

    *  Version 0.7 - 30th March 2020
        *  Non-Delay version of code.
        *  Allows sequences to be interrupted at ay time.
        *  Waiting for sequence completion is no longer required
        *  Set the default brightness in setup from the Brightness POT

    *  Version 0.6 - 29th March 2020
        *  Base versions of most sequences implemented
        *  Support for Front/Rear color selection using Jumper implemented
        *  Brightness Pot implemented

## Sketch Details

This sketch is provided to control MaxStang's PSI Pro. Details on operation and setup will be provided here.

Basic Operation



  
  
                                  ***************************   
                                  ********* WARNING *********
                                  ***************************
                                        
           This PSI CAN DRAW MORE POWER THAN YOUR COMPUTER'S USB PORT CAN SUPPLY!! 
      
      When using the USB connection on the Pro Micro to power the PSI (during programming 
      for instance) be sure to have the brightness POT turned nearly all the way COUNTERCLOCKWISE.  
      Having the POT turned up too far when plugged into USB can damage the Pro Micro and/or your 
      computer's USB port!!!! If you are using the internal brightness control and are connected 
      to USB, KEEP THIS VALUE LOW, not higher than 20. The Pro Micro can also be removed from the 
      PSI and programmed separately. 


ESD SAFETY

Like any sensitive piece of electronics, the PSI Pro Connected can be damaged by static discharge.  Before touching the PSI, be sure to ground yourself.  

SET UP

The PSI Pro Connected comes assembled and preprogrammed with standard front and rear PSI colors.  

DEFAULT COLORS

Placing the the included jumper on the Front/Back header on the back of the PSI will change the colors from red/blue to green/yellow.

BRIGHTNESS ADJUSTMENT

Brightness may be adjusted manually by turning the potentiometer on the back of the PSI. Take care not to force the potentiometer more than a single turn. DO NOT TURN THE BRIGHTNESS UP WHEN POWERING THE PSI THROUGH THE USB PORT ON THE PRO MICRO. Doing so may damage the Pro Micro.  Brightness may also be adjusted via software commands. See below. 

POWERING THE PSI PRO

The PSI Pro requires a regulated 5 volt power supply of at least 500mA.  IT may be powered through any one of the +5v input headers on the back of the PSI.  If powering the PSI Pro through a serial or I2c device chain, be sure the chain can supply at least 500mA to the PSI Pro.  The PSI can be temporarily powered during programming or testing through the USB port on the Pro Mini, but only with the brightness set to low.   

The PSI will default to Mode 1 (SWIPE), with default colors and timings when powered on. Colors and timings may be customized by changing settings in the config.h tab of the PSI Pro Connected sketch (see below). 

 

COMMANDS AND COMMAND STRUCTURE 

The PSI Pro's display Mode can be changed by sending JawaLite commands via serial or I2c.
          
  
  
   Supported JAWALite Commands via Serial or i2c:
 
   Serial:
 
   Command T - Trigger a numbered Mode.  Txx where xx is the pattern number below. When using the R2 Touch app, commands
               should be in the form @0Tx\r or @0Txx\r. Please see below for address information for the T command. 
               
               The Optional time parameter can be sent by adding |yy to the T command.  Commands should be in the form
               @0Tx|y.  y is a value in seconds.
   
   Command A - Go to Main mode of operation which is Standard Swipe Pattern.
               @0A from R2 Touch
   
   Command D - Go to Default mode which is the Standard Swipe Pattern.
               @0D from R2 Touch
   
   Command xPy - Sets various board parameters.
                 If x is 0, Set the alwaysOn behavior of the panel
                   The default mode for the panel is to display command sequences for 
                   a given time, then revert to the default pattern.  
                   By sending the xPy command, this can be changed.
                   Y is either 0 or 1 (default or always on mode)
                   0P0 - Default mode, where default pattern is restored after the sequence plays
                   0P1 - The sequence continues to play until a new comand is received.
				   
                 If x is 1, Set the POT mode
                   The default is to read the external POT value for setting brightness
                   Y is either 0 or 1 (Pot or internal setting)
                   1P0 - Default mode, uses the external POT to set the LED brightness
                   1P1 - Use the internal brightness, which is set using command 2Py below
                   
                 If x is 2, Set the internal brightness value, overriding the POT.
                   The default setting is that brightness is 20.
                   Y is a value between 0 (off) and 255 (max brightness) Values over 200 
                   will be limited to 200 to preserve the life of the LEDs.This value
                   is saved to the EPROM and will persist after power down. 
                   for example:  2Py or 2Pyy or 2Pyyy
                   
                 If x is 3, Set the internal brighness value, overriding the POT, but do not save to EEPROM.
                   3P0 will restore the brightness to it's previous value.  If that was POT control, the POT setting
                   will be used, if it was internal brightness, then the previous global internal brightness will be used.
                   3Pyyy will set the brightness in the range 1 to 200.  Values over 200 will be limited to 200 to preserve
                   the life of the LEDs.
                
                @xPy from R2 Touch (You don't need the '0' before the x when using the P command. 
                                           
 
   i2c:
 
   When sending i2c command the Panel Address is defined on the config.h tab to be 22.  The command type and value are needed.  
   To trigger a pattern, send an address (0 for all, 4 for front, 5 for rear) then the character 'T' and the Mode value corresponding 
   to the pattern list below to trigger the corresponding sequence. Sequences must be terminated with a carriage return (\r).  
   
   Using i2c with the R2 Touch app, commands must be sent in hex. For example, &220T6\r would be spelled &22,x33,x54,x36,x0D\r
   
   Commands:
   
   Address modifiers for "T" commands.  The digit preceeding the T is the address:
   
   0 is all
   4 is Front PSI
   5 is Rear PSI as taken from Marc's Teeces command guide.
   
       Address field is interpreted as follows:
       0 - global address, all displays that support the command are set
       1 - TFLD (Top Front Logic Dislay)
       2 - BFLD (Bottom Front Logic Display)
       3 - RLD  (Rear Logic Display)
       4 - Front PSI
       5 - Rear PSI
       6 - Front Holo (not implemented here)
       7 - Rear Holo  (not implemented here)
       8 - Top Holo   (not implemented here)
 
   Command T Modes
	* Sensitivity to flashing lights can be as slow as 3x/second.  
	* e.g. Flash, Alarm, Scream
	* You must be cautious.
 
     Mode 0  - Turn Panel off (This will also turn stop the Teeces if they share the serial connection and the "0" address is used)
     Mode 1  - Default (Swipe) The default mode can be changed on the config.h tab
     Mode 2  - Flash (fast flash) (4 seconds) 
     Mode 3  - Alarm (slow flash) (4 seconds)
     Mode 4  - Short Circuit (10 seconds)
     Mode 5  - Scream (4 seconds)
     Mode 6  - Leia Message (34 seconds)
     Mode 7  - I Heart U (10 seconds)
     Mode 8  - Quarter Panel Sweep (7 seconds)
     Mode 9  - Flashing Red Heart (Front PSI), Pulse Monitor (Rear PSI)
     Mode 10 - Star Wars - Title Scroll (15 seconds)
     Mode 11 - Imperial March (47 seconds)
     Mode 12 - Disco Ball (4 seconds)
     Mode 13 - Disco Ball -Runs Indefinitely
     Mode 14 - Rebel Symbol (5 seconds)
     Mode 15 - Knight Rider (20 seconds)
     Mode 16 - Test Sequence (White on Indefinitely)
     Mode 17 - Red on Indefinitely  
     Mode 18 - Green on Indefinitely
     Mode 19 - LightSaber Battle
     Mode 20 - Star Wars Intro (scrolling yellow "text" getting smaller and dimmer)
     Mode 21 - VU Meter (4 seconds)
     Mode 92 - VU Meter - Runs Indefinitely (Spectrum on Teeces)


SKETCH BASED PSI PRO SETTINGS

	The PSI Pro's default behaviors may be changed by editing the config.h file of the PSI Pro sketch.  


TIMER SETTINGS

	The numbered pattern Modes have various preprogrammed lengths to match those of the Teeces Logic patterns. Some of the additional Modes have 
	indefinite lengths.  To set ALL pattern Modes called using the Mode (T) command to remain on indefinitely, then set 'bool alwaysOn = false;' 
	to true. The default is false, meaning that each selected pattern Mode will remain on for its set time, and then will return to the default 
	pattern Mode. This can also be changed using command P as described above. 

BAUD RATE

	By default, the PSI Pro Connected uses a 2400bps baud rate.  This is due to the Teeces lighting running at this speed.  To change the default 
	speed to a more reasonable 9600bps, uncomment '#define_9600BAUDSJEDI_' in the sketch. 

SETTING THE DEFAULT PATTERN MODE

	The PSI Pro is shipped with Mode 1 (SWIPE) as the default pattern mode, but any display Mode can be the default Mode the PSI returns to after 
	completing a command initiated Mode.  To change the default mode, enter the mode number desired in 'uint8_t defaultPattern = 1;'.


SWIPE MODE SETTINGS

	Colors are divided into 
		Primary (Default is Blue for the front PSI and Green for the Rear) and 
		Secondary (Default is Red for the front PSI and Yellow for the rear).


	The behavior of the default SWIPE mode may be changed by adjusting the following parameters:

	Primary Color Duration Minimum/Maximum

		Choose the maximum and minimum random number of milliseconds the PSI pauses on the Primary color before switching to the secondary color.

		Choose the maximum and minimum random number of milliseconds the PSI pauses on the Secondary color before switching to the secondary color.

		Choose the maximum and minimum random speed range of the swipe animation.

		Define the chance proportion between the various options for the secondary color. Increasing a value compared to the others increases the 
		likelihood of that option occurring. If the chance for an option is set to 0, it will not be occur.

		Choose the maximum and minimum random number of columns to display the secondary color. 
		The remainder of the columns will display the primary color. 

		Choose the number of off (unlit) columns. This enables the 'half dark' PSI as seen in A New Hope. 

		Choose the Primary and Secondary colors for the SWIPE mode.  These may be any RGB combination.  
		Default colors are red/blue and green/yellow. 

		Choose the colors determined by setting the Front/Rear jumper on the back of the PSI Pro. 

SERIAL SETTINGS

	If 'USB_SERIAL' is defined, the serial port on the USB of the Pro Micro will be used for communication, and debug output. Uncomment this if you 
	want to debug, add new patterns etc, and are working via USB.  Note the brightness warning above! The normal mode is that any serial control 
	device (MarcDuino, STEALTH etc) will be connected to the PSI via the header pins on the PSI PCB by default. These pins are referred to as Serial1. 
	Uncommenting 'USB_SERIAL' switches to using the USB port and the Serial on the USB of the Pro Micro instead.

I2C ADDRESS

	By default, the PSI Pro's I2c address is 22.  This can be changed by inserting the desired address in 'byte I2CAdress = 22;'.
	
