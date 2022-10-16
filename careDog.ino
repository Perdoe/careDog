//The servo motor will allow the head of the dog to swivel and turn in accordance to the object it is following
#include <Servo.h>  //servo library
Servo myservo;      // create servo object to control servo

//Ultrasonic sensor variables
int One = A4;  
int Two = A5; 


//motor controller pins
//used to assign motor speed values and motor direction
#define ENA 5
#define ENB 6
#define IN1 7
#define IN2 8
#define IN3 9
#define IN4 11

//The speed of the dog
#define dogSpeed 125
#define dogSpeed2 125

//distinguish left and right
int rightDistance = 0, leftDistance = 0;

//the dog will move forward according to this function
void forward(){ 
  analogWrite(ENA, dogSpeed);
  analogWrite(ENB, dogSpeed);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  Serial.println("Forward");
}

//the dog will move backwards according to this function
void back() {
  analogWrite(ENA, dogSpeed);
  analogWrite(ENB, dogSpeed);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  Serial.println("Back");
}

//the dog will left according to this function
void left() {
  analogWrite(ENA, dogSpeed2);
  analogWrite(ENB, dogSpeed2);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH); 
  Serial.println("Left");
}

//the dog will move right according to this function
void right() {
  analogWrite(ENA, dogSpeed2);
  analogWrite(ENB, dogSpeed2);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  Serial.println("Right");
}

//the dog will stop according to this function
void stop() {
  digitalWrite(ENA, LOW);
  digitalWrite(ENB, LOW);
  Serial.println("Stop!");
} 

//Ultrasonic distance measurement method
//uses the ultrasonic sensor to have certain distances set for certain things
int Distance_test() {
  digitalWrite(Two, LOW);   
  delayMicroseconds(3);
  digitalWrite(Two, HIGH);  
  delayMicroseconds(25);
  digitalWrite(Two, LOW);   
  float Fdistance = pulseIn(One, HIGH);  
  Fdistance= Fdistance / 58;       
  return (int)Fdistance;
}  


//This will makes sure that all the motors have been initialized and all connections are ready
//IF this fails then come connection has been misplaced
//IF you change code here then change code at the start where they are defined aswell
void setup() { 
  myservo.attach(3);  // attach servo on pin 3 to servo object
  Serial.begin(9600);     
  pinMode(One, INPUT);    
  pinMode(Two, OUTPUT);  
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  stop();
} 

//This code is used to set certain boundaries
//IF the distances reaches a certain value then the dog will move a predetermined amount
//continuous function, this means the code will not stop running until turned off
//KEEP IN MIND, even if the dog stops, that does not mean the code has stopped.
void loop() { 
  
    myservo.write(65);  //setservo position to right side
    delay(220); 
    rightDistance = Distance_test();

    myservo.write(120);  //setservo position to left side
    delay(220); 
    leftDistance = Distance_test();

    if((rightDistance > 75)&&(leftDistance > 75)){
      stop();
    }else if((rightDistance >= 25) && (leftDistance >= 25)) {     
      forward();
    }else if((rightDistance <= 15) && (leftDistance <= 15)) {
        back();
        delay(120);
    }else if(rightDistance - 4 > leftDistance) {
        left();
        delay(120);
    }else if(rightDistance + 4 < leftDistance) {
        right();
        delay(120);
    }else{
      stop();
    }
    
}    
