#include "DFRobot_SIMsms.h"

bool DFRobot_SIMsms::beginSMS(const char* to)
{
  if(checkSendCmd("AT+CMGF=1\r\n","OK")){
    delay(100);
  }else{
    closeCommand();
    return false;
  }
  sendCmd("AT+CMGS=\"");
  sendCmd(to);
  if(checkSendCmd("\"\r\n",">")){
    delay(100);
    setCommandCounter(2);
    return true;
  }else{
    closeCommand();
    return false;
  }
}

void DFRobot_SIMsms::editSMS(const char* c)
{
  if(getCommandCounter() == 2){
    sendCmd(c);
    setCommandCounter(3);
  }else{
    closeCommand();
  }
}

bool DFRobot_SIMsms::sendSMS(void)
{
  if(getCommandCounter() == 3){
    if(checkSendCmd("","+CMGS")){
      closeCommand();
      return true;
    }else{
      closeCommand();
      return false;
    }
  }else{
  	closeCommand();
  	return false;
  }
}
