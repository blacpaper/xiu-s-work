// 引用软串口库
#include <SoftwareSerial.h>

// 定义一个软串口 loraSerial，RX-5，TX-6
SoftwareSerial loraSerial(5, 6);

void setup() {
  // 串口初始化，波特率设置为9600
  Serial.begin(9600);

  // 软串口初始化，波特率设置为9600
  loraSerial.begin(9600);

}

void loop() {
  // lora发送
  // 设置要发送的消息内容
  String data = "Hello from Board 1";

  // lora发送消息
  loraSerial.prntln(data);

  // 适当延时，避免串口堵塞，ms
  delay(1000);
}

/////////////////////////////////////////////
// 接收消息
// 这需要在另外一块开发版上重新写入代码，注释代码前注释即可

// void loop() {
//  // lora接收
//  // 检查是否接收到消息
//  if(loraSerial.available()){
//    // 储存接收到的消息
//    String data = loraSerial.readStringUntil('\n');
//    // 打印接收到的消息
//    Serial.println(data);
//  }
// }
