//타이머 인터럽트
#include <MsTimer2.h>

//LCD
#include <LiquidCrystal.h>

LiquidCrystal lcd(13, 12, 8, 9, 10, 11); //RS, E, DB4, DB5, DB6,DB7
//GND Vcc Vee RS  RW  EN  DB0 DB1 DB2 DB3 DB4 DB5 DB6 DB7 BL+ BL-
//1   2   3   4   5   6   7   8   9   10  11  12  13  14  15  16

//SW
#define leftSW_pin 2
#define rightSW_pin 3

//buzzer
#define buzzer_pin 5
#define sos_buzzer_pin 7

//SONIC
#define trig 3
#define echo 4

//JoyStick
#define X_pin 0
#define Y_pin 1
#define SW 2

//LED
#define LED 6

volatile int repeat = 0, buzzer_repeat = 0, ultra_repeat = 0;
volatile int report_cnt = 0, sw_cnt = 0, led_cnt = 0, lcd_cnt = 0;
volatile int mod1 = 0, mod2 = 0, mod3 = 0, mod4 = 0;
int before_distance = 0;
int buzzer_run = 0, joy_run = 0, report_run = 0,sw_run = 1, led_run = 0, lcdclear_run = 0;
int send1time = 0, clear1time = 0;
int mode1 = 1, mode2 = 0, mode3 = 0, mode4 = 0;

int UltraSonic_measure()
{
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  int distance = pulseIn(echo, HIGH);
  distance = distance/29/2;//더 정확한가? 테스트 필요
  return distance;
}

void flash()//Timer function
{
  if(lcdclear_run == 1)
  {
    lcd_cnt++;
    if(lcd_cnt >= 100)
    {
      lcd.clear();
      lcd_cnt = 0;
      lcdclear_run = 0;
    }
  }
  if(analogRead(leftSW_pin) >= 1000)
  {
    sw_cnt++;
    if(sw_cnt == 50)
    {
      if(analogRead(rightSW_pin) >= 1000)
      {
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("This direction");
        lcd.setCursor(0,1);
        lcd.print("Restaurant");
        lcdclear_run = 1;
      }
      else
      {
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("This direction");
        lcd.setCursor(0,1);
        lcd.print("Metro");
        lcdclear_run = 1;
      }
    }
  }
  else if(analogRead(rightSW_pin) >= 1000)
  {
    sw_cnt++;
    if(sw_cnt == 50)
    {
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("This direction");
      lcd.setCursor(0,1);
      lcd.print("Bus stop");
        lcdclear_run = 1;
    }
  }
  else
    sw_cnt = 0;

  if(buzzer_run == 1)
  {
    buzzer_repeat--;
    if(buzzer_repeat <= 0 && buzzer_repeat > -2)
    {
      digitalWrite(buzzer_pin, HIGH);
    }
    else if(buzzer_repeat <= -2)
    {
      digitalWrite(buzzer_pin, LOW);
      buzzer_repeat = repeat;
    }
    else
      digitalWrite(buzzer_pin, LOW);
  }
  if(joy_run == 1)
  {
    if(analogRead(X_pin) >= 900)
    {
      mod3++;
      mod2 = mod1 = mod4 = 0;
      if(mod3 >= 100)
      {
        joy_run = 0;
        mod3 = 0;
        mode3 ^= 1;
      }
    }
    else if(analogRead(X_pin) <= 100)
    {
      mod1++;
      mod2 = mod3 = mod4 = 0;
      if(mod1 >= 100)
      {
        joy_run = 0;
        mod1 = 0;
        mode1 ^= 1;
      }
    }
    if(analogRead(Y_pin) >= 900)
    {
      mod4++;
      mod1 = mod3 = mod2 = 0;
      if(mod4 >= 100)
      {
        joy_run = 0;
        mod4 = 0;
        mode4 ^= 1;
      }
    }
    else if(analogRead(Y_pin) <= 100)
    {
      mod2++;
      mod4 = mod3 = mod1 = 0;
      if(mod2 >= 100)
      {
        joy_run = 0;
        mod2 = 0;
        mode2 ^= 1;
      }
    }
  }
  if(report_run == 1)
  {
    if(report_cnt == 0)
      Serial.println("37.503027, 126.776175");
    report_cnt++;
    if(report_cnt >= 1000)
      report_cnt = 0;
  }
  if(led_run == 1)
  {
    led_cnt++;
    digitalWrite(LED, led_cnt / 20);
    if(led_cnt >= 40)
      led_cnt = 0;
  }
}//Timer function end

void setup()
{
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(buzzer_pin, OUTPUT);
  pinMode(SW, INPUT_PULLUP);  // Input mode, pull-up
  pinMode(LED, OUTPUT);
  pinMode(sos_buzzer_pin,OUTPUT);
  digitalWrite(buzzer_pin,LOW);
  MsTimer2::set(10, flash); // 10ms period
  MsTimer2::start();
  lcd.begin(16,2);
  lcd.clear();
  lcd.setCursor(0,0);
  Serial.begin(9600);
}

void loop()
{
  if(digitalRead(SW) == 0 & joy_run == 0)
  {
    joy_run = 1;
  }
  
  if(mode1 == 1)
  {
    int distance = UltraSonic_measure();
    distance /= 10;
    if(before_distance != distance)
    {
      if(distance <= 7)
      {
        repeat = distance * 6 + 5;
        buzzer_repeat = repeat;
        buzzer_run = 1;
      }
      else
      {
        buzzer_run = 0;
        digitalWrite(buzzer_pin,LOW);
      }
      before_distance = distance;
    }
  }
  else
  {
    buzzer_run = 0;
    digitalWrite(buzzer_pin, LOW);
    before_distance = 10;
  }
  if(mode2 == 1)
  {
    if(report_run == 0)
      report_run = 1;
  }
  else
  {
    report_run = 0;
    report_cnt = 0;
  }
  if(mode3 == 1)
  {
    digitalWrite(sos_buzzer_pin,HIGH);
    if(send1time == 0)
    {
      led_run = 1;
      lcd.setCursor(0,0);
      lcd.print("Name : ParkIlDo");
      lcd.setCursor(0,1);
      lcd.print("010-4440-1692");
      Serial.println("37.503027, 126.776175, SOS");
      send1time = 1;
    }
    clear1time = 0;
  }
  else
  {
    if(mode4 == 1)
      digitalWrite(LED,HIGH);
    else
      digitalWrite(LED,LOW);
    led_run = 0;
    led_cnt = 0;
    if(clear1time == 0)
    {
      lcd.clear();
      clear1time = 1;
    }
    digitalWrite(sos_buzzer_pin, LOW);
    send1time = 0;
  }
  delay(100);
}
