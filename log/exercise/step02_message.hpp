// 头文件保护宏开始：避免重复包含导致重定义错误。
#ifndef __STEP02_MESSAGE_H__
// 定义保护宏。
#define __STEP02_MESSAGE_H__

// 引入字符串类型。
#include <string>
// 引入线程 ID 类型。
#include <thread>
// 引入时间戳相关函数。
#include <ctime>

// 定义教学版命名空间，和正式实现隔离。
namespace bitlog_step02 {

// 日志级别定义：为了让 Step02 独立可编译，这里提供一个最小版本。
class LogLevel {
public:
    // value 枚举：表示日志严重程度。
    enum class value {
        // 未知级别。
        UNKNOW = 0,
        // 调试级别。
        DEBUG,
        // 信息级别。
        INFO,
        // 警告级别。
        WARN,
        // 错误级别。
        ERROR,
        // 致命级别。
        FATAL,
        // 关闭日志输出。
        OFF
    };
};

// LogMsg 结构体：描述“一条日志”在系统中的标准数据形态。
struct LogMsg {
    // 行号：日志调用点所在的代码行。
    size_t line;
    // 时间戳：记录日志创建时刻（秒级时间戳）。
    size_t ctime;
    // 线程 ID：记录是哪条线程写出的日志。
    std::thread::id tid;
    // 日志器名称：例如 root / network / database。
    std::string logger_name;
    // 文件名：日志调用点所在文件路径。
    std::string file_name;
    // 正文：格式化前或格式化后的核心消息文本。
    std::string payload;
    // 日志级别：DEBUG / INFO / ERROR 等。
    LogLevel::value level;

    // 构造函数：把一条日志所需字段一次性组装完整。
    LogMsg(const std::string& name,
           const std::string& file,
           size_t line_number,
           const std::string& text,
           LogLevel::value lv)
        // 初始化日志器名称。
        : line(line_number)
        // 初始化创建时间（time(nullptr) 返回当前 Unix 时间戳）。
        , ctime(static_cast<size_t>(std::time(nullptr)))
        // 初始化当前线程 ID。
        , tid(std::this_thread::get_id())
        // 初始化日志器名称。
        , logger_name(name)
        // 初始化文件名。
        , file_name(file)
        // 初始化日志正文。
        , payload(text)
        // 初始化日志级别。
        , level(lv) {
        // 构造函数体留空：所有字段都在初始化列表里完成赋值。
    }
};

// 命名空间结束。
} // namespace bitlog_step02

// 头文件保护宏结束。
#endif
