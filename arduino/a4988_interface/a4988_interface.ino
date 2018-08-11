const int dir_pin = 13;
const int step_pin = 12;
bool clockwise = true;

void setup() {
  pinMode(dir_pin, OUTPUT);
  pinMode(step_pin, OUTPUT);
  Serial.begin(9600);

  digitalWrite(dir_pin, LOW);
}

void loop() {
  // Switch direction command
  if (Serial.available()) {
    int incoming = Serial.read();
    if (incoming == '-') {
      clockwise = !clockwise;
      Serial.println("Changing direction!");
    }
  }

  // Direction control
  if (clockwise) {
    digitalWrite(dir_pin, LOW);
  } else {
    digitalWrite(dir_pin, HIGH);
  }
  delayMicroseconds(1);  // 200ns setup t
  
  // Step motor
  digitalWrite(step_pin, HIGH);
  delayMicroseconds(3);  // 1us setup time
  digitalWrite(step_pin, LOW);
  delayMicroseconds(3);
  Serial.println("Step!");
  delay(10);  // wait between steps
}
