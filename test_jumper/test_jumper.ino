
#define zone1 A2
#define rezone1 13
#define turnall A0
#define turnlast A1
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(zone1, INPUT_PULLUP);
  pinMode(rezone1, INPUT_PULLUP);
  pinMode(turnall, INPUT_PULLUP);
  pinMode(turnlast, INPUT_PULLUP);
    pinMode(A0, INPUT_PULLUP);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print(digitalRead(zone1));

  Serial.print(digitalRead(rezone1));

  Serial.print(digitalRead(turnall));

  Serial.println(digitalRead(turnlast));

}
