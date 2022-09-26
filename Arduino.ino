#include <Servo.h>     //ServoMotor library
Servo servo;  
// Outside Ultrasonic   
#define trigPin 5
#define echoPin 4
// ServoMotor Pin 
#define servoPin 8
// Buzzer pin
#define buzzer 9
#define message1 13
#define message2 12
#define IR1 11
#define IR2 10


int duration, dist, average;   
int aver[3];        //array for average
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  servo.attach(servoPin);  
  pinMode(trigPin, OUTPUT);  
  pinMode(echoPin, INPUT);  
  servo.write(0);         //close cap on power on
  delay(100);
  servo.detach(); 
  pinMode(IR1, INPUT);
  pinMode(IR2, INPUT);
  pinMode(buzzer, OUTPUT); // Set buzzer - pin 9 as an output
  pinMode(message1, OUTPUT);
  pinMode(message2, OUTPUT);

  digitalWrite(message1, LOW);
  digitalWrite(message2, LOW);

}

void measure() 
{  
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(15);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  dist = duration / 58;    //obtain distance
}

void loop() {
  digitalWrite(message1, LOW);
  digitalWrite(message2, LOW);
  for (int i=0;i<=2;i++) 
  {   //average distance
    measure();               
    aver[i] = dist;            
    delay(50);              //delay between measurements
  }
  dist=(aver[0]+aver[1]+aver[2])/3; 
  // put your main code here, to run repeatedly:
   if ( dist < 50 ) 
  {
//Change distance as per your need
    servo.attach(servoPin);
    delay(1);
    servo.write(0);  
    delay(3000);       
    servo.write(150);    
    delay(1000);
    servo.detach(); 
  if ((digitalRead(IR1) == 0) && (digitalRead(IR2) == 0))
  {
    digitalWrite(message1, HIGH);
    digitalWrite(message2, HIGH);
    
    tone(buzzer, 70000); // Send 1KHz sound signal...
    delay(1000);        // ...for 1 sec
    noTone(buzzer);     // Stop sound...
    delay(1000);        // ...for 1sec

    tone(buzzer, 70000); // Send 1KHz sound signal...
    delay(1000);        // ...for 1 sec
    noTone(buzzer);     // Stop sound...
    delay(1000);        // ...for 1sec

    tone(buzzer, 70000); // Send 1KHz sound signal...
    delay(1000);        // ...for 1 sec
    noTone(buzzer);     // Stop sound...
    delay(1000);        // ...for 1sec

    while((digitalRead(IR1) == 0) && (digitalRead(IR2) == 0))
    {
      
    }
    }
  }
}
