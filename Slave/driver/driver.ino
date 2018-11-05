#include <Wire.h>
#include "motordriver.h"
#define slave_addr  7

char mot;
int value=0;
int pwmValue=0;
unsigned char dir=0, pinEn=8;

void setup() {
  Wire.begin(slave_addr);
  Wire.onReceive(receiveEvent);
  Serial.begin(9600);
  setupPWM16();
  pinMode(pinEn,INPUT_PULLUP);
}

void loop() {
  if(mot=='S')dir=stp;//stop
  else if(mot=='F'||mot=='B'){//forward or backward
    pwmValue=value;
    if(slave_addr==6||slave_addr==8){
      if(mot=='F')dir=fw;
      else dir=bw;
    }
    else dir=stp;
  } 
  else if(mot=='L'){//left
    if(slave_addr==6||slave_addr==8){
      pwmValue=value/2;
      if(slave_addr==6)dir=bw;
      else dir=fw;
    }
    else {
      pwmValue = value;
      dir = bw;  
    }
  }
  else if(mot=='R'){//right
    if(slave_addr==6||slave_addr==8){
      pwmValue=value/2;
      if(slave_addr==6)dir=fw;
      else dir=bw;
    }
    else {
      pwmValue = value;
      dir = fw;  
    }
  }
  else if(mot=='E'){//slide right front
    pwmValue=value;
    if(slave_addr==6||slave_addr==7)dir=fw;
    else dir=stp;
  }
  else if(mot=='Q'){//slide left front
    pwmValue=value;
    if(slave_addr==7)dir=bw;
    else if(slave_addr==8)dir=fw;
    else dir=stp;
  }
  else if(mot=='C'){//slide right backward
    pwmValue=value;
    if(slave_addr==7)dir=fw;
    else if(slave_addr==8)dir=bw;
    else dir=stp;
  }
  else if(mot=='Z'){//slide left backward
    pwmValue=value;
    if(slave_addr==6||slave_addr==7)dir=bw;
    else dir=stp;
  }
  else if(mot=='A'){
    pwmValue=value;
    if(slave_addr==7||slave_addr==8)dir=fw;
    else dir=bw;
  }
  else if(mot=='D'){
    pwmValue=value;
    if(slave_addr==7||slave_addr==8)dir=bw;
    else dir=fw;
  }
  //enable motor
  if(digitalRead(pinEn)==HIGH){
    motorDrive(dir,pwmValue); 
  }
  else motor_disable();
}

void receiveEvent(){
  mot = ((char)Wire.read());
  value=0;
  value |= ((int)(Wire.read()) << 8);
  value |= ((int)(Wire.read()));
}

