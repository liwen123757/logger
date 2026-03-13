#ifndef __M_SINK_H__
#define __M_SINK_H__
#include <mutex>
#include <memory>
#include <string>
#include <fstream>
#include <cstdio>
#include <assert.h>
#include <iostream>
namespace lwlog{
    class LogSink{
        public:
        using ptr=std::shared_ptr<LogSink>;

        LogSink(){}
        virtual ~LogSink(){}
        //纯虚函数，把日志写到具体目标
        virtual void log(const char* data,size_t len)=0;
    };

    //控制台落地
    class StdoutSink:public LogSink{
        public:
        //覆盖基类接口
        void log(const char* data,size_t len){
            std::lock_guard<std::mutex> lock(_mtx);//加锁，防止多线程并发互相打断
            std::fwrite(data,1,len,stdout);//写入控制台
            std::fflush(stdout);//立即刷新，便于实时看见日志
        }
        private:std::mutex _mtx;
    };

    class FileSink:public LogSink{
        public: 
        FileSink(const std::string path):_path(path){
            std::lock_guard<std::mutex> lock(_mtx);
            _ofs.open(_path,std::ios::binary|std::ios::app);
            assert(_ofs.is_open());
        }
        void log(const char* data , size_t len){
            _ofs.write(data,len);
            _ofs.flush();
            if(!_ofs.good())
            {
                std::cout<<"文件操作失败"<<std::endl;
            }
        }
        private:
        std::mutex _mtx;
        std::string _path;
        std::ofstream _ofs;
    };
}

#endif