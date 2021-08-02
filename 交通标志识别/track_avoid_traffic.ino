#include <Wire.h>

int Left_motor_back=8;     //左电机前进(IN1)
int Left_motor_go=9;     //左电机后退(IN2)
int Right_motor_go=10;    // 右电机前进(IN3)
int Right_motor_back=11;    // 右电机后退(IN4)

int Distance = 0;
const int SensorRight = 3;   	//右循迹红外传感器(P3.2 OUT1)
const int SensorLeft = 4;     	//左循迹红外传感器(P3.3 OUT2)

int SL;    //左循迹红外传感器状态
int SR;    //右循迹红外传感器状态

int command = 0;

void setup()
{
  pinMode(Left_motor_back,OUTPUT); // PIN 8 (PWM)
  pinMode(Left_motor_go,OUTPUT); // PIN 9 (PWM)
  pinMode(Right_motor_go,OUTPUT);// PIN 10 (PWM) 
  pinMode(Right_motor_back,OUTPUT);// PIN 11 (PWM)
  pinMode(SensorRight, INPUT); //定义右循迹红外传感器为输入
  pinMode(SensorLeft, INPUT); //定义左循迹红外传感器为输入
  Wire.begin(8);
  Wire.onReceive(receiveEvent);
}

//=======================智能小车的基本动作=========================
//void run(int time)     // 前进
void run()
{
   digitalWrite(Right_motor_go,HIGH);  // 右电机前进
  digitalWrite(Right_motor_back,LOW);     
  analogWrite(Right_motor_go,100);
  analogWrite(Right_motor_back,0);
  digitalWrite(Left_motor_back,LOW);  
  digitalWrite(Left_motor_go,HIGH);// 左电机前进
  analogWrite(Left_motor_back,0);
  analogWrite(Left_motor_go,100);
  //delay(time * 100);   //执行时间，可以调整  
}

//void brake(int time)  //刹车，停车
void brake()
{
  digitalWrite(Right_motor_go,LOW);
  digitalWrite(Right_motor_back,LOW);
  digitalWrite(Left_motor_back,LOW);
  digitalWrite(Left_motor_go,LOW);
  //delay(time * 100);//执行时间，可以调整  
}

//void left(int time)         //左转(左轮不动，右轮前进)
void left()
{
  digitalWrite(Right_motor_go,HIGH);	// 右电机前进
  digitalWrite(Right_motor_back,LOW);
  analogWrite(Right_motor_go,150); 
  analogWrite(Right_motor_back,0);//PWM比例0~255调速
  digitalWrite(Left_motor_back,LOW);   
  digitalWrite(Left_motor_go,LOW);
  analogWrite(Left_motor_back,0); 
  analogWrite(Left_motor_go,0);//PWM比例0~255调速
  //delay(time * 100);	//执行时间，可以调整  
}

//void right(int time)        //右转(右轮不动，左轮前进)
void right()
{
  digitalWrite(Right_motor_go,LOW);   
  digitalWrite(Right_motor_back,LOW);
  analogWrite(Right_motor_go,0); 
  analogWrite(Right_motor_back,0);//PWM比例0~255调速
  digitalWrite(Left_motor_back,LOW);
  digitalWrite(Left_motor_go,HIGH);//左电机前进
  analogWrite(Left_motor_back,0); 
  analogWrite(Left_motor_go,150);//PWM比例0~255调速
  //delay(time * 100);	//执行时间，可以调整  
}

//void back(int time)
void back()
{
  digitalWrite(Right_motor_go,LOW);   //右电机后退
  digitalWrite(Right_motor_back,HIGH);
  analogWrite(Right_motor_go,0); 
  analogWrite(Right_motor_back,150);//PWM比例0~255调速
  digitalWrite(Left_motor_back,LOW);
  digitalWrite(Left_motor_go,HIGH);//左电机后退
  analogWrite(Left_motor_back,0); 
  analogWrite(Left_motor_go,150);//PWM比例0~255调速
  //delay(time * 100);	//执行时间，可以调整  
}

void loop()
{ 
}

void receiveEvent(int howMany)
{
  while(Wire.available())
  {
		command = Wire.read();
			
		if(command == 1){
    	left();
		delay(50);
		//continue;
		}

		else if(command == 2){
		right();
		delay(50);
		//continue;
		}

		else if(command == 3){
		brake();
		delay(50);
		//continue;
		}

		else if(command == 4){
		back();
		delay(50);
		//continue;
		}

		else if(command == 5){
		run();
		delay(50);
		//continue;
		}

	else{
	 SR = digitalRead(SensorRight);
	 SL = digitalRead(SensorLeft);
	 if (SL == LOW&&SR==LOW)
	   run();   
	 else if (SL == HIGH & SR == LOW){
	   right();
	  }
	  else if (SR == HIGH & SL == LOW) {
		left();
	  }
      
    }
   }
}
