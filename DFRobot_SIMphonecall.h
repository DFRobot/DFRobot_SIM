/*!
 * @file DFRobot_SIMphonecall.h
 * @brief Basic structure of DFRobot_SIMphonecall class
 * @details A basic class library for SIM series products communication.
 * @copyright	Copyright (c) 2021 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license     The MIT License (MIT)
 * @author [TangJie](jie.tang@dfrobot.com)
 * @version  V1.0.1
 * @date  2021-09-16
 * @url https://github.com/DFRobot/DFRobot_SIM
 */
#ifndef __DFRobot_SIMPHONECALL_H__
#define __DFRobot_SIMPHONECALL_H__

#include "DFRobot_SIMcore.h"

class DFRobot_SIMphonecall:DFRobot_SIMcore{
public:
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
private:
  void answerCallContinue(void);
  void hangCallContinue(void);
};

#endif
