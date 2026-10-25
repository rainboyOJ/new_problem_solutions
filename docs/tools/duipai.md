# duipai.py

位置：

```text
scripts/problem-analysis-tools/duipai.py
```

作用：非交互式对拍工具，适合 Agent 和自动化调用。

## 基本用法

```bash
python3 scripts/problem-analysis-tools/duipai.py \
  --gen problems/luogu/P1001/gen.py \
  --user problems/luogu/P1001/main.cpp \
  --brute problems/luogu/P1001/brute.cpp \
  -n 200
```

## 默认约定

- `main.cpp`：待验证的正式解法。
- `brute.cpp`：朴素正确解。
- `gen.py`：当前题目的随机数据生成器。

脚本会自动编译 `.cpp`，Python 文件用 `python3` 运行。

## 输出位置

失败样例默认保存到：

```text
problems/<oj>/<problem_id>/duipai-failed/
```

对拍报告默认写到：

```text
problems/<oj>/<problem_id>/problem-analysis-workspace/duipai-report.md
```

## 常用参数

- `-n, --count`：对拍次数。
- `--timeout`：单次运行超时时间（gen、user、brute 各算一次，默认 2 秒）。
- `--deadline`：**整轮对拍总时限**（秒，默认 `0` 表示不限）。从编译/准备阶段开始计时，预算用尽后不再开新用例，写出报告并返回 `3`；已开跑的那组仍由 `--timeout` 收尾，所以超额最多一组用例的三次运行。
- `-m, --memory-mb`：用户程序和 brute 的内存判定线。
- `--memory-guard-mb`：内部硬限制保护余量，默认 `16`。
- `--checker`：special judge，接口为 `checker input.txt user.out brute.out`。
- `--eps`：浮点输出容差比较。
- `--seed`：基础随机种子，会通过 `DUPAI_SEED` 传给生成器环境变量。
- `--report`：指定报告路径。
- `--failed-dir`：指定失败样例目录。
- `--strict`：严格逐字节比较输出。

## checker 接口

```bash
python3 checker.py input.txt user.out brute.out
```

- 退出码 `0`：通过。
- 非 `0`：失败。
- stdout/stderr 会写入失败样例的 `meta.json`。

## 退出码

| 码 | 含义 |
| --- | --- |
| `0` | 全部通过 |
| `1` | 发现差异或运行异常，失败用例已保存 |
| `2` | 准备/编译失败，或参数错误 |
| `3` | `--deadline` 总时限用尽，报告已写出（不是提交的问题） |

## 资源状态优先级

```text
TIMEOUT > MEMORY_LIMIT > RUNTIME_ERROR > WRONG_ANSWER > PASS
```
