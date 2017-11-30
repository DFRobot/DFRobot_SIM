# DFROBOT_SIM Library for Arduino
Provides an Arduino library for GSM Shield
This is a base class library for AT communication module, many communicate device of DFRobot depend on it.

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

## Methods
```C++
/*
 * @brief Set software serial
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
 * @brief Get time
 *
 * @return
 *     Current time
 */
char* getTime(void);

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
 *     ptl    Choose connection protocol Passible value: TCP UDP
 *     port   Contented port
 *
 * @return
 *     ture   Success
 *     false  Failed
 */
bool connect(char *server,Protocol ptl,int port);

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

```

## History

- data 2017-11-22
- version V0.1

## Credits

- author [Zhangjiawei  <jiawei.zhang@dfrobot.com>]