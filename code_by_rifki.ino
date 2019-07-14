#include <Servo.h>

const int enablePin  = 12; 
const int stepPin    = 6; 
const int dirPin     = 5;  

const int limitPin   = 9;
const int servoPinLL = 8; 
const int servoPinLR = 7; 
const int servoPinRL = 4; 
const int servoPinRR = 3;
const int servoPinX  = 2;

const int inputPin0 = A2; 
const int inputPin1 = A3; 
const int inputPin2 = A4; 
const int inputPin3 = A5; 
const int inputPin4 = A6; 

int value0 = 0;
int value1 = 0;
int value2 = 0;
int value3 = 0;
int value4 = 0;
int limit  = 0;

int i, done;
Servo servoLL,servoLR,servoRL,servoRR, servoX; 

void kananTutup()   {  servoLL.write(98);   servoLR.write(32); }
void kananBuka()    {  servoLL.write(40);    servoLR.write(73); }
void kiriBuka()     {  servoRL.write(90);    servoRR.write(50); }
void kiriTutup()    {  servoRL.write(49);    servoRR.write(100);}
void armR()         {
                      for (i=13;i<=87;i++) 
                      {
                        servoX.write(i);
                        delay(7); 
                      }
                      done=0;
                    }
void armL()         { 
                      for (i=87;i>=13;i--)
                      {
                        servoX.write(i);
                        delay(7);
                      }
                      done=1;
                    }
      
void setup()        {
  Serial.begin(9600);
  
  pinMode(servoPinLL,INPUT);
  pinMode(servoPinLR,INPUT);
  pinMode(servoPinRL,INPUT);
  pinMode(servoPinRR,INPUT);
  pinMode(servoPinX,INPUT);

  pinMode(limitPin,INPUT);
  
  servoLL.attach(8);
  servoLR.attach(7);
  servoRL.attach(4);
  servoRR.attach(3);
  servoX.attach(2);
  
  pinMode(inputPin0,INPUT);
  pinMode(inputPin1,INPUT);
  pinMode(inputPin2,INPUT);
  pinMode(inputPin3,INPUT);
  pinMode(inputPin4,INPUT);

  pinMode(enablePin,OUTPUT);
  pinMode(stepPin,OUTPUT); 
  pinMode(dirPin,OUTPUT);
  
kiriTutup();
kananTutup();

servoX.write(87);

digitalWrite(enablePin,LOW);
limit = digitalRead(limitPin);
while(limit==1){          
    limit = digitalRead(limitPin);
    digitalWrite(dirPin, HIGH);   
    digitalWrite(stepPin,HIGH); delayMicroseconds(2000); 
    digitalWrite(stepPin,LOW);  delayMicroseconds(2000);
    kiriTutup();
    kananTutup();
    done == 0;
  }
}

void loop() { 
    Serial.println(value4);
    value0 = analogRead(inputPin0); 
    value1 = analogRead(inputPin1); 
    value2 = analogRead(inputPin2); 
    value3 = analogRead(inputPin3); 
    value4 = analogRead(inputPin4);
    limit  = digitalRead(limitPin); 

  if (value0<600 || value1<600 || value2<600 || value3<600 || value4<600) 
  {
    if(value0 < 600 )             kiriBuka();
    else                          kiriTutup();
     
    if(value1 < 600 )             kananBuka();  
    else                          kananTutup();
  
    if      (value2 < 600 && done==0)         armL();
    else if (value2 > 600 && done==1)         armR();
  
    if(value3 > 600 && value4<=600 && limit==1) { 
            digitalWrite(dirPin, HIGH);
            digitalWrite(stepPin,HIGH); delayMicroseconds(1000); 
            digitalWrite(stepPin,LOW);  delayMicroseconds(1000);}
    if(value3<=600 && value4>=600){
            digitalWrite(dirPin, LOW);
            digitalWrite(stepPin,HIGH); delayMicroseconds(1000); 
            digitalWrite(stepPin,LOW);  delayMicroseconds(1000);
    }
  }

  else if (value0>600 && value1>600 && value2>600 && value3>600 && value4>600) 
  { 
  delay(200);
  }
}

