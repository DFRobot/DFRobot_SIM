# DFROBOT_SIM Library for Arduino

* [中文版](./README_CN.md)
  
This is a base class library for AT communication module, which supports many communication modules from DFRobot.

## Product Link (Link to DFRobot store)
    SKU: 

## Table of Contents

  - [Summary](#summary)
  - [Installation](#installation)
  - [Methods](#methods)
  - [History](#history)
  - [Credits](#credits)

## Summary

In this library some communication AT instructions are encapsulated into a functional interface, a base class library convenient to use.

## Installation

To use this library, first download the library file, paste it into the \Arduino\libraries directory, then open the examples folder and run the demo in the folder.

## Methods
```C++
class DFRobot_SIMcore{
 /**
   * @fn DFRobot_SIMcore
   * @brief DFRobot_SIMcore constructor of abstract class. Construct serial ports.
   * @param s The pointer to abstract class, where you can fill in the pointer to serial object.
   */
  DFRobot_SIMcore(Stream *s);
  ~DFRobot_SIMcore(){};

  /**
   * @fn begin
   * @brief Init specified module
   * @return bool type, indicating initialization status
   * @retval true Success 
   * @retval false Failed
   */
  bool begin(void);

  /**
   * @fn checkSendCmd
   * @brief Send data and check accuracy of the returned data.
   * @param cmd Command to be sent
   * @param resp Check the returned data
   * @param timeout Timeout value (unit: ms)
   * @return bool type, indicating the status of checking returned data
   * @retval true same 
   * @retval false different
   */
  bool checkSendCmd(const char* cmd = NULL, const char* resp = NULL, uint32_t timeout = 1000);

  /**
   * @fn checkReadable
   * @brief Check the number of data in serial port
   * @return Return the number of data in serial port
   */
  int checkReadable(void);

  /**
   * @fn sendCmd
   * @brief Send command
   * @param cmd The sent command
   */
  void sendCmd(const char* cmd);

  /**
   * @fn sendBuff
   * @brief Send data
   * @param buff Data to be sent
   * @param num Length of data to be sent
   */
  void sendBuff(const char* buff, size_t num);

  /**
   * @fn sendString
   * @brief Send string through serial port
   * @param buff Buffer for string to be sent
   */
  void sendString(const char* buff);

  /**
   * @fn cleanBuffer
   * @brief Clear data in buffer
   * @param buffer Buffer to be cleared
   * @param count Length of data to be cleared
   */
  void cleanBuffer(char *buffer, int count);

  /**
   * @fn readBuffer
   * @brief Parse the data returned by the serial port
   * @param buffer Receive data buffer
   * @param count  Receive data length
   * @param timeout Timeout value (unit: ms)
   * @return Receive data length
   */
  uint16_t readBuffer(char *buffer = NULL, uint16_t count = 1, uint32_t timeout =1000);
 
  /**
   * @fn turnOFF
   * @brief Turn off SIM7000X module
   * @return bool type, indicating closing status
   * @retval true Success 
   * @retval false Failed
   */
  bool turnOFF(void);

  /**
   * @fn setCommandCounter
   * @brief Set command counter
   * @param c Command value
   */
  void setCommandCounter(uint8_t c);

  /**
   * @fn getCommandCounter
   * @brief Get command counter
   * @return Command count value 
   */
  uint8_t	getCommandCounter();

  /**
   * @fn get_String
   * @brief Print the string returned by the serial port
   */
  void get_String(void);

  /**
   * @fn closeCommand
   * @brief Close control command
   */
  void closeCommand(void);
};
class DFRobot_SIMclient:DFRobot_SIMcore{
 /**
   * @fn checkSignalQuality
   * @brief Get signal quality 
   * @return Return signal quality
   */
  int checkSignalQuality(void);

  /**
   * @fn initNet
   * @brief Check the network connection status
   * @return bool type, indicating status of obtaining signal
   * @retval true Success 
   * @retval false Failed
   */
  bool initNet(void);

  /**
   * @fn connect
   * @brief Connect to the server
   * @param server Connect to the server address
   * @param ptl Communication protocol select
   * @param port Port number
   * @return bool type, indicating server connection status
   * @retval true Success 
   * @retval false Failed
   */
  bool connect(char *server,eProtocol ptl,int port);

  /**
   * @fn send
   * @brief Send data to the connected server
   * @param data Data to be sent
   * @return bool type, indicating status of sending data
   * @retval true Success 
   * @retval false Failed
   */
  bool send(char *data);

  /**
   * @fn send
   * @brief Send data to the connected server
   * @param buffer Data to be sent
   * @param len Send length of data
   * @return bool type, indicating status of sending data
   * @retval true Success 
   * @retval false Failed
   */
  bool send(char *buffer,size_t len);

  /**
   * @fn close
   * @brief Disconnect the connected server
   * @return bool type, indicating status of disconnecting server
   * @retval true Success 
   * @retval false Failed
   */
  bool close(void);
};
class DFRobot_SIMphonecall:DFRobot_SIMcore{
 /**
   * @fn voiceCall
   * @brief Call the specified phone number
   * @param number The phone number to be called
   * @return bool type, indicating status of the call
   * @retval true Success 
   * @retval false Failed
   */
  bool voiceCall(const char* number);

  /**
   * @fn hangCall
   * @brief Hang up the call
   */
  void hangCall(void);
};
class DFRobot_SIMsms:DFRobot_SIMcore{
 /**
  * @fn beginSMS
  * @brief Initialize SMS
  * @param to Address of SMS to be sent
  * @return bool type, indicating status of initializing SMS
   * @retval true Success 
   * @retval false Failed
  */
  bool beginSMS(const char* to);

 /**
  * @fn editSMS
  * @brief Send the SMS
  * @param c Send the SMS content
  */
  void editSMS(const char* c);

 /**
  * @fn sendSMS
  * @brief Send the SMS
  * @return bool type, indicating status of sending SMS
   * @retval true Success 
   * @retval false Failed
  */
  bool sendSMS(void);
};
};
```

## History

- 2017/8/30 - 1.0.0 version
- 2021/09/16 - 1.0.1 version

## Credits

- Written by TangJie(jie.tang@dfrobot.com), 2021. (Welcome to our [website](https://www.dfrobot.com/))
