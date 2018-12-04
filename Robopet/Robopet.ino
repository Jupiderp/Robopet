/*
   created by Rui Santos, http://randomnerdtutorials.wordpress.com
   Control DC motor with Smartphone via bluetooth
   2013
*/
#include <TimedAction.h>
#include <Servo.h>

#define led 13
#define enabler 3
#define phaser 5
#define phaserl 6
#define enablel 9
#define phasel 10
#define phaselr 11
#define FORWARD HIGH
#define BACKWARD LOW
#define THROTTLE_MIN 0
#define THROTTLE_MAX 255

#define servo_tail 7
Servo servoTail;
void tail_search();
void tail_found();
void blink();

TimedAction TailThreadS  = TimedAction(50,tail_search);
TimedAction TailThreadF = TimedAction(50,tail_found);
TimedAction BlinkThread = TimedAction(50,blink);

bool locating = true;
int pos = 0;

void setup() {
  // Start Serial Monitor for feedback
  Serial.begin(9600);

  servoTail.attach(servo_tail);

  // Set phase (digital) pin as an output
  pinMode(phaser,OUTPUT);
  pinMode(phaserl,OUTPUT);
  pinMode(phasel,OUTPUT);
  pinMode(phaselr,OUTPUT);
  // Set initial condition for motor driver
  digitalWrite(phaser,FORWARD);
  digitalWrite(phaserl,BACKWARD);
  digitalWrite(phaselr,BACKWARD);
  digitalWrite(phasel,FORWARD);
  analogWrite(enabler,0);
  analogWrite(enablel,0);
}

void loop() {
  if (locating == false) {
  TailThreadS.disable();
  TailThreadF.check();
  BlinkThread.check();



    
  }
  if (locating == true) {
    TailThreadF.disable();
    TailThreadS.check();
    BlinkThread.disable();
    

    
  }
}

void tail_search() {
  for(pos = -45; pos < 45; pos += 1) // goes from 0 degrees to 180 degrees 
  { // in steps of 1 degree 
    servoTail.write(pos); // tell servo to go to position in variable 'pos' 
    delay(15); // waits 15ms for the servo to reach the position 
  } 
  for(pos = 45; pos>=-45; pos-=1) // goes from 180 degrees to 0 degrees 
  { 
    servoTail.write(pos); // tell servo to go to position in variable 'pos' 
    delay(15); // waits 15ms for the servo to reach the position 
  }
}

void tail_found() {
  for(pos = -45; pos < 45; pos += 1) // goes from 0 degrees to 180 degrees 
  { // in steps of 1 degree 
    servoTail.write(pos); // tell servo to go to position in variable 'pos' 
    delay(10); // waits 15ms for the servo to reach the position 
  } 
  for(pos = 45; pos>=-45; pos-=1) // goes from 180 degrees to 0 degrees 
  { 
    servoTail.write(pos); // tell servo to go to position in variable 'pos' 
    delay(10); // waits 15ms for the servo to reach the position 
  }
}

void blink() {
  digitalWrite(led, HIGH); // turn the LED on (HIGH is the voltage level)
  delay(50); // wait for two seconds
  digitalWrite(led, LOW); // turn the LED off by making the voltage LOW
  //delay(1000); // wait for a second
}
  
  /*// Sweep motor at phase = FORWARD,
  //  and motor speed at enable steps 0 to 255
  //  speed up 
  digitalWrite(phaser,FORWARD);
  digitalWrite(phaselr,BACKWARD);
  digitalWrite(phaserl,BACKWARD);
  digitalWrite(phasel,FORWARD);
  for(int i = THROTTLE_MIN; i <= THROTTLE_MAX; i++) {
    analogWrite(enabler,i);   
    analogWrite(enablel,i);         
    Serial.print("(phase,enable)=(");
    Serial.print(FORWARD);
    Serial.print(",");
    Serial.print(i);
    Serial.println(")");
    delay(5);
  }
  delay(500);

  // Sweep motor at phase = FORWARD,
  //  and motor speed at enable steps 255 to 0
  //  slow down
  for(int i = THROTTLE_MAX; i >= THROTTLE_MIN; i--) {
    analogWrite(enabler,i);   
    analogWrite(enablel,i);             
    Serial.print("(phase,enable)=(");
    Serial.print(FORWARD);
    Serial.print(",");
    Serial.print(i);
    Serial.println(")");
    delay(5);
  }
  delay(500);



  // Sweep motor at phase = BACKWARD,
  //  and motor speed at enable steps 0 to 255
  //  speed up 
  digitalWrite(phaser,BACKWARD);
  digitalWrite(phasel,BACKWARD);
  digitalWrite(phaselr,FORWARD);
  digitalWrite(phaserl,FORWARD);
  
  for(int i = THROTTLE_MIN; i <= THROTTLE_MAX; i++) {
    analogWrite(enabler,i);   
    analogWrite(enablel,i);           
    Serial.print("(phase,enable)=(");
    Serial.print(BACKWARD);
    Serial.print(",");
    Serial.print(i);
    Serial.println(")");
    delay(5);
  }
  delay(500);

  // Sweep motor at phase = BACKWARD,
  //  and motor speed at enable steps 255 to 0
  //  slow down
  for(int i = THROTTLE_MAX; i >= THROTTLE_MIN; i--) {
    analogWrite(enabler,i);
    analogWrite(enablel,i);         
    Serial.print("(phase,enable)=(");
    Serial.print(BACKWARD);
    Serial.print(",");
    Serial.print(i);
    Serial.println(")");
    delay(5);
  }
  delay(500);
}*/
