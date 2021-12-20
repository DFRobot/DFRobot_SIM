/*!
 * @file DFRobot_SIMsms.h
 * @brief Basic structure of DFRobot_SIMsms class
 * @details This is basic class library for SIM series products communication.
 * @copyright	Copyright (c) 2021 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license     The MIT License (MIT)
 * @author [TangJie](jie.tang@dfrobot.com)
 * @version  V1.0.1
 * @date  2021-09-16
 * @url https://github.com/DFRobot/DFRobot_SIM
 */
#ifndef __DFRobot_SIMSMS_H__
#define __DFRobot_SIMSMS_H__

#include "DFRobot_SIMcore.h"

class DFRobot_SIMsms:DFRobot_SIMcore{
public:
 /**
  * @fn beginSMS
  * @brief Initialize SMS
  * @param Address of SMS to be sent
  * @return bool type, indicating status of initializing SMS
   * @retval true Success 
   * @retval false Failed
  */
  bool beginSMS(const char* to);

 /**
  * @fn editSMS
  * @brief Send the SMS
  * @param c SMS content
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

#endif
