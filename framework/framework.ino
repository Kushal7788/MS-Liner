#define lpwm 7
#define left1 5
#define left2 6
#define rpwm 4
#define right1 3
#define right2 2
#define maxpwm 210
#define slturn 80
#define sladj 15
#define mdadj 25
#define hdadj 40
#define turn 200
#define minpwm 80
#define reading
int count, vflag = 0;
int lcorr = -30, rcorr = 0; // Add zero error if required here
int left = 0, right = 0;      // Give the base pwm here
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
#ifdef reading
  Serial.println("In Forward");
#endif
  digitalWrite(left1, HIGH);
  digitalWrite(left2, LOW);
  digitalWrite(right1, HIGH);
  digitalWrite(right2, LOW);
  Serial.println("forward");
  left = right = maxpwm;

  analogWrite(lpwm, ltval);
  analogWrite(rpwm, rtval);
}
void sleft()          //slight left
{
#ifdef reading
  Serial.println("In slight left adj");
#endif
  digitalWrite(left1, HIGH);
  digitalWrite(left2, LOW);
  digitalWrite(right1, HIGH);
  digitalWrite(right2, LOW);

  left = maxpwm - sladj;
  right = maxpwm + sladj;
  analogWrite(lpwm, ltval);
  analogWrite(rpwm, rtval);
}
void hleft()          //slight left
{
#ifdef reading
  Serial.println("In hard left adj");
#endif
  digitalWrite(left1, HIGH);
  digitalWrite(left2, LOW);
  digitalWrite(right1, HIGH);
  digitalWrite(right2, LOW);

  left = maxpwm - hdadj;
  right = maxpwm + hdadj;
  analogWrite(lpwm, ltval);
  analogWrite(rpwm, rtval);
}
void mleft()          //slight left
{
#ifdef reading
  Serial.println("In med left adj");
#endif
  digitalWrite(left1, HIGH);
  digitalWrite(left2, LOW);
  digitalWrite(right1, HIGH);
  digitalWrite(right2, LOW);

  left = maxpwm - mdadj;
  right = maxpwm + mdadj;
  analogWrite(lpwm, ltval);
  analogWrite(rpwm, rtval);
}
void sright()     //slight right
{
#ifdef reading
  Serial.println("In slight right adj");
#endif
  digitalWrite(left1, HIGH);
  digitalWrite(left2, LOW);
  digitalWrite(right1, HIGH);
  digitalWrite(right2, LOW);

  left = maxpwm + sladj;
  right = maxpwm - sladj;
  analogWrite(lpwm, ltval);
  analogWrite(rpwm, rtval);
}
void hright()     //slight right
{
#ifdef reading
  Serial.println("In hard right adj");
#endif
  digitalWrite(left1, HIGH);
  digitalWrite(left2, LOW);
  digitalWrite(right1, HIGH);
  digitalWrite(right2, LOW);

  left = maxpwm + hdadj;
  right = maxpwm - hdadj;
  analogWrite(lpwm, ltval);
  analogWrite(rpwm, rtval);
}
void mright()     //slight right
{
#ifdef reading
  Serial.println("In med right adj");
#endif
  digitalWrite(left1, HIGH);
  digitalWrite(left2, LOW);
  digitalWrite(right1, HIGH);
  digitalWrite(right2, LOW);

  left = maxpwm + mdadj;
  right = maxpwm - mdadj;
  analogWrite(lpwm, ltval);
  analogWrite(rpwm, rtval);
}
void back()
{
#ifdef reading
  Serial.println("In Forward");
#endif
  digitalWrite(left1, LOW);
  digitalWrite(left2, HIGH);
  digitalWrite(right1, LOW);
  digitalWrite(right2, HIGH);

  left = maxpwm;
  right = maxpwm;
  analogWrite(lpwm, ltval);
  analogWrite(rpwm, rtval);
}
void lturn()      //left turn
{
#ifdef reading
  Serial.println("In left turn");
#endif
  digitalWrite(left1, LOW);
  digitalWrite(left2, HIGH);
  digitalWrite(right1, HIGH);
  digitalWrite(right2, LOW);

  left = right = turn;
  analogWrite(lpwm, ltval);
  analogWrite(rpwm, rtval);
}
void rturn()      //right turn
{
#ifdef reading
  Serial.println("In right turn");
#endif
  digitalWrite(left1, HIGH);
  digitalWrite(left2, LOW);
  digitalWrite(right1, LOW);
  digitalWrite(right2, HIGH);

  left = right = turn;
  analogWrite(lpwm, ltval);
  analogWrite(rpwm, rtval);
}

void srtturn()      //right turn
{
#ifdef reading
  Serial.println("In slow right turn");
#endif
  digitalWrite(left1, HIGH);
  digitalWrite(left2, LOW);
  digitalWrite(right1, LOW);
  digitalWrite(right2, HIGH);

  left = right = slturn;
  analogWrite(lpwm, ltval);
  analogWrite(rpwm, rtval);
}
void slfturn()      //left turn
{
#ifdef reading
  Serial.println("In slow left turn");
#endif
  digitalWrite(left1, LOW);
  digitalWrite(left2, HIGH);
  digitalWrite(right1, HIGH);
  digitalWrite(right2, LOW);

  left = right = slturn;
  analogWrite(lpwm, ltval);
  analogWrite(rpwm, rtval);
}
void slforward()    //slow forward
{
#ifdef reading
  Serial.println("In slow forward");
#endif
  digitalWrite(left1, HIGH);
  digitalWrite(left2, LOW);
  digitalWrite(right1, HIGH);
  digitalWrite(right2, LOW);

  left = right = minpwm;
  analogWrite(lpwm, ltval);
  analogWrite(rpwm, rtval);
}
void adjust()
{
  sensor1 = PINC;
  if ( sensor1 == B00010000  ) // adjust left
  {
    sleft();
  }
  else if (sensor1 == B00100000 || sensor1 == B00110000 ) // adjust med left
  {
    mleft();
  }
    else if (sensor1 == B00100000 || sensor1 == B00110000 ) // adjust med left
  {
    mright();
  }
  else if (sensor1 == B00001000 ) // adjust right
  {
    sright();
  }
  else if (sensor1 == B01100000 || sensor1 == B01000000) // hard left adjust
  {
    hleft();
  }
  else if (sensor1 == B00000110 || sensor1 == B00000010) // hard right adjust
  {
    hright();
  }
  else if (sensor1 == B00000000 || sensor1 == B00011000)  //When Line is not there
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
      slfturn();
    }
    else if ((sensor1 | B00011000) == B00011100 || (sensor1 | B00011000) == B00011110 || (sensor1 | B00011000) == B00011111 || (sensor1 | B11011000) == B00011011 || (sensor1 | B11011000) == B00011001) // adjust right
    {
      srtturn();
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
      slfturn();
    }
    else if ((sensor1 | B00011000) == B00011100 || (sensor1 | B00011000) == B00011110 || (sensor1 | B00011000) == B00011111 || (sensor1 | B11011000) == B00011011 || (sensor1 | B11011000) == B00011001) // adjust right
    {
      srtturn();
    }
  }
}
void rotate() //turn when found junction
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

  ltval = left + lcorr; //These are for total value considering the corrected val
  rtval = right + rcorr;
  // put your main code here, to run repeatedly:

  //forward();
  adjust();
  rotate();
  sensor1 = PINC;
  Serial.println(PINC, BIN);



}
