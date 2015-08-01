#include <Servo.h> 
#define trigPin 4
#define echoPin 7
#define mouthLed 9

Servo leftServo;
Servo rightServo;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(mouthLed, OUTPUT);
  Serial.begin(9600);
  // put your setup code here, to run once:
  rightServo.attach(5);
  leftServo.attach(6);
  forward();
}

void loop() {  
  int distance = getDistance();
  Serial.println(distance);
  if(distance < 10){
    stopServos();
    blinkMouth(250, 4);
    backward();
    delay(750);
    turnLeft();
    delay(400);
    forward();    
  }
  delay(250);

  /*Serial.print(analogRead(A6)); //Higher is darker
   Serial.print("  ");
   Serial.println(analogRead(A7)); //Higher is darker
   */
  if(analogRead(A6) > 700 || analogRead(A7) > 700){
    digitalWrite(mouthLed, HIGH);
  } 
  else {
    digitalWrite(mouthLed, LOW);
  }
}

void blinkMouth(int duration, byte repeat){
  for(byte i = repeat; i != 0; i--){
    digitalWrite(mouthLed, HIGH);
    delay(duration);
    digitalWrite(mouthLed, LOW);
    delay(duration);
  }
}

void stopServos(){
  rightServo.write(90); //Forwards
  leftServo.write(90); //Forwards
}

void forward(){
  rightServo.write(0); //Forwards
  leftServo.write(180); //Forwards
}

void backward(){
  rightServo.write(180); 
  leftServo.write(0); 
}

void turnLeft(){
  rightServo.write(0); 
  leftServo.write(0); 
}

void turnRight(){
  rightServo.write(180); 
  leftServo.write(180); 
}

//Approx. distance in CM
unsigned int getDistance(){
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(trigPin, LOW);
  //read bounce back wave
  unsigned long duration = pulseIn(echoPin, HIGH);
  return duration >> 6;
}




