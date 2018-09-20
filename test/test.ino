const int pwm_1 = 9;
int left1 = 8, left2 = 9, right1 = 10, right2 = 11;
void motor_control()
{

  digitalWrite(left1, HIGH);
  digitalWrite(left2, LOW);
  digitalWrite(right1, HIGH);
  digitalWrite(right2, LOW);
  analogWrite(3, 245 );
  analogWrite(5, 250 );

}
void setup() {
  Serial.begin(9600);
  pinMode(left1, OUTPUT);
  pinMode(left2, OUTPUT);
  pinMode(right1, OUTPUT);
  pinMode(right2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(5, OUTPUT);
  delay(500);
}

void loop() {
  motor_control();
}
