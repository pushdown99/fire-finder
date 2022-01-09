#include <LiquidCrystal_I2C.h>

#define COLUMNS 16
#define ROWS    2

LiquidCrystal_I2C lcd(0x27, COLUMNS, ROWS);  

int dirPin = 5; // 방향 설정 핀
int stepPin = 6; // 펄스 발생 핀
int enablePin = 7; // 모터 동작 여부 설정 핀

void printLCD (char* s1, char* s2) 
{
  lcd.clear();
  lcd.setCursor(2,0);
  lcd.print(s1);

  lcd.setCursor(2,1);
  lcd.print(s2);
}

void setup() {
  Serial.begin(115200);
  
  pinMode (dirPin,    OUTPUT);
  pinMode (enablePin, OUTPUT);
  pinMode (stepPin,   OUTPUT);
  digitalWrite (enablePin, HIGH);

  lcd.init();
  lcd.clear();
  lcd.backlight();

  printLCD ("Hi", "there!!");
}

#define TIMES 50
#define DELAY 100

void TurnLeft()
{
  digitalWrite(dirPin, HIGH);
  for(int i = 0; i < TIMES; i++) {
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(DELAY);
    digitalWrite(stepPin, LOW);
  }
}

void TurnRight()
{
  digitalWrite(dirPin, LOW);
  for(int i = 0; i < TIMES; i++) {
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(DELAY);
    digitalWrite(stepPin, LOW);
  }
}

void loop() 
{
  if (Serial.available()) {
    char buf[20];
    int x = Serial.parseInt();
    printLCD ("Got something!", itoa(x, buf, 10));
    if (x == 0) TurnLeft();
    else        TurnRight();
  }  
}
