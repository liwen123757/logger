#include <iostream>
#include "level.hpp"
#include <assert.h>
#include "message.hpp"
#include "sink.hpp"
#include <fstream>
#include <memory>
#include "Formatter.hpp"
#include "logger.hpp"

int main()
{
    // 创建格式化器
    lwlog::Formatter::ptr formatter = std::make_shared<lwlog::Formatter>("[%d{%H:%M:%S}][%t][%p][%c][%f:%l] %m%n");

    // 创建 sinks
    std::vector<lwlog::LogSink::ptr> sinks;
    sinks.push_back(std::make_shared<lwlog::StdoutSink>());

    // 创建同步日志器
    lwlog::Logger::ptr logger = std::make_shared<lwlog::SyncLogger>("sync_logger", lwlog::Loglevel::level::DEBUG, formatter, sinks);

    // 测试不同级别的日志
    logger->debug(__FILE__, __LINE__, "This is a debug message: %s", "test");
    logger->info(__FILE__, __LINE__, "This is an info message: %d", 42);
    logger->warn(__FILE__, __LINE__, "This is a warning message: %f", 3.14);
    logger->error(__FILE__, __LINE__, "This is an error message: %s", "error occurred");
    logger->fatal(__FILE__, __LINE__, "This is a fatal message: %s", "fatal error");

    std::cout << "同步日志器测试通过" << std::endl;
    return 0;
}