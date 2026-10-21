---
name: oj-judge-and-stress
description: >-
  Verify OJ solutions in this repository with roj-local-judge instead of
  hand-rolled scripts. Use whenever a task needs to run samples or testdata,
  compare main.cpp against main.py or brute.cpp, do stress testing or 对拍,
  measure time and memory, judge recursion depth against the stack limit, or
  report AC/WA/TLE/MLE/RE/CE. Do not build ad-hoc runners, shell loops over
  ulimit, or bespoke diff scripts.
---

# OJ 评测与对拍

本库所有 OJ 代码的验证统一走 `roj-local-judge`。**不要自己造评测脚本**：不手写 shell 循环比对输出，不用 `ulimit -s` 试探栈限制，不用临时 Python 脚本拼 `subprocess` 做对拍。

这个 skill 只管“怎么验证”，不管代码风格（见 `oj-cpp-style` / `oj-python-style`），也不管题解写作。

## 找到工具

```sh
roj-local-judge-lite --help              # 启动器，通常已装好
ls ~/.local/share/roj-local-judge-lite/judge.py
```

程序本体是 `judge.py`。`~/.local/share/roj-local-judge-lite` 应为指向源码仓库的符号链接，这样安装版与源码版就是同一份，不会出现“本地都支持 `--data-dir`、安装版却报 `unrecognized arguments`”的情况。确认：

```sh
readlink -f ~/.local/share/roj-local-judge-lite   # 应指向源码目录
```

C++ 用 `g++ -std=c++17 -O2 -DONLINE_JUDGE` 编译，Python 用 `py_compile` 检查语法。

## 三种验证任务

### 一、跑样例与测试点

```sh
# 题库布局：<testdata>/<pid>/data/*.in|*.out
roj-local-judge-lite problems/luogu/P1234/main.cpp --pid P1234 --testdata /path/to/testData

# 任意配对目录：直接给含 .in/.out 的目录
roj-local-judge-lite problems/luogu/P1234/main.cpp --data-dir /tmp/cases

# 零散文件：答案默认取同名 .out
roj-local-judge-lite main.cpp --case a.in --case b.in
```

C++ 与 Python 用同一组参数，只换源文件。`--data-dir`、`--case`、`--pid/--testdata` 三者互斥。

### 二、对拍

对拍 = 用 `gen.py` 造数据，让 `brute` 产出答案，再让 `main` 与 `brute` 各自过一遍判题器，比较 **verdict**。

```sh
mkdir -p /tmp/stress
# 1. 造输入
for i in $(seq 1 300); do python3 gen.py > /tmp/stress/$i.in; done
# 2. 让独立实现产出答案（brute 只适合小数据，正好用来判 main）
g++ -O2 -o /tmp/brute brute.cpp
for i in $(seq 1 300); do /tmp/brute < /tmp/stress/$i.in > /tmp/stress/$i.out; done
# 3. main.cpp 与 main.py 都判一遍，必须都 AC
roj-local-judge-lite main.cpp --data-dir /tmp/stress
roj-local-judge-lite main.py  --data-dir /tmp/stress
```

组数不少于 300，覆盖最小规模、边界值、负数权、无解情形。`main.cpp` 与 `main.py` 两个都 AC 才算通过。

### 三、递归深度

递归写法（DFS、Tarjan、树剖、点分治）**不需要预防性地改成显式栈**。判题器默认给 **64 MB 栈**（`--stack` 可改，`0` 表示沿用继承的 rlimit），远大于本机 shell 常见的 8 MB，所以拿本机 `ulimit -s` 推出来的“会爆栈”结论经常是错的。

要确认是否安全，构造最深递归的输入（如 1 到 n 的链）并显式给栈上限：

```sh
roj-local-judge-lite main.cpp --case /tmp/deep_chain.in --stack 8
```

真实测得的数据（递归 Tarjan，$n=10^5$ 长链）：

| `--stack` | 结果 |
| --- | --- |
| 2 MiB | RE，signal 11 |
| 4 MiB | RE，signal 11 |
| 8 MiB | AC |
| 64 MiB（默认） | AC |

所以“$10^5$ 深度的递归会不会爆”是一个可以用 `--stack` 直接量出来的数，不需要猜。

### 判读崩溃信号

| signal | 含义 | 典型原因 |
| --- | --- | --- |
| 11 | `SIGSEGV` | 栈溢出写到保护区外 |
| 6 | `SIGABRT` | `std::bad_alloc`、`assert`、堆破坏 |

**看到 signal 6 不要当成栈溢出。** 常见真实原因是数组越界把堆写坏了，例如 `MAXN = 100000 + 5` 却给了 $n = 2\times10^5$ 的数据，这时加 `--stack` 完全无用（实测 8/64/128 MiB 都一样 RE），应先核对输入规模与数组上界。

## 读结果

需要程序化读取时一律加 `--output-format json`（stdout 只有 JSON，进度信息走 stderr）：

```sh
roj-local-judge-lite main.cpp --data-dir /tmp/stress --output-format json \
  | python3 -c 'import json,sys;d=json.load(sys.stdin);print(d["verdict"],d["passed"],"/",d["total"])'
```

| 字段 | 注意 |
| --- | --- |
| `verdict` | `AC` / `WA` / `TLE` / `MLE` / `RE` / `CE` / `SE` |
| `isolation.mode` | 必须是 `cgroup`；为 `degraded` 时 **MLE 不可信** |
| `memory_peak_bytes` | 可能是 `null`，表示未测量，不等于 0 |
| `cases[].cpu_time_us`、`memory_peak_bytes` | 精确判据；`cpu_time_ms`、`memory_kb` 是展示位 |
| `SE` | 评测设施故障，不是提交的问题 |

`--data-dir` 的点若无 `.out`，`verdict` 会是 `NO_ANSWER`（仅表示没有可比答案），此时读程序输出或改用 `--case-out`。

## 常用参数

```sh
--time 2000 --memory 256   # 覆盖题目限制（ms / MiB）
--stack 8                  # 栈上限 MiB，默认 64；0 表示沿用继承的 rlimit
--no-cgroup                # 跳过 cgroup（此时无法判定 MLE）
--keep-work-dir            # 保留工作目录，case-N/_judge.stdout 是程序输出
--checker none             # 强制按行比较
--list                     # 列出 testdata 下可用的题目
```

## 报告要求

说“验证通过”时必须给出可复现的证据：

- 实际执行的命令（含 `--data-dir` / `--pid --testdata` 与 `--time --memory` 覆盖值）
- `verdict` 与通过点数，例如 `AC 300/300`
- 对拍时说明数据来源与覆盖了哪些边界
- 涉及递归深度的结论，写出用的最深链输入与 `--stack` 值（例如「`--stack 8`，AC」）

不要用“我跑过了”“应该没问题”代替上面的内容，也不要把本机自测当成 OJ 判决。
