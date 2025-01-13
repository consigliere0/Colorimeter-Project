#include <Arduino.h> 
// Pins dels LEDs
const int ledPins[5] = { 2, 3, 4, 5, 6 };  
const int comparatorPin = 7;               
const int capacitorPin = 8;                
const int switchPin = 9;

// Constants
const int numLeds = 5;              
const unsigned long timeout = 20000; 


bool sequenceCompleted = false;

// Array to store charge times
unsigned long chargeTimes[5];  // Stores charge times for the 5 LEDs

void setup() {
  
  pinMode(switchPin, INPUT_PULLUP); 
  for (int i = 0; i < numLeds; i++) {
    pinMode(ledPins[i], OUTPUT);
    digitalWrite(ledPins[i], HIGH);  // LEDs apagats
  }

  
  pinMode(comparatorPin, INPUT);

  
  pinMode(capacitorPin, OUTPUT);
  digitalWrite(capacitorPin, LOW);

  
  Serial.begin(9600);
  delay(3000);

  
  Serial.println("Place the white card and press switch when done.");

  
  while (digitalRead(switchPin) == HIGH) {
    
  }

  
  calibrateWhiteCard();

  
  Serial.println("Callibration complete.");
  Serial.println("Place the unknown card and press switch when done.");

  
  while (digitalRead(switchPin) == HIGH) {
  
  }

  measureUnknownCard();
  Serial.println("Introduce the data in Matlab in the form of row vectors.");
}

 

void loop() {
  if (!sequenceCompleted) {
    for (int i = 0; i < numLeds; i++) {
      manageLedAndCapacitor(i);
      delay(2000);
    }
    sequenceCompleted = true;
    Serial.println("LED sequence complete.");
  }
}

void manageLedAndCapacitor(int ledIndex) {
  for (int i = 0; i < numLeds; i++) {
    digitalWrite(ledPins[i], HIGH);
  }
  pinMode(capacitorPin, OUTPUT);
  digitalWrite(capacitorPin, LOW);
  delay(1000);

  digitalWrite(ledPins[ledIndex], LOW);
  Serial.print("LED ");
  Serial.print(ledIndex + 1);
  Serial.println(" ON.");

  pinMode(capacitorPin, INPUT);

  // Inicia el temporitzador
  unsigned long start = millis();

  while (digitalRead(comparatorPin) == LOW) {
    if (millis() - start > timeout) {
      Serial.print("Error: el comparador no ha canviat d'estat en el temps esperat per al LED ");
      Serial.println(ledIndex + 1);
      break;
    }
  }

  // Mesura el temps transcorregut
  unsigned long elapsedTime = millis() - start;

  chargeTimes[ledIndex] = elapsedTime;  // Store the elapsed time in the array

  digitalWrite(ledPins[ledIndex], HIGH);

  Serial.print("LED ");
  Serial.print(ledIndex + 1);
  Serial.println(" OFF.");

  Serial.print("Capacitor charge time ");
  Serial.print(ledIndex + 1);
  Serial.print(": ");
  Serial.print(elapsedTime);
  Serial.println(" ms.");
}

void calibrateWhiteCard() {
  if (!sequenceCompleted) {
    for (int i = 0; i < numLeds; i++) {
      manageLedAndCapacitor(i);
      delay(2000);  // Retard entre transicions de LEDs
    }
    Serial.println("LED sequence complete.");
    sendDataToMATLAB();  // Send calibration data to MATLAB
  }
}

void measureUnknownCard() {
  if (!sequenceCompleted) {
    for (int i = 0; i < numLeds; i++) {
      manageLedAndCapacitor(i);
      delay(2000);  // Retard entre transicions de LEDs
    }
    sequenceCompleted = true;
    Serial.println("LED sequence complete.");
    sendDataToMATLAB();  // Send unknown card data to MATLAB
  }
}

// New function to send data to MATLAB
void sendDataToMATLAB() {
  for (int i = 0; i < numLeds; i++) {
    Serial.print(chargeTimes[i]);  // Send each charge time
    Serial.print(' ');
    if (i < numLeds - 1) {
//    Serial.print();
    }
  }
  Serial.println();
}