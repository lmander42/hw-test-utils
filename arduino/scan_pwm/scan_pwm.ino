/**
 * Scans PWM on pin 9;
 */

const uint16_t pwm[4] = [500, 1000, 1500, 2000, 2500];
uint8_t pwm_index = 0;
 
void setup()
{
  Serial.begin(9600);
  Serial.println("Press enter to increment PWM");
  testServo.attach(9);
}

void loop()
{
  if (Serial.available()) {
    pwm_index += 1;
    pwm_index %= 5;
    testServo.writeMicroseconds(pwm[pwm_index]);
    Serial.println("Press enter to increment PWM");
  }
}
