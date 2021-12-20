/*!
 * @file DFRobot_SIMcore.h
 * @brief Basic structure of DFRobot_SIMcore class
 * @details A basic class library for SIM product series communication.
 * @copyright	Copyright (c) 2021 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license     The MIT License (MIT)
 * @author [TangJie](jie.tang@dfrobot.com)
 * @version  V1.0.1
 * @date  2021-09-16
 * @url https://github.com/DFRobot/DFRobot_SIM
 */
#ifndef __DFRobot_SIMCORE_H__
#define __DFRobot_SIMCORE_H__

#include <Arduino.h>
#include <stdint.h>
#include <Wire.h>
#include <stdio.h>
#include "SoftwareSerial.h"

#if 0
#define DBG(...) {Serial.print("["); Serial.print(__FUNCTION__); Serial.print("(): "); Serial.print(__LINE__); Serial.print(" ] "); Serial.println(__VA_ARGS__);}
#else
#define DBG(...)
#endif

#define DEFAULT_TIMEOUT                 5    //seconds
#define DEFAULT_INTERCHAR_TIMEOUT    1500    //miliseconds

class DFRobot_SIMcore{
public:
  /**
   * @enum eSIMCommand_t
   * @brief SIM mode select command
   */
  typedef enum { 
    eXON,                             
    eNONE,                             
    eMODEMCONFIG,                     
    eALIVETEST,                       
    eBEGINSMS,                      
    eENDSMS,                          
    eAVAILABLESMS,                   
    eFLUSHSMS,                       
    eVOICECALL,                     
    eANSWERCALL,                  
    eHANGCALL,                    
    eRETRIEVECALLINGNUMBER,      
    eATTACHGPRS,                
    eDETACHGPRS,               
    eCONNECTTCPCLIENT,        
    eDISCONNECTTCP,           
    eBEGINWRITESOCKET,      
    eENDWRITESOCKET,       
    eAVAILABLESOCKET,    
    eFLUSHSOCKET,         
    eCONNECTSERVER,     
    eGETIP,            
    eGETCONNECTSTATUS, 
    eGETLOCATION,        
    eGETICCID         
  }eSIMCommand_t;

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
   * @brief Send data and judge the accuracy the returned data
   * @param cmd Command to be sent
   * @param resp The returned data to be judged
   * @param timeout Timeout value (unit: ms)
   * @return bool type, indicating the status of judging the returned data
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
   * @param buffer Buffer for data to be received
   * @param count  Length of data to be received
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
private:
  void	setPhoneNumber(char *n);
  char*	getPhoneNumber();
  void	setPort(int p);
  int16_t	getPort(void);
  void	setCommandError(uint8_t n);
  uint8_t	getCommandError(void);
  void	setOngoingCommand(eSIMCommand_t c);
  eSIMCommand_t	getOngoingCommand(void);
  void	openCommand(eSIMCommand_t c);
  
  char*   _phoneNumber;
  uint8_t _commandCounter;
  int16_t _port;
  uint8_t _commandError;
  eSIMCommand_t  _ongoingCommand;
  Stream *_s;
	long  _baudrate = 19200;
};
#endif
