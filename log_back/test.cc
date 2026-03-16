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
    lwlog::Formatter::ptr f1(new lwlog::Formatter("[%p][%c][%f:%l]%m%n"));
    std::vector<lwlog::LogSink> sink(lwlog::StdoutSink);
    lwlog::Logger::ptr Logger=std::make_shared<lwlog::SyncLogger>("synclogger",lwlog::Loglevel::level::DEBUG,f1,sink);
    
    std::cout<<"测试通过"<<std::endl;
    return 0;
}