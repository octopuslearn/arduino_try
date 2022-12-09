#include <Arduino.h>

int interruptD2=2;//设置D2为中断
unsigned long ch[8],t[9];//1-8共8个通道，定时值从第一个通道初开始触发，共9个
int pulse=0,cont=1;

void interrupT0() {
  cont++;
  t[pulse]=cont;
  switch(pulse)
  {
    case 1: ch[1]=t[1]-t[0];pulse++; 
        if(ch[1]>3000)
    {
      t[0]=t[1];
      pulse=1;
    }break;
    case 2: ch[2]=t[2]-t[1];pulse++;
        if(ch[2]>3000)
    {
      t[0]=t[2];
      pulse=1;
    } break;
    case 3: ch[3]=t[3]-t[2];pulse++;
        if(ch[3]>3000)
    {
      t[0]=t[3];
      pulse=1;
    } break;
    case 4: ch[4]=t[4]-t[3];pulse++;
        if(ch[4]>3000)
    {
      t[0]=t[4];
      pulse=1;
    } break;
    case 5: ch[5]=t[5]-t[4];pulse++;
        if(ch[5]>3000)
    {
      t[0]=t[5];
      pulse=1;
    } break;
    case 6: ch[6]=t[6]-t[5];pulse++;
        if(ch[6]>3000)
    {
      t[0]=t[6];
      pulse=1;
    } break;
    case 7: ch[7]=t[7]-t[6];pulse++;
        if(ch[7]>3000)
    {
      t[0]=t[7];
      pulse=1;
    } break;
    case 8: ch[8]=t[8]-t[7];pulse++;
        if(ch[8]>3000)
    {
      t[0]=t[8];
      pulse=1;
    } break;
    default: pulse++; break;//由于第一次时pulse本身作为起始点0，故而不属于8个通道，然后加一次进入下一个脉冲
  }
}

void setup() {
  attachInterrupt(digitalPinToInterrupt(interruptD2),interrupT0,RISING);//注册中断号interruptD2，要调用中断函数interrupt0，触发模式上升沿触发RISING
  Serial.begin(9600);
}

void loop() {


}


void print_information() {
  Serial.print(ch[1]);
  Serial.print("-");
  Serial.print(ch[2]);
  Serial.print("-");
  Serial.print(ch[3]);
  Serial.print("-");
  Serial.print(ch[4]);
  Serial.print("-");
  Serial.print(ch[5]);
  Serial.print("-");
  Serial.print(ch[6]);
  Serial.print("-");
  Serial.print(ch[7]);
  Serial.print("-");
  Serial.print(ch[8]);
}