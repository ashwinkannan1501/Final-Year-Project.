/*************lcd pins*************/
#include <LiquidCrystal.h>
LiquidCrystal lcd(13, 12, 11, 10, 9, 8);
/************rfid with serial pins**************/
#include"rfid.h"
#include"softserial.h"

/*************motor pins***************/
#define m1_pos_pos 7       
#define m1_pos_neg 6
#define m2_neg_pos 5
#define m2_neg_neg 4
/*************buzzer pin****************/
#define buz A0

bool SCHOOL_STATUS = false;
bool HOSPITAL_STATUS = false;

int r_id;

void setup() {
  lcd.begin(16, 2);
  Serial.begin(9600);
//  rf.begin(9600);
  lcd.clear();

  digitalWrite(buz, LOW);
  digitalWrite(m1_pos, LOW);
  digitalWrite(m1_neg, LOW);
  digitalWrite(m2_pos, LOW);
  digitalWrite(m2_neg, LOW);


  pinMode(buz, OUTPUT);//buz

  pinMode(m1_pos, OUTPUT);
  pinMode(m1_neg, OUTPUT);
  pinMode(m2_pos, OUTPUT);
  pinMode(m2_neg, OUTPUT);
  lcd.setCursor(0, 0);
  lcd.print("AUTOMATIC SPEED");
  lcd.setCursor(2, 1);
  lcd.print(" CONTROL ");
  delay(3000);
  lcd.clear();
}

void loop() {

  lcd.setCursor(0, 0);
  lcd.print("Vehicle:");
  rfid();
  r_id = rfidno;
  if ((r_id == 1 || r_id == 2))
  {
    Serial.print("School Zone");
    lcd.setCursor(9, 0);
    lcd.print("SLOW   ");
    lcd.setCursor(0, 1);
    lcd.print("School Zone");
    digitalWrite(buz, HIGH);
    analogWrite(m1_pos, 255);
    analogWrite(m1_neg, 100);
    analogWrite(m2_pos, 150);
    analogWrite(m2_neg, 100);
    rfidno = 0;

  }
  else if ((r_id == 3 || r_id == 4))
  {
    lcd.setCursor(9, 0);
    lcd.print("SLOW   ");
    lcd.setCursor(0, 1);
    lcd.print("Hospital Zone");
    digitalWrite(buz, HIGH);
    analogWrite(m1_pos, 255);
    analogWrite(m1_neg, 100);
    analogWrite(m2_pos, 150);
    analogWrite(m2_neg, 100);
    rfidno = 0;
  }
}
void serialEvent()
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Vehicle:");
  while (Serial.available() > 0)
  {
    char inByte = (char)Serial.read();
    Serial.print(inByte);
    switch (inByte)
    {
      case 'W':
        lcd.setCursor(9, 0);
        lcd.print("FORWARD");
        digitalWrite(m1_pos, LOW);
        digitalWrite(m1_neg, LOW);
        digitalWrite(m2_pos, LOW);
        digitalWrite(m2_neg, LOW);
        delay(1000);
        digitalWrite(m1_pos, HIGH);
        digitalWrite(m1_neg, LOW);
        digitalWrite(m2_pos, HIGH);
        digitalWrite(m2_neg, LOW);
        digitalWrite(buz, LOW);
        break;
      case 'X':
        lcd.setCursor(9, 0);
        lcd.print("REVERSE");
        digitalWrite(m1_pos, LOW);
        digitalWrite(m1_neg, LOW);
        digitalWrite(m2_pos, LOW);
        digitalWrite(m2_neg, LOW);
        delay(1000);
        digitalWrite(m1_pos, LOW);
        digitalWrite(m1_neg, HIGH);
        digitalWrite(m2_pos, LOW);
        digitalWrite(m2_neg, HIGH);
        digitalWrite(buz, LOW);
        break;
      case 'Y':
        lcd.setCursor(9, 0);
        lcd.print("LEFT   ");
        digitalWrite(m1_pos, LOW);
        digitalWrite(m1_neg, LOW);
        digitalWrite(m2_pos, LOW);
        digitalWrite(m2_neg, LOW);

        delay(1000);
        digitalWrite(m1_pos, LOW);
        digitalWrite(m1_neg, HIGH);
        digitalWrite(m2_pos, HIGH);
        digitalWrite(m2_neg, LOW);
        digitalWrite(buz, LOW);
        break;
      case 'Z':
        lcd.setCursor(9, 0);
        lcd.print("RIGHT  ");
        digitalWrite(m1_pos, LOW);
        digitalWrite(m1_neg, LOW);
        digitalWrite(m2_pos, LOW);
        digitalWrite(m2_neg, LOW);
        delay(1000);
        digitalWrite(m1_pos, HIGH);
        digitalWrite(m1_neg, LOW);
        digitalWrite(m2_pos, LOW);
        digitalWrite(m2_neg, HIGH);
        digitalWrite(buz, LOW);
        break;
      case 'V':
        lcd.setCursor(9, 0);
        lcd.print("STOP   ");
        digitalWrite(m1_pos, LOW);
        digitalWrite(m1_neg, LOW);
        digitalWrite(m2_pos, LOW);
        digitalWrite(m2_neg, LOW);
        digitalWrite(buz, LOW);
        break;
    }
  }
}
