#include "DFRobot_SIMclient.h"

int DFRobot_SIMclient::checkSignalQuality(void)
{
  char  signalBuffer[26];
  int i = 0,j = 0,k = 0;
  char *signalQuality;
  cleanBuffer(signalBuffer, 26);
  sendCmd("AT+CSQ\r\n");
  readBuffer(signalBuffer, 26);
  if (NULL != (signalQuality = strstr(signalBuffer, "+CSQ:"))){
    i = *(signalQuality + 6) - 48;
    j = *(signalQuality + 7) - 48;
    k = (i * 10) + j;
  }else{
    closeCommand();
    return 0;
  }
  if( k == 99){
    closeCommand();
    return 0;
  }else{
    setCommandCounter(1);
    return k;
  }
}

bool DFRobot_SIMclient::initNet(void)
{
  int  count = 0;
  while(count < 3){
    if(checkSendCmd("AT+CGATT?\r\n","1")){
      break;
    }else{
      count++;
      delay(500);
    }
  }
  if(count == 3){
    closeCommand();
    return false;
  }
  if(checkSendCmd("AT+CSTT\r\n","OK")){
    if(checkSendCmd("AT+CIICR\r\n","OK")){
      setCommandCounter(2);
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

bool DFRobot_SIMclient::connect(char *server, eProtocol ptl, int port)
{
  if(getCommandCounter() == 2){
    char num[4];
    char serverIP[100];
    cleanBuffer(serverIP,100);
    itoa(port, num, 10);
    sendCmd("AT+CIPSTART=\"");
    if(ptl == eTCP){
      sendCmd("TCP\",\"");
    }else if(ptl == eUDP){
      sendCmd("UDP\",\"");
    }else{
      return false;
    }
    sendCmd(server);
    sendCmd("\",");
    sendCmd(num);
    sendCmd("\r\n");
    while(1){
      while(checkReadable()){
        readBuffer(serverIP,100);
        if(NULL != strstr(serverIP,"ALREADY CONNECT")){
          setCommandCounter(3);
          return true;
        }
        if(NULL != strstr(serverIP,"CONNECT OK")){
          setCommandCounter(3);
            return true;
        }
        if(NULL != strstr(serverIP,"CONNECT FAIL")){
          return false;
        }
      }
    }
  }else{
    return false;
  }
}

bool DFRobot_SIMclient::send(char *data){
  if(getCommandCounter() == 3){
    char num[4];
    char resp[20];
    int len = strlen(data);
    itoa(len, num, 10);
    sendCmd("AT+CIPSEND=");
    sendCmd(num);
    if(checkSendCmd("\r\n",">")){
      sendCmd(data);
      while(1){
        while(checkReadable()){
          readBuffer(resp,20);
          if(NULL != strstr(resp,"OK")){
            return true;
          }
          if(NULL != strstr(resp,"ERROR")){
            return false;
          }
        }
      }
    }else{
      closeCommand();
      return false;
    }
  }else{
    return false;
  }
}

bool DFRobot_SIMclient::send(char *buffer,size_t len)
{
  if(getCommandCounter() == 3){
    char num[4];
    itoa(len, num, 10);
    sendCmd("AT+CIPSEND=");
    sendCmd(num);
    if(checkSendCmd("\r\n",">")){
      if(checkSendCmd(buffer,"OK")){
        return true;
      }else{
        setCommandCounter(3);
        return false;
      }
    }else{
      setCommandCounter(3);
      return false;
    }
  }else{
    return false;
  }
}

bool DFRobot_SIMclient::close(void)
{
  if(getCommandCounter() == 3){
    if(checkSendCmd("AT+CIPSHUT\r\n","OK")){
      setCommandCounter(2);
      return true;
    }else{
      setCommandCounter(2);
      return false;
    }
  }else{
    return false;
  }
}