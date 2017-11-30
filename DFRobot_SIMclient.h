#ifndef __DFRobot_SIMCLIENT_H__
#define __DFRobot_SIMCLIENT_H__

#include "DFRobot_SIMcore.h"

enum Protocol {
    TCP    = 1,
    UDP    = 2,
};

class DFRobot_SIMclient
{
public:
    int        checkSignalQuality(void);
    bool       initNet(void);
    bool       connect(char *server,Protocol ptl,int port);
    bool       send(char *data);
    bool       send(void *buffer,size_t len);
    bool       close(void);

};

#endif