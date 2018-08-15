/**
 * Moves servo on Pin9 to a position from serial
 */
#include <Servo.h>
Servo testServo;
int pos = 0;
int tmp;

void setup()
{
  Serial.begin(9600);
  testServo.attach(10);
}


void loop()
{
  if (Serial.available()) {
    tmp = Serial.parseInt();
    if (tmp > 180 || tmp < 0) {
      Serial.println("Position must be on [0, 180]!");
    } else {
      pos = tmp;
      Serial.print("Moving to ");
      Serial.println(pos);
    }
  }
  testServo.write(pos);
}
