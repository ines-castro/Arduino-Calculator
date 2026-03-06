#include <LiquidCrystal_I2C.h>
#include <Keypad.h>
#include <string.h>
#include <stdlib.h>

// =============================================================================
// KEYPAD CONFIGURATION
// =============================================================================
const byte ROWS = 4;    // Total number of rows on your keypad
const byte COLS = 4;    // Total number of columns on your keypad

// TODO: Arrange these characters to match your physical buttons exactly
// Matrix of physical buttons
char keys[ROWS][COLS] = {
  {'1','2','3', '/'},
  {'4','5','6', '*'},
  {'7','8','9', '-'},
  {'.','0','=', '+'}
};
byte rowPins[ROWS] = {9, 8, 7, 6}; // Arduino pins plugged into R1, R2, R3 and R4
byte colPins[COLS] = {5, 4, 3, 2}; // Arduino pins plugged into C1, C2, C3 and C4

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

// =============================================================================
// KEYPAD CONFIGURATION
// =============================================================================
LiquidCrystal_I2C lcd(0x27, 16, 2);  // Set the LCD address for a 16 chars and 2 line display

// Memory setup for storing typed keys
#define MAX_INPUT 16
char input[MAX_INPUT];
int index = 0;
int res = 0;

// =============================================================================
// RUNS ONCE IN THE BEGGING 
// =============================================================================
void setup(){
  Serial.begin(9600);       // Initialise communication with the Serial Monitor
  lcd.init();               // Initialise the LCD
  lcd.backlight();
}

// =============================================================================
// RUNS CONTINUOUSLY
// =============================================================================
void loop(){
  char key = keypad.getKey();
  
  if (key == '='){
    input[index] = '\0'; 
    lcd.setCursor(10, 1);
    lcd.print('=');         
    res = calculate(input, MAX_INPUT);
    if (res == -1) {
      lcd.print("ERROR");
    } else {
      lcd.print(res);
    }
  } else if (key != '==' and key){
    Serial.print("Key clicked: ");
  	Serial.println(key);
    input[index] = key;
    index++;
  	lcd.print(key);
  }

}

char calculate(char keys[], int length) {
  int num1 = 0;
  int num2 = 0;
  char op = 0;
  int result = 0;
  int operatorFound = false;

  for (int i = 0; keys[i] != '\0'; i++) {
    char c = keys[i];

    if (c == '+' || c == '-' || c == '*' || c == '/'){
      op = c;
      operatorFound = true;
    }
    int key = convert_key(c);
    if (key >= 0 && key <= 9) {
      if (!operatorFound) {
        num1 = key;
      } else {
        num2 = key;
      }
    } 
  }

  // Be sure you are retrieving the correct values
  Serial.print("num1 = ");
  Serial.print(num1);
  Serial.print(", num2 = ");
  Serial.print(num2);
  Serial.print(", op = ");
  Serial.println(op);

  if (!operatorFound) {
    result = num1;  // Only one number entered
  } else {
    switch (op) {
      case '+': 
        result = num1 + num2;
        break;
      case '-': 
        result = num1 - num2;
        break;
      case '*': 
        result = num1 * num2;
        break;
      case '/':
        if (num2 != 0){
          result = num1 / num2;
        } else {
          result = -1;
        } 
        break;
    }
  }

  return result;

}

int convert_key(char key){
  return key - '0'; 
}

