#include <Servo.h>
#include <NewPing.h>

// Constants for pin configuration
const int trigPin = 12;
const int echoPin = 11;
const int leftMotorForward = 5;
const int leftMotorBackward = 4;
const int rightMotorForward = 3;
const int rightMotorBackward = 2;
const int servoPin = 9;

// Distance threshold for obstacle detection
const int obstacleDistanceThreshold = 20; // in centimeters

// Servo object to control the servo motor
Servo myServo;

// Ultrasonic sensor object
NewPing sonar(trigPin, echoPin, 200); // 200 cm max distance

void setup() {
  // Initialize motor pins as outputs
  pinMode(leftMotorForward, OUTPUT);
  pinMode(leftMotorBackward, OUTPUT);
  pinMode(rightMotorForward, OUTPUT);
  pinMode(rightMotorBackward, OUTPUT);

  // Initialize servo motor
  myServo.attach(servoPin);
  myServo.write(90); // Initial position at 90 degrees

  // Begin serial communication for debugging
  Serial.begin(9600);
}

void loop() {
  // Get distance from the ultrasonic sensor
  int distance = sonar.ping_cm();
  Serial.print("Distance: ");
  Serial.println(distance);

  if (distance > 0 && distance < obstacleDistanceThreshold) {
    // Obstacle detected
    Serial.println("Obstacle detected! Taking evasive action.");
    stopMotors();
    delay(500);
    turnRight();
    delay(500);
    stopMotors();
    delay(500);
  } else {
    // No obstacle, move forward
    moveForward();
  }

  delay(100);
}

void moveForward() {
  digitalWrite(leftMotorForward, HIGH);
  digitalWrite(leftMotorBackward, LOW);
  digitalWrite(rightMotorForward, HIGH);
  digitalWrite(rightMotorBackward, LOW);
}

void moveBackward() {
  digitalWrite(leftMotorForward, LOW);
  digitalWrite(leftMotorBackward, HIGH);
  digitalWrite(rightMotorForward, LOW);
  digitalWrite(rightMotorBackward, HIGH);
}

void turnLeft() {
  digitalWrite(leftMotorForward, LOW);
  digitalWrite(leftMotorBackward, HIGH);
  digitalWrite(rightMotorForward, HIGH);
  digitalWrite(rightMotorBackward, LOW);
}

void turnRight() {
  digitalWrite(leftMotorForward, HIGH);
  digitalWrite(leftMotorBackward, LOW);
  digitalWrite(rightMotorForward, LOW);
  digitalWrite(rightMotorBackward, HIGH);
}

void stopMotors() {
  digitalWrite(leftMotorForward, LOW);
  digitalWrite(leftMotorBackward, LOW);
  digitalWrite(rightMotorForward, LOW);
  digitalWrite(rightMotorBackward, LOW);
}

void scanWithServo() {
  for (int pos = 0; pos <= 180; pos += 1) {
    myServo.write(pos);
    delay(15);
  }
  for (int pos = 180; pos >= 0; pos -= 1) {
    myServo.write(pos);
    delay(15);
  }
}

