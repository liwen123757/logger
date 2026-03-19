// 引入 bitlog 的统一头文件，包含日志器、格式化器、落地器等核心能力。
#include "../logs/bitlog.h"

// 传入日志器名称，演示一次完整的日志输出流程。
void loggerTest(const std::string &logger_name) {
    // 通过日志管理器按名称获取日志器。
    bitlog::Logger::ptr lp = bitlog::getLogger(logger_name);
    // 运行时断言：日志器必须存在，否则说明构建阶段有问题。
    assert(lp.get());

    // 使用 root 日志器打印分隔线（宏会自动带上文件名与行号）。
    LOGF("------------example--------------------");

    // 直接调用 Logger 成员函数输出不同级别日志。
    lp->debug("%s", "logger->debug");
    // 输出 INFO 级别日志。
    lp->info("%s", "logger->info");
    // 输出 WARN 级别日志。
    lp->warn("%s", "logger->warn");
    // 输出 ERROR 级别日志。
    lp->error("%s", "logger->error");
    // 输出 FATAL 级别日志。
    lp->fatal("%s", "logger->fatal");

    // 使用通用宏输出 DEBUG 级别日志（与成员函数等价）。
    LOG_DEBUG(lp, "%s", "LOG_DEBUG");
    // 使用通用宏输出 INFO 级别日志。
    LOG_INFO(lp, "%s", "LOG_INFO");
    // 使用通用宏输出 WARN 级别日志。
    LOG_WARN(lp, "%s", "LOG_WARN");
    // 使用通用宏输出 ERROR 级别日志。
    LOG_ERROR(lp, "%s", "LOG_ERROR");
    // 使用通用宏输出 FATAL 级别日志。
    LOG_FATAL(lp, "%s", "LOG_FATAL");

    // 使用 root 日志器打印结束分隔线。
    LOGF("---------------------------------------");

    // 压测前缀：用于构造大量日志内容。
    std::string log_msg = "hello bitejiuyeke-";
    // 文件大小变量（这里保留作扩展演示，当前未使用）。
    size_t fsize = 0;
    // 计数器：控制压测日志条数。
    size_t count = 0;
    // 连续写入 100 万条日志，观察异步日志吞吐。
    while (count < 1000000) {
        // 生成带序号的消息，避免每条日志完全相同。
        std::string msg = log_msg + std::to_string(count++);
        // 以 ERROR 级别写入，触发格式化与落地流程。
        lp->error("%s", msg.c_str());
    }

    // 显式标记 fsize 未使用，避免编译器告警。
    (void)fsize;
}

// 功能测试：配置一个“多落地 + 异步”日志器并运行 loggerTest。
void functional_test() {
    // 创建全局日志器构建器：构建完成后会注册到 loggerManager。
    bitlog::GlobalLoggerBuilder::ptr lbp(new bitlog::GlobalLoggerBuilder);

    // 设置日志器名称（后续 getLogger 通过该名称获取）。
    lbp->buildLoggerName("all_sink_logger");
    // 设置格式串：时间、名称、文件行号、级别、正文、换行。
    lbp->buildFormatter("[%d][%c][%f:%l][%p] %m%n");
    // 设置最低日志等级为 DEBUG。
    lbp->buildLoggerLevel(bitlog::LogLevel::value::DEBUG);
    // 添加标准输出落地器。
    lbp->buildSink<bitlog::StdoutSink>();
    // 添加普通文件落地器（单文件持续追加）。
    lbp->buildSink<bitlog::FileSink>("./logs/sync.log");
    // 添加滚动文件落地器（超过 10MB 自动切换新文件）。
    lbp->buildSink<bitlog::RollSink>("./logs/roll-", 10 * 1024 * 1024);
    // 设置日志器类型为异步。
    lbp->buildLoggerType(bitlog::Logger::Type::LOGGER_ASYNC);
    // 执行 build：真正创建并注册日志器。
    lbp->build();

    // 执行日志输出测试。
    loggerTest("all_sink_logger");
}

// 程序入口。
int main(int argc, char *argv[]) {
    // 标记参数未使用，避免编译告警。
    (void)argc;
    (void)argv;

    // 运行功能测试。
    functional_test();
    // 正常退出。
    return 0;
}
