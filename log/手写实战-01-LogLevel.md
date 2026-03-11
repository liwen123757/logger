# 手写实战 01：LogLevel（逐行注释版）

这一关目标：你自己手写出“日志级别 + 级别转字符串”。

## 你要看的文件

- `log/exercise/step01_level.hpp`：教学版本，几乎每行都带注释。
- `log/exercise/step01_level_test.cpp`：最小测试程序。

## 本关知识点

- `enum class` 的作用与好处（强类型、避免污染）。
- `switch + case` 做枚举分发。
- 用宏 `#name` 把标识符变成字符串（字符串化）。
- 默认分支作为兜底（防御式编程）。

## 建议练习

1. 先不看答案，自己写一遍 `toString`。
2. 把 `WARN` 注释掉试试，观察测试如何失败。
3. 给它再加一个反向函数 `fromString("INFO")`。

## 编译与运行

```bash
g++ -std=c++11 -g log/exercise/step01_level_test.cpp -o /tmp/step01_level_test
/tmp/step01_level_test
```
