#ifndef __DFRobot_SIMPHONECALL_H__
#define __DFRobot_SIMPHONECALL_H__

#include "DFRobot_SIMcore.h"

enum DFSIM_voiceCall_e { IDLE_CALL, CALLING, RECEIVINGCALL, TALKING};

class DFRobot_SIMphonecall
{
public:
    int    voiceCall(const char* number);
    int    hangCall(void);
    void   setvoiceCallStatus(DFSIM_voiceCall_e status);
    void   answerCallContinue(void);
    void   hangCallContinue(void);
private:
    DFSIM_voiceCall_e  voiceCallstatus;
};

#endif