/**
 * Increments/Decrements PWM as the joystick is help
 */

#include <Servo.h>

const int xpin = A0;  // xdir reader
const int ypin = A1;  // ydir reader
const int bt = 8;     // button pin
Servo xservo;
Servo yservo;

int prevstate = LOW;
int state;
int xval;
int yval;
int xpos = 90;
int ypos = 90;

long reftime, curtime;

void setup()
{
  Serial.begin(9600);
  pinMode(bt, INPUT);
  xservo.attach(10);
  yservo.attach(11);
  reftime = millis();
}

void loop()
{
  // read state
  xval = analogRead(xpin);
  yval = analogRead(ypin);
  state = digitalRead(bt);
  curtime = millis();

  // button press
  if (state != prevstate && state == HIGH) {
    Serial.println("Button pressed!");
    Serial.print("xpos: "); Serial.print(xpos);
    Serial.print(" ypos: "); Serial.println(ypos);
  }
  prevstate = state;

  // Move servos
  if (curtime - reftime > 50) {
    if (xval >= 450) {
      xpos += 1;
    } else if (xval <= 150) {
      xpos -= 1;
    }
    if (yval >= 450) {
      ypos += 1;
    } else if (yval <= 150) {
      ypos -= 1;
    }
    xpos = constrain(xpos, 0, 180);
    ypos = constrain(ypos, 0, 180);
    xservo.write(xpos);
    yservo.write(xpos);
    
    reftime = millis();
  }
}
