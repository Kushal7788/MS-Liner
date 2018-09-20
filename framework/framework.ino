#define lpwm 3
#define left1 4
#define left2 5
#define rpwm 9
#define right1 10
#define right2 11
int count, vflag = 0;
int lcorr = 30, rcorr = 0; // Add zero error if required here
int left, right;          // Give the base pwm here
int ltval = left + lcorr; //These are for total value considering the corrected val
int rtval = right + rcorr;
uint8_t sensor1;    //For cytron
void setup() {

  Serial.begin(9600);

  pinMode(left1, OUTPUT);
  pinMode(left2, OUTPUT);
  pinMode(right1, OUTPUT);
  pinMode(right2, OUTPUT);
  pinMode(lpwm, OUTPUT);
  pinMode(rpwm, OUTPUT);
}
void forward()
{
  digitalWrite(left1, HIGH);
  digitalWrite(left2, LOW);
  digitalWrite(right1, HIGH);
  digitalWrite(right2, LOW);

  left = 220;
  right = 220;
  analogWrite(lpwm, ltval);
  analogWrite(rpwm, rtval);
}
void sleft()          //slight left
{
  digitalWrite(left1, HIGH);
  digitalWrite(left2, LOW);
  digitalWrite(right1, HIGH);
  digitalWrite(right2, LOW);

  left = 220;
  right = 250;
  analogWrite(lpwm, ltval);
  analogWrite(rpwm, rtval);
}
void sright()     //slight right
{
  digitalWrite(left1, HIGH);
  digitalWrite(left2, LOW);
  digitalWrite(right1, HIGH);
  digitalWrite(right2, LOW);

  left = 250;
  right = 220;
  analogWrite(lpwm, ltval);
  analogWrite(rpwm, rtval);
}
void back()
{
  digitalWrite(left1, LOW);
  digitalWrite(left2, HIGH);
  digitalWrite(right1, LOW);
  digitalWrite(right2, HIGH);

  left = 220;
  right = 220;
  analogWrite(lpwm, ltval);
  analogWrite(rpwm, rtval);
}
void lturn()      //left turn
{
  digitalWrite(left1, LOW);
  digitalWrite(left2, HIGH);
  digitalWrite(right1, HIGH);
  digitalWrite(right2, LOW);

  left = 220;
  right = 220;
  analogWrite(lpwm, ltval);
  analogWrite(rpwm, rtval);
}
void rturn()      //right turn
{
  digitalWrite(left1, HIGH);
  digitalWrite(left2, LOW);
  digitalWrite(right1, LOW);
  digitalWrite(right2, HIGH);

  left = 220;
  right = 220;
  analogWrite(lpwm, ltval);
  analogWrite(rpwm, rtval);
}

void srturn()      //right turn
{
  digitalWrite(left1, HIGH);
  digitalWrite(left2, LOW);
  digitalWrite(right1, LOW);
  digitalWrite(right2, HIGH);

  left = 80;
  right = 80;
  analogWrite(lpwm, ltval);
  analogWrite(rpwm, rtval);
}
void slturn()      //left turn
{
  digitalWrite(left1, LOW);
  digitalWrite(left2, HIGH);
  digitalWrite(right1, HIGH);
  digitalWrite(right2, LOW);

  left = 80;
  right = 80;
  analogWrite(lpwm, ltval);
  analogWrite(rpwm, rtval);
}
void slforward()    //slow forward
{
  digitalWrite(left1, HIGH);
  digitalWrite(left2, LOW);
  digitalWrite(right1, HIGH);
  digitalWrite(right2, LOW);

  left = 140;
  right = 140;
  analogWrite(lpwm, ltval);
  analogWrite(rpwm, rtval);
}
void adjust()
{
  sensor1 = PINC;
  if ((sensor1 | B00011000) == B00111000 || (sensor1 | B00011000) == B01111000 || (sensor1 | B00011000) == B11111000 || (sensor1 | B11011000) == B11011000 || (sensor1 | B11011000) == B10011000) // adjust left
  {
    sleft();
  }
  else if ((sensor1 | B00011000) == B00011100 || (sensor1 | B00011000) == B00011110 || (sensor1 | B00011000) == B00011111 || (sensor1 | B11011000) == B00011011 || (sensor1 | B11011000) == B00011001) // adjust right
  {
    sright();
  }
  else if (sensor1 == B00000000)    //When Line is not there
  {
    forward();
  }
}
void phase()    //call when black line comes on white surface
{
  sensor1 = PINC;
  if (((sensor1 | B00100100) == B11100111 || (sensor1 | B00100100) == B11110111 || (sensor1 | B00100100) == B11101111) || ((sensor1 | B00110000) == B11110011 || (sensor1 | B00110000) == B11111011 || (sensor1 | B00001100) == B11001111 || (sensor1 | B00001100) == B11011111))  //when Black on White OFF
  {
    sensor1 = ~sensor1;
    adjust();
  }
}
void vrturn()   //V shape right turn
{
  sensor1 = PINC;
  if ((sensor1 | B00011000) == B00011001 || (sensor1 | B00011000) == B00011011)
  {
    while (sensor1 != B00011000 || sensor1 != B00001100)
      slforward();
    vflag = 1;
  }
  if ((sensor1 == B00011000) && vflag == 1)
  {
    rturn();
    while ((sensor1 | B00011000) == B00011111)
      rturn();
    rturn();
    delay(100);
    vflag = 0;
  }
  else if (vflag == 1)
  {
    if ((sensor1 | B00011000) == B00111000 || (sensor1 | B00011000) == B01111000 || (sensor1 | B00011000) == B11111000 || (sensor1 | B11011000) == B11011000 || (sensor1 | B11011000) == B10011000) // adjust left
    {
      slturn();
    }
    else if ((sensor1 | B00011000) == B00011100 || (sensor1 | B00011000) == B00011110 || (sensor1 | B00011000) == B00011111 || (sensor1 | B11011000) == B00011011 || (sensor1 | B11011000) == B00011001) // adjust right
    {
      srturn();
    }
  }
}
void vlturn()   //V shape left turn
{
  sensor1 = PINC;
  if ((sensor1 | B00011000) == B10011000 || (sensor1 | B00011000) == B11011000)
  {
    while (sensor1 != B00011000 || sensor1 != B00110000)
      slforward();
    vflag = 1;
  }
  if ((sensor1 == B00011000) && vflag == 1)
  {
    lturn();
    while ((sensor1 | B00011000) == B11111000)
      lturn();
    lturn();
    delay(100);
    vflag = 0;
  }
  else if (vflag == 1)
  {
    if ((sensor1 | B00011000) == B00111000 || (sensor1 | B00011000) == B01111000 || (sensor1 | B00011000) == B11111000 || (sensor1 | B11011000) == B11011000 || (sensor1 | B11011000) == B10011000) // adjust left
    {
      slturn();
    }
    else if ((sensor1 | B00011000) == B00011100 || (sensor1 | B00011000) == B00011110 || (sensor1 | B00011000) == B00011111 || (sensor1 | B11011000) == B00011011 || (sensor1 | B11011000) == B00011001) // adjust right
    {
      srturn();
    }
  }
}
void turn() //turn when found junction
{
  if (((sensor1 | B10000000) == B11111000) || ((sensor1 | B10000000) == B11110000)) //turn left
  {
    while ((sensor1 | B10000001) == B11111111)
      lturn();
  }
  else if (((sensor1 | B00000001) == B00011111) || ((sensor1 | B00000001) == B00001111)) //turn right
  {
    while ((sensor1 | B10000001) == B11111111)
      rturn();
  }
}
void loop() {
  // put your main code here, to run repeatedly:
  forward();
  //adjust();
  sensor1 = PINC;
  Serial.println(PINC, BIN);


}
