// 引入断言，用于验证测试结果是否符合预期。
#include <cassert>
// 引入 iostream，用于在控制台打印测试通过信息。
#include <iostream>
// 引入我们刚写的 step01 头文件。
#include "step01_level.hpp"

// main：执行最小化自测。
int main() {
    // 使用更短别名，减少后续代码长度。
    using bitlog_step01::LogLevel;

    // 校验 DEBUG 枚举是否能正确转成字符串。
    assert(std::string(LogLevel::toString(LogLevel::value::DEBUG)) == "DEBUG");
    // 校验 ERROR 枚举是否能正确转成字符串。
    assert(std::string(LogLevel::toString(LogLevel::value::ERROR)) == "ERROR");
    // 校验 UNKNOW 是否能走 default 分支并返回 "UNKNOW"。
    assert(std::string(LogLevel::toString(LogLevel::value::UNKNOW)) == "UNKNOW");

    // 所有断言通过后打印成功提示。
    std::cout << "step01_level_test passed" << std::endl;
    // 正常结束程序。
    return 0;
}
