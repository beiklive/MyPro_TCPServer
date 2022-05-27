#include "bApp.h"

void bTcp::startup(int port, std::string ip){
    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_fd == -1)
    {
        spdlog::error("socket create failed");
        exit(1);
    }

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = inet_addr(ip.c_str());

    spdlog::info("start to connect ...");
    if (connect(socket_fd, (struct sockaddr *)&addr, sizeof(addr)) == -1)
    {
        spdlog::error("connect failed");
        exit(1);
    }
    spdlog::info("connect success");

    auto fd = socket_fd;

    json j;
    j["msg"] = "welcome, this is client!";
    // char *msg = nullptr;
    char buffer[255]={};
    int size = read(fd, buffer, sizeof(buffer));//通过fd与客户端联系在一起,返回接收到的字节数
    j = json::parse(buffer);
    spdlog::info("[recive] {}", j["msg"]);



    std::thread doSend(SendHandler, fd);
    std::thread doRecv(RecvHandler, fd);

    while (1){};


    // 7.关闭sockfd
    close(fd);
    close(socket_fd);
    return ;
}


void bTcp::SendMsg(int fd, json j){
    std::string s = j.dump();
    write(fd, s.c_str(), s.size());
    spdlog::info("[send] {}", j["msg"]);
    return ;
}

void bTcp::RecvMsg(int fd){
    char buffer[BUFFER_SIZE]={};
    int size = read(fd, buffer, sizeof(buffer));
    json j = json::parse(buffer);
    spdlog::info("[recive] {}", j["msg"]);
    spdlog::info("Say something to client\n:");
    return ;
}

void bTcp::SendHandler(int fd){
    json j;
    char say[BUFFER_SIZE]={};
    while(isOnline(fd)){
        memset(say, 0, BUFFER_SIZE);
        std::cin >> say;
        j["msg"] = say;
        SendMsg(fd, j);
    }
    return ;
}

void bTcp::RecvHandler(int fd){
    while(isOnline(fd)){
        RecvMsg(fd);
    }
    return ;
}

bool bTcp::isOnline(int fd){
    // char buffer[BUFFER_SIZE]={};
    // int size = read(fd, buffer, sizeof(buffer));
    // if(size == 0){
    //     return false;
    // }
    return true;
}