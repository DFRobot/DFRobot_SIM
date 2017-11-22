#include "DFRobot_SIMphonecall.h"

int    DFRobot_SIMphonecall::voiceCall(const char* number)
{
    SIMcore.send_cmd("ATD");
    SIMcore.send_cmd(number);
    if(SIMcore.check_send_cmd(";\r\n","OK")){
        return true;
    }else{
        return false;
    }
}

int    DFRobot_SIMphonecall::hangCall(void)
{
    SIMcore.send_cmd("ATH\r\n");
}
