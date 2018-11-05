#ifndef MOTORI2C_H
#define MOTORI2C_H

//List of The Register Function
#define SEND_MOTOR_CONTROL     0x01
#define SEND_ENCODER_VALUE     0x02
//define the number of the slave
#define nSlave  3
#define L       'L'
#define M       'M'
#define R       'R'
#define kir     0
#define tgh     1
#define kan     2

typedef struct{
  unsigned char address;
}slave;

byte reglist[nSlave];
//variable to send
int pwmValue;
int encoderData[nSlave];

//function
void define_slave(unsigned char addr, char pt);
void transmitdata(char mot, unsigned char addrs, unsigned char reg);

#endif
