#ifndef __DFRobot_SIMCORE_H__
#define __DFRobot_SIMCORE_H__

#include <Arduino.h>
#include <stdint.h>
#include <Wire.h>
#include <stdio.h>
#include "SoftwareSerial.h"
#include <HardwareSerial.h>

#define DEFAULT_TIMEOUT                 5    //seconds
#define DEFAULT_INTERCHAR_TIMEOUT    1500    //miliseconds

enum DFSIM_commandType_e { XON, NONE, MODEMCONFIG, ALIVETEST, BEGINSMS, ENDSMS, AVAILABLESMS, FLUSHSMS,
VOICECALL, ANSWERCALL, HANGCALL, RETRIEVECALLINGNUMBER, ATTACHGPRS, DETACHGPRS, CONNECTTCPCLIENT,
DISCONNECTTCP, BEGINWRITESOCKET, ENDWRITESOCKET, AVAILABLESOCKET, FLUSHSOCKET, CONNECTSERVER, GETIP,
GETCONNECTSTATUS, GETLOCATION, GETICCID};

class DFRobot_SIMcore
{
public:
    void                   begin(Stream &s_);
    bool                   init(void);
    void                   setPhoneNumber(char *n);
    char*                  getPhoneNumber();
    void                   setPort(int p);
    int                    getPort();
    void                   setCommandCounter(uint8_t c);
    uint8_t                getCommandCounter();
    void                   setCommandError(uint8_t n);
    uint8_t                getCommandError();
    void                   setOngoingCommand(DFSIM_commandType_e c);
    DFSIM_commandType_e    getOngoingCommand();
    void                   openCommand(DFSIM_commandType_e c);
    void                   closeCommand(void);
    bool                   check_send_cmd(const char* cmd, const char* resp);
    void                   send_cmd(const char* cmd);
    int                    checkReadable(void);
    void                   sendCmd(const char* cmd);
    void                   send_buff(const char* buff,size_t num);
    void                   send_String(String buff);
    String                 get_String(String buff);
    void                   cleanBuffer(char *buffer,int count);
    void                   flushSerial(void);
    void                   setRate(long rate);
    int                    readBuffer(char *buffer, int count, unsigned int timeout = DEFAULT_TIMEOUT, unsigned int chartimeout = DEFAULT_INTERCHAR_TIMEOUT);
    bool                   turnOFF(void);
    char*                  getTime(void);
    long                   baudrate = 19200;
private:
    char*                  phoneNumber;
    uint8_t                commandCounter;
    int                    port;
    uint8_t                commandError;
    DFSIM_commandType_e    ongoingCommand;
};

extern   DFRobot_SIMcore   SIMcore;

#endif