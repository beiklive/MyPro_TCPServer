#include <iostream>
#include <bApp.h>
#include <spdlog/spdlog.h>

int main(){
    spdlog::set_level(spdlog::level::debug);
    spdlog::info("\n\
    -------------------------\n\
    |  This is server ~~~~  |\n\
    ------------------------- ");
    try{
    bTcp::startup(9901);
    }catch(std::exception& e){
        spdlog::error("{}", e.what());
    }
    return 0;
}