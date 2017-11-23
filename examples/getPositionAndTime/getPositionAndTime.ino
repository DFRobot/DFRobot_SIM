 /*
  * file getPostion.ino
  * brief DFRobot's SIM module
  * This example use for get time ,longitude and latitude
  * After initialization is completed u will get time and enter anything to get longitude and latitude
  */

#include <Wire.h>
#include <DFRobot_SIM.h>

SoftwareSerial mySerial(8,7);                                 //RX TX
DFSIM            sim;
DFSIMGetPostion  simGP;

void setup(){
    Serial.begin(115200);
    Serial.println("Get Postion");
    Serial.println("Check and init SIMcard......");
    bool Connected = false;
    sim.begin(mySerial);                                      //Set SoftwareSerial
    while(!Connected){
        if(sim.init()){                                       //Check and init SIMcard
            Connected = true;
        }else{
            Serial.println("Not connected");
        }
    }
    Serial.println("SIM initialized.");
    Serial.println("Init positioning function......");
    Connected = false;
    while(!Connected){
        if(simGP.init()){                                     //Init GPS module
            Connected = true;
        }else{
            Serial.println("Fail to init positioning function");
            delay(1000);
        }
    }
    Serial.println("Positioning function initialized");
    delay(100);
    Serial.print("Time:");
    Serial.println(sim.getTime());                            //Get the current time
}

void loop(){
    Serial.println("Enter anything to get positioning ");
    char loge[10];
    readSerial(loge);
    if(simGP.getPosition()){                                  //Get the current position
        Serial.print("Longtude :");
        Serial.println(simGP.getLongitude());                 //Get longitude
        Serial.print("Latitude :");
        Serial.println(simGP.getLatitude());                  //Get latitude
    }else{
        Serial.println("Wrong data try again");
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