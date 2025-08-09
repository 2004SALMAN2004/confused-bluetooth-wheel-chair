#include <AFMotor.h>

// Initialize 2 DC motors
AF_DCMotor motor1(1, MOTOR12_1KHZ); // Left motor
AF_DCMotor motor2(2, MOTOR12_1KHZ); // Right motor

char command;

void setup() {
  Serial.begin(9600); // Bluetooth module baud rate
}

void loop() {
  if (Serial.available() > 0) {
    command = Serial.read();
    Stop(); // Default to stop before any command

    switch (command) {
      case 'F':  // Forward command → Move backward
        back();
        break;
      case 'B':  // Backward command → Move forward
        forward();
        break;
      case 'L':  // Left command → Turn right
        right();
        break;
      case 'R':  // Right command → Turn left
        left();
        break;
      case 'S':  // Stop command
        Stop();
        break;
      default:
        Stop();
        break;
    }
  }
}

// ---------------- Motor Functions ----------------

void forward() {
  motor1.setSpeed(255);
  motor1.run(FORWARD);
  motor2.setSpeed(255);
  motor2.run(FORWARD);
}

void back() {
  motor1.setSpeed(255);
  motor1.run(BACKWARD);
  motor2.setSpeed(255);
  motor2.run(BACKWARD);
}

void left() {  // Car turns left
  motor1.setSpeed(0);       // Stop left motor
  motor2.setSpeed(255);     // Run right motor forward
  motor2.run(FORWARD);
}

void right() {  // Car turns right
  motor1.setSpeed(255);     // Run left motor forward
  motor1.run(FORWARD);
  motor2.setSpeed(0);       // Stop right motor
}

void Stop() {
  motor1.setSpeed(0);
  motor1.run(RELEASE);
  motor2.setSpeed(0);
  motor2.run(RELEASE);
}