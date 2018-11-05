//Master
#include <ros.h>
#include <std_msgs/String.h>
#include <std_msgs/Int16.h>
#include <Wire.h>
#include <LiquidCrystal.h>
#include "motorI2C.h"
#include "interface.h"

LiquidCrystal lcd(42,40,38,36,34,32);

ros::NodeHandle nh;

slave kiri={6};
slave tengah={7};
slave kanan={8};
unsigned char pinEn[3]={22,24,26};
unsigned char kirim=0;
String val;
int pwmVal=0;

void run_program();

void subs_com(const std_msgs::String & dat){
  val = dat.data;
  kirim=0;
}

void subs_pwm(const std_msgs::Int16 & pwmval){
  pwmVal = pwmval.data; 
  kirim=0;
}

ros::Subscriber<std_msgs::String> sub("movement", &subs_com);
ros::Subscriber<std_msgs::Int16> sub1("pwm_value", &subs_pwm);

void setup() {
  define_slave(kiri.address,L);
  define_slave(tengah.address,M);
  define_slave(kanan.address,R);  
  lcd.begin(16,2);
  for(unsigned char i=0;i<3;i++){
    pinMode(pinEn[i],OUTPUT);
    digitalWrite(pinEn[i],LOW);
  }
  Wire.begin();
  nh.initNode();
  nh.subscribe(sub);
  nh.subscribe(sub1);
}

void loop() {
  // put your main code here, to run repeatedly:
  run_program();
  nh.spinOnce();
}

void run_program(){
  if(kirim==0){
    if(val=="f")mov('F',pwmVal,0);
    else if(val=="l")mov('L',pwmVal,0);
    else if(val=="r")mov('R',pwmVal,0);
    else if(val=="b")mov('B',pwmVal,0);
    else if(val=="q")mov('Q',pwmVal,0);
    else if(val=="e")mov('E',pwmVal,0);
    else if(val=="z")mov('Z',pwmVal,0);
    else if(val=="c")mov('C',pwmVal,0);
    else if(val=="o")mov('D',pwmVal,0);
    else if(val=="p")mov('A',pwmVal,0);
    else mov('S',0,0);
    motor_enable();
    kirim=1;  
  }  
}
