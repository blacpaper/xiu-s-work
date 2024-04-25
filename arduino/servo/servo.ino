#include <Servo.h>	// 引入Arduino的Servo库，用于控制伺服电机

Servo servo;		// 创建Servo对象，用于操作伺服电机

void setup(){
 Serial.begin(9600);	// 初始化串口通信，设置波特率为9600，用于调试信息输出
 servo.attach(9);	// 将伺服电机连接到数字口9，开始控制伺服电机
}

void loop(){
 servo.write(0);	// 将伺服电机的角度设置为0度
 delay(1000);		// 等待1000毫秒（1秒），让伺服电机达到指定角度
 
 servo.write(90);	// 将伺服电机的角度设置为90度
 delay(1000);		// 等待1000毫秒，让伺服电机达到指定角度

 servo.write(180);	// 将伺服电机的角度设置为180度
 delay(1000);		// 等待1000毫秒，让伺服电机达到指定角度

 servo.write(90);	// 将伺服电机的角度设置回90度
 delay(1000);		// 等待1000毫秒，让伺服电机达到指定角度
}
