#include <IRremote.h>

int before; //initial state
int fan_speed;
int fan=9; //connect your fan to pin 9
int led=5; //connect your LED to pin 5
int steps=8; //dimmer steps
int recv_pin = 12; //connect your IR receiver output to pin 12

IRrecv irrecv(recv_pin);

decode_results results;

void setup(){
  irrecv.enableIRIn(); // start the receiver
  before=0;
  fan_speed=255; // Fan speed is at maximum (255)
  pinMode(fan,OUTPUT);
  pinMode(led,OUTPUT);
  }

void loop() {
  if (irrecv.decode(&results)) {

  if (results.value==0x38863BFE && before==0){ // if the Fan was turned off, then we turn it on 
      digitalWrite(fan,HIGH);
      digitalWrite(led,HIGH);
      before=1; // Fan is now turned on
    }
  if (results.value==0x38863BF4 && before==1){
      digitalWrite(fan,LOW); //if the Fan was turned on, then we turn it off
      digitalWrite(led,LOW);
      before=0;
      fan_speed=255; 
    }
  if (results.value==0x38863BFA && before==1){ //Code to decrease the Fan speed
    if(fan_speed-255/steps<0){ 
      analogWrite(fan,fan_speed);
      analogWrite(led,fan_speed);
    }
    else{
    fan_speed=fan_speed-255/steps;
    analogWrite(fan,fan_speed);
    analogWrite(led,fan_speed);
  }}
  if (results.value==0x38863BF2 && before==1){ //Code to increase the Fan speed
    if(fan_speed+255/steps>255){
      analogWrite(fan,fan_speed);
      analogWrite(led,fan_speed);
    }
    else{    
    fan_speed=fan_speed+255/steps;
    analogWrite(fan,fan_speed);
    analogWrite(led,fan_speed);
  }}
    irrecv.resume();
}}
