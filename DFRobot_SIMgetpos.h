#ifndef __DFRobot_SIMGETPOS_H__
#define __DFRobot_SIMGETPOS_H__

#include "DFRobot_SIMcore.h"

class DFRobot_SIMgetpos
{
public:
    bool     init(void);
    bool     getPosition(void);
    char*    getLongitude(void);
    char*    getLatitude(void);
private:
    char     latitude[8];
    char     longitude[8];
};

#endif