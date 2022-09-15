# MentallyRetardedCar
esp8266+L298N+TT马达搭建的智能小车.控制APP使用MIT APP开发.实现向前,向后,差速转向等功能.

###### 文件说明

.
├── Arduino
├── LICENSE
├── MentallyRetardedCar-V5.0.ino 小车主程序
├── MentallyRetardedCar.jpg 接线图
├── MentallyRetardedCar2.jpg 接线图
├── NodeMCUManager2.0.aia apk 源文件
└── README.md


###### 获取APP

- 登录[MIT App Inventor (gzjkw.net)](http://app.gzjkw.net/login/)
- 项目->导入项目(NodeMCUManager2.0.aia)
- 按需修改
- 打包apk,下载安装


###### 注意

- 修改程序主文件中的wifi名称和密码
- ESP8266地址从串口日志获取,或其他途径(路由器后台之类的)
- apk和主文件不做任何更改的情况下,运行app之后顶部输入框输入ESP8266的ip地址,点击确定即可
