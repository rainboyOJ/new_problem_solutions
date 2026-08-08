# check_sample.py

位置：

```text
scripts/problem-analysis-tools/check_sample.py
```

作用：编译并运行题目目录中的样例和本地数据，自动 diff 输出。

## 基本用法

在题目目录中直接运行：

```bash
python3 ../../../scripts/problem-analysis-tools/check_sample.py
```

从项目根目录指定题目目录：

```bash
python3 scripts/problem-analysis-tools/check_sample.py problems/luogu/P1001
```

指定源文件和超时时间：

```bash
python3 scripts/problem-analysis-tools/check_sample.py problems/luogu/P1001 --source main.cpp --timeout 2
```

指定时间和内存限制：

```bash
python3 scripts/problem-analysis-tools/check_sample.py problems/luogu/P1001 --timeout 1 --memory-mb 256
python3 scripts/problem-analysis-tools/check_sample.py problems/luogu/P1001 -m 256 --memory-guard-mb 16
```

## 默认规则

- 无参数时使用当前工作目录。
- 默认先找 `main.cpp`，没有则回退到 `1.cpp`。
- C++ 编译产物放在 `/tmp/problem-analysis-sample/`。
- `.py` 源文件用 `python3` 运行。
- 不传 `--memory-mb` 时，只检查时间和输出，不检查内存。
- 传入 `--memory-mb 256` 时，判定线是 256MB，内部硬限制默认是 `256 + 16` MB。

## 数据识别

支持：

```text
in/out
in1/out1
in2/out2
data/*.in + data/*.out
data/*.in + data/*.ans
```

如果只有输入没有答案，会运行程序并标记为 `NO_ANSWER`。

## 退出码

- `0`：没有失败样例。
- `1`：存在 diff 失败、运行错误或超时。
- `2`：准备阶段失败，例如找不到目录、源文件或样例数据。

## 资源限制

时间限制使用：

```bash
--timeout 2
```

内存限制使用：

```bash
--memory-mb 256
```

内部会额外加一个保护余量：

```bash
--memory-guard-mb 16
```

例如 `--memory-mb 256 --memory-guard-mb 16` 会给子进程设置 272MB 的硬限制，但最终仍按 peak RSS 是否超过 256MB 判定 `MEMORY_LIMIT`。

资源状态优先级：

```text
TIMEOUT > MEMORY_LIMIT > RUNTIME_ERROR > FAIL > PASS > NO_ANSWER
```

内存限制只作用于运行程序，不限制 C++ 编译过程。
