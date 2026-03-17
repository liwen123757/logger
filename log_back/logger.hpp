#ifndef __M_LOGGER_H__
#define __M_LOGGER_H__
#include <mutex>
#include <string>
#include <atomic>
#include "level.hpp"
#include "Formatter.hpp"
#include "sink.hpp"
#include <cstdarg>
#include "looper.hpp"

namespace lwlog{
    class Logger{
    public:
        using ptr=std::shared_ptr<Logger>;
        Logger(const std::string name,
            Loglevel::level level,
            Formatter::ptr &formatter,
            std::vector<LogSink::ptr> &sinks):_logger_name(name),
                                            _limit_level(level),
                                            _formatter(formatter),
                                            _sinks(sinks.begin(),sinks.end()) {}
        const std::string &name()
        {
            return _logger_name;
        }
        void debug(const std::string file,size_t line,const std::string &fmt,...)
        {
            if(Loglevel::level::DEBUG <_limit_level)
            {
                return;
            }
            va_list ap;
            va_start(ap,fmt);
            char *res;
            int ret=vasprintf(&res,fmt.c_str(),ap);
            if(ret==-1)
            {
                std::cout<<"vasprintf failed\n";
                return;
            }
            va_end(ap);
            serialize(Loglevel::level::DEBUG,file,line,res);
            free(res);
        }
        void info(const std::string file,size_t line,const std::string &fmt,...)
        {
            if(Loglevel::level::INFO <_limit_level)
            {
                return;
            }
            va_list ap;
            va_start(ap,fmt);
            char *res;
            int ret=vasprintf(&res,fmt.c_str(),ap);
            if(ret==-1)
            {
                std::cout<<"vasprintf failed\n";
                return;
            }
            va_end(ap);
            serialize(Loglevel::level::INFO,file,line,res);
            
            free(res);
        }
        void warn(const std::string file,size_t line,const std::string &fmt,...)
        {
            if(Loglevel::level::WARNING <_limit_level)
            {
                return;
            }
            va_list ap;
            va_start(ap,fmt);
            char *res;
            int ret=vasprintf(&res,fmt.c_str(),ap);
            if(ret==-1)
            {
                std::cout<<"vasprintf failed\n";
                return;
            }
            va_end(ap);
            serialize(Loglevel::level::WARNING,file,line,res);
            free(res);
        }
        void error(const std::string file,size_t line,const std::string &fmt,...)
        {
            if(Loglevel::level::ERROR <_limit_level)
            {
                return;
            }
            va_list ap;
            va_start(ap,fmt);
            char *res;
            int ret=vasprintf(&res,fmt.c_str(),ap);
            if(ret==-1)
            {
                std::cout<<"vasprintf failed\n";
                return;
            }
            va_end(ap);
            serialize(Loglevel::level::ERROR,file,line,res);
            free(res);
        }
        void fatal(const std::string file,size_t line,const std::string &fmt,...)
        {
            if(Loglevel::level::FATAL <_limit_level)
            {
                return;
            }
            va_list ap;
            va_start(ap,fmt);
            char *res;
            int ret=vasprintf(&res,fmt.c_str(),ap);
            if(ret==-1)
            {
                std::cout<<"vasprintf failed\n";
                return;
            }
            va_end(ap);
            serialize(Loglevel::level::FATAL,file,line,res);
            free(res);
        }
        
        
    protected:
        void serialize(Loglevel::level level,const std::string file,size_t line,char *str){
            //构造LogMsg对象
            LogMeg msg(level,line,file,_logger_name,str);
            //通过格式化工具对LogMsg进行格式化，得到格式化之后的日志字符串
            std::stringstream ss;
            _formatter->format(ss,msg);
            //抽象接口按成实际的落地输出--不同的日志起会有不同的实际落地方式
            log(ss.str().c_str(),ss.str().size());
    }
        virtual void log(const char*data,size_t len)=0;
    protected:
        std::mutex _mutx;
        std::string _logger_name;
        std::atomic<Loglevel::level> _limit_level;
        Formatter::ptr _formatter;
        std::vector<LogSink::ptr> _sinks;

      };

      class SyncLogger:public Logger{
      public:SyncLogger(const std::string name,
            Loglevel::level level,
            Formatter::ptr &formatter,
            std::vector<LogSink::ptr> &sinks):Logger(name,level,formatter,sinks){}
        void log(const char* data,size_t len){
            std::unique_lock<std::mutex> lock(_mutx);
            if(_sinks.empty())
            {
                return;
            }
            for(auto &sink:_sinks)
            {   
                sink->log(data,len);
            }
        }
      };

      class AsyncLogger:public Logger{
        public:
            AsyncLogger(const std::string name,
            Loglevel::level level,
            Formatter::ptr &formatter,
            std::vector<LogSink::ptr> &sinks):Logger(name,level,formatter,sinks){}
            void log(const char *data,size_t len)
            {
                
            }
            //设计一个实际落地函数
            void realLog(){}
        private:
            AsyncLooper::ptr _looper;
      };
      enum class LoggerType{
            LOGGER_SYNC,
            LOGGER_ASYNC
      };

      //使用建造者模式来建造日志器，不要让用户自己去构造日志器
      //1.抽象一个建造者类（完成日志器对象多余零部件的构造&日志器的构建）
      //    1。设置日志器类型
      //    2.将不同类型的日志器的创建放到同一个日志器建造者类中完成
      class LoggerBuilder
      {
        public:
            LoggerBuilder(){}
        private:
            LoggerType _logger_type;
            std::string _logger_name;
      };
      

      
}
#endif
