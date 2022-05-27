#ifndef __TCP_H__
#define __TCP_H__
#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<spdlog/spdlog.h>
#include <nlohmann/json.hpp>
#include <thread>
using nlohmann::json;

namespace bTcp{
#define BUFFER_SIZE 255

void startup(int port, std::string ip);

void SendMsg(int fd, json j);
void RecvMsg(int fd);
void SendHandler(int fd);
void RecvHandler(int fd);
bool isOnline(int fd);

}




#endif