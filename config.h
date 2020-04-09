// Use these settings to customize the PSI animations. 
//

// Colors are divded into Primary (Default is Blue for the 
// front PSI and Green for the Rear) and Secondary (Default
// is Red for the front PSI and Yellow for the rear).

// Settings:

// The numberd pattern Modes have various preprogrammed lengths
// to match those of the Teeces Logic patterns. Some of the additional Modes 
// have indefinite lengths.  If you want ALL pattern Modes called using the
// Mode (T) comand to remain on indefinitely, then set 'alwaysOn' below to true. 
// The default is false, meaning that each selected pattern Mode will remain on for 
// its set time, and then will return to the default pattern Mode. This can also
// be changed using command P as described on the main sketch tab.  

bool alwaysOn = false;

// If your JEDI Device can send ay 9600 baud, uncomment this line.
// The Current Teeces interface runs at a mindnumbingly slow 2400 only!
//#define _9600BAUDSJEDI_


///////////////////////////////////////////////////////
///////////// SET DEFAULT PATTERN  ////////////////////
///////////////////////////////////////////////////////

// Any display Mode can be the default Mode the PSI returns to
// after completing a command initiated Mode.  The standard default Mode
// is Swipe.  Use this to set the default Mode number
uint8_t defaultPattern = 1; //Mode 1 is Swipe

// The number of milliseconds pauses on the primary color
// before switching to the secondary color.
// A random value between MINIMUM and MAXIMUM will be used.

#define PRIMARY_COLOR_DURATION_MINIMUM 1000
#define PRIMARY_COLOR_DURATION_MAXIMUM 4000

// Number of milliseconds that the secondary color will be
// visible before switching back to the primary color.
// A random value between MINIMUM and MAXIMUM will be used.

#define SECONDARY_COLOR_DURATION_MINIMUM 4000
#define SECONDARY_COLOR_DURATION_MAXIMUM 10000

// Speed range of the swipe animation. Longer delay means
// slower animation speed. 

#define SWIPE_DELAY_MINIMUM 20
#define SWIPE_DELAY_MAXIMUM 100

// Define the chance proportion between the various options for
// the secondary color. Increasing a value compared to the others increases
// the likelihood of that option occuring. If the chance for an option is 
// set to 0, it will not be selected.

#define CHANCE_SECONDARY_FULL 6
#define CHANCE_SECONDARY_PARTIAL 2
#define CHANCE_SECONDARY_PARTIAL_OFF 6

// How many columns to display the secondary color.

#define SECONDARY_PARTIAL_LINES_MIN 3 //The remainder will be the primary color.
#define SECONDARY_PARTIAL_LINES_MAX 6 //The remainder will be the primary color.
#define SECONDARY_PARTIAL_OFF_LINES 5 //The remainder will be off.

// Use the jumpers on the PSI CPU board to set Font (jumper off)
// or Rear (jumper on)

// Use the folloing settings to adjust the colors for font and rear.

// Set colors for the front PSI.

CRGB frontPrimaryColor = CRGB(0, 0, 255);  // Blue
CRGB frontSecondaryColor = CRGB(255, 0, 0); // Red
CRGB frontSecondaryOffColor = CRGB::Black; // Off

// Colors for the rear PSI
CRGB rearPrimaryColor = CRGB(0, 255, 0);      // Green
CRGB rearSecondaryColor = CRGB(200, 170, 0);  // Yellow
CRGB rearSecondaryOffColor = CRGB::Black; // Off

#define JUMP_FRONT_REAR 14

// Set the colours based on the pin.
CRGB primary_color() {
  if (digitalRead(JUMP_FRONT_REAR)) {
    return frontPrimaryColor;
  } else {
    return rearPrimaryColor;
  }
}

CRGB secondary_color() {
  if (digitalRead(JUMP_FRONT_REAR)) {
    return frontSecondaryColor;
  } else {
    return rearSecondaryColor;
  }
}

CRGB secondary_off_color() {
  if (digitalRead(JUMP_FRONT_REAR)) {
    return frontSecondaryOffColor;
  } else {
    return rearSecondaryOffColor;
  }
}

// This is the pin for the Brighness POT.
#define POT_BRIGHT_PIN 19

/////////////////////////////////////////////
/////////  Assign IC2 Address Below   ///////
/////////////////////////////////////////////
byte I2CAdress = 22;
/////////////////////////////////////////////
/////////////////////////////////////////////



// CHANGED BEYOND THESE LINES SHOULD NOT BE NECESSARY
// 


// This is Neil's personal setup ... probably don't play with this!
//#define NEIL_PERSONAL_DEBUG
#ifdef NEIL_PERSONAL_DEBUG
  #define DEBUG       // Prints Debug Strings to help debugging
  #define USB_DEBUG   // Sets the Serial to use the USB port for sending and receiving commands instead of the TxRx on the board.
#endif
// End Neil's personal setup.

//Setup Debug stuff

// Uncomment this if you want Debug output.
// By default debug output is not enabled in
// the release version
//#define DEBUG

//Setup Debug stuff for Real Arduino Pro Micros
#ifdef DEBUG
    #define DEBUG_PRINT_LN(msg)  serialPort->println(msg)
    #define DEBUG_PRINT(msg)  serialPort->print(msg)
#else
  #define DEBUG_PRINT_LN(msg)
  #define DEBUG_PRINT(msg)
#endif // DEBUG

// If USB_DEBUG is defined, the Serial port on the USB of the 
// Pro Micro will be used for communication, and debug output
// Uncomment this if you want to debug, add new patterns etc,
// and are working via USB.  Note the brigtness warning below!
// The normal mode is that the Controller will be connected
// using the Tx and R pins on the controller to talk to other
// devices in R2.
// Default is to use the Serial Pins, which are on Serial1
// Uncommenting the line beow switches to using the USB port
// and the Serial on the USB.

//#define USB_DEBUG

#define LED_PIN 4
#define NUM_LEDS 48
#define LEDS_PER_COLUMN 6
#define COLUMNS 10
  
  int8_t ledMatrix[COLUMNS][LEDS_PER_COLUMN] = {
    { -1, -1, 23, 24, -1, -1 }, 
    { -1, 6, 22, 25, 41, -1 }, 
    { 5, 7, 21, 26, 40, 42, },
    { 4, 8, 20, 27, 39, 43, }, 
    { 3, 9, 19, 28, 38, 44, }, 
    { 2, 10, 18, 29, 37, 45, },
    { 1, 11, 17, 30, 36, 46, },
    { 0, 12, 16, 31, 35, 47, },
    { -1, 13, 15, 32, 34, -1, },
    { -1, -1, 14, 33, -1, -1, } 
  };


// Command processing stuff
#define CMD_MAX_LENGTH 64 // maximum number of characters in a command (63 chars since we need the null termination)
// memory for command string processing
char cmdString[CMD_MAX_LENGTH];


// EEPROM SETTINGS
int alwaysOnAddress = 0;
int externalPOTAddress = 1;
int internalBrightnessAddress = 2;
