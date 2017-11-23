 /*
  * file client.ino
  * brief DFRobot's SIM module
  * This example use for connect net and send data
  * After initialization is completed input Server IP if connected input ur data
  */

#include <Wire.h>
#include <DFRobot_SIM.h>

SoftwareSerial mySerial(8,7);                                //RX TX
DFSIM            sim;
DFSIMClient      simC;

void setup(){
    int signalQuality;
    Serial.begin(115200);
    sim.begin(mySerial);                                     //Set SoftwareSerial
    Serial.println("SIM Client");
    Serial.println("Check and init SIMcard......");
    bool Connected = false;
    while(!Connected){
        if(sim.init()){                                      //Check and init SIMcard
            Connected = true;
        }else{
            Serial.println("Not connected");
        }
    }
    Serial.println("SIM initialized.");
    Connected = false;
    while(!Connected){
        signalQuality = simC.checkSignalQuality();           //Check signal quality
        if(signalQuality){
            Serial.print("Signal Quality = ");
            Serial.println(signalQuality);
            Connected = true;
        }else{
            Serial.println("No Signal ! ");
            delay(500);
        }
    }
    Connected = false;
    while(!Connected){
        if(simC.init()){                                     //Init web module
            Serial.println("Init connect server");
            Connected = true;
        }else{
            Serial.println("Failed to init connect server");
            delay(500);
        }
    }
}

void loop(){
    Serial.println("Enter a server IP");
    char  Loge[10];
    char  serverIP[20];
    char  sendData[100];
    readSerial(serverIP);
    Serial.print("Connect to :");
    Serial.println(serverIP);
    if(simC.connect(serverIP, TCP, 80)){                     //Connect to server
        Serial.println("Connected!");
        Serial.println("Input data:");
        readSerial(sendData);
        Serial.print("Send data :");
        Serial.println(sendData);
        if(simC.send(sendData)){                             //Send data to server
            Serial.println("Send data, recive:");
            Serial.println(mySerial.read());                 //Get the recive data
        }else{
            Serial.println("Failed to send");
        }
        Serial.println("Enter anything to close connect");
        readSerial(Loge);
        if(simC.close()){                                    //Close connection
            Serial.println("Close connect");
            delay(1000);
        }else{
            Serial.println("Failed to close connect");
            delay(1000);
        }
    }else{
        Serial.println("Failed to connect");
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