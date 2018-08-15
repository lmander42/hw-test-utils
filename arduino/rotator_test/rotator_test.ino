/**
 * Stepper Motor test script using an
 * A4988 Stepper Motor Controller breakout board.
 * 
 * connect Pin12 to STEP
 * connect Pin13 to DIRECTION
 * 
 * Author: Marion Anderson
 * Date: 2018-08-11
 */
 #include <Servo.h>
 
const int dir_pin = 13;
const int step_pin = 12;
bool clockwise = true;

int pos = 0;

Servo elServo;

void setup()
{
  pinMode(dir_pin, OUTPUT);
  pinMode(step_pin, OUTPUT);
  elServo.attach(9);
  Serial.begin(9600);
}

void loop()
{
  // Switch direction command
  if (Serial.available()) {
    int incoming = Serial.read();
    if (incoming == '-') {
      clockwise = !clockwise;
      Serial.print("Changing direction to ");
      if (clockwise) {
        Serial.println("clockwise!");
      } else {
        Serial.println("counter clockwise!");
      }
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
  // delay(10);  // wait between steps

  elServo.write(pos);
  pos += 5;
  if (pos > 180) {
    pos = 0;
  }
  
  Serial.println(pos);
  delay(1000);
}
