#ifndef __DFRobot_SIMFILE_H__
#define __DFRobot_SIMFILE_H__

#include "DFRobot_SIMcore.h"

class DFRobot_SIMfile
{
public:
    bool     init(void);
    char*    getList(void);
    char*    getList(char *foldername);
    bool     createFile(char *filename);
    char*    readFile(char *filename,int offset = 0, int len = 50);
    bool     deleteFile(char *filename);
    bool     writeFile(char *filename, char *data);
    bool     createFolder(char *foldername);
    bool     deleteFolder(char *foldername);
};

#endif