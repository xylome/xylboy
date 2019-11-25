#include <Arduino.h>
#include <U8g2lib.h>
/* https://github.com/olikraus/u8g2/wiki/u8g2reference */
//#ifdef U8X8_HAVE_HW_SPI
//#include <SPI.h>
//#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

//#define DEBUG

U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);
#define MAX_X 127
#define MAX_Y 63

#define BUT1 2
#define BUT2 3
#define BUT3 4
#define BUT4 5

// Game logic
#define BAR_W 14
#define BAR_H 2
#define MAX_ACCEL 5

int x = 0;
int y = MAX_Y;
int accel = 1;
int increment = 7;

// Game input;
bool but_1_pressed = false;
bool but_2_pressed = false;
bool but_3_pressed = false;
bool but_4_pressed = false;

void setup(void) {
  u8g2.begin();
  pinMode(BUT1, INPUT);
  pinMode(BUT2, INPUT);
  pinMode(BUT3, INPUT);
  pinMode(BUT4, INPUT);
#ifdef DEBUG
  Serial.begin(9600);
#endif
}

void user_input() {
  but_1_pressed = digitalRead(BUT1) == 1;
  but_2_pressed = digitalRead(BUT2) == 1;
  but_3_pressed = digitalRead(BUT3) == 1;
  but_4_pressed = digitalRead(BUT4) == 1;
#ifdef DEBUG
  Serial.print(but_1_pressed);
  Serial.print(but_2_pressed);
  Serial.print(but_3_pressed);
  Serial.println(but_4_pressed);
#endif
}

void draw() {
  u8g2.clearBuffer();
  u8g2.drawBox(x, y - BAR_H, BAR_W, BAR_H);
  u8g2.sendBuffer();
}

void game_logic() {
  int last_x = x;
  x = but_2_pressed ? x + increment : x;
  x = but_1_pressed ? x - increment : x;

  if (x > MAX_X - BAR_W) {
    x = MAX_X - BAR_W;
  }
  
  if (x < 0) {
    x = 0; 
  }
  
  y = but_3_pressed ? y - increment : y;
  y = but_4_pressed ? y + increment : y;
  
  if (y < BAR_H) {
    y = BAR_H;
  }

  if (y > MAX_Y - BAR_H) {
    y = MAX_Y - BAR_H;
  }

}

void loop(void) {
  user_input();
  game_logic();
  draw();
#ifdef DEBUG
  Serial.println(y);
  delay(200);
#endif
}
