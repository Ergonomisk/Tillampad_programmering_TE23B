/*
* Name: clock, temp and temp warning project
* Author: Erik
* Date: 2024-10-11
* Description: This project uses a ds3231 to measure time and displays the time to an 1306 oled display,
* Further, it measures temprature with a analog temprature module and displays a mapped value to a 9g-servo-motor
*/

// Include Libraries
#include <RTClib.h>
#include <Wire.h>
#include "U8glib.h"
#include <Servo.h>

// Init constants
const int tmpPin = A1;
const int potPin = A0;
const int buzzer = 2;
// Init global variables
float pos = 0;
// construct objects
RTC_DS3231 rtc;
U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NO_ACK);
Servo eriksservo;

void setup() {
  // init communication
  // Serial.begin(9600);
  // Init Hardware
  for (int i = 4; i <= 7; i++) {  //start dpin 4-7
    pinMode(i, OUTPUT);
  }
  u8g.setFont(u8g_font_6x10);
  pinMode(buzzer, OUTPUT); 
  pinMode(tmpPin, INPUT);
  pinMode(potPin, INPUT);
  eriksservo.attach(9);
  Wire.begin();
  rtc.begin();
  rtc.adjust(DateTime(F(__DATE__),F(__TIME__)));
  //rtc.adjust(DateTime(2019, 1, 21, 5, 0, 0));
}

void loop() {

//  Serial.println(getTime());
//  Serial.println(getTemp());
  if (getTemp() > getThershold()){
    alarm();
    oledWrite(0, 30, getTime(), 0, 50, "TOO HOT");
  }else{
  oledWrite(0, 30, getTime(), 0, 50, String(getThershold()));
  servoWrite(getTemp());
  }

}


/*
*This function reads time from an ds3231 module and package the time as a String
*Parameters: Void
*Returns: time in hh:mm:ss as String
*/
String getTime() {

  DateTime now = rtc.now();

  return ("Time: " + String(now.hour()) + ":" + String(now.minute()) + ":" + String(now.second()));

}

/*
* This function reads an analog pin connected to an analog temprature sensor and calculates the corresponding temp
*Parameters: Void
*Returns: temprature as float
*/

float getTemp() {

  int Vo;
  float R1 = 10000;  // value of R1 on board
  float logR2, R2, T;
  float c1 = 0.001129148, c2 = 0.000234125, c3 = 0.0000000876741;  //steinhart-hart coeficients for thermistor

  Vo = analogRead(tmpPin);
  R2 = R1 * (1023.0 / (float)Vo - 1.0);  //calculate resistance on thermistor
  logR2 = log(R2);
  T = (1.0 / (c1 + c2 * logR2 + c3 * logR2 * logR2 * logR2));  // temperature in Kelvin
  T = T - 273.15;                                              //convert Kelvin to Celcius

  return T;
}

/*
* This function takes a string and draws it to an oled display
*Parameters: - text: two x-coordinates, two y-coordinates and two String to write to display
*Returns: void
*/
void oledWrite(int x1, int y1, String text1, int x2, int y2, String text2) {
  u8g.firstPage();
  do{ 
    u8g.drawStr(x1, y1, text1.c_str());
    u8g.drawStr(x2, y2, text2.c_str());
  } while (u8g.nextPage());
}

/*
* takes a temprature value and maps it to corresppnding degree on a servo
*Parameters: - value: temprature
*Returns: void
*/
void servoWrite(float value) {
  value = map(getTemp(), 10, 40, 0, 180);
  eriksservo.write(pos = value );
}
/*
* takes the value form a potentiometer an maps it to a smaller range
*Parameters: void
*Returns: map as int
*/
int getThershold() {
  return map(analogRead(potPin), 0, 1023, 10, 40);
}
/*
* This funtion turns 4 LEDs and a buzzer on and off in rapid succession 
*Parameters: void
*Returns: void
*/
void alarm() {
  for (int i = 4; i <= 7; i++) {
    digitalWrite(i, HIGH);
    tone(buzzer, i*1000);
    delay(40);
    digitalWrite(i, LOW);
    noTone(buzzer);
  }
}
