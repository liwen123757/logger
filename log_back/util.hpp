#ifndef __M_UTIL_H__
#define __M_UTIL_H__
#include <iostream>
#include <ctime>
#include <filesystem>
namespace fs = std::filesystem;
namespace lwlog
{
    namespace Util
    {
        class date
        {
        public:
            static size_t now() { return (size_t)time(nullptr); };
        };

        class file
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
            static std::string path(const std::string &name)
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
        };
    }
}
#endif