# PSIPro Version 0.99 - Released April 9th 2020

## Author
Written by Neil Hutchison

## Thanks
Main sequence transitions by Krijn Schaap, based on his PSI sketch.  Many thanks Krijn.

Pattern Timing Tuning by Malcolm MacKenzie

Thanks to Malcolm (Maxstang) for the boards, support, testing and encouragement.

## Version History

    * Version 0.99 - 9th April 2020
        * Fixed the Command line setting for per pattern timeout that was added yesterday
            * Timings over 32 seconds did not work
            * To set the pattern as "always On" Set the timing parameter to 256 which will
            * run the pattern for 16 hours - I'll call that good enough for always on!

    *  Version 0.98 - 8th April 2020
       *  Added the ability for each sequence to run for a given time.
           * Rather than try to set the time a pattern runs for by setting the loops, you can
           * specify the total time the pattern should run for.  To disable the total run time
           * and use a set number of loops, set the run time parameter to 0.
       *  Added the ability to set the command duration in seconds via the command.
           * This only applies to T commands.  
           * Send the command using 0Tx|y where |y is optional.  y is in seconds.

    *  Version 0.97 - 7th April 2020
        *  Added ability to set Disco Ball and VU Meter on Indefinately.
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
        *    Uncomment #define USB_DEBUG for serial comunications using Tx and Rx (removed again)
        *  Set the default behavior for unrecognised commands to just keep running the swipe pattern.
        *  Configuration data moved to config.h rather than being scattered.

    *  Version 0.7 - 30th March 2020
        *  Non-Delay version of code.
        *  Allows sequences to be interrupted at ay time.
        *  Waiting for sequence completion is no longer required
        *  Set the defauly brightness in setup from the Brightness POT

    *  Version 0.6 - 29th March 2020
        *  Base versions of most sequences implented
        *  Support for Front/Rear color selection using Jumper implemented
        *  Brightness Pot implemented

## Sketch Details

This sketch is provided to control MaxStang's PSI Pro

Details on operation and setup will be provided here.
