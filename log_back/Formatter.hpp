#ifndef __M_FORMATTER_H__
#define __M_FORMATTER_H__
#include <memory>
#include "util.hpp"
#include "message.hpp"
#include <string>
#include <time.h>
#include <vector>
#include <sstream>

namespace lwlog{
    class FormatItem{
        public:
        using ptr=std::shared_ptr<FormatItem>;
        virtual ~FormatItem(){}
        virtual void format(std::ostream &os,const LogMeg &msg)=0;
    };

    class LevelFormatItem:public FormatItem{
        public:LevelFormatItem(const std::string &str=""){}
        void format(std::ostream &os,const LogMeg &msg){
            os<<Loglevel::to_string(msg._level);
        }
    };
    class MsgFormatItem:public FormatItem{
        public:MsgFormatItem(const std::string &str=""){}
        virtual void format(std::ostream &os,const LogMeg &msg){
            os<<msg._message;
        }
    };
    class NameFormatItem:public FormatItem{
        public:NameFormatItem(const std::string &str=""){}
        void format(std::ostream &os,const LogMeg &msg){
            os<<msg.logger_name;
        }
    };
    class ThreadFormatItem:public FormatItem{
        public:ThreadFormatItem(const std::string &str=""){}
        void format(std::ostream &os,const LogMeg &msg){
            os<<msg._id;
        }
    };
    class TimeFormatItem:public FormatItem{
        public:TimeFormatItem(const std::string &format="%H:%M:%S"):_format(format){
            if(format.empty()) _format="%H:%M:%S";
        }
        
        void format(std::ostream &os,const LogMeg &msg){
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
        void format(std::ostream &os,const LogMeg &msg){
            os<<msg._file;
        }
    };

    class CLineFormatItem:public FormatItem{
        public:CLineFormatItem(const std::string &str=""){}
        void format(std::ostream &os,const LogMeg &msg){
            os<<msg._line;
        }
    };
    class TabFormatItem:public FormatItem{
        public:TabFormatItem(const std::string &str=""){}
        void format(std::ostream &os,const LogMeg &msg){
            os<<"\t";
        }
    };
    class NLineFormatItem:public FormatItem{
        public:NLineFormatItem(const std::string &str=""){}
        void format(std::ostream &os,const LogMeg &msg){
            os<<"\n";
        }
    };
    class OtherFormatItem:public FormatItem{
        public:OtherFormatItem(const std::string &str=""):_str(str){}
        void format(std::ostream &os,const LogMeg &msg){
            os<<_str;
        }
        private:
        std::string _str;
    };

    class Formatter{
        public:
        using ptr=std::shared_ptr<Formatter>;
        Formatter(std::string pattern="[%d{%H:%M:%S}][%t][%p][%c][%f:%l] %m%n"):_pattern(pattern){
            parsePatter();
        }
        
        std::string format(LogMeg &msg)
        {
            std::stringstream ss;
            for(auto& it:_item)
            {
                it->format(ss,msg);
            }
            return ss.str();
        }
        std::ostream& format(std::ostream &os,LogMeg &msg)
        {
            for(auto &it:_item)
            {
                it->format(os,msg);
            }
            return os;
        }

        FormatItem::ptr CreateItem(const std::string &fc,const std::string &subfmt)
        {
            if(fc=="m") return FormatItem::ptr(new MsgFormatItem(subfmt));
            if(fc=="p") return FormatItem::ptr(new LevelFormatItem(subfmt));
            if(fc=="c") return FormatItem::ptr(new NameFormatItem(subfmt));
            if(fc=="t") return FormatItem::ptr(new ThreadFormatItem(subfmt));
            if(fc=="n") return FormatItem::ptr(new NLineFormatItem(subfmt));
            if(fc=="d") return FormatItem::ptr(new TimeFormatItem(subfmt));
            if(fc=="f") return FormatItem::ptr(new CFileFormatItem(subfmt));
            if(fc=="l") return FormatItem::ptr(new CLineFormatItem(subfmt));
            if(fc=="T") return FormatItem::ptr(new TabFormatItem(subfmt));
            return nullptr;
        }

        bool parsePatter()
        {
            std::vector<std::tuple<std::string,std::string,int>> tokens;
            std::string text;
            size_t pos = 0;
            while (pos < _pattern.size()) {
                if (_pattern[pos] != '%') {
                    text += _pattern[pos++];
                    continue;
                }
                // _pattern[pos] == '%'
                pos++; // skip %
                if (pos < _pattern.size() && _pattern[pos] == '%') {
                    text += '%';
                    pos++;
                    continue;
                }
                // expect alpha
                if (pos >= _pattern.size() || !std::isalpha(_pattern[pos])) return false;
                std::string key(1, _pattern[pos]);
                pos++;
                std::string val;
                if (pos < _pattern.size() && _pattern[pos] == '{') {
                    pos++; // skip {
                    while (pos < _pattern.size() && _pattern[pos] != '}') {
                        val += _pattern[pos++];
                    }
                    if (pos >= _pattern.size()) return false; // no closing }
                    pos++; // skip }
                }
                if (!text.empty()) {
                    tokens.push_back(std::make_tuple(text, "", 0));
                    text.clear();
                }
                tokens.push_back(std::make_tuple(key, val, 1));
            }
            if (!text.empty()) {
                tokens.push_back(std::make_tuple(text, "", 0));
            }
            // convert tokens to _item
            for (auto& token : tokens) {
                if (std::get<2>(token) == 0) {
                    _item.push_back(std::make_shared<OtherFormatItem>(std::get<0>(token)));
                } else {
                    FormatItem::ptr it = CreateItem(std::get<0>(token), std::get<1>(token));
                    if (it == nullptr) return false;
                    _item.push_back(it);
                }
            }
            return true;
        }
        private:
        std::string _pattern;
        std::vector<FormatItem::ptr> _item;
    };
}

#endif
