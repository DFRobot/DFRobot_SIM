 /*
  * file file.ino
  * brief DFRobot's SIM module
  * This example use for L218 file system
  */

#include <Wire.h>
#include <DFRobot_SIM.h>

SoftwareSerial   mySerial(8,7);
DFSIM            SIM;
DFSIMFile        simF;

void setup(){
    Serial.begin(115200);
    sim.begin(mySerial);                                             //Set SoftwareSerial
    Serial.println("L218 file system");
    bool Connected = false;
    while(!Connected){
        if(sim.init()){                                              //Check and init SIMcard
            Connected = true;
        }else{
            Serial.println("Not connected");
        }
    }
    Serial.println("SIM initialized.");
    if(simF.init()){                                                 //Init file system
        Serial.println("File system init");
    }else{
        Serial.println("Fail to init file system");
    }
}

void loop(){
    Serial.println("List file :");
    Serial.println(simF.getList());                                  //Get the list of all files
    delay(200);
    Serial.println("Create folder :");
    if(simF.createFolder("test")){                                   //Create a folder
        Serial.println("New file list :");
        Serial.println(simF.getList());
        delay(200);
        Serial.println("New folder list :");
        Serial.println(simF.getList("test"));                        //Get the list of specified folder
        delay(200);
        Serial.println("Create file :");
        if(simF.createFile("test/test.txt")){                        //Create a file
            Serial.println("New folder list :");
            Serial.println(simF.getList("test"));
            delay(200);
            if(simF.writeFile("test/test.txt", "Hi DFRobot")){       //Write data to specified file
                Serial.println("Read file :");
                Serial.println(simF.readFile("test/test.txt",0,10)); //Read data from specified file
                delay(200);
                Serial.println("Delete file");
                if(simF.deleteFile("test/test.txt")){                //Delete the file
                    Serial.println("New folder list :");
                    Serial.println("test");
                    delay(200);
                    Serial.println("Delete folder");
                    if(simF.deleteFolder("test")){                   //Delete the folder
                        Serial.println("New file list :");
                        Serial.println(simF.getList());
                    }else{
                        Serial.println("Fail to delet folder");
                    }
                }else{
                    Serial.println("Fail to delet file");
                }
            }else{
                Serial.println("Fail to write file");
            }
        }else{
             Serial.println("Fail to create file");
        }
    }
    while(1);
}
