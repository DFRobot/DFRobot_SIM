 /*
  * file sendShortMessage.ino
  * brief DFRobot's SIM module
  * This example use for send short message
  * After initialization is completed ennter a phone number then enter the message data
  */

#include <Wire.h>
#include <DFRobot_SIM.h>

SoftwareSerial   mySerial(8,7);                            //RX TX
DFSIM            sim;
DFSIMSendMessage simSMS;

void setup(){
    Serial.begin(115200);
    sim.begin(mySerial);                                   //Set SoftwareSerial
    Serial.println("Send Short Message");
    Serial.println("Check and init SIMcard......");
    bool Connected = false;
    while(!Connected){
        if(sim.init()){                                    //Check and init SIMcard
            Connected = true;
        }else{
            Serial.println("Not connected");
        }
    }
    Serial.println("SIM initialized.");
}

void loop(){
    Serial.println("Enter a mobile number:");
    char phoneNum[20];
    char message[200];
    readSerial(phoneNum);
    Serial.println(phoneNum);
    Serial.println("Enter the message content: ");
    readSerial(message);
    Serial.println("Message:");
    Serial.println(message);
    simSMS.beginSMS(phoneNum);                             //Input phone number
    simSMS.editSMS(message);                               //Input message content
    if(simSMS.sendSMS()){                                  //Send message
        Serial.println("Send completed!");
    }else{
        Serial.println("Send error!");
    }
}

int readSerial(char result[]){
    int i = 0;
    while(1){
        while(Serial.available() > 0){
            char inChar = Serial.read();
            if(inChar == '\n'){
                result[i] = '\0';
                Serial.flush();
                return 0;
            }
            if(inChar != '\r'){
                result[i] = inChar;
                i++;
            }
        }
    }
}