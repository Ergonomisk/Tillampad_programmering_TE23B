
Here’s a README text file specifically formatted for a .txt document. It keeps details concise and free of markdown for ease of reading.

Clock, Temperature, and Warning System Project

Author: Erik
Date: 2024-10-11

Project Overview
This project combines a clock, temperature monitor, and warning system using an Arduino, DS3231 RTC, OLED display, and other components. It shows the time, measures ambient temperature, and triggers a warning if the temperature exceeds a set threshold, which can be adjusted with a potentiometer.

Features

Real-time clock with DS3231, displayed on an OLED screen
Temperature measurement using an analog sensor, displayed on a servo
Temperature threshold warning system with LEDs and a buzzer
Adjustable temperature threshold using a potentiometer
Components

Arduino-compatible microcontroller
DS3231 Real-Time Clock (RTC) module
SSD1306 OLED Display (128x64)
Analog temperature sensor (e.g., NTC Thermistor)
9g servo motor
Potentiometer for adjusting temperature threshold
Buzzer for warning alert
4 LEDs for visual alert
Libraries Needed

RTClib for DS3231 RTC (https://github.com/adafruit/RTClib)
Wire library for I2C communication
U8glib for OLED display (https://github.com/olikraus/u8glib)
Servo library for servo motor control
Pin Configuration

Temperature Sensor: A1
Potentiometer: A0
Buzzer: Digital Pin 2
LEDs: Digital Pins 4 to 7
Servo Motor: Digital Pin 9
DS3231 RTC: I2C (SDA/SCL) Pins
Setup Instructions

Install required libraries via the Arduino Library Manager or GitHub.
Connect components to their designated pins as listed above.
Upload the code to the Arduino using the Arduino IDE.
Adjust the temperature threshold by turning the potentiometer.
Function Descriptions

getTime(): Fetches the current time from DS3231 and formats it as hh:mm:ss.
getTemp(): Reads and calculates temperature in Celsius.
oledWrite(x1, y1, text1, x2, y2, text2): Displays text on OLED at specified coordinates.
servoWrite(value): Maps temperature to servo angle, simulating a thermometer.
getThershold(): Maps the potentiometer reading to a temperature threshold.
alarm(): Activates the warning system with LEDs and buzzer in quick succession.
Usage Instructions

Power on the system after uploading the code.
The OLED displays the current time and threshold.
If the temperature exceeds the threshold, LEDs and the buzzer activate, and "TOO HOT" appears on the OLED.
Future Improvements

Integrate a humidity sensor.
Add remote notifications for temperature alerts.
Add battery backup for the RTC module.
License
This project is open-source under the MIT License (https://opensource.org/licenses/MIT).