#include "DFRobot_SIMgetpos.h"

bool   DFRobot_SIMgetpos::init(void)
{
    int  count = 0;
    while(count < 3){
        if(SIMcore.check_send_cmd("AT+CGATT?\r\n","1")){
            break;
        }else{
            count++;
            delay(500);
        }
    }
    if(count == 3){
        SIMcore.closeCommand();
        return false;
    }
    if(SIMcore.check_send_cmd("AT+CSTT=\"CMNET\"\r\n","OK")){
        if(SIMcore.check_send_cmd("AT+GTPOS=1\r\n","CONNECT OK")){
            SIMcore.setCommandCounter(2);
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

bool   DFRobot_SIMgetpos::getPosition(void)
{
    char  posBuffer[50];
    char *pLongitude,*pLatitude;
    SIMcore.cleanBuffer(posBuffer,50);
    if(SIMcore.getCommandCounter() == 2){
        SIMcore.send_cmd("AT+GTPOS=2\r\n");
        SIMcore.readBuffer(posBuffer,50);
        if(NULL != strstr(posBuffer,"+GTPOS")){
            SIMcore.setCommandCounter(3);
        }else{
            SIMcore.closeCommand();
            return false;
        }
    }else{
        SIMcore.closeCommand();
        return false;
    }
    if(SIMcore.getCommandCounter() == 3){
        pLongitude = strstr(posBuffer,":");
        pLatitude  = strstr(posBuffer,",");
        memcpy(longitude,pLongitude+2,7);
        memcpy(latitude, pLatitude+1 ,7);
        SIMcore.setCommandCounter(4);
        return true;
    }
}

char*   DFRobot_SIMgetpos::getLongitude(void)
{
    if(SIMcore.getCommandCounter() == 4){
        return longitude;
    }else{
        return "error";
    }
}

char*   DFRobot_SIMgetpos::getLatitude(void)
{
    if(SIMcore.getCommandCounter() == 4){
        return latitude;
    }else{
        return "error";
    }
}
