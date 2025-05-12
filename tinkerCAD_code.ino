const int sensorPin = A0;

// LED pin mappings
const int redLED = 2;     // Overheat
const int blueLED = 3;    // Idle
const int yellowLED = 4;  // Stabilizing
const int greenLED = 5;   // Heating
const int orangeLED = 6;  // Target Reached
const int heaterPin = 7;
const int buzzerPin = 8;

int celsius = 0;

enum HeaterState {
  IDLE,
  HEATING,
  STABILIZING,
  TARGET_REACHED,
  OVERHEAT
};

HeaterState currentState = IDLE;

void setup() {
  pinMode(sensorPin, INPUT);

  pinMode(redLED, OUTPUT);
  pinMode(blueLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(orangeLED, OUTPUT);
  pinMode(heaterPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  int raw = analogRead(sensorPin);
  float voltage = raw * (5.0 / 1023.0);
  celsius = (voltage - 0.5) * 100.0;  // TMP36 formula

  updateState(celsius);
  controlLEDs();
  logStatus(celsius);

  delay(1000);
}

void updateState(int temp) {
  if (temp < 30) {
    currentState = IDLE;
  } else if (temp >= 30 && temp < 38) {
    currentState = HEATING;
  } else if (temp >= 38 && temp < 42) {
    currentState = STABILIZING;
  } else if (temp >= 42 && temp < 65) {
    currentState = TARGET_REACHED;
  } else if (temp >= 65) {
    currentState = OVERHEAT;
  }
}

void controlLEDs() {
  // Turn all LEDs off first
  digitalWrite(redLED, LOW);
  digitalWrite(blueLED, LOW);
  digitalWrite(yellowLED, LOW);
  digitalWrite(greenLED, LOW);
  digitalWrite(orangeLED, LOW);
  digitalWrite(heaterPin, LOW); // Turn off heater by default
  digitalWrite(buzzerPin, LOW);

  // Light the LED for the current state
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
      digitalWrite(heaterPin, LOW);
      break;
    case OVERHEAT:
      digitalWrite(redLED, HIGH);
      digitalWrite(buzzerPin, HIGH);
      break;
  }
}

void logStatus(int temp) {
  Serial.print("Temperature: ");
  Serial.print(temp);
  Serial.print(" C | State: ");
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
