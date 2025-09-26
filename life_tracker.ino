#include <TinyWireM.h>
#include <Tiny4kOLED.h>
//currents

//lasts variables
  bool lastState = HIGH;
  int laststateclk;
//pins
  #define BUTTON 1  // PB1 = Arduino pin 1
  #define dt 4
  #define clk 3
//variables
  int maxhp = 31;
  int hp = 1;
  int lasthp = 0;

  const char* playerName = "Hero";//changes this to change your characters name

void setup() {
  oled.begin();
  oled.clear();
  oled.on();

    pinMode(BUTTON, INPUT_PULLUP);
    pinMode(dt, INPUT);
    pinMode(clk, INPUT);
  oled.setFont(FONT8X16);
  oled.setCursor(0, 0);
  oled.print(playerName);

  // Display initial HP in big font
  oled.setFont(FONT8X16);
  oled.setCursor(0, 3);  // adjust row for big font
  oled.print(F("HP:   "));
  oled.print(hp);
}

void loop() {
  bool buttonState = digitalRead(BUTTON);
  int currentclk = digitalRead(clk);

  if(currentclk != laststateclk && currentclk == LOW){
    if(digitalRead(dt)){
      hp++;
    }else{
      hp--;
    }
  }
    laststateclk = currentclk;
  if (buttonState != lastState) {
    if (buttonState == LOW) {
      hp = maxhp;
    }
    lastState = buttonState;
  }

//set the max and min
  if(hp < 0) hp = 0;
  if(hp > maxhp) hp = maxhp;

  if (hp != lasthp) {
    // Clear just the HP area by printing spaces first
    oled.setFont(FONT8X16);
    oled.setCursor(0, 3);
    oled.print(F("HP:     "));  // enough spaces to overwrite old number
    oled.setCursor(4*8, 3);     // position cursor after "HP: "
    oled.print(hp);
    lasthp = hp;
  }
}
