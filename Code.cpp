#include<Servo.h>
Servo myservo;
int pos=0;
long time;

#define en1 11
#define en2 12

int M1_Speed=128; // speed of motor 1
int M2_Speed=128; // speed of motor 2

#define LEFT A0
#define RIGHT A3

const int in1 =5;
const int in2 =4;
const int in3 =3;
const int in4 =2;

const int trigpin =9;
const int echopin =10;

long duration;
long distance;

void setup()
{
  myservo.attach(8);
  myservo.write(0);
  for(pos=0;pos<=45;pos+=1){
    myservo.write(pos);
    delay(15);
  }
  for(pos=45;pos>=0;pos-=1){
    myservo.write(pos);
    delay(15);
  }
  for(pos=0;pos<=20;pos+=1) {
    myservo.write(pos);
    delay(15);
  }
  pinMode(en1,OUTPUT);
  pinMode(en2,OUTPUT);

  pinMode(in1,OUTPUT);
  pinMode(in2,OUTPUT);
  pinMode(in3,OUTPUT);
  pinMode(in4,OUTPUT);

  pinMode(RIGHT,INPUT);
  pinMode(LEFT,INPUT);

  pinMode(trigpin,OUTPUT);
  pinMode(echopin,INPUT);
  Serial.begin(9600);
}
long microsecondsToCentimrters( long microseconds)
  {
    return microseconds/29/2;
  }
void loop()
{
  digitalWrite(trigpin,LOW);
  delayMicroseconds(2);

  digitalWrite(trigpin,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigpin,LOW);

  duration=pulseIn(echopin,HIGH);
  distance=microsecondsToCentimrters(duration);
 
  
  Serial.print("Duration:");
  Serial.println(duration);
  Serial.print("Distance:");
  Serial.println(distance);

  int Right_Value=digitalRead(RIGHT);
  int Left_Value=digitalRead(LEFT);

  Serial.print("RIGHT");
  Serial.println(Right_Value);
   Serial.print("LEFT");
  Serial.println(Left_Value);

  

// Forward
if((Right_Value==1)&&(distance>=10)&&(distance<=30)&&(Left_Value==1))
{
  Serial.print("Forward:");
  digitalWrite(in1,HIGH);
  digitalWrite(in2,LOW);
  digitalWrite(in3,HIGH);
  digitalWrite(in4,LOW);

      analogWrite(en1,M1_Speed);
       analogWrite(en2,M2_Speed);
}
// Right Turn
else if((Right_Value==0)&&(Left_Value==1))
{
  Serial.print("Right:");
  digitalWrite(in1,HIGH);
  digitalWrite(in2,LOW);
  digitalWrite(in3,LOW);
  digitalWrite(in4,HIGH);

      analogWrite(en1,M1_Speed);
       analogWrite(en2,M2_Speed);
}
// Left Turn
else if((Right_Value==1)&&(Left_Value==0))

{
  Serial.print("Left:");
  digitalWrite(in1,LOW);
  digitalWrite(in2,HIGH);
  digitalWrite(in3,HIGH);
  digitalWrite(in4,LOW);

      analogWrite(en1,M1_Speed);
       analogWrite(en2,M2_Speed);
}
// Stop
else if((Right_Value==1)&&(Left_Value==1))
{
  digitalWrite(in1,LOW);
  digitalWrite(in2,LOW);
  digitalWrite(in3,LOW);
  digitalWrite(in4,LOW);


}
// Stop
else if(distance>1 && distance<10)
{
  digitalWrite(in1,LOW);
  digitalWrite(in2,LOW);
  digitalWrite(in3,LOW);
  digitalWrite(in4,LOW);


}

  
}