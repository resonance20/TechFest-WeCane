#include <Adafruit_DotStar.h>

// Pattern types supported:
enum  pattern { NONE, RAINBOW_CYCLE, THEATER_CHASE, COLOR_WIPE, SCANNER, FADE };
// Patern directions supported:
enum  direction { FORWARD, REVERSE };

// NeoPattern Class - derived from the Adafruit_NeoPixel class
// %: public Adafruit_DotStar
class NeoPatterns: public Adafruit_DotStar  {
    public:

    // Member Variables:
    pattern  ActivePattern;  // which pattern is running
    direction Direction;     // direction to run the pattern

    unsigned long Interval;   // milliseconds between updates
    unsigned long lastUpdate; // last update of position

    uint32_t Color1, Color2;  // What colors are in use
    uint16_t TotalSteps;  // total number of steps in the pattern
    uint16_t Index;  // current step within the pattern
    uint16_t startLED;
    uint16_t numActiveLEDS;




    void (*OnComplete)();  // Callback on completion of pattern

    // Constructor - calls base-class constructor to initialize strip
    NeoPatterns(uint16_t pixels, uint8_t data, uint8_t clock,uint8_t o, void (*callback)());

    // Update the pattern
    void Update();
      // Increment the Index and reset at the end
    void Increment();
      // Reverse pattern direction
    void Reverse();
    // Initialize for a RainbowCycle
    //void RainbowCycle(uint8_t interval, direction dir = FORWARD);
    // Initialize for a RainbowCycle at a specific section
    void RainbowCycle(uint8_t interval, direction dir = FORWARD,uint16_t strtLED=0, uint16_t nActiveLEDS=0);
    // Update the Rainbow Cycle Pattern
    void RainbowCycleUpdate();
    // Initialize for a Theater Chase
    void TheaterChase(uint32_t color1, uint32_t color2, uint8_t interval, direction dir = FORWARD);
    // Update the Theater Chase Pattern
    void TheaterChaseUpdate();
    // Initialize for a ColorWipe
    void ColorWipe(uint32_t color, uint8_t interval, direction dir = FORWARD);
    // Update the Color Wipe Pattern
    void ColorWipeUpdate();
    // Initialize for a SCANNNER
    void Scanner(uint32_t color1, uint8_t interval);
    // Update the Scanner Pattern
    void ScannerUpdate();
    // Initialize for a Fade
    void Fade(uint32_t color1, uint32_t color2, uint16_t steps, uint8_t interval, direction dir = FORWARD);
    // Update the Fade Pattern
    void FadeUpdate();
    // Calculate 50% dimmed version of a color (used by ScannerUpdate)
    uint32_t DimColor(uint32_t color);
    // Set all pixels to a color (synchronously)
    void ColorSet(uint32_t color);
    // Returns the Red component of a 32-bit color
    uint8_t Red(uint32_t color);
    // Returns the Green component of a 32-bit color
    uint8_t Green(uint32_t color);
    // Returns the Blue component of a 32-bit color
    uint8_t Blue(uint32_t color);
    // Input a value 0 to 255 to get a color value.
    // The colours are a transition r - g - b - back to r.
    uint32_t Wheel(byte WheelPos);
};
