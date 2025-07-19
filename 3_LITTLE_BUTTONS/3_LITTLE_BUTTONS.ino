#include <LiquidCrystal_I2C.h>
#include <Wire.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); 

int correct = 4;
int button[] = {3,4,5};
int chance = 0;
int buzz = 6;
bool locked = false;
int e = 0;
int x = 1;

void setup() {
  for (int i = 0; i < 3; i++) {
    pinMode(button[i], INPUT_PULLUP);
  }
  pinMode(buzz, OUTPUT);

  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Choose a button");
}

void loop() {
  if (locked) {
    return;
  }

  for (int i = 0; i < 3; i++) {
    if (digitalRead(button[i]) == LOW) {
      lcd.clear();
      digitalWrite(buzz, HIGH);
      delay(200);
      digitalWrite(buzz, LOW);

      if (button[i] == correct) {
        lcd.print("Correct!");
        delay(2000);
        lcd.clear();
        lcd.print("Unlocked");
        lcd.setCursor(0, 1);
        lcd.print("");
      } 
      else {
        digitalWrite(buzz, HIGH);
        delay(200);
        digitalWrite(buzz, LOW);
        lcd.print("Wrong!");
        delay(1000);
        lcd.clear();
        
        chance++;
        
        if (chance < 3 || chance == 4){
          lcd.print("You have");
          lcd.setCursor(0, 1);
          lcd.print(x -chance);
          lcd.print(" chances left");
          delay(1000);
          lcd.clear();
        
        }
        if(chance == 3){
          lcd.print("You have");
          lcd.setCursor(0, 1);
          lcd.print(x -chance);
          lcd.print(" chance left");
          delay(1000);
          lcd.clear();

        }
      
      delay(300); 
    }
  }

  if (chance >= x ) {
    locked = true;
    while (e < 3){
      digitalWrite(buzz, HIGH);
      delay(200);
      digitalWrite(buzz, LOW);
      delay(200);
      e++;
    }


    digitalWrite(buzz, HIGH);
    delay(200);
    digitalWrite(buzz, LOW);

    lcd.clear();
    lcd.print("Detonate in ");
    lcd.setCursor(0,1);
    lcd.print("2 mins");
    delay(60000);
  


    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Unlocking in");
    lcd.setCursor(0,1);
    lcd.print("1 min");
    delay(57000);
    lcd.clear();
    lcd.print("Unlocking in");
    lcd.setCursor(0,1);
    lcd.print("...3");
    delay(1000);
    lcd.print("...2");
    delay(1000);
    lcd.print("...1!");
    delay(2000);



    lcd.clear();
    lcd.print("Unlocked");
    digitalWrite(buzz, HIGH);
    delay(2000);
    digitalWrite(buzz, LOW);
    delay(1000);
    lcd.clear();
    lcd.print("Click a button");

    locked = false;
    chance = 0;
  }
}
}
