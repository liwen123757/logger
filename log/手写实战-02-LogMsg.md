# 手写实战 02：LogMsg（逐行注释版）

这一关目标：你手写出“单条日志对象”的标准数据结构。

## 你要看的文件

- `log/exercise/step02_message.hpp`：教学版 `LogMsg`，几乎每行注释。
- `log/exercise/step02_message_test.cpp`：最小验证程序。

## 本关你会掌握

- 一条日志最核心的字段应该包含什么。
- 为什么要记录线程 ID、时间戳、文件和行号。
- 构造函数初始化列表的写法与好处。

## 建议练习

1. 给 `LogMsg` 增加进程 ID 字段。
2. 把 `ctime` 改成毫秒级时间戳。
3. 再写一个“移动构造”版本，观察字符串拷贝差异。

## 编译与运行

```bash
g++ -std=c++11 -g log/exercise/step02_message_test.cpp -o /tmp/step02_message_test
/tmp/step02_message_test
```
