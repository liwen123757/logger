// 引入断言库，用来做最小化单元验证。
#include <cassert>
// 引入字符串比较支持。
#include <string>
// 引入 iostream 打印测试结果。
#include <iostream>
// 引入教学版 LogMsg 定义。
#include "step02_message.hpp"

// 程序入口：执行 Step02 的自测。
int main() {
    // 简化类型名书写。
    using bitlog_step02::LogLevel;
    // 简化类型名书写。
    using bitlog_step02::LogMsg;

    // 构造一条测试日志。
    LogMsg msg("root", "main.cpp", 42, "hello-bitlog", LogLevel::value::INFO);

    // 验证日志器名称是否正确保存。
    assert(msg.logger_name == "root");
    // 验证文件名是否正确保存。
    assert(msg.file_name == "main.cpp");
    // 验证行号是否正确保存。
    assert(msg.line == 42);
    // 验证正文是否正确保存。
    assert(msg.payload == "hello-bitlog");
    // 验证级别是否正确保存。
    assert(msg.level == LogLevel::value::INFO);
    // 验证时间戳非零（通常当前时间都大于 0）。
    assert(msg.ctime > 0);

    // 输出通过信息。
    std::cout << "step02_message_test passed" << std::endl;
    // 正常返回。
    return 0;
}
