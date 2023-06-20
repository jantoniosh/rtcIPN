#include <TimerOne.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>

#define i2c_Address 0x3c
#define SCREEN_WIDTH 128 
#define SCREEN_HEIGHT 64 
#define OLED_RESET -1  
Adafruit_SH1106G display = Adafruit_SH1106G(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

int count, dCount;

// Create a counter event timer 
void counter() {
  // count +1
  count = count + 1;
 Serial.println(count);
}

void setup() {
   Serial.begin(9600);
  // Set up an counter event timer  every second
  Timer1.initialize(1000000);
  Timer1.attachInterrupt(counter);
  // Inicializar OLED
  delay(250); // wait for the OLED to power up
  display.begin(i2c_Address, true);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SH110X_WHITE);
  display.setCursor(5, 5);
  display.println("Contador:");
  display.display();
  dCount = count;
}

void loop() {
  if (dCount != count) {
    dCount = count;
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SH110X_WHITE);
    display.setCursor(5, 5);
    display.println("Contador:");
    display.setCursor(5, 15);
    display.println(count);
    display.display();
  }
}
