#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

#define sensor A0
#define buttonPin 2  // Assuming the button is connected to digital pin 2

byte degree[8] =
{
    0b00011,
    0b00011,
    0b00000,
    0b00000,
    0b00000,
    0b00000,
    0b00000,
    0b00000
};

bool isCelsius = true;         // Flag to track the temperature unit
unsigned long previousMillis;  // Previous time value for button timing
const unsigned long interval = 200;  // Button debounce interval in milliseconds

void setup()
{
    pinMode(buttonPin, INPUT_PULLUP);

    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // Address 0x3C for 128x64
    display.display();
    display.clearDisplay();

    display.setTextSize(1);
    display.setTextColor(WHITE);

    display.setCursor(0, 0);
    display.print(" Digital ");
    display.setCursor(0, 10);
    display.print(" Thermometer ");
    display.display();
    delay(2000);
    display.clearDisplay();
}

void loop()
{
    float reading = analogRead(sensor);
    float temperature = reading * (5.0 / 1023.0) * 100;

    unsigned long currentMillis = millis();  // Get the current time

    if (currentMillis - previousMillis >= interval) {
        if (digitalRead(buttonPin) == LOW) {
            isCelsius = !isCelsius;  // Toggle the temperature unit flag
        }

        previousMillis = currentMillis;  // Update the previous time value
    }

    display.clearDisplay();
    display.setTextSize(1);
    display.setCursor(2, 0);
    display.print("Temperature");

    if (isCelsius) {
        display.setCursor(4, 10);
        display.print(temperature);
        display.write(1);
        display.print("C");
    } else {
        float temperatureF = (temperature * 9.0 / 5.0) + 32.0;
        display.setCursor(3, 10);
        display.print(temperatureF);
        display.write(1);
        display.print("F");
    }

    display.display();
    delay(1000);
}
