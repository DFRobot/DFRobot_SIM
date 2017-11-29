#include "DFRobot_SIMsms.h"

bool   DFRobot_SIMsms::beginSMS(const char* to)
{
    if(SIMcore.check_send_cmd("AT+CMGF=1\r\n","OK")){
        delay(100);
    }else{
        SIMcore.closeCommand();
        return false;
    }
    SIMcore.send_cmd("AT+CMGS=\"");
    SIMcore.send_cmd(to);
    if(SIMcore.check_send_cmd("\"\r\n",">")){
        delay(100);
        SIMcore.setCommandCounter(2);
        return true;
    }else{
        SIMcore.closeCommand();
        return false;
    }
}

void   DFRobot_SIMsms::editSMS(const char* c)
{
    if(SIMcore.getCommandCounter() == 2){
        SIMcore.send_cmd(c);
        SIMcore.setCommandCounter(3);
    }else{
        SIMcore.closeCommand();
    }
}

bool   DFRobot_SIMsms::sendSMS(void)
{
    if(SIMcore.getCommandCounter() == 3){
        if(SIMcore.check_send_cmd("","+CMGS")){
            SIMcore.closeCommand();
            return true;
        }else{
            SIMcore.closeCommand();
            return false;
        }
    }else{
        SIMcore.closeCommand();
        return false;
    }
}
