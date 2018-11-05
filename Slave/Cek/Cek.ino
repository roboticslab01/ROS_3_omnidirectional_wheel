#include <Wire.h>
#define slave_addr  6

int value=0;

void setup() {
  // put your setup code here, to run once:
  Wire.begin(slave_addr);
  Wire.onReceive(receiveEvent);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println(value);

}

void receiveEvent(){
    value = 0;
    value |= ((int)(Wire.read())) << 8;
    value |= ((int)(Wire.read()));
}
