#define lpwm 7
#define left1 5
#define left2 6
#define rpwm 4
#define right1 3
#define right2 2
#define maxpwm 200
#define slturn 130
#define sladj 40
#define mdadj 55
#define hdadj 90
#define turn 150
#define minpwm 120
#define bkpwm 130
#define reading
//#define jumper
#define lastck 13
#define ckinzone1 A2
#define zone1 11
#define rezone1 10
#define turnlast 9
#define turnall 8
#define lastzone A0
#define belowlast A1

uint32_t prevread = 0, finalread = 0;
bool ph = false, phaseflag = false, rotateflag = false, lrotate = false, llrotate = false, ralwaysflag = false, rrotate = false, rrrotate = false;
int count = 0, countlturn = 0, countrturn = 0;
int lcorr = -38, rcorr = 4; // Add zero error if required here
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
  pinMode(zone1, INPUT_PULLUP);
  pinMode(rezone1, INPUT_PULLUP);
  pinMode(turnall, INPUT_PULLUP);
  pinMode(turnlast, INPUT_PULLUP);
  pinMode(lastck, INPUT_PULLUP);
  pinMode(ckinzone1, INPUT_PULLUP);
  pinMode(belowlast, INPUT_PULLUP);
  pinMode(lastzone, INPUT_PULLUP);
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
#endif
  digitalWrite(left1, HIGH);
  digitalWrite(left2, LOW);
  digitalWrite(right1, HIGH);
  digitalWrite(right2, LOW);

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

  left = 175;
  right = 98;
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

  left = 110;
  right = 145;
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
  if (digitalRead(lastzone) != LOW)
  {
    if (sensor1 == B10000000)
    {
      hleft();
    }
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
  if (digitalRead(lastzone) != LOW)
  {
    if (sensor1 == B00000001)
    {
      hright();
    }
  }
  else if (sensor1 == B00011000)  //When Line is not there
  {
    forward();
  }
  else if (sensor1 == B00000000 )
  {
    black();
  }
  else if (sensor1 == B10110000 || sensor1 == B10111000 || sensor1 == B10011100 || sensor1 == B10011000)
  {
    leftalways();
  }
  else if (sensor1 == B00001101 || sensor1 == B00011101 || sensor1 == B00011001 || sensor1 == B00111001)
  {
    rightalways();
  }
  else if (sensor1 | B10000001 == B11111111)
  {
    rightalways();
  }
}
void phase()    //call when black line comes on white surface
{
  sensor1 = PINC;
  if (((sensor1 | B00100100) == B11100111) || ((sensor1 | B00100100) == B11110111) || ((sensor1 | B00100100) == B11101111) || ((sensor1 | B00110000) == B11110011) || ((sensor1 | B00110000) == B11111011) || ((sensor1 | B00001100) == B11001111) || ((sensor1 | B00001100) == B11011111) || ((sensor1 | B01111000) == B11111001) || ((sensor1 | B00011110) == B10011111))
  {
    sensor1 = ~sensor1;
    ph = true;
    lcorr = 0;
    rcorr = 18;
    adjust();
    sensor1 = PINC;
#ifdef reading
    Serial.println("in Phase");
#endif
    ralwaysflag = true;
  }
  else
  {
    lcorr = -38;
    rcorr = 4;
    delay(100);
    if (ralwaysflag == true)
    {
      if ((sensor1 | B10000001) == B10000001)
      {
        rightalways();
        ph = false;
      }
      ralwaysflag = false;
    }
    if (ph == true)
    {
#ifdef reading
      Serial.println("out Phase");
#endif
      delay(150);
      ph = false;
    }
    phaseflag = false;
  }
}
void black()
{
#ifdef reading
  Serial.println("In Black");
#endif
  prevread = millis();
  while (sensor1 == B0000000)
  {
    sensor1 = PINC;
    forward();
  }
  finalread = millis();
  if (abs(finalread - prevread) > 300)
  {
    rotateflag = true;

  }
}
void rightalways()
{
  while (((sensor1 | B11111100) != B11111100))
  {
    slforward();
    sensor1 = PINC;
#ifdef reading
    Serial.println(sensor1, BIN);
    Serial.println("In 1 st right");
#endif
    if (((sensor1 | B00100100) == B11100111) || ((sensor1 | B00100100) == B11110111) || ((sensor1 | B00100100) == B11101111) || ((sensor1 | B00110000) == B11110011) || ((sensor1 | B00110000) == B11111011) || ((sensor1 | B00001100) == B11001111) || ((sensor1 | B00001100) == B11011111) || ((sensor1 | B01111000) == B11111001) || ((sensor1 | B00011110) == B10011111))
    {
      phaseflag = true;
      break;
    }
  }
  if (phaseflag == false)
  {
    while (((sensor1 | B11111100) != B11111111))
    {
      back();
      sensor1 = PINC;
#ifdef reading
      Serial.println(sensor1, BIN);
      Serial.println("In 2 nd right");
#endif
    }
    while ((sensor1 | B11111100) != B11111100)
    {
      srtturn();
      //slforward();
      sensor1 = PINC;
#ifdef reading
      Serial.println(sensor1, BIN);
      Serial.println("In 3 rd right");
#endif
    }
    while ((sensor1 | B10000000) != B10110000)
    {
      srtturn();
      sensor1 = PINC;
#ifdef reading
      Serial.println(sensor1, BIN);
      Serial.println("In 4th right");
#endif
      rrotate = true;
    }
  }
}
void leftalways()
{
  while (((sensor1 | B00111111) != B00111111))
  {
    slforward();
    sensor1 = PINC;
#ifdef reading
    Serial.println(sensor1, BIN);
    Serial.println("In 1 st left rotate");
#endif
    if (((sensor1 | B00100100) == B11100111) || ((sensor1 | B00100100) == B11110111) || ((sensor1 | B00100100) == B11101111) || ((sensor1 | B00110000) == B11110011) || ((sensor1 | B00110000) == B11111011) || ((sensor1 | B00001100) == B11001111) || ((sensor1 | B00001100) == B11011111) || ((sensor1 | B01111000) == B11111001) || ((sensor1 | B00011110) == B10011111))
    {
      phaseflag = true;
      break;
    }
  }
  if (phaseflag == false)
  {
    while (((sensor1 | B00111111) != B11111111) )
    {
      back();
      sensor1 = PINC;
#ifdef reading
      Serial.println(sensor1, BIN);
      Serial.println("In 2 nd left rotate");
#endif
    }
    while ((sensor1 | B00111111) != B00111111)
    {
      slfturn();
      //slforward();
      sensor1 = PINC;
#ifdef reading
      Serial.println(sensor1, BIN);
      Serial.println("In 3 rd left rotate");
#endif
    }
    while ((sensor1 | B00000001) != B00001101)
    {
      slfturn();
      sensor1 = PINC;
#ifdef reading
      Serial.println(sensor1, BIN);
      Serial.println("In 4 th left rotate");
#endif
      lrotate = true;
      llrotate = true;
    }
  }
}
void leftrotate()
{
  sensor1 = PINC;
  if (((sensor1 | B00000000) == B11111000) || ((sensor1 | B00000000) == B11110000) || ((sensor1 | B00000000) == B11111100) || ((sensor1 | B00000000) == B11100000) || ((sensor1 | B00000000) == B01111000)) //turn left
  {
    while (((sensor1 | B00111111) != B00111111))
    {
      slforward();
      sensor1 = PINC;
#ifdef reading
      Serial.println(sensor1, BIN);
      Serial.println("In 1 st left rotate");
#endif
      if (((sensor1 | B00100100) == B11100111) || ((sensor1 | B00100100) == B11110111) || ((sensor1 | B00100100) == B11101111) || ((sensor1 | B00110000) == B11110011) || ((sensor1 | B00110000) == B11111011) || ((sensor1 | B00001100) == B11001111) || ((sensor1 | B00001100) == B11011111) || ((sensor1 | B01111000) == B11111001) || ((sensor1 | B00011110) == B10011111))
      {
        phaseflag = true;
        break;
      }
    }
    if (phaseflag == false)
    {
      while (((sensor1 | B00111111) != B11111111) )
      {
        back();
        sensor1 = PINC;
#ifdef reading
        Serial.println(sensor1, BIN);
        Serial.println("In 2 nd left rotate");
#endif
      }
      while ((sensor1 | B00111111) != B00111111)
      {
        slfturn();
        //slforward();
        sensor1 = PINC;
#ifdef reading
        Serial.println(sensor1, BIN);
        Serial.println("In 3 rd left rotate");
#endif
      }
      while ((sensor1 | B00000001) != B00001101)
      {
        slfturn();
        sensor1 = PINC;
#ifdef reading
        Serial.println(sensor1, BIN);
        Serial.println("In 4 th left rotate");
#endif
        lrotate = true;
        llrotate = true;
      }
    }
  }
}
void rightrotate()
{
  if (((sensor1 | B00000000) == B00011111) || ((sensor1 | B00000000) == B00001111) || ((sensor1 | B00000000) == B00111111) || ((sensor1 | B00000000) == B00000111) || ((sensor1 | B00000000) == B00011110)) //turn right
  {
    while (((sensor1 | B11111100) != B11111100))
    {
      slforward();
      sensor1 = PINC;
#ifdef reading
      Serial.println(sensor1, BIN);
      Serial.println("In 1 st right rotate");
#endif
      if (((sensor1 | B00100100) == B11100111) || ((sensor1 | B00100100) == B11110111) || ((sensor1 | B00100100) == B11101111) || ((sensor1 | B00110000) == B11110011) || ((sensor1 | B00110000) == B11111011) || ((sensor1 | B00001100) == B11001111) || ((sensor1 | B00001100) == B11011111) || ((sensor1 | B01111000) == B11111001) || ((sensor1 | B00011110) == B10011111))
      {
        phaseflag = true;
        break;
      }
    }
    if (phaseflag == false)
    {
      while (((sensor1 | B11111100) != B11111111))
      {
        back();
        sensor1 = PINC;
#ifdef reading
        Serial.println(sensor1, BIN);
        Serial.println("In 2 nd right rotate");
#endif
      }
      while ((sensor1 | B11111100) != B11111100)
      {
        srtturn();
        //slforward();
        sensor1 = PINC;
#ifdef reading
        Serial.println(sensor1, BIN);
        Serial.println("In 3 rd right rotate");
#endif
      }
      while ((sensor1 | B10000000) != B10110000)
      {
        srtturn();
        sensor1 = PINC;
#ifdef reading
        Serial.println(sensor1, BIN);
        Serial.println("In 4th right rotate");
#endif
        rrotate = true;
        rrrotate = true;
      }
    }
  }
}
void cosrightrotate()
{
  if (((sensor1 | B00000000) == B00011111) || ((sensor1 | B00000000) == B00001111) || ((sensor1 | B00000000) == B00111111) || ((sensor1 | B00000000) == B00000111) || ((sensor1 | B00000000) == B00011110)) //turn right
  {
    while (((sensor1 | B11111000) != B11111000))
    {
      slforward();
      sensor1 = PINC;
#ifdef reading
      Serial.println(sensor1, BIN);
      Serial.println("In 1 st right cos");
#endif
      if (((sensor1 | B00100100) == B11100111) || ((sensor1 | B00100100) == B11110111) || ((sensor1 | B00100100) == B11101111) || ((sensor1 | B00110000) == B11110011) || ((sensor1 | B00110000) == B11111011) || ((sensor1 | B00001100) == B11001111) || ((sensor1 | B00001100) == B11011111) || ((sensor1 | B01111000) == B11111001) || ((sensor1 | B00011110) == B10011111))
      {
        phaseflag = true;
        break;
      }
    }
    if (phaseflag == false)
    {
      while (((sensor1 | B11111000) != B11111111))
      {
        back();
        sensor1 = PINC;
#ifdef reading
        Serial.println(sensor1, BIN);
        Serial.println("In 2 nd right cos");
#endif
      }
      while (((sensor1 | B11111100) != B11111100))
      {
        back();
        sensor1 = PINC;
#ifdef reading
        Serial.println(sensor1, BIN);
        Serial.println("In 3 rd right cos");
#endif
      }
      while (((sensor1 | B11111000) != B11111111))
      {
        back();
        sensor1 = PINC;
#ifdef reading
        Serial.println(sensor1, BIN);
        Serial.println("In 4 th right cos");
#endif
      }
      while ((sensor1 | B11111100) != B11111100)
      {
        srtturn();
        //slforward();
        sensor1 = PINC;
#ifdef reading
        Serial.println(sensor1, BIN);
        Serial.println("In 5 th right cos");
#endif
      }
      while ((sensor1 | B10000000) != B10110000)
      {
        srtturn();
        sensor1 = PINC;
#ifdef reading
        Serial.println("yay im in right");
        Serial.println(sensor1, BIN);
        Serial.println("In 6th right cos");
#endif
      }
    }
  }
}
void rotatezone1() //turn when found junction
{
  sensor1 = PINC;
  if (((sensor1 | B00000000) == B11111000) || ((sensor1 | B00000000) == B11110000) || ((sensor1 | B00000000) == B11111100) || ((sensor1 | B00000000) == B11100000) || ((sensor1 | B00000000) == B01111000) || ((sensor1 | B00000000) == B01110000)) //turn left
  {
    if ((sensor1 | B10011001) == B11111111)
    {
      rightalways();
    }
    else
    {
      while (((sensor1 | B00001111) != B00001111))
      {
        slforward();
#ifdef reading
        Serial.println(sensor1, BIN);
        Serial.println("In 1 st left of rotate at last");
#endif
        sensor1 = PINC;
        if (((sensor1 | B00100100) == B11100111) || ((sensor1 | B00100100) == B11110111) || ((sensor1 | B00100100) == B11101111) || ((sensor1 | B00110000) == B11110011) || ((sensor1 | B00110000) == B11111011) || ((sensor1 | B00001100) == B11001111) || ((sensor1 | B00001100) == B11011111) || ((sensor1 | B01111000) == B11111001) || ((sensor1 | B00011110) == B10011111))
        {
          phaseflag = true;
          break;
        }
        if (((sensor1 | B00011111) == B00011111))
        {
          slforward();
          sensor1 = PINC;
          if ((sensor1 | B00000000) != B00000000)
          {
            break;
          }
        }
      }
      if (sensor1 == B00000000)          // Check if there is line forward when encounted jucntion
      {
        while (((sensor1 | B00111111) != B11111111))
        {
          back();
          sensor1 = PINC;
#ifdef reading
          Serial.println(sensor1, BIN);
          Serial.println("In 2 nd left last");
#endif
        }
        while ((sensor1 | B00111111) != B00111111)
        {
          slfturn();
          //slforward();
          sensor1 = PINC;
#ifdef reading
          Serial.println(sensor1, BIN);
          Serial.println("In 3 rd left last");
#endif
        }
        while ((sensor1 | B00000001) != B00001101)
        {
          slfturn();
          sensor1 = PINC;
#ifdef reading
          Serial.println(sensor1, BIN);
          Serial.println("In 4 th left last");
#endif
        }
      }
    }
  }
  else if (((sensor1 | B00000000) == B00011111) || ((sensor1 | B00000000) == B00001111) || ((sensor1 | B00000000) == B00111111) || ((sensor1 | B00000000) == B00000111) || ((sensor1 | B00000000) == B00011110) || ((sensor1 | B00000000) == B00001110)) //turn right
  {
    while (((sensor1 | B11100000) != B11100000))
    {
      slforward();
      sensor1 = PINC;
#ifdef reading
      Serial.println(sensor1, BIN);
      Serial.println("In 1 st  right of rotate at last..");
#endif
      if (((sensor1 | B00100100) == B11100111) || ((sensor1 | B00100100) == B11110111) || ((sensor1 | B00100100) == B11101111) || ((sensor1 | B00110000) == B11110011) || ((sensor1 | B00110000) == B11111011) || ((sensor1 | B00001100) == B11001111) || ((sensor1 | B00001100) == B11011111) || ((sensor1 | B01111000) == B11111001) || ((sensor1 | B00011110) == B10011111))
      {
        phaseflag = true;
        break;
      }
      if (((sensor1 | B11111000) == B11111000))
      {
        slforward();
        sensor1 = PINC;
        if ((sensor1 | B00000000) != B00000000)
        {
          break;
        }
      }
    }
    if (sensor1 == B00000000)          // Check if there is line forward when encounted jucntion
    {
      while (((sensor1 | B11111100) != B11111111))
      {
        back();
        sensor1 = PINC;
#ifdef reading
        Serial.println(sensor1, BIN);
        Serial.println("In 2 nd right last");
#endif
      }
      while ((sensor1 | B11111100) != B11111100)
      {
        srtturn();
        //slforward();
        sensor1 = PINC;
#ifdef reading
        Serial.println(sensor1, BIN);
        Serial.println("In 3 rd right last");
#endif
      }
      while ((sensor1 | B10000000) != B10110000)
      {
        srtturn();
        sensor1 = PINC;
#ifdef reading
        Serial.println(sensor1, BIN);
        Serial.println("In 4th right last");
#endif
      }
    }
  }
}

void rotate() //turn when found junction
{
  sensor1 = PINC;
  if (((sensor1 | B00000000) == B11111000) || ((sensor1 | B00000000) == B11110000) || ((sensor1 | B00000000) == B11111100) || ((sensor1 | B00000000) == B11100000) || ((sensor1 | B00000000) == B01111000)) //turn left
  {
    while (((sensor1 | B00111111) != B00111111))
    {
      slforward();
      sensor1 = PINC;
#ifdef reading
      Serial.println(sensor1, BIN);
      Serial.println("In 1 st left");
#endif
      if (((sensor1 | B00100100) == B11100111) || ((sensor1 | B00100100) == B11110111) || ((sensor1 | B00100100) == B11101111) || ((sensor1 | B00110000) == B11110011) || ((sensor1 | B00110000) == B11111011) || ((sensor1 | B00001100) == B11001111) || ((sensor1 | B00001100) == B11011111) || ((sensor1 | B01111000) == B11111001) || ((sensor1 | B00011110) == B10011111))
      {
        phaseflag = true;
        break;
      }
    }
    if (phaseflag == false)
    {
      while (((sensor1 | B00111111) != B11111111) )
      {
        back();
        sensor1 = PINC;
#ifdef reading
        Serial.println(sensor1, BIN);
        Serial.println("In 2 nd left");
#endif
      }
      while ((sensor1 | B00111111) != B00111111)
      {
        slfturn();
        //slforward();
        sensor1 = PINC;
#ifdef reading
        Serial.println(sensor1, BIN);
        Serial.println("In 3 rd left");
#endif
      }
      while ((sensor1 | B00000001) != B00001101)
      {
        slfturn();
        sensor1 = PINC;
#ifdef reading
        Serial.println(sensor1, BIN);
        Serial.println("In 4 th left");
#endif
        lrotate = true;
      }
    }
  }
  else if (((sensor1 | B00000000) == B00011111) || ((sensor1 | B00000000) == B00001111) || ((sensor1 | B00000000) == B00111111) || ((sensor1 | B00000000) == B00000111) || ((sensor1 | B00000000) == B00011110)) //turn right
  {
    while (((sensor1 | B11111100) != B11111100))
    {
      slforward();
      sensor1 = PINC;
#ifdef reading
      Serial.println(sensor1, BIN);
      Serial.println("In 1 st right");
#endif
      if (((sensor1 | B00100100) == B11100111) || ((sensor1 | B00100100) == B11110111) || ((sensor1 | B00100100) == B11101111) || ((sensor1 | B00110000) == B11110011) || ((sensor1 | B00110000) == B11111011) || ((sensor1 | B00001100) == B11001111) || ((sensor1 | B00001100) == B11011111) || ((sensor1 | B01111000) == B11111001) || ((sensor1 | B00011110) == B10011111))
      {
        phaseflag = true;
        break;
      }
    }
    if (phaseflag == false)
    {
      while (((sensor1 | B11111100) != B11111111))
      {
        back();
        sensor1 = PINC;
#ifdef reading
        Serial.println(sensor1, BIN);
        Serial.println("In 2 nd right");
#endif
      }
      while ((sensor1 | B11111100) != B11111100)
      {
        srtturn();
        //slforward();
        sensor1 = PINC;
#ifdef reading
        Serial.println(sensor1, BIN);
        Serial.println("In 3 rd right");
#endif
      }
      while ((sensor1 | B10000000) != B10110000)
      {
        srtturn();
        sensor1 = PINC;
#ifdef reading
        Serial.println(sensor1, BIN);
        Serial.println("In 4th right");
#endif
        rrotate = true;
      }
    }
  }
}
void loop() {
#ifdef jumper
  Serial.print(digitalRead(turnall));
  Serial.print(digitalRead(turnlast));
  Serial.print(digitalRead(rezone1));
  Serial.print(digitalRead(zone1));
  Serial.println(digitalRead(lastck));
  Serial.println("Analog");
  Serial.println(digitalRead(lastzone));
  Serial.print(digitalRead(belowlast));
  Serial.println(digitalRead(ckinzone1));
  Serial.print(lcorr);
  Serial.println(rcorr);
#endif

  if (digitalRead(zone1) == LOW)        // will run initially at starting
  {
    //pin 11
#define reading Serial.println("In zone 1");#endif
    phase();
    if (phaseflag == false)
    {
      adjust();
    }
    if (rrotate == false)
    {
#define reading Serial.println("IN rotate right");#endif
      rotate();
    }
    else if (rotateflag == true)
    {
      if (phaseflag == false)
      {
#define reading  Serial.println("IN rotate after all 0");#endif
        rotate();
      }
    }
    else
    {
      if (phaseflag == false)
      {
#define reading Serial.println("IN rotate for all");#endif
        rotatezone1();
      }
    }
  }
  else if (digitalRead(rezone1) == LOW)     //change pins if reset before ramp
  {
    // pin 10
#define reading Serial.println("In rezone");#endif
    phase();
    if (phaseflag == false)
    {
      adjust();
    }
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
  else if (digitalRead(turnlast) == LOW) //use for rotate if no line
  {
    //pin 9
    phase();
    if (phaseflag == false)
    {
      adjust();
    }
    if (phaseflag == false)
    {
      rotatezone1();
    }
#define reading Serial.println("In all Turn");#endif
  }
  else if (digitalRead(turnall) == LOW) // use for rotate when junction is present
  {
    //pin 8
    phase();
    if (phaseflag == false)
    {
      adjust();
    }
    if (phaseflag == false)
    {
      rotate();

    }
#define reading Serial.println("last checkpoint");#endif
  }
  else if (digitalRead(lastck) == LOW)
  {
    //pin 9
    phase();
    if (phaseflag == false)
    {
      adjust();
    }
    if (phaseflag == false)
    {
      leftrotate();

    }
#define reading Serial.println("In CheckPoint in zone 1");#endif
  }
  else if (digitalRead(ckinzone1) == LOW)
  {
    //pin 13
    phase();
    if (phaseflag == false)
    {
      adjust();
    }
    if (phaseflag == false)
    {
      rightrotate();

    }
#define reading Serial.println("last zone");#endif
  }
  else if (digitalRead(lastzone) == LOW)
  { //pin A0
    phase();
    if (phaseflag == false)
    {
      adjust();
    }
    if (phaseflag == false)
    {
      leftrotate();
      cosrightrotate();

    }
#define reading Serial.println("In below last checkpoint");#endif
  }
  else if (digitalRead(belowlast) == LOW)
  {
    //pin A0
    phase();
    if (phaseflag == false)
    {
      adjust();
    }
    if (phaseflag == false)
    {
      if (rrrotate == false)
      {
#define reading  Serial.println("going in if................");#endif
        rightrotate();
      }

      leftrotate();
    }
#define reading Serial.println("In below last checkpoint");#endif
  }
  else
  {
    //forward();
    phase();
    adjust();
    //Serial.println(sensor1, BIN);
#define reading  Serial.println("In else");#endif
  }// return from junctions cases now begins----------------------------------------------------------------------------//////////////////
}
