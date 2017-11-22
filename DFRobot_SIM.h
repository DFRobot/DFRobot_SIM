#ifndef __DFRobot_SIM_H__
#define __DFRobot_SIM_H__

#include "DFRobot_SIMcore.h"
#include "DFRobot_SIMphonecall.h"
#include "DFRobot_SIMsms.h"
#include "DFRobot_SIMgetpos.h"
#include "DFRobot_SIMclient.h"
#include "DFRobot_SIMfile.h"

#include <SoftwareSerial.h>
#include <HardwareSerial.h>

#define  DFSIM                 DFRobot_SIMcore
#define  DFSIMVoiceCall        DFRobot_SIMphonecall
#define  DFSIMSendMessage      DFRobot_SIMsms
#define  DFSIMGetPostion       DFRobot_SIMgetpos
#define  DFSIMClient           DFRobot_SIMclient
#define  DFSIMFile             DFRobot_SIMfile

#endif