#define ch1 11
#define ch2 10 
#define MotorA 5 //Velocidade Motor A(0-255)//电机速度
#define MotorB 6 //Velocidade Motor B(0-255)
//// #define DirA 7 //Direção Motor A//电机方向
//// #define DirB 8 //Direção Motor B
double ch1Raw = 0;
double ch1Adj = 0;
double ch2Raw = 0;
double ch2Adj = 0;
double r=0;
double rAdj=0;
float theta=0;
float thetaD=0;
float velB=0;
float velA=0;
int dir=0;
/*dir=0 centro
  dir=1 frente esquerda
  dir=2 frente direita
  dir=3 ré esquerda
  dir=4 ré direita
  dir=5 frente total
  dir=6 ré total
  dir=7 esquerda total
  dir=8 direita total
  
*/
void setup() {
 pinMode(11,INPUT);
 pinMode(10,INPUT);
 pinMode(MotorA,OUTPUT);
 pinMode(MotorB,OUTPUT);
////  pinMode(DirA,OUTPUT);//电机方向
////  pinMode(DirB,OUTPUT);
 Serial.begin(9600);

}

void loop() {
  readCh();
  adjCh();
  //printCh();
  //printAdjCh();
  recToPolar();
  pwmMotor();
  
  
  /*Serial.print("thetaD:");
  //Serial.println(thetaD);
  Serial.print("r:");
  Serial.println(r);
  Serial.print("velA:");
  Serial.println(velA);
  Serial.print("velB:");
  Serial.println(velB);
  delay(500);*/
  
  
}
void readCh(){ 
  ch1Raw = pulseIn(ch1,HIGH);//Lê  o tempo que os pinos conectados aos canais do receptor//读取引脚连接到接收器通道的时间 pulseIn(ch1,HIGH)-读取ch1高电平脉冲宽度
  ch2Raw = pulseIn(ch2,HIGH);//Turnigy 9X permaneceram ativos durante o pulso recebido//Turnigy 9X 在接收脉冲期间保持活动状态
}

void adjCh(){
  ch1Adj=map(ch1Raw,1030,1860,-255,255);//Remapeia os valores recebidos dos canais, ajustando-os//重新映射从通道接收到的值，调整它们 map()-x =map(value, fromLow, fromHigh, toLow, toHigh);
//x,value为同类型变量，fromHigh与fromLow为t变量本身的上下界，toHigh与toLow为x变量的上下界。该函数将t变量值根据范围比例变换后将结果存入x变量。


  ch2Adj=map(ch2Raw,1030,1860,-255,255);//ajustando-os para valores entre -255 e +255//将它们调整为 -255 和 +255 之间的值
  if(ch1Adj>-10 && ch1Adj<10){
    ch1Adj=0;                  //Cria deadzones, ou zonas mortas p/ compensar variações //创建死区或死区以补偿变化
  }                            //naturais na centralização do joystick//操纵杆居中自然
  if(ch2Adj>-20 && ch2Adj<20){
   ch2Adj=0;
  }
}

void printCh(){//打印原先值
  Serial.print("Ch1 = ");
  Serial.print(ch1Raw);
  Serial.print(" -  ");  //Imprime os Valores lidos pelos canais (somente DEBUG)//打印通道读取的值（仅限 DEBUG）
  Serial.print("Ch2 = ");
  Serial.print(ch2Raw);
  Serial.println(" -  ");
  delay(500);
}
void printAdjCh(){//打印使用map()重新规划范围后的值
  Serial.print("ch1Adj = ");
  Serial.print(ch1Adj);
  Serial.print(" -  ");     //Imprime os valores já remapeados (somente DEBUG).//打印已经重新映射的值（仅限 DEBUG）
  Serial.print("ch2Adj = ");
  Serial.print(ch2Adj);
  Serial.println(" -  ");
  delay(500);
}
//// void recToPolar(){
////   r=sqrt(pow(ch1Adj,2)+pow(ch2Adj,2));//Executa a conversão das coordenadas retangulares(ch1Adj e ch2Adj)//执行直角坐标的转换（ch1Adj 和 ch2Adj）

////   theta=atan2(ch2Adj,ch1Adj);         //em coordenada polares( raio e ângulo), de forma trigonométrica.//在极坐标（半径和角度）中，三角函数。
////   if(ch1Adj<-5&&ch2Adj>5){ //Realiza as conversões necessárias entre o resultado em radianos gerado pelas funções //在函数生成的弧度结果之间执行必要的转换
////     thetaD=theta*(180/PI);//trigonométricas da Linguagem C, para Graus, e define os quadrantes do movimento segundo a tabela acima (dir)//C语言三角函数，对于Degrees，根据上表（右）定义运动的象限
////     dir=1;
////  }
////   if(ch1Adj>5&&ch2Adj>5){
////     thetaD=theta*(180/PI);
////     dir=2;
////   }
////   if(ch1Adj<-5&&ch2Adj<-5){
////     thetaD=360+(theta*(180/PI));
////     dir=3;
////   }
////   if(ch1Adj>5&&ch2Adj<-5){
////     thetaD=360+(theta*(180/PI));
////     dir=4;
////  }
////   if(ch1Adj>-5&&ch1Adj<5&&ch2Adj>-5&&ch2Adj<=255){
////    r=ch2Adj;
////     thetaD=90;
////     dir=5;
////   }
////   if(ch1Adj>-5&&ch1Adj<5&&ch2Adj<5&&ch2Adj>=-255){
////     r=-ch2Adj;
////    thetaD=270;
////     dir=6;
////   }
////   if(ch1Adj<5&&ch1Adj>=-255&&ch2Adj>-5&&ch2Adj<5){
////    r=-ch1Adj;
////     thetaD=180;
////     dir=7;
////   }
////   if(ch1Adj>-5&&ch1Adj<=255&&ch2Adj>-5&&ch2Adj<5){
////     r=ch1Adj;
////     thetaD=0;
////     dir=8;
////   }
////   if(r>-10&&r<10){
////    r=0;
////     thetaD=0;
////     dir=0;
////   }
////---------------------------------------------------------------------------------------------------------- 
////}
// void pwmMotor(){ //根据不同的方式控制电机
//   操纵杆所在的方向和象限。
//   它使用正弦的三角实体，因为速度
//   其中一个电机必须更小，这样机器人才能执行曲线，所以
//   其中一个电机接收总半径值作为 PWM，它的一对接收
//   变量 velA 或 velB 由半径、正弦相乘构成
//   那一刻的角度和修正系数（允许更紧或更开放的转弯）
  /*Realiza o controle dos motores de forma diferencial, de acordo  
  com a direção e o quadrante que a alavanca do joystick se encontra.
  Utiliza-se da entidade trigonométrica do seno, pois a velocidade de 
  um dos motores deve ser menor para que o robô consiga realizar curvas, logo
  um dos motores recebe o valor total do raio como PWM, e o seu par recebe a 
  variável velA ou velB que é constituída pela multiplicação entre o raio,o  seno 
  do ângulo naquele momento e um fator de correção (possibilita curvas mais fechadas ou mais abertas)
  */
//   rAdj=map(r,0,361,0,255);
 
//   if(dir==0&&thetaD==0){//parada
//   ////  digitalWrite(DirA,LOW); 
//   ////  digitalWrite(DirB,LOW); 
//    analogWrite(MotorA,0); //Velocidade Motor A = 0 a 255
//    analogWrite(MotorB,0); //Velocidade Motor B = 0 a 255  
//   }
//   if(dir==1&&(thetaD!=0&&thetaD!=90&&thetaD!=180&&thetaD!=270)){//frente esquerda
//   ////  digitalWrite(DirA,HIGH); //Motor A para FRENTE//发动机A前进
//   ////  digitalWrite(DirB,HIGH); //Motor B para FRENTE
//    velA = 0.7*rAdj*sin(theta);
//    analogWrite(MotorA,velA); //Velocidade Motor A = 0 a 255//马达转速A = 0 to 255
//    analogWrite(MotorB,rAdj); //Velocidade Motor B = 0 a 255  
//   }
//   if(dir==2&&(thetaD!=0&&thetaD!=90&&thetaD!=180&&thetaD!=270)){//frente direita//右前方
//   ////  digitalWrite(DirA,HIGH); //Motor A para FRENTE
//   ////  digitalWrite(DirB,HIGH); //Motor B para FRENTE
//    analogWrite(MotorA,rAdj); //Velocidade Motor A = 0 a 255
//    velB = 0.7*rAdj*sin(theta);
//    analogWrite(MotorB,velB); //Velocidade Motor B = 0 a 255  
//   }
//   if(dir==3&&(thetaD!=0&&thetaD!=90&&thetaD!=180&&thetaD!=270)){//ré esquerda//左倒车
//   ////  digitalWrite(DirA,LOW); //Motor A para TRÁS//发动机 A 向后
//   ////  digitalWrite(DirB,LOW); //Motor B para TRÁS
//    velA = 0.7*(-rAdj)*sin(theta);
//    analogWrite(MotorA,velA); //Velocidade Motor A = 0 a 255
//    analogWrite(MotorB,rAdj); //Velocidade Motor B = 0 a 255  
//   }
//   if(dir==4&&(thetaD!=0&&thetaD!=90&&thetaD!=180&&thetaD!=270)){//ré direita
//   ////  digitalWrite(DirA,LOW); //Motor A para TRÁS
//   ////  digitalWrite(DirB,LOW); //Motor B para TRÁS
//    analogWrite(MotorA,rAdj); //Velocidade Motor A = 0 a 255
//    velB = 0.7*(-rAdj)*sin(theta);
//    analogWrite(MotorB,velB); //Velocidade Motor B = 0 a 255  
//   }  
//   if(dir==5&&thetaD==90){//frente
//   ////  digitalWrite(DirA,HIGH); //Motor A para FRENTE
//   ////  digitalWrite(DirB,HIGH); //Motor B para FRENTE
//    analogWrite(MotorA,rAdj); //Velocidade Motor A = 0 a 255
//    analogWrite(MotorB,rAdj); //Velocidade Motor B = 0 a 255
//   }
//   if(dir==6&&thetaD==270){//ré
//   ////  digitalWrite(DirA,LOW); //Motor A para TRÁS
//   ////  digitalWrite(DirB,LOW); //Motor B para TRÁS
//    analogWrite(MotorA,rAdj); //Velocidade Motor A = 0 a 255
//    analogWrite(MotorB,rAdj); //Velocidade Motor B = 0 a 255
//   }
//   if(dir==7&&thetaD==180){//esquerda
//   ////  digitalWrite(DirA,LOW); //Motor A para FRENTE
//   ////  digitalWrite(DirB,HIGH); //Motor B para TRÁS
//    analogWrite(MotorA,rAdj); //Velocidade Motor A = 0 a 255
//    analogWrite(MotorB,rAdj); //Velocidade Motor B = 0 a 255
//   }    
//   if(dir==8&&thetaD==0){//direita
//   ////  digitalWrite(DirA,HIGH); //Motor A para TRÁS
//   ////  digitalWrite(DirB,LOW); //Motor B para FRENTE
//    analogWrite(MotorA,rAdj); //Velocidade Motor A = 0 a 255
//    analogWrite(MotorB,rAdj); //Velocidade Motor B = 0 a 255
//   }
// }


