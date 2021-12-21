/*
   This sketch is used to check the direction of left and right wheel.

   Open the Serial Monitor to check the test message
*/


//  Define Arduino pin for left motor
#define enA 10
#define in1 2
#define in2 3

// Define Arduino pin for right motor
#define enB 11
#define in3 4
#define in4 5

int motor_speed = 100;

void setup() {
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  Serial.println("Rotate left motor forward for 3 seconds");
  leftMotorFwd(motor_speed);
  delay(3000);

  Serial.println("Left motor stop");
  leftMotorStop();
  delay(1000);

  Serial.println("Rotate left motor reverse for 3 seconds");
  leftMotorRev(motor_speed);
  delay(3000);

  Serial.println("Left motor stop");
  leftMotorStop();
  delay(1000);

  Serial.println("Rotate right motor forward for 3 seconds");
  rightMotorFwd(motor_speed);
  delay(3000);

  Serial.println("right motor stop");
  rightMotorStop();
  delay(1000);

  Serial.println("Rotate right motor reverse for 3 seconds");
  rightMotorRev(motor_speed);
  delay(3000);

  Serial.println("right motor stop");
  rightMotorStop();

  Serial.println("Reset Arduino Board to repeat the test");
  while (1);
}

void leftMotorStop() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  analogWrite(enA, 0); // stop left motor
}

void leftMotorRev(int val) {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  analogWrite(enA, val); // Send PWM signal to left motor
}

void leftMotorFwd(int val) {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  analogWrite(enA, val); // Send PWM signal to left motor
}

void rightMotorStop() {
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  analogWrite(enB, 0); // stop right motor
}

void rightMotorRev(int val) {
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(enB, val);
}

void rightMotorFwd(int val) {
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  analogWrite(enB, val);
}
