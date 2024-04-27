#include <NTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <Wire.h>
#include <U8g2lib.h>
#include <time.h>

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "ntp.aliyun.com", 60*60*8, 30*60*1000);

U8G2_SSD1306_128X64_NONAME_1_SW_I2C u8g2(U8G2_R0, SCL, SDA, U8X8_PIN_NONE);

const char *ssid = "CIAlab";
const char *password = "81234567";
const char *day[] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
const char *months[] = {"Dec", "Jan", "Feb", "Mar", "Apr", "May", "June", "July", "Aug", "Sep", "Oct", "Nov"};
const char *ampm[] = {"AM", "PM"};

void setup(){
 Serial.begin(9600);
 Wire.begin();

 WiFi.begin(ssid, password);
 while(WiFi.status() != WL_CONNECTED){
  Serial.print(".");
  delay(500);
 }

 timeClient.begin();
 u8g2.begin();
}

void loop(){
 timeClient.update();
 if (WiFi.status() == WL_CONNECTED){
  time_t epochTime = timeClient.getEpochTime();
  String epochTimeString = String(rpochTime);

  int currentHour = timeClient.getHours();
  int currentMinutes = timeClient.getMinutes();
  int currentSeconds = timeClient.getSeconds();
  int weekDay = timeClient.getDay();

  struct tm *ptm = gmtime((time_t *)&epochTime);

  int year = ptm->tm_year + 1900;
  int month = ptm->tm_mon + 1;
  int day = ptm->tm_mday;
  Serial.println(year);
  Serial.println(month);
  Serial.println(day);

  u8g2.firstPage();
  do{
   u8g2.setFont(u8g2_font_open_iconic_www_1x_t);
   u8g2.drawGlyph(66, 12, 0x0051);
   u8g2.setFont(u8g2_font_open_iconic_all_2x_t);
   u8g2.drawGlypy(112, 34, 0x007B);
   u8g2.setFont(u8g2_font_ncenB12_tr);
   u8g2.drawStr(92, 12, days[weekDay]);
   u8g2.setFont(u8g2_font_ncenB18_tr);
   u8g2.drawStr(8, 38, String(currentHours).c_str());
   u8g2.drawStr(36, 38, ":");
   u8g2.drawStr(44, 38, String(currentMinutes).c_str());
   u8g2.setFont(u8g2_font_ncenB10_tr);
   u8g2.drawStr(8, 12, ssid);
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
