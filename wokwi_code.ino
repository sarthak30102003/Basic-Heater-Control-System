#include <OneWire.h>
#include <DallasTemperature.h>

// DS18B20 pin
#define ONE_WIRE_BUS A0
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

// LED pin mappings
const int redLED = 2;     // Overheat
const int blueLED = 3;    // Idle
const int yellowLED = 4;  // Stabilizing
const int greenLED = 5;   // Heating
const int orangeLED = 6;  // Target Reached
const int heaterPin = 7;
const int buzzerPin = 8;

float celsius = 0;

enum HeaterState {
  IDLE,
  HEATING,
  STABILIZING,
  TARGET_REACHED,
  OVERHEAT
};

HeaterState currentState = IDLE;

void setup() {
  pinMode(redLED, OUTPUT);
  pinMode(blueLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(orangeLED, OUTPUT);
  pinMode(heaterPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);

  Serial.begin(9600);
  sensors.begin(); // Initialize DS18B20
}

void loop() {
  sensors.requestTemperatures(); 
  celsius = sensors.getTempCByIndex(0); // Read °C from first sensor

  updateState(celsius);
  controlLEDs();
  logStatus(celsius);

  delay(1000);
}

void updateState(float temp) {
  if (temp < 30) {
    currentState = IDLE;
  } else if (temp >= 30 && temp < 38) {
    currentState = HEATING;
  } else if (temp >= 38 && temp < 42) {
    currentState = STABILIZING;
  } else if (temp >= 42 && temp < 50) {
    currentState = TARGET_REACHED;
  } else if (temp >= 50) {
    currentState = OVERHEAT;
  }
}

void controlLEDs() {
  // Turn all outputs OFF first
  digitalWrite(redLED, LOW);
  digitalWrite(blueLED, LOW);
  digitalWrite(yellowLED, LOW);
  digitalWrite(greenLED, LOW);
  digitalWrite(orangeLED, LOW);
  digitalWrite(heaterPin, LOW);
  digitalWrite(buzzerPin, LOW);

  switch (currentState) {
    case IDLE:
      digitalWrite(blueLED, HIGH);
      break;
    case HEATING:
      digitalWrite(greenLED, HIGH);
      digitalWrite(heaterPin, HIGH);
      break;
    case STABILIZING:
      digitalWrite(yellowLED, HIGH);
      digitalWrite(heaterPin, HIGH);
      break;
    case TARGET_REACHED:
      digitalWrite(orangeLED, HIGH);
      break;
    case OVERHEAT:
      digitalWrite(redLED, HIGH);
      digitalWrite(buzzerPin, HIGH);
      break;
  }
}

void logStatus(float temp) {
  Serial.print("Temperature: ");
  Serial.print(temp);
  Serial.print(" °C | State: ");
  switch (currentState) {
    case IDLE:
      Serial.println("IDLE");
      break;
    case HEATING:
      Serial.println("HEATING");
      Serial.println("TURNING THE HEATER PIN ON");
      break;
    case STABILIZING:
      Serial.println("STABILIZING");
      break;
    case TARGET_REACHED:
      Serial.println("TARGET_REACHED");
      Serial.println("TURNING THE HEATER PIN OFF");
      break;
    case OVERHEAT:
      Serial.println("OVERHEAT");
      break;
  }
}
