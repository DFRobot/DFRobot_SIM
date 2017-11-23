 /*
  * file makePhoneCall.ino
  * brief DFRobot's SIM module
  * This example use for make a phone call
  * After initialization is completed enter a phone number to make a phone call then enter anything to hang call
  */

#include <Wire.h>
#include <DFRobot_SIM.h>

SoftwareSerial mySerial(8,7);                                          //RX TX
DFSIM            sim;
DFSIMVoiceCall   simVC;

String remoteNumber = "";                                              //The number you will call
char charbuffer[20];

void setup(){
    Serial.begin(115200);
    sim.begin(mySerial);                                               //Set SoftwareSerial
    Serial.println("Make Voice Call");
    Serial.println("Check and init SIMcard......");
    bool Connected = false;
    while(!Connected){
        if(sim.init()){                                                //Check and init SIMcard
            Connected = true;
        }else{
            Serial.println("Not connected");
        }
    }
    Serial.println("SIM initialized.");
    Serial.println("Enter phone number to call.");
}

void loop() {
    while(Serial.available() > 0){
        char inChar = Serial.read();
        if(inChar == '\n'){
            if(remoteNumber.length() < 25){
                Serial.print("Calling to : ");
                Serial.println(remoteNumber);
                remoteNumber.toCharArray(charbuffer, 25);
                if(simVC.voiceCall(charbuffer)){                       //Make a phonecall
                    Serial.println("Call Established. Enter line to end");
                    while(Serial.read() != '\n');
                    Serial.println("Hang call");
                    simVC.hangCall();                                  //Hang call
                }
                Serial.println("Call Finished");
                remoteNumber = "";
                Serial.println("Enter phone number to call.");
            }else{
                Serial.println("That's too long for a phone number. I'm forgetting it");
                remoteNumber = "";
            }
        }else{
            if (inChar != '\r'){
            remoteNumber += inChar;
            }
        }
    }
}