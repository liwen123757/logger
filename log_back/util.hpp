#ifndef __M_UTIL_H__
#define __M_UTIL_H__
#include <iostream>
#include <ctime>
#include <sys/stat.h>   // 提供 stat 结构体、stat() 函数和 mkdir() 函数
#include <sys/types.h>  // 可选，部分系统需要此头文件声明类型
#include <unistd.h>     // 可选，补充系统调用声明

namespace lwlog
{
    namespace Util
    {
        class date
        {
        public:
            static size_t now() { return (size_t)time(nullptr); };
        };

        /* class file
        {
        public:
            static bool exists(const std::string &name)
            {
                return fs::exists(name);
            }
            /* static std::string path(const std::string &name)
            {
                return fs::path(name).parent_path().string();
                std::cout << "提取父目录成功" << std::endl;
            } */
            /* static std::string path(const std::string &name)
            {
                // 先构造 fs::path，再取父路径
                fs::path p(name.c_str()); // 用 const char* 构造，兼容性更好
                return p.parent_path().string();
            }
            static void create_directory(const std::string &path)
            {
                if (!path.empty() && !fs::exists(path))
                    fs::create_directories(path);
                std::cout << "目录创建成功" << std::endl;
            }
        }; */ 
        class file {
            public:
                static bool exists(const std::string &name) {
                    struct stat st;
                    return stat(name.c_str(), &st) == 0;
                }
                static std::string path(const std::string &name) {
                    if (name.empty()) return ".";
                    size_t pos = name.find_last_of("/\\");
                    if (pos == std::string::npos) return ".";
                    return name.substr(0, pos + 1);
                }
                static void create_directory(const std::string &path) { 
                    if (path.empty()) return ;
                    if (exists(path)) return ;
                    size_t pos, idx = 0;
                    while(idx < path.size()) {
                        pos = path.find_first_of("/\\", idx);
                        if (pos == std::string::npos) {
                            mkdir(path.c_str(), 0755);
                            return;
                        }
                        if (pos == idx) {idx = pos + 1; continue;}
                        std::string subdir = path.substr(0, pos);
                        if (subdir == "." || subdir == "..") {idx = pos + 1; continue;}
                        if (exists(subdir)) {idx = pos + 1; continue;}
                        mkdir(subdir.c_str(), 0755);
                        idx = pos + 1;
                    }
                }
        };
    }
}
#endif