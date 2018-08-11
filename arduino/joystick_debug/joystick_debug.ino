/**
 * Prints state of joystick every 0.5s, and any time
 * the button is pressed.
 */

const int xpin = A0;  // xdir reader
const int ypin = A1;  // ydir reader
const int bt = 8;     // button pin

int prevstate = LOW;
int state;
int xval;
int yval;

long reftime, curtime;

void setup()
{
  Serial.begin(9600);
  pinMode(bt, INPUT);
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
    Serial.print("xval: "); Serial.print(xval);
    Serial.print(" yval: "); Serial.println(yval);
    reftime = millis();
  }
  prevstate = state;

  // output
  if (curtime - reftime > 500) {
    Serial.print("xval: "); Serial.print(xval);
    Serial.print(" yval: "); Serial.println(yval);
    reftime = millis();
  }
}
