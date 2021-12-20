#include <DFRobot_SIMcore.h>

DFRobot_SIMcore::DFRobot_SIMcore(Stream *s)
{
  _s = s;
}
bool DFRobot_SIMcore::begin(void)
{
  int count = 0;
  delay(1000);
  while(count < 3){
    if(checkSendCmd("AT\r\n","OK")){
      break;
    }else{
      count++;
      delay(300);
    }
  }
  if(count == 3){
    closeCommand();
    return false;
  }
  count = 0;
  while(count < 3){
    if(checkSendCmd("AT+CPIN?\r\n","READY")){
      break;
    }else{
      count++;
      delay(300);
    }
  }
  if(count == 3){
    closeCommand();
    return false;
  }
  setCommandCounter(1);
  return true;
}

bool DFRobot_SIMcore::turnOFF(void)
{
  if(checkSendCmd("AT+CPOWD=1\r\n","NORMAL POWER DOWN")){
    closeCommand();
    return true;
  }else{
    return false;
  }
}

void DFRobot_SIMcore::setPhoneNumber(char *n)
{
  _phoneNumber = n;
}

char* DFRobot_SIMcore::getPhoneNumber(void)
{
  return _phoneNumber;
}

void DFRobot_SIMcore::setPort(int p)
{
  _port = p;
}

int16_t DFRobot_SIMcore::getPort(void)
{
  return _port;
}

void DFRobot_SIMcore::setCommandCounter(uint8_t c)
{
  _commandCounter = c;
}

uint8_t DFRobot_SIMcore::getCommandCounter(void)
{
  return _commandCounter;
}

void DFRobot_SIMcore::setCommandError(uint8_t n)
{
  _commandError = n;
}

uint8_t DFRobot_SIMcore::getCommandError(void)
{
  return _commandError;
}

void DFRobot_SIMcore::setOngoingCommand(eSIMCommand_t c)
{
  _ongoingCommand = c;
}

DFRobot_SIMcore::eSIMCommand_t DFRobot_SIMcore::getOngoingCommand(void)
{
  return _ongoingCommand;
}

void DFRobot_SIMcore::openCommand(eSIMCommand_t c)
{
  setCommandError(0);
  setCommandCounter(1);
  setOngoingCommand(c);
}

void DFRobot_SIMcore::closeCommand()
{
  setCommandError(0);
  setCommandCounter(0);
  setOngoingCommand(eNONE);
}

bool DFRobot_SIMcore::checkSendCmd(const char* cmd, const char* resp, uint32_t timeout)
{
  char SIMbuffer[100];
  cleanBuffer(&SIMbuffer[0],100);
  sendCmd(cmd);
  readBuffer(&SIMbuffer[0],100, timeout);
  DBG(SIMbuffer);
  if(NULL != strstr(SIMbuffer,resp)){
    return  true;
  }else{
    return  false;
  }
}

int DFRobot_SIMcore::checkReadable(void)
{
  return _s->available();
}

void DFRobot_SIMcore::sendCmd(const char* cmd)
{
  _s->write(cmd);
}

void DFRobot_SIMcore::sendBuff(const char* buff,size_t num)
{
  _s->write(buff,num);
}

void DFRobot_SIMcore::sendString(const char* buff)
{
  DBG(buff);
  _s->print(buff);
}


void DFRobot_SIMcore::cleanBuffer(char *buffer,int count)
{
  int i;
  for(i=0; i < count; i++){
    buffer[i] = '\0';
    
  }
}
  

uint16_t  DFRobot_SIMcore::readBuffer(char *buffer, uint16_t count, uint32_t timeout)
{
  uint16_t i = 0;
  uint64_t timecnt = millis();
  while(1){
    if(_s->available()){
      buffer[i++] =(char)_s->read();
      timecnt = millis();
    }
    if(i == count)
      return i;
    if((millis()-timecnt) > (timeout)){
      DBG(buffer);
      DBG(i);
      break;
    }
  }
  return i;
}

void DFRobot_SIMcore::get_String(void)
{
    uint64_t t1 = millis();
    while(1){
        if(checkReadable()){
            Serial.print(char(_s->read()));
            t1 = millis();
        }
        if((millis() - t1) > 10000){
            return;
        }
    }
}