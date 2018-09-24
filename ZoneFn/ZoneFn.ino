#define lpwm 7
#define left1 5
#define left2 6
#define rpwm 4
#define right1 3
#define right2 2
#define maxpwm 215
#define slturn 130
#define sladj 55
#define mdadj 70
#define hdadj 100
#define turn 150
#define minpwm 120
#define bkpwm 120
#define reading
#define zone1 12
#define rezone1 11
#define zone2 10

bool ph = false, phaseflag = false, rotateflag = false;
int count = 0, countlturn = 0, countrturn = 0;
int lcorr = -35, rcorr = 0; // Add zero error if required here
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
  pinMode(zone1, INPUT);
  pinMode(rezone1, INPUT);
  pinMode(zone2, INPUT);
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

  analogWrite(lpwm, left + lcorr);
  analogWrite(rpwm, right + rcorr);
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
  right = maxpwm;
  analogWrite(lpwm, left + lcorr);
  analogWrite(rpwm, right + rcorr);
}
void hleft()          //slight left
{
#ifdef reading
  Serial.println("In hard left adj");

  digitalWrite(left1, HIGH);
  digitalWrite(left2, LOW);
  digitalWrite(right1, HIGH);
  digitalWrite(right2, LOW);
#endif
  left = maxpwm - hdadj;
  right = maxpwm;
  analogWrite(lpwm, left + lcorr);
  analogWrite(rpwm, right + rcorr);
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
  right = maxpwm;
  analogWrite(lpwm, left + lcorr);
  analogWrite(rpwm, right + rcorr);
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

  left = maxpwm;
  right = maxpwm - sladj;
  analogWrite(lpwm, left + lcorr);
  analogWrite(rpwm, right + rcorr);
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

  left = maxpwm ;
  right = maxpwm - hdadj;
  analogWrite(lpwm, left + lcorr);
  analogWrite(rpwm, right + rcorr);
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

  left = maxpwm;
  right = maxpwm - mdadj;
  analogWrite(lpwm, left + lcorr);
  analogWrite(rpwm, right + rcorr);
}
void back()
{
#ifdef reading
  Serial.println("In Back");
#endif
  digitalWrite(left1, LOW);
  digitalWrite(left2, HIGH);
  digitalWrite(right1, LOW);
  digitalWrite(right2, HIGH);

  left = right = bkpwm;
  analogWrite(lpwm, left + lcorr);
  analogWrite(rpwm, right + rcorr);
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
  analogWrite(lpwm, left + lcorr);
  analogWrite(rpwm, right + rcorr);
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
  analogWrite(lpwm, left + lcorr);
  analogWrite(rpwm, right + rcorr);
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

  left = 170;
  right = 80;
  analogWrite(lpwm, left + lcorr);
  analogWrite(rpwm, right + rcorr);
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

  left = 105 ;
  right = 170;
  analogWrite(lpwm, left + lcorr);
  analogWrite(rpwm, right + rcorr);
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
  analogWrite(lpwm, left + lcorr);
  analogWrite(rpwm, right + rcorr);
}
void adjust()
{
  sensor1 = PINC;
  if ( sensor1 == B00010000 || sensor1 == B00110000 ) // adjust slight left
  {
    sleft();
  }
  else if (sensor1 == B00100000 || sensor1 == B01100000 ) // adjust med left
  {
    mleft();
  }
  else if ( sensor1 == B01000000 || sensor1 == B11000000) // hard left adjust
  {
    hleft();
  }
  else if (sensor1 == B00001000 || sensor1 == B00001100 ) // adjust slight right
  {
    sright();
  }
  else if ( sensor1 == B00000100 || sensor1 == B00000110) // adjust med right
  {
    mright();
  }
  else if ( sensor1 == B00000010 || sensor1 == B00000011) // hard right adjust
  {
    hright();
  }
  else if (sensor1 == B00011000)  //When Line is not there
  {
    forward();
  }
  else if (sensor1 == B00000000 )
  {
    forward();
    rotateflag = true;
  }
}
void phase()    //call when black line comes on white surface
{
  sensor1 = PINC;
  if (((sensor1 | B00100100) == B11100111 || (sensor1 | B00100100) == B11110111 || (sensor1 | B00100100) == B11101111) || ((sensor1 | B00110000) == B11110011 || (sensor1 | B00110000) == B11111011 || (sensor1 | B00001100) == B11001111 || (sensor1 | B00001100) == B11011111) || (sensor1 | B01111000) == B11111001) || (sensor1 | B00011110) == B10011111)) //when Black on White OFF
  {
    sensor1 = ~sensor1;
    ph = true;
  }
  else
  {
    if (ph == true)
    {
      delay(350);
      ph = false;
    }
    phaseflag = false;
  }
}
//void vrturn()   //V shape right turn
//{
//  sensor1 = PINC;
//  if ((sensor1 | B00011000) == B00011001 || (sensor1 | B00011000) == B00011011)
//  {
//    while (sensor1 != B00011000 || sensor1 != B00001100)
//      slforward();
//    vflag = 1;
//  }
//  if ((sensor1 == B00011000) && vflag == 1)
//  {
//    rturn();
//    while ((sensor1 | B00011000) == B00011111)
//      rturn();
//    rturn();
//    delay(100);
//    vflag = 0;
//  }
//  else if (vflag == 1)
//  {
//    if ((sensor1 | B00011000) == B00111000 || (sensor1 | B00011000) == B01111000 || (sensor1 | B00011000) == B11111000 || (sensor1 | B11011000) == B11011000 || (sensor1 | B11011000) == B10011000) // adjust left
//    {
//      slfturn();
//    }
//    else if ((sensor1 | B00011000) == B00011100 || (sensor1 | B00011000) == B00011110 || (sensor1 | B00011000) == B00011111 || (sensor1 | B11011000) == B00011011 || (sensor1 | B11011000) == B00011001) // adjust right
//    {
//      srtturn();
//    }
//  }
//}
//void vlturn()   //V shape left turn
//{
//  sensor1 = PINC;
//  if ((sensor1 | B00011000) == B10011000 || (sensor1 | B00011000) == B11011000)
//  {
//    while (sensor1 != B00011000 || sensor1 != B00110000)
//      slforward();
//    vflag = 1;
//  }
//  if ((sensor1 == B00011000) && vflag == 1)
//  {
//    lturn();
//    while ((sensor1 | B00011000) == B11111000)
//      lturn();
//    lturn();
//    delay(100);
//    vflag = 0;
//  }
//  else if (vflag == 1)
//  {
//    if ((sensor1 | B00011000) == B00111000 || (sensor1 | B00011000) == B01111000 || (sensor1 | B00011000) == B11111000 || (sensor1 | B11011000) == B11011000 || (sensor1 | B11011000) == B10011000) // adjust left
//    {
//      slfturn();
//    }
//    else if ((sensor1 | B00011000) == B00011100 || (sensor1 | B00011000) == B00011110 || (sensor1 | B00011000) == B00011111 || (sensor1 | B11011000) == B00011011 || (sensor1 | B11011000) == B00011001) // adjust right
//    {
//      srtturn();
//    }
//  }
//}
void rotatezone1() //turn when found junction
{
  sensor1 = PINC;
  if (((sensor1 | B00000000) == B11111000) || ((sensor1 | B00000000) == B11110000) || ((sensor1 | B00000000) == B11111100) || ((sensor1 | B00000000) == B11100000)) //turn left
  {
    while (((sensor1 | B00011111) != B00011111))
    {
      slforward();
      sensor1 = PINC;
      Serial.println(sensor1, BIN);
      Serial.println("In 1 st left");
      if (((sensor1 | B00100100) == B11100111 || (sensor1 | B00100100) == B11110111 || (sensor1 | B00100100) == B11101111) || ((sensor1 | B00110000) == B11110011 || (sensor1 | B00110000) == B11111011 || (sensor1 | B00001100) == B11001111 || (sensor1 | B00001100) == B11011111) || (sensor1 | B01111000) == B11111001) || (sensor1 | B00011110) == B10011111))
      {
        phaseflag = true;
        break;
      }
    }
    if (sensor1 == B0000000)          // Check if there is line forward when encounted jucntion
    {
      while (((sensor1 | B00111111) != B11111111))
      {
        back();
        sensor1 = PINC;
        Serial.println(sensor1, BIN);
        Serial.println("In 2 nd left");
      }
      while ((sensor1 | B00111111) != B00111111)
      {
        slfturn();
        //slforward();
        sensor1 = PINC;
        Serial.println(sensor1, BIN);
        Serial.println("In 3 rd left");
      }
      while ((sensor1 | B00000001) != B00001101)
      {
        slfturn();
        sensor1 = PINC;
        Serial.println(sensor1, BIN);
        Serial.println("In 4 th left");
      }
    }
  }
  else if (((sensor1 | B00000000) == B00011111) || ((sensor1 | B00000000) == B00001111) || ((sensor1 | B00000000) == B00111111) || ((sensor1 | B00000000) == B00000111)) //turn right
  {
    while (((sensor1 | B11111000) != B11111000))
    {
      slforward();
      sensor1 = PINC;
      Serial.println(sensor1, BIN);
      Serial.println("In 1 st right");
      if (((sensor1 | B00100100) == B11100111 || (sensor1 | B00100100) == B11110111 || (sensor1 | B00100100) == B11101111) || ((sensor1 | B00110000) == B11110011 || (sensor1 | B00110000) == B11111011 || (sensor1 | B00001100) == B11001111 || (sensor1 | B00001100) == B11011111) || (sensor1 | B01111000) == B11111001) || (sensor1 | B00011110) == B10011111))
      {
        phaseflag = true;
        break;
      }
    }
    if (sensor1 == B0000000)          // Check if there is line forward when encounted jucntion
    {
      while (((sensor1 | B11111100) != B11111111))
      {
        back();
        sensor1 = PINC;
        Serial.println(sensor1, BIN);
        Serial.println("In 2 nd right");
      }
      while ((sensor1 | B11111100) != B11111100)
      {
        srtturn();
        //slforward();
        sensor1 = PINC;
        Serial.println(sensor1, BIN);
        Serial.println("In 3 rd right");
      }
      while ((sensor1 | B10000000) != B10110000)
      {
        srtturn();
        sensor1 = PINC;
        Serial.println(sensor1, BIN);
        Serial.println("In 4th right");
      }
    }
  }
}
void rotate() //turn when found junction
{
  sensor1 = PINC;
  if (((sensor1 | B00000000) == B11111000) || ((sensor1 | B00000000) == B11110000) || ((sensor1 | B00000000) == B11111100) || ((sensor1 | B00000000) == B11100000)) //turn left
  {
    while (((sensor1 | B00011111) != B00011111))
    {
      slforward();
      sensor1 = PINC;
      Serial.println(sensor1, BIN);
      Serial.println("In 1 st left");
      if (((sensor1 | B00100100) == B11100111 || (sensor1 | B00100100) == B11110111 || (sensor1 | B00100100) == B11101111) || ((sensor1 | B00110000) == B11110011 || (sensor1 | B00110000) == B11111011 || (sensor1 | B00001100) == B11001111 || (sensor1 | B00001100) == B11011111) || (sensor1 | B01111000) == B11111001) || (sensor1 | B00011110) == B10011111))
      {
        phaseflag = true;
        break;
      }
    }
    while (((sensor1 | B00111111) != B11111111))
    {
      back();
      sensor1 = PINC;
      Serial.println(sensor1, BIN);
      Serial.println("In 2 nd left");
    }
    while ((sensor1 | B00111111) != B00111111)
    {
      slfturn();
      //slforward();
      sensor1 = PINC;
      Serial.println(sensor1, BIN);
      Serial.println("In 3 rd left");
    }
    while ((sensor1 | B00000001) != B00001101)
    {
      slfturn();
      sensor1 = PINC;
      Serial.println(sensor1, BIN);
      Serial.println("In 4 th left");
    }
  }
  else if (((sensor1 | B00000000) == B00011111) || ((sensor1 | B00000000) == B00001111) || ((sensor1 | B00000000) == B00111111) || ((sensor1 | B00000000) == B00000111)) //turn right
  {
    while (((sensor1 | B11111000) != B11111000))
    {
      slforward();
      sensor1 = PINC;
      Serial.println(sensor1, BIN);
      Serial.println("In 1 st right");
      if (((sensor1 | B00100100) == B11100111 || (sensor1 | B00100100) == B11110111 || (sensor1 | B00100100) == B11101111) || ((sensor1 | B00110000) == B11110011 || (sensor1 | B00110000) == B11111011 || (sensor1 | B00001100) == B11001111 || (sensor1 | B00001100) == B11011111) || (sensor1 | B01111000) == B11111001) || (sensor1 | B00011110) == B10011111))
      {
        phaseflag = true;
        break;
      }
    }
    while (((sensor1 | B11111100) != B11111111))
    {
      back();
      sensor1 = PINC;
      Serial.println(sensor1, BIN);
      Serial.println("In 2 nd right");
    }
    while ((sensor1 | B11111100) != B11111100)
    {
      srtturn();
      //slforward();
      sensor1 = PINC;
      Serial.println(sensor1, BIN);
      Serial.println("In 3 rd right");
    }
    while ((sensor1 | B10000000) != B10110000)
    {
      srtturn();
      sensor1 = PINC;
      Serial.println(sensor1, BIN);
      Serial.println("In 4th right");
    }
  }
}
void loop() {
  phase();
  adjust();
  if (rotateflag == true)
  {
    if (phaseflag == false)
    {
      rotate();
    }
  }
  else
  {
    if (phaseflag == false)
    {
      rotatezone1();
    }
  }
}
