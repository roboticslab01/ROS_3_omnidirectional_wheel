#include "motorI2C.h"

void define_slave(unsigned char addr, char pt){
  if(pt=='L')reglist[kir]=addr;
  else if(pt == 'M')reglist[tgh]=addr;
  else if(pt == 'R')reglist[kan]=addr;
}

void transmitdata(char mot, unsigned char addrs, unsigned char reg){
  Wire.beginTransmission(addrs);
  //Wire.write(reg);
  if(reg==SEND_MOTOR_CONTROL){
    Wire.write((char)mot);
    Wire.write((byte)(pwmValue>>8)); 
    Wire.write((byte)(pwmValue));
  }
  Wire.endTransmission();
}

void mov(char mot, int val, int enc){
  pwmValue = val;
  for(unsigned char i=0;i<3;i++){
    transmitdata(mot, reglist[i], SEND_MOTOR_CONTROL);  
  }  
}

void motor_enable(){
  digitalWrite(pinEn[0],HIGH);  
  digitalWrite(pinEn[1],HIGH);
  digitalWrite(pinEn[2],HIGH);
}

void motor_disable(){
  digitalWrite(pinEn[0],LOW);  
  digitalWrite(pinEn[1],LOW);
  digitalWrite(pinEn[2],LOW);
}
