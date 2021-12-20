# DFROBOT_SIM Arduino库

* [English Versions](./README.md)
  
这是一个AT通信模块的基类库，DFRobot的很多通信设备都依赖于它。

## 产品链接（链接到中文商城）
    SKU: 

## 目录
  - [概述](#概述)
  - [库安装](#库安装)
  - [方法](#方法)
  - [历史](#历史)
  - [创作者](#创作者)

## 概述

这个库将一些通信的AT指令封装成函数接口，方便使用的基类库。

## 库安装

使用此库前，请首先下载库文件，将其粘贴到\Arduino\libraries目录中，然后打开examples文件夹并在该文件夹中运行演示。

## 方法
```C++
class DFRobot_SIMcore{
 /**
   * @fn DFRobot_SIMcore
   * @brief DFRobot_SIMcore 抽象类的构造函数。构建串行端口。
   * @param s 抽象类的类指针对象，这里可以填入串口对象的指针。
   */
  DFRobot_SIMcore(Stream *s);
  ~DFRobot_SIMcore(){};

  /**
   * @fn begin
   * @brief Init specified module
   * @return bool类型，表示初始化状态
   * @retval true Success 
   * @retval false Failed
   */
  bool begin(void);

  /**
   * @fn checkSendCmd
   * @brief 发送数据，比较返回的数据是否准确
   * @param cmd 需要发送的命令
   * @param resp 比较返回的数据
   * @param timeout 超时时间（单位：毫秒）
   * @return bool类型，表示返回比较数据状态
   * @retval true 相同 
   * @retval false 不同
   */
  bool checkSendCmd(const char* cmd = NULL, const char* resp = NULL, uint32_t timeout = 1000);

  /**
   * @fn checkReadable
   * @brief 判断串口中有多少数据
   * @return 返回串口中数据个数
   */
  int checkReadable(void);

  /**
   * @fn sendCmd
   * @brief 发送命令
   * @param cmd 发送的命令
   */
  void sendCmd(const char* cmd);

  /**
   * @fn sendBuff
   * @brief 发送数据
   * @param buff 需要发送的数据
   * @param num 发送数据的长度
   */
  void sendBuff(const char* buff, size_t num);

  /**
   * @fn sendString
   * @brief 通过串口发送字符串
   * @param buff 需要发送字符串的buffer
   */
  void sendString(const char* buff);

  /**
   * @fn cleanBuffer
   * @brief 清空buffer中的数据
   * @param buffer 需要清空的buffer
   * @param count 需要清空数据长度
   */
  void cleanBuffer(char *buffer, int count);

  /**
   * @fn readBuffer
   * @brief 解析串口返回数据
   * @param buffer 接受数据的buffer
   * @param count  接收数据长度
   * @param timeout 超时时间（单位：毫秒）
   * @return 接收数据长度
   */
  uint16_t readBuffer(char *buffer = NULL, uint16_t count = 1, uint32_t timeout =1000);
 
  /**
   * @fn turnOFF
   * @brief 关闭SIM7000X模块
   * @return bool类型，表示关闭状态
   * @retval true Success 
   * @retval false Failed
   */
  bool turnOFF(void);

  /**
   * @fn setCommandCounter
   * @brief 设置命令计数器
   * @param c 命令值
   */
  void setCommandCounter(uint8_t c);

  /**
   * @fn getCommandCounter
   * @brief 获取命令计数器
   * @return 命令计数值 
   */
  uint8_t	getCommandCounter();

  /**
   * @fn get_String
   * @brief 打印串口返回的字符串
   */
  void get_String(void);

  /**
   * @fn closeCommand
   * @brief 关闭控制命令
   */
  void closeCommand(void);
};
class DFRobot_SIMclient:DFRobot_SIMcore{
 /**
   * @fn checkSignalQuality
   * @brief 获取信号强度 
   * @return 返回信号强度
   */
  int checkSignalQuality(void);

  /**
   * @fn initNet
   * @brief 检测网络是否正常
   * @return bool类型，表示获取状态
   * @retval true Success 
   * @retval false Failed
   */
  bool initNet(void);

  /**
   * @fn connect
   * @brief 连接服务器
   * @param server 连接服务器地址
   * @param ptl 通信协议选择
   * @param port 端口号
   * @return bool类型，表示连接服务器状态
   * @retval true Success 
   * @retval false Failed
   */
  bool connect(char *server,eProtocol ptl,int port);

  /**
   * @fn send
   * @brief 发送数据到连接的服务器
   * @param data 发送的数据
   * @return bool类型，表示发送数据状态
   * @retval true Success 
   * @retval false Failed
   */
  bool send(char *data);

  /**
   * @fn send
   * @brief 发送数据到连接的服务器
   * @param buffer 发送的数据
   * @param len 发送数据长度
   * @return bool类型，表示发送数据状态
   * @retval true Success 
   * @retval false Failed
   */
  bool send(char *buffer,size_t len);

  /**
   * @fn close
   * @brief 断开连接的服务器
   * @return bool类型，表示断开服务器状态
   * @retval true Success 
   * @retval false Failed
   */
  bool close(void);
};
class DFRobot_SIMphonecall:DFRobot_SIMcore{
 /**
   * @fn voiceCall
   * @brief 呼叫指定电话号码
   * @param number 需要呼叫的电话号码
   * @return bool类型，表示呼叫状态状态
   * @retval true Success 
   * @retval false Failed
   */
  bool voiceCall(const char* number);

  /**
   * @fn hangCall
   * @brief 挂断电话
   */
  void hangCall(void);
};
class DFRobot_SIMsms:DFRobot_SIMcore{
 /**
  * @fn beginSMS
  * @brief 初始化发送短信
  * @param to 要发送短信的地址
  * @return bool类型，表示初始化SMS状态
   * @retval true Success 
   * @retval false Failed
  */
  bool beginSMS(const char* to);

 /**
  * @fn editSMS
  * @brief 发送短信
  * @param c 发送短信内容
  */
  void editSMS(const char* c);

 /**
  * @fn sendSMS
  * @brief 发送短信
  * @return bool类型，表示发送短信状态
   * @retval true Success 
   * @retval false Failed
  */
  bool sendSMS(void);
};
```

## 历史

- 2017/8/30 - 1.0.0 版本
- 2021/09/16 - 1.0.1 版本

## 创作者

- Written by TangJie(jie.tang@dfrobot.com), 2021. (Welcome to our [website](https://www.dfrobot.com/))
