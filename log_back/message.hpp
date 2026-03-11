#ifndef __M_MSG_H__
#define __M_MSG_H__


#include <string>
#include <mingw.thread.h>
#include "level.hpp"
#include <memory>
namespace lwlog{
    struct LogMeg{
        //行号
        size_t _line;
        //时间戳
        size_t _time;
        //日志器名称
        std::string logger_name;
        //文件名
        std::string _file;
        //正文
        std::string _message;
        //日志级别
        Loglevel::level _level;
        //线程ID
        std::thread::id _id;
        LogMeg(std::string &name,std::string file,size_t line,Loglevel::level value,std::string &&payload):logger_name{name},_file(file),_level(value),
        _line(line),_time(),_id(std::this_thread::get_id()),_message(std::move(payload)){}

    };
}

#endif