// Release version 1.2

///////////////////////////////////////////////////
//////////////// PSI CONFIGURATION ////////////////
///////////////////////////////////////////////////


///////////////////////////////////////////////////
///////////////// Timer Settings /////////////////
/////////////////////////////////////////////////

// The numbered pattern Modes have various preprogrammed lengths
// to match those of the Teeces Logic patterns. Some of the additional Modes 
// have indefinite lengths.  If you want ALL pattern Modes called using the
// Mode (T) command to remain on, then set 'alwaysOn' below to true. 
// The default is false, each selected pattern Mode will remain on for 
// its set time, and then return to the default pattern (swipe) Mode. 
// This can also ????
// The Current Teeces interface runs at a mind numbingly slow 2400 only!

bool alwaysOn = false;


// If your JEDI Device can send at 9600 baud, uncomment this line.
// The Current Teeces interface runs at a mindnumbingly slow 2400 only!

//#define _9600BAUDSJEDI_


///////////////////////////////////////////////////
////////////// SET DEFAULT PATTERN ///////////////
/////////////////////////////////////////////////

// Any display Mode can be the default Mode the PSI returns to
// after completing a command initiated Mode.  The standard default Mode
// is Swipe.  Use this to set the default Mode number.

uint8_t defaultPattern = 1; //Mode 1 is Swipe


///////////////////////////////////////////////////
////////////// SWIPE MODE SETTINGS ///////////////
/////////////////////////////////////////////////

// Colors are divded into Primary (Default is Blue for the 
// front PSI and Green for the Rear) and Secondary (Default
// is Red for the front PSI and Yellow for the rear).

// The number of milliseconds the PSI pauses on the primary color
// before switching to the secondary color.
// A random value between MINIMUM and MAXIMUM will be used.

#define PRIMARY_COLOR_DURATION_MINIMUM 2000  // Default 2000
#define PRIMARY_COLOR_DURATION_MAXIMUM 10000 // Default 10000

// Number of milliseconds that the secondary color will be
// visible before switching back to the primary color.
// A random value between MINIMUM and MAXIMUM will be used.

#define SECONDARY_COLOR_DURATION_MINIMUM 5000  // Default 4000
#define SECONDARY_COLOR_DURATION_MAXIMUM 12000 // Default 12000

// Speed range of the swipe animation. Longer delay means
// slower animation speed. 

#define SWIPE_DELAY_MINIMUM 20    // Default 20
#define SWIPE_DELAY_MAXIMUM 50    // Default 50

// Define the chance proportion between the various options for
// the secondary color. Increasing a value compared to the others increases
// the likelihood of that option occuring. If the chance for an option is 
// set to 0, it will not be selected.

#define CHANCE_SECONDARY_FULL 6
#define CHANCE_SECONDARY_PARTIAL 4
#define CHANCE_SECONDARY_PARTIAL_OFF 6

// How many columns to display the secondary color.

#define SECONDARY_PARTIAL_LINES_MIN 3 //The remainder will be the primary color.
#define SECONDARY_PARTIAL_LINES_MAX 6 //The remainder will be the primary color.
#define SECONDARY_PARTIAL_OFF_LINES 5 //The remainder will be off.

// Use the jumpers on the PSI CPU board to set Front colors (jumper off)
// or Rear colors (jumper on).

// Use the following settings to adjust the colors for font and rear.

// Set colors for the front PSI.
                                            // Default colors
CRGB frontPrimaryColor = CRGB(0, 0, 255);   // Blue (0, 0, 255)
CRGB frontSecondaryColor = CRGB(255, 0, 0); // Red  (255, 0, 0)
CRGB frontSecondaryOffColor = CRGB::Black;  // Off Black

// Colors for the rear PSI
                                              // Default colors
CRGB rearPrimaryColor = CRGB(0, 255, 0);      // Green  (0, 255, 0)
CRGB rearSecondaryColor = CRGB(200, 170, 0);  // Yellow (200, 170, 0)
CRGB rearSecondaryOffColor = CRGB::Black;     // Off Black

#if defined(ARDUINO_AVR_PRO)
#define JUMP_FRONT_REAR 12
#else
#define JUMP_FRONT_REAR 14
#endif

// Set the colors based on the pin being jumpered to ground.

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

///////////////////////////////////////////////////
//////////////// Serial SETTINGS ///////////////// 
/////////////////////////////////////////////////

// If USB_SERIAL is defined, the Serial port on the USB of the 
// Pro Micro will be used for communication, and debug output
// Uncomment this if you want to debug, add new patterns etc,
// and are working via USB.  Note the brigtness warning on the main
// sketch tab! The normal mode is that any serial control device (MarcDuino,
// STEALTH etc) will be connected to the PSI via the header pins on the
// PSI PCB by default.  These pins are referred to as Serial1.
// Uncommenting the line beow switches to using the USB port
// and the Serial on the USB of the Pro Micro instead.

// If you are using an Arduino with only one serial connection such
// as the Pro Mini, then you will want to uncomment this line to ensure
// the sketch uses Serial and not Serial1 for communication.  

//#define USB_SERIAL
#if defined(ARDUINO_AVR_PRO) && !defined(USB_SERIAL)
#define USB_SERIAL
#endif

///////////////////////////////////////////////////
//////////// Assign IC2 Address Below ////////////
/////////////////////////////////////////////////

#if !defined(ARDUINO_AVR_PRO)
#define USE_I2C 1
byte I2CAdress = 22;
#else
#define USE_I2C 0
#endif

///////////////////////////////////////////////////
/////////////////////////////////////////////////

// This is the pin for the Brighness POT

#if defined(ARDUINO_AVR_PRO)
#define POT_BRIGHT_PIN A1
#else
#define POT_BRIGHT_PIN 19
#endif

///////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////
// CHANGES BEYOND THESE LINES SHOULD NOT BE NECESSARY ///
////////////////////////////////////////////////////////
///////////////////////////////////////////////////////

// This is Neil's personal setup ... probably don't play with this!
//#define NEIL_PERSONAL_DEBUG
#ifdef NEIL_PERSONAL_DEBUG
  #define DEBUG       // Prints Debug Strings to help debugging
  #define USB_SERIAL  // Sets the Serial to use the USB port for sending and receiving commands instead of the TxRx on the board.
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

#define UNUSED(a) (void)(a);
#define FALL_THROUGH() __attribute__((fallthrough));

#define LED_PIN 4
#define NUM_LEDS 48
#define LEDS_PER_COLUMN 6
#define COLUMNS 10
 
// Addressible LED Array
// -1 = no LED in that grid space

  int8_t ledMatrix[COLUMNS][LEDS_PER_COLUMN] = {
    { -1, -1, 23, 24, -1, -1, },
    { -1,  6, 22, 25, 41, -1, },
    {  5,  7, 21, 26, 40, 42, },
    {  4,  8, 20, 27, 39, 43, },
    {  3,  9, 19, 28, 38, 44, },
    {  2, 10, 18, 29, 37, 45, },
    {  1, 11, 17, 30, 36, 46, },
    {  0, 12, 16, 31, 35, 47, },
    { -1, 13, 15, 32, 34, -1, },
    { -1, -1, 14, 33, -1, -1, } 
  };


// Command processing stuff
// maximum number of characters in a command (63 chars since we need the null termination)
#define CMD_MAX_LENGTH 64 

// memory for command string processing
char cmdString[CMD_MAX_LENGTH];

// POT Averager
#define POT_AVG_SIZE 30
// Change this if you get flicker.  A larger number will reduce POT noise.
#define POT_VARIANCE_LEVEL 2
uint16_t POTReadings[POT_AVG_SIZE];
uint8_t POTIndex = 0;
unsigned long POTSum = 0;
uint8_t POTCount = 0;

// EEPROM SETTINGS
int alwaysOnAddress = 0;
int externalPOTAddress = 1;
int internalBrightnessAddress = 2;
