# DFROBOT_SIM Library for Arduino
Provides an Arduino library for GSM Shield

## Table of Contents

* [Summary](#summary)
* [Methods](#methods)
* [History](#history)
* [Credits](#credits)
<snippet>
<content>

## Summary

The library use for GSM Shield as following function
#### Make phone call
#### Send short message
#### As a web client
#### Get time
#### Get current position    (L218)
#### Independent file system (L218)

## Methods
```C++
/*
 * @brief Set L218 software serial
 *
 * @Param
 *     &s_ SoftwareSerial
 */
void begin(Stream &s_);

/*
 * @brief Init specified module
 *
 * @return
 *     ture   Success
 *     false  Failed
 */
bool init(void);

/*
 * @brief Check signal quality
 *
 * @return
 *     0-99:Signal quality
 */
int checkSignalQuality(void);

/*
 * @brief Start up connection
 *
 * @param 
 *    *server Server domain name
 *     port   Contented port
 *
 * @return
 *     ture   Success
 *     false  Failed
 */
bool connect(char *server,int port);

/*
 * @brief Send data
 *
 * @param 
 *    *data The data to send
 */
void send(char *data);

/*
 * @brief Send data with specify the length
 *
 * @param 
 *     buffer The buffer stored data to be send
 *     len    The length of data to be send
 */
void send(void* buffer,size_t len);

/*
 * @brief End the connection
 *
 * @return
 *     ture   Success
 *     false  Failed
 */
bool close(void);

/*
 * @brief Get time
 *
 * @return
 *     Current time
 */
char* getTime(void);

/*
 * @brief Get the current position
 *
 * @return
 *     ture   Success
 *     false  Failed
 */
bool getPosition(void);

/*
 * @brief Get longitude
 *
 * @return
 *     Longitude value
 */
char* getLongitude(void);

/*
 * @brief Get latitude
 *
 * @return
 *     Latitude value
 */
char* getLatitude(void);

/*
 * @brief Start a voice call
 * 
 * @param
 *     number Target phonenumber
 *
 * @return
 *     ture   Success
 *     false  Failed
 */
bool voiceCall(char* number);

/*
 * @brief Hang up the call
 */
void hangCall(void);

/*
 * @brief Ready to send short message
 *
 * @param 
 *     to     Target number for send short message
 *
 * @return
 *     ture   Success
 *     false  Failed
 */
bool beginSMS(const char* to);

/*
 * @brief Edit message content
 *
 * @param 
 *     c   The message content
 */
void editSMS(const char* c);

/*
 * @brief Send short message
 *
 * @return
 *     ture   Success
 *     false  Failed
 */
bool sendSMS(void);

/*
 * @brief Get file list
 *
 * @return
 *     The list of all file
 */
char* getList(void);

/*
 * @brief Get specified folder's list
 *
 * @param 
 *    *foldername   The name of specified folder
 *
 * @return
 *     The list of specified folder
 */
char* getList(char *foldername);

/*
 * @brief Create a new file
 *
 * @param 
 *    *filename   The name of new file
 *
 * @return
 *     ture   Success
 *     false  Failed
 */
bool createFile(char *filename);

/*
 * @brief Create a new folder
 *
 * @param 
 *    *foldername   The name of new folder
 *
 * @return
 *     ture   Success
 *     false  Failed
 */
bool createFolder(char *foldername);

/*
 * @brief Read a file data
 *
 * @param 
 *     *filename   The name of specified file
 *      offset     Offset from the file beginning Passible value: 0-65536, default value: 0
 *      len        The length of data to be read Passible value: 0-1024, default value: 50
 *
 * @return
 *     The data of specified file
 */
char* readFile(char *filename, int offset = 0, int len = 50);

/*
 * @brief Delete specified file
 *
 * @param
 *    *filename   The name of specified file
 *
 * @return
 *     ture   Success
 *     false  Failed
 */
bool deleteFile(char *filename);

/*
 * @brief Delete specified folder
 *
 * @param
 *    *folder   The name of specified folder
 *
 * @return
 *     ture   Success
 *     false  Failed
 */
bool deleteFolder(char *foldername);

/*
 * @brief Write data to specified file
 *
 * @param
 *    *filename   The name of specified file
 *    *data       The input data
 *
 * @return
 *     ture   Success
 *     false  Failed
 */
bool writeFile(char *filename, char *data);

```

## History

- data 2017-11-22
- version V0.1

## Credits

- author [Zhangjiawei  <jiawei.zhang@dfrobot.com>]