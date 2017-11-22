#include <DFRobot_SIMcore.h>

static SoftwareSerial* DFSIMSerial;
DFRobot_SIMcore   SIMcore;

void DFRobot_SIMcore::begin(Stream &s_)
{
    DFSIMSerial = &s_;
}

bool DFRobot_SIMcore::init(void)
{
    char SIMBuffer[32];
    int  count = 0;
    cleanBuffer(SIMBuffer,32);
    delay(1000);
    while(count < 3){
        if(check_send_cmd("AT+IPR=38400\r\n","OK")){
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
    baudrate = 38400;
    while(count < 3){
        if(check_send_cmd("AT\r\n","OK")){
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
    cleanBuffer(SIMBuffer,32);
    while(count < 3){
        if(check_send_cmd("AT+CPIN?\r\n","READY")){
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

bool  DFRobot_SIMcore::turnOFF(void)
{
    if(check_send_cmd("AT+CPOWD=1\r\n","NORMAL POWER DOWN")){
        closeCommand();
        return true;
    }else{
        return false;
    }
}

char* DFRobot_SIMcore::getTime()
{
    char  recBuffer[50],timeBuffer[20];
    char *pTime;
    cleanBuffer(recBuffer,50);
    cleanBuffer(timeBuffer,20);
    send_cmd("AT+CCLK?\r\n");
    readBuffer(recBuffer,50);
    if(NULL != strstr(recBuffer,"+CCLK")){
        pTime = strstr(recBuffer,":");
        memcpy(timeBuffer,pTime+3,17);
        return timeBuffer;
    }else{
        return "error";
    }
}

void  DFRobot_SIMcore::setPhoneNumber(char *n)
{
    phoneNumber = n;
}

char* DFRobot_SIMcore::getPhoneNumber(void)
{
    return  phoneNumber;
}

void  DFRobot_SIMcore::setPort(int p)
{
    port = p;
}

int   DFRobot_SIMcore::getPort(void)
{
    return  port;
}

void  DFRobot_SIMcore::setCommandCounter(uint8_t c)
{
    commandCounter = c;
}

uint8_t DFRobot_SIMcore::getCommandCounter(void)
{
    return commandCounter;
}

void DFRobot_SIMcore::setCommandError(uint8_t n)
{
    commandError = n;
}

uint8_t DFRobot_SIMcore::getCommandError(void)
{
    return commandError;
}

void DFRobot_SIMcore::setOngoingCommand(DFSIM_commandType_e c)
{
    ongoingCommand = c;
}

DFSIM_commandType_e DFRobot_SIMcore::getOngoingCommand(void)
{
    return ongoingCommand;
}

void DFRobot_SIMcore::openCommand(DFSIM_commandType_e c)
{
    setCommandError(0);
    setCommandCounter(1);
    setOngoingCommand(c);
}

void DFRobot_SIMcore::closeCommand()
{
    setCommandError(0);
    setCommandCounter(0);
    setOngoingCommand(NONE);
}

bool DFRobot_SIMcore::check_send_cmd(const char* cmd, const char* resp)
{
    char SIMbuffer[100];
    cleanBuffer(SIMbuffer,100);
    sendCmd(cmd);
    readBuffer(SIMbuffer,100);
    if(NULL != strstr(SIMbuffer,resp)){
        return  true;
    }else{
        return  false;
    }
}

void DFRobot_SIMcore::send_cmd(const char* cmd)
{
    sendCmd(cmd);
}

int     DFRobot_SIMcore::checkReadable(void)
{
    return DFSIMSerial->available();
}

void DFRobot_SIMcore::sendCmd(const char* cmd)
{
    DFSIMSerial->begin(baudrate);
    DFSIMSerial->write(cmd);
}

void DFRobot_SIMcore::cleanBuffer(char *buffer,int count)
{
    for(int i=0; i < count; i++){
        buffer[i] = '\0';
    }
}

int     DFRobot_SIMcore::readBuffer(char *buffer, int count, unsigned int timeout, unsigned int chartimeout)
{
    int i = 0;
    unsigned long timerStart, prevChar;
    timerStart = millis();
    prevChar = 0;
    while(1){
        while(checkReadable()){
            buffer[i++] = DFSIMSerial->read();
            prevChar = millis();
            if(i >= count)
                return i;
        }
        if(timeout){
            if((unsigned long) (millis() - timerStart) > timeout*1000){
                break;
            }
        }
        if(((unsigned long) (millis() - prevChar) > chartimeout*10) && (prevChar != 0)){
            break;
        }
    }
    return i;
}