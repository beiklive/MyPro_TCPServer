#ifndef __TCP_H__
#define __TCP_H__
#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include <thread>

#include<spdlog/spdlog.h>
#include <nlohmann/json.hpp>
using nlohmann::json;

namespace bTcp{

#define BUFFER_SIZE 255


void startup(int port);
void SendMsg(int fd, json j);
void RecvMsg(int fd);
void SendHandler(int fd);
void RecvHandler(int fd);
bool isOnline(int fd);

}




#endif