#include "bApp.h"

void bTcp::startup(int port){
    // 1.创建一个socket(服务端)
    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_fd == -1)
    {
        spdlog::error("socket create failed");
        exit(1);
    }
    // 2.建立套接子地址
    // 绑定IP和端口号port
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);// 将一个无符号短整型的主机数值转换为网络字节顺序，即大尾顺序(big-endian)
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");// inet_addr方法可以转化字符串，主要用来将一个十进制的数转化为二进制的数，用途多于ipv4的IP转化。

    // 3.bind()绑定
    int res = bind(socket_fd,(struct sockaddr*)&addr,sizeof(addr));
    if (res == -1)
    {
        spdlog::error("bind failed");
        exit(-1);
    }
    spdlog::info("waiting for connection ...");
    // 4.监听客户端listen()函数
    // 参数二：进程上限，一般小于30
    listen(socket_fd, 30);
    // 5.等待客户端的连接accept()，返回用于交互的socket描述符
    struct sockaddr_in client;
    socklen_t len = sizeof(client);
    int fd = accept(socket_fd,(struct sockaddr*)&client,&len);
    // 6.使用第5步返回socket描述符，进行读写通信。
    char *ip = inet_ntoa(client.sin_addr);
    spdlog::info("client [{}] connect success!", ip);

    json j;
    j["msg"] = "welcome, this is server!";
    SendMsg(fd, j);
    // char *msg = nullptr;
    std::thread doSend(SendHandler, fd);
    std::thread doRecv(RecvHandler, fd);

    while (1){};
    if (fd == -1)
    {
        spdlog::error("accept failed");
        exit(-1);
    }
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