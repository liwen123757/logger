#include <iostream>
#include "level.hpp"
#include <assert.h>
#include "message.hpp"
#include "sink.hpp"
#include <fstream>
#include <memory>
#include "Formatter.hpp"
#include "logger.hpp"
 
int main()
{
    
    // lwlog::LogMeg msg("root","main.cpp",7,lwlog::Loglevel::level::INFO,"hello");
    /* lwlog::Formatter f1("[%p][%c][%f:%l]%m%n");
    std::string out1=f1.format(msg);
    assert(out1 == "[INFO][root][main.cpp:7]hello\n");
    lwlog::LogSink::ptr stdsink=std::make_shared<lwlog::StdoutSink>();
    stdsink->log(out1.c_str(),out1.size());
    // std::cout<<out1<<std::endl;

    lwlog::Formatter f2("%d{%Y}-%m");
    std::string str2=f2.format(msg);
    std::cout<<str2<<std::endl;
    lwlog::LogSink::ptr filesink(new lwlog::FileSink("log.txt"));
    filesink->log(str2.c_str(),str2.size()); */
    // assert(str2.size()>7);
    /* lwlog::LogMeg msg(lwlog::Loglevel::level::INFO,7,"main.cpp","root","hello");
    lwlog::Formatter f1("[%p][%c][%f:%l]%m%n");
    std::string out1=f1.format(msg);
    lwlog::LogSink::ptr ptr= lwlog::SinkFactory::CreateSink<lwlog::RollBySink>("app-roll",1024);
    ptr->log(out1.c_str(),out1.size()); */
    // 创建格式化器
    lwlog::Formatter::ptr formatter = std::make_shared<lwlog::Formatter>("[%d{%H:%M:%S}][%t][%p][%c][%f:%l] %m%n");

    // 创建 sinks
    std::vector<lwlog::LogSink::ptr> sinks;
    sinks.push_back(lwlog::SinkFactory::CreateSink<lwlog::RollBySink>("app-roll",1024));

    // 创建同步日志器
    // lwlog::Logger::ptr logger = std::make_shared<lwlog::SyncLogger>("sync_logger", lwlog::Loglevel::level::DEBUG, formatter, sinks);
    lwlog::Logger::ptr logger=std::make_shared<lwlog::AsyncLogger>("sync_logger", lwlog::Loglevel::level::DEBUG, formatter, sinks,lwlog::AsyncType::ASYNC_SAFE);
    logger->debug(__FILE__, __LINE__, "This is a debug message: %s", "debug");
    std::cout<<"测试通过"<<std::endl;
    return 0;
}