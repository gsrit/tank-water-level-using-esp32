#include <Arduino.h>
#include <Ultrasonic.h>  // Library for HC-SR04
#include <SevSeg.h>     // Library for seven-segment display

#define TRIGGER_PIN 14  // Replace with your GPIO pin for TRIG
#define ECHO_PIN 12     // Replace with your GPIO pin for ECHO

Ultrasonic ultrasonic(TRIGGER_PIN, ECHO_PIN);

// Create an instance of SevSeg
SevSeg sevseg;

float tankHeight = 100.0;  // Height of the water tank in cm (adjust as needed)
float maxDistance = tankHeight; // Maximum distance for 100% full tank

void setup() {
  sevseg.begin(COMMON_ANODE, 3, 2, 1, 0, 4, 5, 6, 7, 8, 9); // Replace pin numbers with your connections
  sevseg.setBrightness(100);  // Adjust brightness as needed
  sevseg.setNumber(0);  // Initialize display to 0%
  sevseg.refreshDisplay();

  Serial.begin(115200);
}

void loop() {
  // Measure distance using HC-SR04
  float distance = ultrasonic.read();

  // Calculate tank level percentage
  int tankPercentage = map(distance, 0, maxDistance, 100, 0);
  tankPercentage = constrain(tankPercentage, 0, 100);

  // Display tankPercentage on the seven-segment display
  sevseg.setNumber(tankPercentage);
  sevseg.refreshDisplay();

  // Print tankPercentage to Serial Monitor for debugging
  Serial.print("Tank Percentage: ");
  Serial.println(tankPercentage);

  delay(1000);  // Delay for updating the display
}
