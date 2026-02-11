#include <LiquidCrystal_I2C.h>
#include <Keypad.h>
#include <string.h>

#define MAX_INPUT 16

const byte ROWS = 4; // number of rows
const byte COLS = 4; // number of columns
char keys[ROWS][COLS] = {
  {'1', '2', '3', 'c'},
  {'4', '5', '6', 'c'},
  {'7', '8', '9', 'c'},
  {'c', 'c', 'c', 'c'}
};
byte rowPins[ROWS] = {6,7,8,9}; // connect to the row pinouts of the keypad
byte colPins[COLS] = {5,4,3,2}; // connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

// LCD Connection
LiquidCrystal_I2C lcd(0x20,20,4);  // set the LCD address for a 16 chars and 2 line display

// To store sequence of key inputs
char input[MAX_INPUT];
int index = 0;

void setup(){
  Serial.begin(9600);
  lcd.init();     
}

void loop(){
  char key = keypad.getKey();
  
  if (key){
  	Serial.print("Key clicked: ");
  	Serial.print(key);
  	Serial.print("\n");
  }
    
}

