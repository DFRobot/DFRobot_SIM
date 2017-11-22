#include <DFRobot_SIMfile.h>

bool  DFRobot_SIMfile::init(void)
{
    if(!SIMcore.check_send_cmd("AT+FSCREATE=?\r\n","OK")){
        SIMcore.setCommandCounter(0);
        return false;
    }
    delay(10);
    if(!SIMcore.check_send_cmd("AT+FSREAD=?\r\n","OK")){
        SIMcore.setCommandCounter(0);
        return false;
    }
    delay(10);
    if(!SIMcore.check_send_cmd("AT+FSWRITE=?\r\n","OK")){
        SIMcore.setCommandCounter(0);
        return false;
    }
    delay(10);
    if(!SIMcore.check_send_cmd("AT+FSMKDIR=?\r\n","OK")){
        SIMcore.setCommandCounter(0);
        return false;
    }
    delay(10);
    if(!SIMcore.check_send_cmd("AT+FSRMDIR=?\r\n","OK")){
        SIMcore.setCommandCounter(0);
        return false;
    }
    delay(10);
    if(!SIMcore.check_send_cmd("AT+FSLS=?\r\n","OK")){
        SIMcore.setCommandCounter(0);
        return false;
    }
    SIMcore.setCommandCounter(1);
    return true;
}

char* DFRobot_SIMfile::getList(void)
{
    if(SIMcore.getCommandCounter() == 1){
        char SIMList[300];
        SIMcore.cleanBuffer(SIMList,300);
        SIMcore.send_cmd("AT+FSLS\r\n");
        SIMcore.readBuffer(SIMList,300);
        return SIMList+7;
    }else{
        return "error";
    }
}

char* DFRobot_SIMfile::getList(char *foldername)
{
    if(SIMcore.getCommandCounter() == 1){
        char SIMList[300];
        SIMcore.cleanBuffer(SIMList,300);
        SIMcore.send_cmd("AT+FSLS=\"");
        SIMcore.send_cmd(foldername);
        SIMcore.send_cmd("\"\r\n");
        SIMcore.readBuffer(SIMList,300);
        return SIMList+8;
    }else{
        return "error";
    }
}

bool  DFRobot_SIMfile::createFile(char *filename)
{
    if(SIMcore.getCommandCounter() == 1){
        SIMcore.send_cmd("AT+FSCREATE=\"");
        SIMcore.send_cmd(filename);
        if(SIMcore.check_send_cmd("\"\r\n","OK")){
            return true;
        }else{
            return false;
        }    
    }else{
        return false;
    }
}

char* DFRobot_SIMfile::readFile(char *filename, int offset, int len)
{
    if(SIMcore.getCommandCounter() == 1){
        int   rOffset = len+strlen(filename)+12;
Serial.print("rOffset = ");
Serial.println(rOffset);
        char  SIMFile[rOffset+50];
        SIMcore.cleanBuffer(SIMFile,rOffset+50);
        char  num1[4],num2[4];
        itoa(offset, num1, 10);
        itoa(len,    num2, 10);
        SIMcore.send_cmd("AT+FSREAD=\"");
        SIMcore.send_cmd(filename);
        SIMcore.send_cmd("\",");
        SIMcore.send_cmd(num1);
        SIMcore.send_cmd(",");
        SIMcore.send_cmd(num2);
        SIMcore.send_cmd("\r\n");
        SIMcore.readBuffer(SIMFile,rOffset+50);
        return SIMFile+10;
    }else{
        return "error";
    }
}

bool  DFRobot_SIMfile::deleteFile(char *filename)
{
    if(SIMcore.getCommandCounter() == 1){
        SIMcore.send_cmd("AT+FSDEL=\"");
        SIMcore.send_cmd(filename);
        if(SIMcore.check_send_cmd("\"\r\n","OK")){
            return true;
        }else{
            return false;
        }
    }else{
        return false;
    }
}

bool  DFRobot_SIMfile::writeFile(char *filename, char *data)
{
    if(SIMcore.getCommandCounter() == 1){
        char num[4];
        int len = strlen(data);
        itoa(len, num, 10);
        SIMcore.send_cmd("AT+FSWRITE=\"");
        SIMcore.send_cmd(filename);
        SIMcore.send_cmd("\",1,");
        SIMcore.send_cmd(num);
        if(SIMcore.check_send_cmd("\r\n",">")){
            if(SIMcore.check_send_cmd(data,"OK")){
                return true;
            }else{
                return false;
            }
        }else{
            return false;
        }
    }else{
        return false;
    }
}

bool  DFRobot_SIMfile::createFolder(char *foldername)
{
    if(SIMcore.getCommandCounter() == 1){
        SIMcore.send_cmd("AT+FSMKDIR=\"");
        SIMcore.send_cmd(foldername);
        if(SIMcore.check_send_cmd("\"\r\n","OK")){
            return true;
        }else{
            return false;
        }
    }else{
        return false;
    }
}

bool  DFRobot_SIMfile::deleteFolder(char *foldername)
{
    if(SIMcore.getCommandCounter() == 1){
        SIMcore.send_cmd("AT+FSRMDIR=\"");
        SIMcore.send_cmd(foldername);
        if(SIMcore.check_send_cmd("\"\r\n","OK")){
            return true;
        }else{
            return false;
        }
    }else{
        return false;
    }
}