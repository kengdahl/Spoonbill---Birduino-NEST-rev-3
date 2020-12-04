#include <Servo.h>
#include <Adafruit_NeoPixel.h>
#include “Arduino_SensorKit.h”
SensorKit kit;
#ifdef __AVR__
#include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif
#define LED_PIN    12
#define BUZZER 3
#define LED_COUNT 1
Adafruit_NeoPixel pixels(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
Servo myservo;
int light_sensor = A0;
void setup() {
  // These lines are specifically to support the Adafruit Trinket 5V 16 MHz.
  // Any other board, you can remove this part (but no harm leaving it):
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif
  // END of Trinket-specific code.
  pixels.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  pixels.show();            // Turn OFF all pixels ASAP
  pixels.setBrightness(100); // Set BRIGHTNESS to about 1/5 (max = 255)
  myservo.attach(13);
  //kit.begin();
  pinMode(BUZZER, OUTPUT);
  Serial.begin(9600);
  delay(2000);
  myservo.write(0);
  delay(1200);
  myservo.write(90);
  delay(5000);
  pixels.setPixelColor(0, pixels.Color(0, 0, 255));
  pixels.show();
  delay (2500);
  pixels.setPixelColor(0, pixels.Color(255, 0, 255)); // purple
  pixels.show();
  delay(2500);
  myservo.write(170);
  delay(1500);
  myservo.write(90);
}
void loop() {
  int raw_light = analogRead(light_sensor);
  int light = map(raw_light, 0, 800, 0, 100);
  Serial.println(light);
  if (light <= 10)
  {
    for ( int i = 0; i < 5; i++)
    {
      tone(BUZZER, 1200); //Set the voltage to high and makes a noise
      pixels.setPixelColor(0, pixels.Color(0, 255, 0));
      pixels.show();
      delay(1000);//Waits for 1000 milliseconds
      noTone(BUZZER);//Sets the voltage to low and makes no noise
      pixels.setPixelColor(0, pixels.Color(0, 0, 0));
      pixels.show();
      delay(1000);//
    }
  }
  else
  {
    noTone(BUZZER);
    pixels.setPixelColor(0, pixels.Color(255, 0, 0));
    pixels.show();
  }
}