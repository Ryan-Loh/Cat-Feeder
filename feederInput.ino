/*
  Analog Input

  Demonstrates analog input by reading an analog sensor on analog pin 0 and
  turning on and off a light emitting diode(LED) connected to digital pin 13.
  The amount of time the LED will be on and off depends on the value obtained
  by analogRead().

  The circuit:
  - potentiometer
    center pin of the potentiometer to the analog input 0
    one side pin (either one) to ground
    the other side pin to +5V
  - LED
    anode (long leg) attached to digital output 13
    cathode (short leg) attached to ground

  - Note: because most Arduinos have a built-in LED attached to pin 13 on the
    board, the LED is optional.

  created by David Cuartielles
  modified 30 Aug 2011
  By Tom Igoe

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/AnalogInput
*/

int sensorPin = A0;    // select the input pin for the potentiometer
int triggerPin = A3;      // select the pin for the LED
int sensorValue = 0;  // variable to store the value coming from the sensor
int piPin = A4; //Trigger pin ARDUINO to PI
int cumSum;
int maxR = 0;
int minR = 0;
int triggerValue = 0;

void setup() {
  // declare the ledPin as an OUTPUT:
  pinMode(triggerPin, INPUT);
  pinMode(sensorPin, INPUT);
  pinMode(piPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // read the value from the sensor:
  triggerValue = digitalRead(triggerPin);
  minR = 500;
  maxR = 0;
  while (triggerValue > 0) {
    for (int ii = 1; ii < 100; ii++) {
      sensorValue = analogRead(sensorPin);
      cumSum = cumSum + sensorValue;
      delay(1);
    }
    cumSum = cumSum / 100;
    if (cumSum > maxR) {
      maxR = cumSum;
    }
    if (cumSum < minR) {
      minR = cumSum;
    }
    Serial.print(cumSum);
    Serial.print(' ');
    Serial.println(maxR - minR);
    triggerValue = digitalRead(triggerPin);
    delay(1);
  }
  if (maxR - minR > 8) {
    digitalWrite(piPin, HIGH);
    delay(3000);
    digitalWrite(piPin, LOW);
    delay(1);
    Serial.println("Signal Sent");
  }
}
