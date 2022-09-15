#include <Arduino.h>
#line 1 "h:\\my\\NodeMCUIot\\NodeMCUIot\\MentallyRetardedCar-V5.0\\MentallyRetardedCar-V5.0.ino"
// 驱动两个电机

// 引入ESP8266WiFi库
#include <ESP8266WiFi.h>

#include <ESP8266WiFiMulti.h>
#include <ESP8266WebServer.h>

// 建立ESP8266WiFiMulti对象,对象名称是'wifiMulti'
ESP8266WiFiMulti wifiMulti;
// 建立ESP8266WebServer对象，对象名称为server
ESP8266WebServer server(80);

// L298N驱动板 引脚对应NodeMCU引脚
int ENA = 5;  // GPIO5(D1)
int IN1 = 14; // GPIO14(D5)
int IN2 = 12; // GPIO12(D6)
int ENB = 0;  //  GPIO0(D3)
int IN3 = 13; // GPIO13(D7)
int IN4 = 15; // GPIO15(D8)
// 速度
int speeds = 110;
// 速度系数
int coefficient = 1;
// 参数名称  可以通过 http://192.168.1.100?status=操作  来扩展
String flag;
// 定义wifi名称和密码
const char *ssid = "Mi_IoT";
const char *password = "123123123";

#line 31 "h:\\my\\NodeMCUIot\\NodeMCUIot\\MentallyRetardedCar-V5.0\\MentallyRetardedCar-V5.0.ino"
void setup();
#line 76 "h:\\my\\NodeMCUIot\\NodeMCUIot\\MentallyRetardedCar-V5.0\\MentallyRetardedCar-V5.0.ino"
void loop();
#line 107 "h:\\my\\NodeMCUIot\\NodeMCUIot\\MentallyRetardedCar-V5.0\\MentallyRetardedCar-V5.0.ino"
void startCar();
#line 116 "h:\\my\\NodeMCUIot\\NodeMCUIot\\MentallyRetardedCar-V5.0\\MentallyRetardedCar-V5.0.ino"
void stopCar();
#line 134 "h:\\my\\NodeMCUIot\\NodeMCUIot\\MentallyRetardedCar-V5.0\\MentallyRetardedCar-V5.0.ino"
void front();
#line 151 "h:\\my\\NodeMCUIot\\NodeMCUIot\\MentallyRetardedCar-V5.0\\MentallyRetardedCar-V5.0.ino"
void after();
#line 170 "h:\\my\\NodeMCUIot\\NodeMCUIot\\MentallyRetardedCar-V5.0\\MentallyRetardedCar-V5.0.ino"
void left();
#line 189 "h:\\my\\NodeMCUIot\\NodeMCUIot\\MentallyRetardedCar-V5.0\\MentallyRetardedCar-V5.0.ino"
void right();
#line 208 "h:\\my\\NodeMCUIot\\NodeMCUIot\\MentallyRetardedCar-V5.0\\MentallyRetardedCar-V5.0.ino"
void turn();
#line 224 "h:\\my\\NodeMCUIot\\NodeMCUIot\\MentallyRetardedCar-V5.0\\MentallyRetardedCar-V5.0.ino"
void plus();
#line 238 "h:\\my\\NodeMCUIot\\NodeMCUIot\\MentallyRetardedCar-V5.0\\MentallyRetardedCar-V5.0.ino"
void reduce();
#line 250 "h:\\my\\NodeMCUIot\\NodeMCUIot\\MentallyRetardedCar-V5.0\\MentallyRetardedCar-V5.0.ino"
void root();
#line 31 "h:\\my\\NodeMCUIot\\NodeMCUIot\\MentallyRetardedCar-V5.0\\MentallyRetardedCar-V5.0.ino"
void setup()
{
  // 将所有电机控制引脚设置为输出引脚模式
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  // 启动串口通讯
  Serial.begin(115200);

  // 连接网络
  WiFi.begin(ssid, password);
  Serial.print("Connecting to: ");
  Serial.println(ssid);
  while (WiFi.status() != WL_CONNECTED)
  {                    // WiFi.status()函数的返回值是由NodeMCU的WiFi连接状态所决定的。
    delay(1000);       // 如果WiFi连接成功则返回值为WL_CONNECTED
    Serial.print('.'); // 此处通过While循环让NodeMCU每隔一秒钟检查一次WiFi.status()函数返回值
  }
  Serial.println(); 

  // 打印网络信息
  Serial.print("IP address:");
  Serial.println(WiFi.localIP());

  // 启动server
  server.begin();
  // 添加控制器
  server.on("/", root);
  server.on("/start", startCar);
  server.on("/stop", stopCar);
  server.on("/front", front);
  server.on("/after", after);
  server.on("/left", left);
  server.on("/right", right);
  server.on("/turn", turn);
  server.on("/plus", plus);
  server.on("/reduce", reduce);
  //  ESP8266网络服务功能已经启动
  Serial.println("HTTP esp8266 server started");
}

void loop()
{
  // 处理http服务器访问
  server.handleClient();
  flag = server.arg("status");
  if (flag == "front")
  {
    front();
  }
  else if (flag == "after")
  {
    after();
  }
  else if (flag == "left")
  {
    left();
  }
  else if (flag == "right")
  {
    right();
  }
  else if (flag == "turn")
  {
    turn();
  }
  else if (flag == "stop")
  {
    stopCar();
  }
}

void startCar()
{
  server.send(200, "text/html", "<h1>star</h1>");
}

/**
 * @brief 停止
 *
 */
void stopCar()
{
  server.send(200, "text/plain", "stop");
  Serial.println("stop");
  // 关闭电机
  digitalWrite(IN1, HIGH);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, HIGH);

  digitalWrite(IN1, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, HIGH);
}

/**
 * @brief 前进
 *
 */
void front()
{
  server.send(200, "text/plain", "front");
  Serial.println("front");
  // 打开电机
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, speeds * coefficient);

  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, speeds * coefficient);
}
/**
 * @brief 后退
 *
 */
void after()
{
  server.send(200, "text/plain", "after");

  Serial.println("after");
  // 打开电机
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  analogWrite(ENA, speeds * coefficient);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENB, speeds * coefficient);
}

/**
 * @brief 向左
 *
 */
void left()
{

  server.send(200, "text/plain", "left");

  // stopCar();
  Serial.println("left");
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, 200);
  analogWrite(ENB, 100);
}

/**
 * @brief 向右
 *
 */
void right()
{
  server.send(200, "text/plain", "right");
  // stopCar();

  Serial.println("right");
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, 100);
  analogWrite(ENB, 200);
}

/**
 * @brief 原地转圈
 *
 */

void turn()
{
  server.send(200, "text/plain", "turn");

  Serial.println("turn");
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENA, 200);
  analogWrite(ENB, 200);
}
/**
 * @brief 加速
 *
 */
void plus()
{
  server.send(200, "text/plain", "plus");
  if (coefficient < 3)
  {
    coefficient = coefficient + 1;
  }
  Serial.println(coefficient);
}

/**
 * @brief 减速
 *
 */
void reduce()
{
  server.send(200, "text/plain", "reduce");
  if (coefficient > 1)
  {
    coefficient = coefficient - 1;
  }
  Serial.println(coefficient);
}
/**
   处理网站根目录“/”的访问请求
*/
void root()
{

  server.send(200, "text/plain", "Hello from ESP8266");
}

