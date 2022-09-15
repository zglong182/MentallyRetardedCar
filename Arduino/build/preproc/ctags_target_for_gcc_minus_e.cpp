# 1 "h:\\my\\NodeMCUIot\\NodeMCUIot\\MentallyRetardedCar-V5.0\\MentallyRetardedCar-V5.0.ino"
// 驱动两个电机

// 引入ESP8266WiFi库
# 5 "h:\\my\\NodeMCUIot\\NodeMCUIot\\MentallyRetardedCar-V5.0\\MentallyRetardedCar-V5.0.ino" 2

# 7 "h:\\my\\NodeMCUIot\\NodeMCUIot\\MentallyRetardedCar-V5.0\\MentallyRetardedCar-V5.0.ino" 2
# 8 "h:\\my\\NodeMCUIot\\NodeMCUIot\\MentallyRetardedCar-V5.0\\MentallyRetardedCar-V5.0.ino" 2

// 建立ESP8266WiFiMulti对象,对象名称是'wifiMulti'
ESP8266WiFiMulti wifiMulti;
// 建立ESP8266WebServer对象，对象名称为server
ESP8266WebServer server(80);

// L298N驱动板 引脚对应NodeMCU引脚
int ENA = 5; // GPIO5(D1)
int IN1 = 14; // GPIO14(D5)
int IN2 = 12; // GPIO12(D6)
int ENB = 0; //  GPIO0(D3)
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

void setup()
{
  // 将所有电机控制引脚设置为输出引脚模式
  pinMode(ENA, 0x01);
  pinMode(IN1, 0x01);
  pinMode(IN2, 0x01);

  pinMode(ENB, 0x01);
  pinMode(IN3, 0x01);
  pinMode(IN4, 0x01);
  // 启动串口通讯
  Serial.begin(115200);

  // 连接网络
  WiFi.begin(ssid, password);
  Serial.print("Connecting to: ");
  Serial.println(ssid);
  while (WiFi.status() != WL_CONNECTED)
  { // WiFi.status()函数的返回值是由NodeMCU的WiFi连接状态所决定的。
    delay(1000); // 如果WiFi连接成功则返回值为WL_CONNECTED
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
# 116 "h:\\my\\NodeMCUIot\\NodeMCUIot\\MentallyRetardedCar-V5.0\\MentallyRetardedCar-V5.0.ino"
void stopCar()
{
  server.send(200, "text/plain", "stop");
  Serial.println("stop");
  // 关闭电机
  digitalWrite(IN1, 0x1);
  digitalWrite(IN1, 0x1);
  digitalWrite(IN2, 0x1);

  digitalWrite(IN1, 0x1);
  digitalWrite(IN3, 0x1);
  digitalWrite(IN4, 0x1);
}

/**

 * @brief 前进

 *

 */
# 134 "h:\\my\\NodeMCUIot\\NodeMCUIot\\MentallyRetardedCar-V5.0\\MentallyRetardedCar-V5.0.ino"
void front()
{
  server.send(200, "text/plain", "front");
  Serial.println("front");
  // 打开电机
  digitalWrite(IN1, 0x1);
  digitalWrite(IN2, 0x0);
  analogWrite(ENA, speeds * coefficient);

  digitalWrite(IN3, 0x1);
  digitalWrite(IN4, 0x0);
  analogWrite(ENB, speeds * coefficient);
}
/**

 * @brief 后退

 *

 */
# 151 "h:\\my\\NodeMCUIot\\NodeMCUIot\\MentallyRetardedCar-V5.0\\MentallyRetardedCar-V5.0.ino"
void after()
{
  server.send(200, "text/plain", "after");

  Serial.println("after");
  // 打开电机
  digitalWrite(IN1, 0x0);
  digitalWrite(IN2, 0x1);
  analogWrite(ENA, speeds * coefficient);

  digitalWrite(IN3, 0x0);
  digitalWrite(IN4, 0x1);
  analogWrite(ENB, speeds * coefficient);
}

/**

 * @brief 向左

 *

 */
# 170 "h:\\my\\NodeMCUIot\\NodeMCUIot\\MentallyRetardedCar-V5.0\\MentallyRetardedCar-V5.0.ino"
void left()
{

  server.send(200, "text/plain", "left");

  // stopCar();
  Serial.println("left");
  digitalWrite(IN1, 0x1);
  digitalWrite(IN2, 0x0);
  digitalWrite(IN3, 0x1);
  digitalWrite(IN4, 0x0);
  analogWrite(ENA, 200);
  analogWrite(ENB, 100);
}

/**

 * @brief 向右

 *

 */
# 189 "h:\\my\\NodeMCUIot\\NodeMCUIot\\MentallyRetardedCar-V5.0\\MentallyRetardedCar-V5.0.ino"
void right()
{
  server.send(200, "text/plain", "right");
  // stopCar();

  Serial.println("right");
  digitalWrite(IN1, 0x1);
  digitalWrite(IN2, 0x0);
  digitalWrite(IN3, 0x1);
  digitalWrite(IN4, 0x0);
  analogWrite(ENA, 100);
  analogWrite(ENB, 200);
}

/**

 * @brief 原地转圈

 *

 */
# 208 "h:\\my\\NodeMCUIot\\NodeMCUIot\\MentallyRetardedCar-V5.0\\MentallyRetardedCar-V5.0.ino"
void turn()
{
  server.send(200, "text/plain", "turn");

  Serial.println("turn");
  digitalWrite(IN1, 0x1);
  digitalWrite(IN2, 0x0);
  digitalWrite(IN3, 0x0);
  digitalWrite(IN4, 0x1);
  analogWrite(ENA, 200);
  analogWrite(ENB, 200);
}
/**

 * @brief 加速

 *

 */
# 224 "h:\\my\\NodeMCUIot\\NodeMCUIot\\MentallyRetardedCar-V5.0\\MentallyRetardedCar-V5.0.ino"
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
# 238 "h:\\my\\NodeMCUIot\\NodeMCUIot\\MentallyRetardedCar-V5.0\\MentallyRetardedCar-V5.0.ino"
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
# 250 "h:\\my\\NodeMCUIot\\NodeMCUIot\\MentallyRetardedCar-V5.0\\MentallyRetardedCar-V5.0.ino"
void root()
{

  server.send(200, "text/plain", "Hello from ESP8266");
}
