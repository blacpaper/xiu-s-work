// 引入所需的库
#include <NTPClient.h>	// NTP时间同步客户端库
#include <ESP8266WiFi.h>	// ESP8266 Wi-Fi库
#include <WiFiUdp.h>	// Wi-Fi UDP通信库
#include <Wire.h>	// I2C通信库
#include <U8g2lib.h>	// OLED屏幕显示
#include <time.h>	// 时间函数库

// 创建Wi-Fi UDP对象，用于UDP网络通信
WiFiUDP ntpUDP;
// 创建NTP客户端，使用阿里云的NTP服务器，时区便宜设置为北京时间（东八区）
NTPClient timeClient(ntpUDP, "ntp.aliyun.com", 60*60*8, 30*60*1000);

// 初始化OLED屏幕， 使用I2C通信
U8G2_SSD1306_128X64_NONAME_1_SW_I2C u8g2(U8G2_R0, SCL, SDA, U8X8_PIN_NONE);

// Wi-Fi连接参数
const char *ssid = "CIAlab";	// Wi-Fi SSID
const char *password = "81234567";	// Wi-Fi密码

// 星期和月份的数组
const char *days[] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
const char *months[] = {"Dec", "Jan", "Feb", "Mar", "Apr", "May", "June", "July", "Aug", "Sep", "Oct", "Nov"};
const char *ampm[] = {"AM", "PM"};	//上午和下午的标识

void setup(){
 Serial.begin(9600);	//初始化串口通信
 Wire.begin();		//初始化I2C通信
 
 // 连接到Wi-Fi网络
 WiFi.begin(ssid, password);
 // 等待Wi-Fi连接
 while(WiFi.status() != WL_CONNECTED){
  Serial.print(".");
  delay(500);
 }

 // 开始NTP时间同步
 timeClient.begin();
 u8g2.begin();	// 初始化OLED屏幕
}

void loop(){
 // 更新NTP时间
 timeClient.update();
 if (WiFi.status() == WL_CONNECTED){	// 检查Wi-Fi是否连接
  // 获取时间
  time_t epochTime = timeClient.getEpochTime();
  String epochTimeString = String(epochTime);

  int currentHours = timeClient.getHours();
  int currentMinutes = timeClient.getMinutes();
  int currentSeconds = timeClient.getSeconds();
  int weekDay = timeClient.getDay();

  // 转换时间戳为可读格式
  struct tm *ptm = gmtime((time_t *)&epochTime);

  int year = ptm->tm_year + 1900;
  int month = ptm->tm_mon + 1;
  int day = ptm->tm_mday;
  Serial.println(year);
  Serial.println(month);
  Serial.println(day);

  // 绘制OLED屏幕时间
  u8g2.firstPage();
  do{
   // 绘制图标和文本
   u8g2.setFont(u8g2_font_open_iconic_www_1x_t);
   u8g2.drawGlyph(66, 12, 0x0051);	// 绘制图标
   u8g2.setFont(u8g2_font_open_iconic_all_2x_t);
   u8g2.drawGlyph(112, 34, 0x007B);	// 绘制图标
   u8g2.setFont(u8g2_font_ncenB12_tr);
   u8g2.drawStr(92, 12, days[weekDay]);
   u8g2.setFont(u8g2_font_ncenB18_tr);
   u8g2.drawStr(8, 38, String(currentHours).c_str());
   u8g2.drawStr(36, 38, ":");
   u8g2.drawStr(44, 38, String(currentMinutes).c_str());
   u8g2.setFont(u8g2_font_ncenB10_tr);
   u8g2.drawStr(8, 12, ssid);	// 绘制Wi-Fi SSID
   u8g2.drawStr(80, 34, currentHours > 12 ? "PM" : "AM");
   u8g2.drawStr(8, 56, months[month]);
   u8g2.drawStr(40, 56, String(day).c_str());
   u8g2.drawStr(56, 56, ".");
   u8g2.drawStr(62, 56, String(year).c_str());
   u8g2.drawStr(98, 49, "CIA");
   u8g2.drawStr(103, 63, "lab");
  } while (u8g2.nextPage());
 }
}
