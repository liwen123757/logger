#include <iostream>
#include "level.hpp"
#include <assert.h>
#include "message.hpp"
#include "sink.hpp"
#include <fstream>
 
int main()
{
    lwlog::LogMeg logmeg("root","log",52,lwlog::Loglevel::level::DEBUG,"This is a debug message");
    lwlog::LogSink::ptr stdout_sink=std::make_shared<lwlog::StdoutSink>();
    
    const std::string _msg="step03 stdout sink smoke test\n";
    stdout_sink->log(_msg.c_str(),_msg.size());



    const std::string file_path="./bitlog_step03_test.log";
    lwlog::Util::file::create_directory(lwlog::Util::file::path(file_path));
    lwlog::LogSink::ptr File_sink=std::make_shared<lwlog::FileSink>(file_path);
    
    const std::string file_msg="step03 file sink test success";
    File_sink->log(file_msg.c_str(),file_msg.size());

    //读取文件内容进行校验
    std::ifstream ifs(file_path,std::ios::binary);
    assert(ifs.is_open());
    std::cout<<"test success"<<std::endl;
    std::cout<<"文件内容存在"<<std::endl;
    混合
    return 0;
}