#include <Keypad.h>
#include <Servo.h>
#include <Adafruit_LiquidCrystal.h>

// Construção da matriz de teclas
const byte numRows = 4;
const byte numCols = 4;
char keymap[numRows][numCols] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}};

// Construção do teclado
byte rowPins[numRows] = {12, 11, 10, 9};
byte colPins[numCols] = {8, 7, 6, 5};

// Iniciando as entradas e saídas
Keypad myKeypad = Keypad(makeKeymap(keymap), rowPins, colPins, numRows, numCols);
Servo lockServo;
Adafruit_LiquidCrystal lcd(0);
int forceSensorPin = 0;
int piezoPin = 2;
int tempPin = 1;

// Variáveis de controle
char storedPassword[5] = "0000";
char enteredPassword[5] = "____";
bool isOpen = false;
bool waitingForNewPassword = false;
bool alarmActive = false;
int newPasswordIndex = 0;
int forceSensorRead =  0;
int countAttemp = 0;
int tempRead = 0;

void setup() {
  Serial.begin(9600);
  lockServo.attach(3);
  lockServo.write(0);
  lcd.begin(16, 2);
  lcd.setBacklight(1);
  updateDisplayPassword();
  updateDisplayInstructions();
  pinMode(piezoPin, OUTPUT);
}

void loop() {
  char keypressed = myKeypad.getKey();
  forceSensorRead = analogRead(forceSensorPin);
  tempRead = analogRead(tempPin);
  
  if (keypressed) {

    if (keypressed >= '0' && keypressed <= '9') {
      handleDigitEntry(keypressed);
    } else if (keypressed == 'C') {
      handleCheckPassword();
    } else if (keypressed == 'D') {
      clearPassword();
    } else if (keypressed == 'A') {
      handleAlterPassword();
    } else if (keypressed == 'B') {
      handleCloseSafe();
    }
  }
  
  if (forceSensorRead < 280 || tempRead > 260) {
    alarmActive = true;
  }

  activeAlarm();
}

void activeAlarm() {
  if (alarmActive || countAttemp > 3) {
    tone(piezoPin, 1000, 100);
    delay(400);
    noTone(piezoPin);
  }
}

void handleDigitEntry(char digit) {
  shiftAndInsert(digit);
}

void handleCheckPassword() {
  if (!isOpen) {
    checkPassword();
  }
}

void handleAlterPassword() {
  if (isOpen) {
    for (int i = 0; i < 4; i++) {
      storedPassword[i] = enteredPassword[i];
    }
    displayMessage("Senha Alterada", 1000);
    clearPassword();
  }
}

void handleCloseSafe() {
  if (isOpen) {
    closeSafe();
  }
}

// Altera os dígitos da senha
void shiftAndInsert(char digit) {
  for (int i = 0; i < 3; i++) {
    enteredPassword[i] = enteredPassword[i + 1];
  }
  enteredPassword[3] = digit;
  updateDisplayPassword();
}

void updateNewPassword(char digit) {
  storedPassword[newPasswordIndex] = digit;
  newPasswordIndex++;

  if (newPasswordIndex == 4) {
    storedPassword[4] = '\0';
    waitingForNewPassword = false;
    newPasswordIndex = 0;
    displayMessage("Senha Alterada", 2000);
  }
}

void checkPassword() {
  if (strcmp(enteredPassword, storedPassword) == 0) {
    isOpen = true;
    alarmActive = false;
    countAttemp = 0;
    lockServo.write(90);
    displayMessage("Cofre Aberto", 2000);

  } else {
    displayMessage("Senha Incorreta", 2000);
    countAttemp += 1;
    updateDisplayPassword();
  }

  clearPassword();
  updateDisplayInstructions();
}

void startNewPassword() {
  waitingForNewPassword = true;
  newPasswordIndex = 0;
  clearPassword();
  displayMessage("Nova Senha:", 1000);
}

void closeSafe() {
  isOpen = false;
  lockServo.write(0);
  displayMessage("Cofre Fechado", 2000);
}

void clearPassword() {
  for (int i = 0; i < 4; i++) {
    enteredPassword[i] = '_';
  }
  enteredPassword[4] = '\0';
  updateDisplayPassword();
}

void updateDisplayPassword() {
  lcd.setCursor(0, 0);
  if (isOpen) {
    lcd.print("Nova Senha: ");
  } else {
    lcd.print("Senha: ");
  }

  for (int i = 0; i < 4; i++) {
    lcd.print(enteredPassword[i]);
  }
}

void updateDisplayInstructions() {
  lcd.setCursor(0, 1);

  if (isOpen) {
    lcd.print("A:Alter B:Block");
  } else {
    lcd.print("C:Check D:Clean");
  }
}

void displayMessage(const char *message, int duration) {
  lcd.clear();
  lcd.print(message);
  delay(duration);
  lcd.clear();
  updateDisplayInstructions();
}
