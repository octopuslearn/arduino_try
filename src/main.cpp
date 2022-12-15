                  #include <string.h>
                  #define IBUS_BUFFSIZE 32 ////32个数据   
                  #define IBUS_MAXCHANNELS 10 // I am using only 10 channels because my TX (FlySky i6) supports max 10 channels//我只使用 10 个通道，因为我的 TX (FlySky i6) 最多支持 10 个通道
                  #include <Server.h>

                  static uint8_t ibusIndex = 0;//第几个数据
                  static uint8_t ibus[IBUS_BUFFSIZE] = {0};//存放32个数据的数组
                  static uint16_t rcValue[IBUS_MAXCHANNELS];//通道
                  
                  static boolean rxFrameDone;//布尔型变量
                  
                  int ch_width_1;//pwm输出值
                  int ch_width_2;
                  int ch_width_3;
                  int ch_width_4;
                  int ch_width_5;
                  int ch_width_6;
                  int ch_width_7;
                  int ch_width_8;
                  int ch_width_9;
                  int ch_width_10;
                  
                  Servo ch1;//声明用到的电机
                  Servo ch2;
                  Servo ch3;
                  Servo ch4;
                  Servo ch5;
                  Servo ch6;
                  Servo ch7;
                  Servo ch8;
                  Servo ch9;
                  Servo ch10;
                  
                  void setup()
                  {
                    Serial.begin(115200);
                    // ch1.attach(2);//电机接到的引脚
                    ch1.attach(7);
                    // ch3.attach(4);
                    ch2.attach(5);
                    ch3.attach(6);
                    // ch6.attach(7);
                    // ch7.attach(8);
                    ch4.attach(9);
                    ch5.attach(10);
                    ch6.attach(11);
                    pinMode(13,OUTPUT);
                  }
                  
                  void loop()
                  {
                    readRx();
                  }
                  
                  void readRx()
                  {

                    rxFrameDone = false;//flase-0,true-1(即真假)
                   
                    if (Serial.available())//返回串口缓冲区中当前剩余的字符个数。一般用这个函数来判断串口的缓冲区有无数据，当Serial.available()>0时，说明串口接收到了数据，可以读取；
                                           //Serial.read()指从串口的缓冲区取出并读取一个Byte的数据，比如有设备通过串口向Arduino发送数据了，我们就可以用Serial.read()来读取发送的数据。
                    {
                    digitalWrite(13,HIGH);
                    delay(1000);
                    digitalWrite(13,LOW);
                    delay(1000);
                      uint8_t val = Serial.read();////读到的串口数据
                      // Look for 0x2040 as start of packet
                      if (ibusIndex == 0 && val != 0x20)//寻找 0x2040 作为数据包的开始
                      {
                        ibusIndex = 0;
                        return;
                      }
                      if (ibusIndex == 1 && val != 0x40)
                      {
                        ibusIndex = 0;
                        return;
                      }////到此为检测开始位
                  
                      if (ibusIndex == IBUS_BUFFSIZE)
                      {
                        ibusIndex = 0;
                        int high=3;
                        int low=2;
                        for(int i=0;i<IBUS_MAXCHANNELS; i++)//左移第一个字节的前 8 位，并加上前一个字节的全部值
                        {
                          rcValue[i] = (ibus[high] << 8) + ibus[low];
                          high += 2;
                          low += 2;
                        }
                        ch_width_1 = map(rcValue[0], 1000, 2000, 1000, 2000);
                        ch1.writeMicroseconds(ch_width_1);////将一个以微秒 (us) 为单位的值写入伺服，相应地控制轴。在标准伺服系统上，这将设置轴的角度。
                  
                            Serial.print(ch_width_1);
                            Serial.print("     ");
                  
                        ch_width_2 = map(rcValue[1], 1000, 2000, 1000, 2000);
                        ch2.writeMicroseconds(ch_width_2);
                  
                            Serial.print(ch_width_2);
                            Serial.print("     ");
                  
                        ch_width_3 = map(rcValue[2], 1000, 2000, 1000, 2000);
                        ch3.writeMicroseconds(ch_width_3);
                  
                            Serial.print(ch_width_3);
                            Serial.print("     ");
                  
                        ch_width_4 = map(rcValue[3], 1000, 2000, 1000, 2000);
                        ch4.writeMicroseconds(ch_width_4);
                  
                            Serial.print(ch_width_4);
                            Serial.print("     ");
                                    
                        ch_width_5 = map(rcValue[4], 1000, 2000, 1000, 2000);
                        ch5.writeMicroseconds(ch_width_5);
                  
                            Serial.print(ch_width_5);
                            Serial.print("      ");
                  
                        ch_width_6 = map(rcValue[5], 1000, 2000, 1000, 2000);
                        ch6.writeMicroseconds(ch_width_6);
                  
                            Serial.print(ch_width_6);
                            Serial.print("      ");
                  
                        ch_width_7 = map(rcValue[6], 1000, 2000, 1000, 2000);
                        ch7.writeMicroseconds(ch_width_7);
                  
                            Serial.print(ch_width_7);
                            Serial.print("      ");
                       
                       
                        ch_width_8 = map(rcValue[7], 1000, 2000, 1000, 2000);
                        ch8.writeMicroseconds(ch_width_8);
                            Serial.print(ch_width_8);
                            Serial.print("     ");
                       
                        ch_width_9 = map(rcValue[8], 1000, 2000, 1000, 2000);
                        ch9.writeMicroseconds(ch_width_9);
                  
                            Serial.print(ch_width_9);
                            Serial.print("     ");
                  
                        ch_width_10 = map(rcValue[9], 1000, 2000, 1000, 2000);
                        ch10.writeMicroseconds(ch_width_10);
                  
                            Serial.print(ch_width_10);
                            Serial.println("     ");
                                                  
                        rxFrameDone = true;
                        return;
                      }
                      else
                      {
                        ibus[ibusIndex] = val;
                        ibusIndex++;
                    digitalWrite(13,HIGH);
                    delay(1000);
                    digitalWrite(13,LOW);
                    delay(1000);
                      }
                    }
                  }
