#define DELAY 200
#define DELAY10 10000
#define DELAY15 15000
#define DELAY20 20000
#define DELAY5 5000
#define DELAY3 3000
#define Flashing 333

#define ON  0x01
#define OFF 0x00
#define NUM_LEDS 0x03

#define RED_LED 0x400000
#define BLUE_LED 0x200000
#define GREEN_LED 0x080000

#define NS_RED 0x40000 //pin2
#define NS_YELLOW 0x800000 //pin7
#define NS_GREEN 0x1 //pin8
#define EW_RED 0x2 //pin9
#define EW_YELLOW 0x800 //pin17
#define EW_GREEN 0x1000 //pin18
#define PED_RED 0x2000 //pin19
#define PED_GREEN 0x100000 //pin4
#define PED_BUTTON 0x200//pin15


void setupGPIO();
int setLED(int color, int state);
void delay(int milliseconds);
int checkPed(int milliseconds);
// int checkBot();
