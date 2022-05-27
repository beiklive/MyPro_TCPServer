#include <iostream>
#include <bApp.h>
#include <spdlog/spdlog.h>
#include <nlohmann/json.hpp>
using nlohmann::json;
int main(){
    spdlog::set_level(spdlog::level::debug);
    spdlog::info("\n\
    -------------------------\n\
    |  This is client ~~~~  |\n\
    ------------------------- ");
    bTcp::startup(9901, "127.0.0.1");

    

    return 0;
}