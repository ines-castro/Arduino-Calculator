#include <LiquidCrystal_I2C.h>
#include <Keypad.h>
#include <string.h>

// =============================================================================
// KEYPAD CONFIGURATION
// =============================================================================
const byte ROWS = 4;    // Total number of rows on your keypad
const byte COLS = 4;    // Total number of columns on your keypad

// TODO: Arrange these characters to match your physical buttons exactly
char keys[ROWS][COLS] = {
  {'', '', '', ''},
  {'', '', '', ''},
  {'', '', '', ''},
  {'', '', '', ''}
};
byte rowPins[ROWS] = {};    // TODO: Match the Arduino pins you plugged R1, R2, R3, R4 into
byte colPins[COLS] = {};    // TODO: Match the Arduino pins you plugged C1, C2, C3, C4 into

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

// =============================================================================
// KEYPAD CONFIGURATION
// =============================================================================
LiquidCrystal_I2C lcd(0x27, 16, 2);  // Set the LCD address for a 16 chars and 2 line display

// Memory setup for storing typed keys
#define MAX_INPUT 16
char input[MAX_INPUT];
int index = 0;

// =============================================================================
// RUNS ONCE IN THE BEGGING 
// =============================================================================
void setup(){
  Serial.begin(9600);       // Initialise communication with the Serial Monitor
  lcd.init();               // Initialise the LCD

  lcd.backlight();
  lcd.setCursor(0, 0);      // Start writing in first position of 1st line
  lcd.print("Ola");
  lcd.setCursor(0, 1);      // Start writing in first position of 2nd line
  lcd.print("estudante :)");
}

// =============================================================================
// RUNS CONTINUOUSLY
// =============================================================================
void loop(){
  char key = keypad.getKey();
  
  if (key){
  	Serial.print("Key clicked: ");
  	Serial.print(key);
  	Serial.print("\n");
  }

}

