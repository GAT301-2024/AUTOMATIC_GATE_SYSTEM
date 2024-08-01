#include <Servo.h>
#include <NewPing.h>

// Define pins
#define TRIGGER_PIN 12
#define ECHO_PIN 13
#define SERVO_PIN 9

const int ledPin=8;
// Define constants
#define MAX_DISTANCE 200 // Maximum distance (in cm) to ping.
#define OPEN_ANGLE 90    // Angle to open the gate.
#define CLOSE_ANGLE 0    // Angle to close the gate.
#define DETECTION_DISTANCE 10 // Distance (in cm) to detect a car.
#define BUZZER_PIN 6

// Create objects
Servo gateServo;
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

void setup() {
    Serial.begin(9600);
    gateServo.attach(SERVO_PIN);
    gateServo.write(CLOSE_ANGLE); // Initialize the gate as closed.
    pinMode(ledPin,OUTPUT);
    pinMode(BUZZER_PIN,OUTPUT);
}

void loop() {
    unsigned int distance = sonar.ping_cm();

    if (distance != 0 && distance < DETECTION_DISTANCE) {
        // Car detected, open the gate
        Serial.println("Car detected, opening gate...");
        gateServo.write(OPEN_ANGLE);
        digitalWrite(ledPin,HIGH);
        digitalWrite(BUZZER_PIN,HIGH);
        delay(5000); // Keep the gate open for 5 seconds.
    } else {
        // No car detected, close the gate
        Serial.println("No car detected, closing gate...");
        gateServo.write(CLOSE_ANGLE);
        digitalWrite(ledPin,LOW);
        digitalWrite(BUZZER_PIN,LOW);
    }

    delay(1000); // Wait for 1 second before checking again.
}
