#ifndef __M_FORMATTER_H__
#define __M_FORMATTER_H__
#include <memory>
#include "util.hpp"
#include "message.hpp"
#include <string>
#include <time.h>
#include <vector>

namespace lwlog{
    class FormatItem{
        public:
        using ptr=std::shared_ptr<FormatItem>;
        virtual ~FormatItem(){}
        virtual void format(std::ostream os,const LogMeg msg)=0;
    };

    class LevelFormatItem:public FormatItem{
        public:LevelFormatItem(const std::string &str=""){}
        void format(std::ostream os,const LogMeg msg){
            os<<Loglevel::to_string(msg._level);
        }
    };
    class MsgFormatItem:public FormatItem{
        public:MsgFormatItem(const std::string &str=""){}
        void format(std::ostream os,const LogMeg msg){
            os<<msg._message;
        }
    };
    class NameFormatItem:public FormatItem{
        public:NameFormatItem(const std::string &str=""){}
        void format(std::ostream os,const LogMeg msg){
            os<<msg.logger_name;
        }
    };
    class ThreadFormatItem:public FormatItem{
        public:ThreadFormatItem(const std::string &str=""){}
        void format(std::ostream os,const LogMeg msg){
            os<<msg._id;
        }
    };
    class TimeFormatItem:public FormatItem{
        public:TimeFormatItem(const std::string &format="%H:%M:%S"):_format(format){
            if(format.empty()) _format="%H:%M:%S";
        }
        
        void format(std::ostream os,const LogMeg msg){
            time_t t=msg ._time;
            struct tm lt;
            localtime_r(&t,&lt);
            char tmp[128];
            strftime(tmp,127,_format.c_str(),&lt);
            os<<tmp;
        }
        private:
        std::string _format;
    };

    class CFileFormatItem:public FormatItem{
        public:CFileFormatItem(const std::string &str=""){}
        void format(std::ostream os,LogMeg msg){
            os<<msg._file;
        }
    };

    class CLineFormatItem:public FormatItem{
        public:CLineFormatItem(const std::string &str=""){}
        void format(std::ostream os,LogMeg msg){
            os<<msg._line;
        }
    };
    class TabFormatItem:public FormatItem{
        public:TabFormatItem(const std::string &str=""){}
        void format(std::ostream os,LogMeg msg){
            os<<"\t";
        }
    };
    class NLineFormatItem:public FormatItem{
        public:NLineFormatItem(const std::string &str=""){}
        void format(std::ostream os,LogMeg msg){
            os<<"\n";
        }
    };
    class OtherFormatItem:public FormatItem{
        public:OtherFormatItem(const std::string &str=""):_str(str){}
        void format(std::ostream os,LogMeg msg){
            os<<_str;
        }
        private:
        std::string _str;
    };

    class Formatter{
        public:
        using ptr=std::shared_ptr<Formatter>;
        private:
        std::string _pattern;
        std::vector<FormatItem::ptr> _item;
    };
}

#endif
