#pragma once
#define _WINSOCK_DEPRECATED_NO_WARNINGS 1
#include "winsock2.h"
#include <ws2tcpip.h>
#include <iostream>

//#define SERVER			1
//#define CLIENT			2
//#define AUTO            3

#define IP_LENGTH       15

#define SENDER_SERVER   11
#define SENDER_CLIENT   12

#define TYPE_CONNECTION 21
#define TYPE_CHECK      22
#define TYPE_SHOOT      23
#define TYPE_DATA       24

#define FLAG_ONE        31
#define FLAG_TWO        32
#define FLAG_THREE      33
#define FLAG_FOUR       34
#define FLAG_DISCONNECT 35

#define MYPORT          54000
#define MML             200

class UDP
{
public:
    enum class ConnectionType
    {
        AUTO = 0,
        SERVER,
        CLIENT
    }CONNECTION_TYPE;

    enum class LastError
    {
        NONE = 0,
        WSA_INIT_ERROR,
        SOCKET_INIT_ERROR,
        BROADCAST_INIT_ERROR,
        BIND_ERROR,
        SEND_ERROR
    } LAST_ERROR;

    struct MSG
    {
        int SENDER;
        int TYPE;
        int FLAG;
        //int SIZE;
        const int MAX_MSG_LENGTH = MML;
        char* msg = new char[MAX_MSG_LENGTH];
    } MESSAGE;

    char* TempMsg = new char[MML + 3];
    UDP();
    ~UDP();
    static std::string ErroToString(UDP::LastError Err);
    UDP::LastError GetLastError(bool ClearLastError);
    void CleanUp();
    void DecodeMsg(MSG& msg, char* str);

    HANDLE HandleID;
    bool Received;
    char* MSGReceived = new char[MML];
    char* FormMsg(int sender, int type, int flag, char* msg);

protected:
    SOCKET sock;
    WSADATA wsaData;
    bool BreakThread;
    char broadcast = '1';
    struct sockaddr_in Recv_addr;
    struct sockaddr_in Sender_addr;
    int len;
    char recvbuff[MML];
    int recvbufflen = MML;
    void MSGReceivedClean();

private:
    void CleanMsg();    
};

