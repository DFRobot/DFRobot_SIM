/*!
 * @file DFRobot_SIMclient.h
 * @brief The basic structure of DFRobot_SIMclient class
 * @details A basic class library for SIM product series communication.
 * @copyright	Copyright (c) 2021 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license     The MIT License (MIT)
 * @author [TangJie](jie.tang@dfrobot.com)
 * @version  V1.0.1
 * @date  2021-09-16
 * @url https://github.com/DFRobot/DFRobot_SIM
 */
#ifndef __DFRobot_SIMCLIENT_H__
#define __DFRobot_SIMCLIENT_H__

#include "DFRobot_SIMcore.h"

class DFRobot_SIMclient:DFRobot_SIMcore{
public:
  /**
   * @enum eProtocol
   * @brief Communication protocol select
   */
  typedef enum {
    eTCP    = 1,  /**<TCP protocol is used for communication */
    eUDP    = 2,  /**<UDP protocol is used for communication */
  }eProtocol;

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
   * @param Server connect to the server address
   * @param ptl Communication protocol select
   * @param port port number
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
   * @param len Length of data to be sent 
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
#endif
