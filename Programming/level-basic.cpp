#include <LiquidCrystal_I2C.h>
#include <Keypad.h>
#include <string.h>

#define MAX_INPUT 16

const byte ROWS = 4; // number of rows
const byte COLS = 4; // number of columns
char keys[ROWS][COLS] = {
  {'1','2','3', '/'},
  {'4','5','6', '*'},
  {'7','8','9', '-'},
  {'.','0','=', '+'}
};
byte rowPins[ROWS] = {9, 8, 7, 6}; // connect to the row pinouts of the keypad
byte colPins[COLS] = {5, 4, 3, 2}; // connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

// LCD Connection
LiquidCrystal_I2C lcd(0x20,20,4);  // set the LCD address for a 16 chars and 2 line display

// To store sequence of key inputs
char input[MAX_INPUT];
char lastKeys[MAX_INPUT];
int index = 0;

// To know if this is my first calculation
bool calculated = false;
bool newCalculation = false;

void setup(){
  Serial.begin(9600);
  lcd.init();     
  
  restartDisplay();
  Serial.println(input);
}

void loop(){
  char key = keypad.getKey();

  if (key != '=' and key){
    
    calculated = false;
    Serial.println(key);
    input[index] = key;
    index++;
  	lcd.print(key);
  }
  
  
  // Calculate
  if (key == '=') {
    input[index] = '\0';          // Null terminate the input string here
    calculate(input, MAX_INPUT);
    calculated = true;
    memcpy(lastKeys, input, MAX_INPUT);
    // Prepare for next calculation
    memset(input, 0, sizeof(input));
    index = 0; 
    newCalculation = true;
  }
  
  // After first calculation, delete first line
  if (!calculated and input[1] == '\0' and lastKeys[2] != '\0' and newCalculation){
    newCalculation = false;
    restartDisplay();
    lcd.print(input[0]);
  }
  
  // Manualy delete what I have writen
  if (key == '.') {
    memset(input, 0, sizeof(input));
    index = 0;  
    restartDisplay();
  }
  
}

void restartDisplay(){
  lcd.clear();
  lcd.setCursor(10, 1);
  lcd.print('=');
  lcd.setCursor(0, 0);
}

void calculate(char keys[], int length) {
  int num1 = 0;
  int num2 = 0;
  char op = 0;
  bool operatorFound = false;

  for (int i = 0; i < length; i++) {
    char c = keys[i];

    if (c >= '0' && c <= '9') {
      if (!operatorFound) {
        num1 = num1 * 10 + (c - '0');  // Build first number
      } else {
        num2 = num2 * 10 + (c - '0');  // Build second number
      }
    } else if (c == '+' || c == '-' || c == '*' || c == '/') {
      op = c;
      operatorFound = true;
    }
  }

  int result = 0;
  bool valid = true;

  if (!operatorFound) {
    result = num1;  // Only one number entered
  } else {
    switch (op) {
      case '+': result = num1 + num2; break;
      case '-': result = num1 - num2; break;
      case '*': result = num1 * num2; break;
      case '/':
        if (num2 != 0) result = num1 / num2;
        else valid = false;
        break;
      default:
        valid = false;
    }
  }

  lcd.setCursor(11, 1);
  Serial.println(result);

  if (valid) {
    lcd.print(result);
    Serial.println(result);
  } else {
    lcd.print("Error!");
    Serial.println("Calculation error!");
  }
  
  lcd.setCursor(0, 0);
  
}

