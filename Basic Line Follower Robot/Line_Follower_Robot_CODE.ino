// Motor driver pins
#define ENA 6
#define ENB 5
#define IN1 7
#define IN2 8
#define IN3 9
#define IN4 10

// IR sensors
#define LEFT_SENSOR 11
#define RIGHT_SENSOR 12

// Speed settings
int motorSpeed = 72;       // Normal forward speed (You can change the speeds as you want..)
int turnRightSpeed = 68;   // Right turn speed
int turnLeftSpeed = 70;    // Left turn speed 
int searchSpeed = 60;      // Speed for 360-degree searching

void setup() {
  // Motor pins
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  // Sensor pins
  pinMode(LEFT_SENSOR, INPUT);
  pinMode(RIGHT_SENSOR, INPUT);
}

void loop() {
  int left = digitalRead(LEFT_SENSOR);
  int right = digitalRead(RIGHT_SENSOR);

  if (left == LOW && right == LOW) {
    moveForward();
  } 
  else if (left == HIGH && right == LOW) {
    turnLeft();
    delay(160);  // Delay to help with sharper left turns
  } 
  else if (left == LOW && right == HIGH) {
    turnRight();
    delay(160);  // Delay to help with sharper right turns
  } 
  else if (left == HIGH && right == HIGH) {
    // Lost the line - spin to relocate
    searchForLine();
  } 
  else {
    stopMotors(); // Safety stop
  }
}

void moveForward() {
  analogWrite(ENA, motorSpeed);
  analogWrite(ENB, motorSpeed);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void turnLeft() {
  analogWrite(ENA, turnLeftSpeed);
  analogWrite(ENB, turnLeftSpeed);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void turnRight() {
  analogWrite(ENA, turnRightSpeed);
  analogWrite(ENB, turnRightSpeed);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void stopMotors() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void searchForLine() {
  // Rotate clockwise to search for line
  analogWrite(ENA, searchSpeed);
  analogWrite(ENB, searchSpeed);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);

  delay(1200); // Adjust this for better results (rotate duration)
  stopMotors();
}
