#include <Wire.h>	// 引入I2C 库

#define SHT30_ADDRESS 0x44	// 定义传感器的I2C地址

struct THData{			// 创建结构体存储温湿度值
 float tempareture;
 float humidity;
};

void setup(){			// 初始设置
 Wire.begin();			// I2C通信初始化
 Serial.begin(9600);		// 串口通信初始化，波特率为9600
}

void loop(){
 THData data = SHT30();		// 调用SHT30()函数测量温湿度，结果储存data中
 if(data.tempareture != -999 && data.humidity != -999){	// 判断数据是否有效
   char temparetureStr[10];	// 定义字符数组用于转换温度数值为字符串
   char humidityStr[10];	// 定义字符数组用于转换湿度树枝为字符串

   // 使用dtostrf函数将浮点数转换为字符串，并指定缓冲区长度、最小宽度、精度和小数点后位数
   dtostrf(data.tempareture, 4, 2, temparetureStr);
   dtostrf(data.humidity, 4, 2, humidityStr);

   delay(100);			// 稍作延时，确保数据稳定

   // 通过串口输出温度和湿度数据
   Serial.print("Tem:");
   Serial.println(temparetureStr);
   Serial.print("Hum:");
   Serial.println(humidityStr);
 }
}

// SHT30函数用于从SHT30温湿度传感器读取数据
THdata SHT30(){
 // 发送开始信号给SHT30，请求测量周期性的温度和湿度数据
 Wire.beginTransmission(SHT30_ADDRESS);	// 发送I2C开始信号并指定SHT30的地址
 Wire.write(0x2c);			// 发送命令字，0x2c是测量周期性数据的指令
 Wire.write(0x06);			// 发送CRC校验码
 Wire.endTransmission();		// 发送I2C结束信号
 delay(500);				// 等待SHT30准备好数据，这里延迟500ms

 // 请求从SHT30读取6个字节的数据
 Wire.requestFrom(SHT30_ADDRESS, 6);

 // 检查是否成功接收了6个字节的数据
 if(Wire.available() == 6){
   uint16_t rawTempareture = Wire.read() << 8 | Wire.read();	// 读取两个字节并合成16位的温度原始值
   Wire.read();		// 跳过校验和字节
   uint16_t rawHumidity = Wire.read() << 8 | Wire.read();	// 读取两个字节并合成16位的湿度原始值
   Wire.read();

   // 将原始的温度和湿度值转换为实际的数值
   float tempareture = -45 + 175 * (float)rawTempareture / 65535.0;
   float humidity = 100 * (float)rawHumidity / 65535.0

   THData data;		// 创建THData结构体实例
   data.tempareture = tempareture; 	// 将计算后的温度赋值给data的tempareture成员
   data.humidity = humidity;		// 将计算后的湿度赋值给data的humidity成员

   return data;		// 返回包含温度和湿度数据的THData结构体
 }else{
  // 如果没有成功接收到数据，返回一个错误值
  THData errorData;
  errorData.tempareture = -999;		// 设置错误的温度值
  errorData.humidity = -999;		// 设置错误湿度值
  return errorData;			// 返回包含错误值的THData结构体
 }
}
