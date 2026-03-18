#include <iostream>
#include "logger.hpp"
#include "sink.hpp"
#include "Formatter.hpp"

int main() {
    // 创建格式化器
    lwlog::Formatter::ptr formatter = std::make_shared<lwlog::Formatter>("[%d{%Y-%m-%d %H:%M:%S}][%p][%c][%f:%l] %m%n");

    // 创建滚动落地 sink
    std::vector<lwlog::LogSink::ptr> sinks;
    sinks.push_back(std::make_shared<lwlog::RollBySink>("async-log", 1024));

    // 创建异步日志器
    lwlog::AsyncLogger logger("async_logger", lwlog::Loglevel::level::DEBUG, formatter, sinks, lwlog::AsyncType::ASYNC_SAFE);

    // 测试不同级别的日志
    logger.debug(__FILE__, __LINE__, "This is a debug message: %s", "debug");
    logger.info(__FILE__, __LINE__, "This is an info message: %d", 42);
    logger.warn(__FILE__, __LINE__, "This is a warning message: %f", 3.14);
    logger.error(__FILE__, __LINE__, "This is an error message: %s", "error occurred");
    logger.fatal(__FILE__, __LINE__, "This is a fatal message: %s", "fatal error");

    std::cout << "异步日志器测试完成" << std::endl;
    return 0;
}