#include "DFRobot_SIMphonecall.h"

bool	DFRobot_SIMphonecall::voiceCall(const char* number)
{
  sendCmd("ATD");
  sendCmd(number);
  if(checkSendCmd(";\r\n","OK")){
    return true;
  }else{
    return false;
  }
}

void	DFRobot_SIMphonecall::hangCall(void)
{
  sendCmd("ATH\r\n");
}
