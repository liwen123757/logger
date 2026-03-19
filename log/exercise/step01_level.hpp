// 头文件保护宏开始：防止这个头文件被重复包含。
#ifndef __STEP01_LEVEL_H__
// 头文件保护宏定义：和上面的 #ifndef 配套使用。
#define __STEP01_LEVEL_H__

// 声明日志库命名空间，避免和其他项目符号重名。
namespace bitlog_step01 {

// LogLevel 类：封装日志级别定义与字符串转换逻辑。
class LogLevel {
public:
    // 枚举类 value：表示日志级别，按严重程度递增。
    enum class value {
        // 未知级别，通常作为默认值或解析失败兜底值。
        UNKNOW = 0,
        // 调试级别：用于开发期排查细节。
        DEBUG,
        // 信息级别：记录正常流程关键节点。
        INFO,
        // 警告级别：记录潜在问题但程序可继续运行。
        WARN,
        // 错误级别：记录已发生错误，通常需要关注。
        ERROR,
        // 致命级别：记录严重错误，可能导致程序退出。
        FATAL,
        // 关闭级别：通常表示不输出任何日志。
        OFF
    };

    // toString：把枚举级别转换成可读字符串，便于格式化输出。
    static const char* toString(value l) {
        // 使用 switch 按枚举值分支处理。
        switch (l) {
            // 宏 TOSTRING：把标识符名字转成字符串字面量。
            #define TOSTRING(name) #name
            // 如果是 DEBUG，返回 "DEBUG"。
            case value::DEBUG: return TOSTRING(DEBUG);
            // 如果是 INFO，返回 "INFO"。
            case value::INFO: return TOSTRING(INFO);
            // 如果是 WARN，返回 "WARN"。
            case value::WARN: return TOSTRING(WARN);
            // 如果是 ERROR，返回 "ERROR"。
            case value::ERROR: return TOSTRING(ERROR);
            // 如果是 FATAL，返回 "FATAL"。
            case value::FATAL: return TOSTRING(FATAL);
            // 如果是 OFF，返回 "OFF"。
            case value::OFF: return TOSTRING(OFF);
            // 取消宏定义，避免污染后续代码。
            #undef TOSTRING
            // 其他未覆盖值统一返回 "UNKNOW"。
            default: return "UNKNOW";
        }
        // 理论上不会走到这里，保留是为了让控制流更完整。
        return "UNKNOW";
    }
};

// 命名空间结束。
} // namespace bitlog_step01

// 头文件保护宏结束。
#endif
