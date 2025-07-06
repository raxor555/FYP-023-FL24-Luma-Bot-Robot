// Motor Pins
#define IN1 25
#define IN2 26
#define IN3 33
#define IN4 32

// Ultrasonic Sensor Pins
#define TRIG 18
#define ECHO 19

// Vacuum System
#define VACUUM_PIN 2

// Manual Start Button
#define BUTTON_PIN 4

// Timing
long duration;
int distance;

bool isRunning = false;

void setup() {
  // Motor Pins
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  // Vacuum
  pinMode(VACUUM_PIN, OUTPUT);
  digitalWrite(VACUUM_PIN, LOW);  // vacuum off initially

  // Ultrasonic Sensor
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);

  // Button
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  // Serial for debugging
  Serial.begin(115200);
}

void loop() {
  // Start on button press
  if (digitalRead(BUTTON_PIN) == LOW) {
    delay(200); // debounce
    isRunning = !isRunning; // toggle start/stop
    digitalWrite(VACUUM_PIN, isRunning ? HIGH : LOW);
    if (!isRunning) stopMotors();
    delay(500);
  }

  if (isRunning) {
    int distance = getDistance();

    if (distance < 20) {
      stopMotors();
      delay(300);
      moveBackward();
      delay(400);
      turnRight();
      delay(500);
    } else {
      moveForward();
    }
  }
}

// --- Functions ---
int getDistance() {
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);

  duration = pulseIn(ECHO, HIGH);
  int dist = duration * 0.034 / 2;

  Serial.print("Distance: ");
  Serial.println(dist);
  return dist;
}

void moveForward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void moveBackward() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void turnRight() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void stopMotors() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}
