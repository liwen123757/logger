#ifndef __M_SINK_H__
#define __M_SINK_H__
#include <mutex>
#include <memory>
#include <string>
#include <fstream>
#include <cstdio>
#include <assert.h>
#include <iostream>
#include <sstream>
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
            Util::file::create_directory(Util::file::path(_path));
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

    class RollBySink : public LogSink
    {
    public:
        RollBySink(const std::string basename,size_t max_size ):_basename(basename),
                                                                _max_fsize(max_size),
                                                                _cur_fsize(0) ,
                                                                _name_count(0)
                                                                
        {
            std::string pathname=CreateFile();
            //1.创建日志文件所在的目录
            Util::file::create_directory(Util::file::path(pathname));
            //2.打开文件
            _ofs.open(pathname,std::ios::binary|std::ios::app);
            assert(_ofs.is_open());
        }
        //将消息写到标准输出，--写前判断文件大小，超过了最大大小就要切换文件
        std::string CreateFile()
        {
            //获取系统时间，以时间来构造文件名扩展名
            time_t time=Util::date::now();
            struct tm lt;
            localtime_r(&time,&lt);
            std::stringstream filename;
            filename<<_basename;
            filename<<lt.tm_year+1900;
            filename<<lt.tm_mon+1;
            filename<<lt.tm_mday;
            filename<<lt.tm_hour;
            filename<<lt.tm_min;
            filename<<lt.tm_sec;
            filename<<"-";
            filename<<_name_count++;
            filename<<".log";
            return filename.str();
           
        }
        void log(const char* data,size_t len)
        {
            //如果大小超过max就新建文件进行落地
            if(_cur_fsize>=_max_fsize)
            {
                std::string pathname=CreateFile();
                Util::file::create_directory(Util::file::path(pathname));
                _ofs.open(pathname,std::ios::binary|std::ios::app);
                assert(_ofs.is_open());
                _cur_fsize=0;

            }
            _ofs.write(data,len);
            _cur_fsize+=len;
        }
    private:
        //通过基础文件名+扩展文件名（以时间生成的），组成一个实际的当前输出文件名
        size_t _name_count;
        std::string _basename; //./logs/text  ->./logs/text-200203456656.log
        std::ofstream _ofs;
        size_t _max_fsize;//记录最大大小，当前文件超过了这个大小就要切换文件
        size_t _cur_fsize;//记录当前文件以及写入的数据大小
    };

    class SinkFactory{
    public:
        template<typename SinkType,typename... Args>
        static LogSink::ptr CreateSink(Args &&...args)
        {
            return std::make_shared<SinkType>(std::forward<Args>(args)...);
        }
    };
}

#endif