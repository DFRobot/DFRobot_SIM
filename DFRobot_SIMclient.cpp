#include "DFRobot_SIMclient.h"

int    DFRobot_SIMclient::checkSignalQuality(void)
{
    char  signalBuffer[26];
    int i = 0,j = 0,k = 0;
    char *signalQuality;
    SIMcore.cleanBuffer(signalBuffer,26);
    SIMcore.send_cmd("AT+CSQ\r\n");
    SIMcore.readBuffer(signalBuffer,26);
    if (NULL != (signalQuality = strstr(signalBuffer, "+CSQ:"))){
        i = *(signalQuality + 6) - 48;
        j = *(signalQuality + 7) - 48;
        k = (i * 10) + j;
    }else{
        SIMcore.closeCommand();
        return 0;
    }
    if( k == 99){
        SIMcore.closeCommand();
        return 0;
    }else{
        SIMcore.setCommandCounter(1);
        return k;
    }
}

bool   DFRobot_SIMclient::initNet(void)
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
    if(SIMcore.check_send_cmd("AT+CSTT\r\n","OK")){
        if(SIMcore.check_send_cmd("AT+CIICR\r\n","OK")){
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

bool   DFRobot_SIMclient::connect(char *server,Protocol ptl,int port)
{
    if(SIMcore.getCommandCounter() == 2){
        char num[4];
        char serverIP[100];
        SIMcore.cleanBuffer(serverIP,100);
        itoa(port, num, 10);
        SIMcore.send_cmd("AT+CIPSTART=\"");
        if(ptl == TCP){
            SIMcore.send_cmd("TCP\",\"");
        }else if(ptl == UDP){
            SIMcore.send_cmd("UDP\",\"");
        }else{
            Serial.println("Wrong protocol");
            return false;
        }
        SIMcore.send_cmd(server);
        SIMcore.send_cmd("\",");
        SIMcore.send_cmd(num);
        SIMcore.send_cmd("\r\n");
        while(1){
            while(SIMcore.checkReadable()){
                SIMcore.readBuffer(serverIP,100);
                if(NULL != strstr(serverIP,"ALREADY CONNECT")){
                    SIMcore.setCommandCounter(3);
                    return true;
                }
                if(NULL != strstr(serverIP,"CONNECT OK")){
                    SIMcore.setCommandCounter(3);
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

bool   DFRobot_SIMclient::send(char *data){
    if(SIMcore.getCommandCounter() == 3){
        char num[4];
        char resp[20];
        int len = strlen(data);
        itoa(len, num, 10);
        SIMcore.send_cmd("AT+CIPSEND=");
        SIMcore.send_cmd(num);
        if(SIMcore.check_send_cmd("\r\n",">")){
            SIMcore.send_cmd(data);
            while(1){
                while(SIMcore.checkReadable()){
                    SIMcore.readBuffer(resp,20);
                    if(NULL != strstr(resp,"OK")){
                        return true;
                    }
                    if(NULL != strstr(resp,"ERROR")){
                        return false;
                    }
                }
            }
        }else{
            SIMcore.closeCommand();
            return false;
        }
    }else{
        return false;
    }
}

bool   DFRobot_SIMclient::send(void *buffer,size_t len)
{
    if(SIMcore.getCommandCounter() == 3){
        char num[4];
        itoa(len, num, 10);
        SIMcore.send_cmd("AT+CIPSEND=");
        SIMcore.send_cmd(num);
        if(SIMcore.check_send_cmd("\r\n",">")){
            if(SIMcore.check_send_cmd(buffer,"OK")){
                return true;
            }else{
                SIMcore.setCommandCounter(3);
                return false;
            }
        }else{
            SIMcore.setCommandCounter(3);
            return false;
        }
    }else{
        return false;
    }
}

bool   DFRobot_SIMclient::close(void)
{
    if(SIMcore.getCommandCounter() == 3){
        if(SIMcore.check_send_cmd("AT+CIPSHUT\r\n","OK")){
            SIMcore.setCommandCounter(2);
            return true;
        }else{
            SIMcore.setCommandCounter(2);
            return false;
        }
    }else{
        return false;
    }
}