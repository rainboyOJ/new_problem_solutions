# shrink_failed.py

位置：

```text
scripts/problem-analysis-tools/shrink_failed.py
```

作用：对 `duipai.py` 保存的失败输入做缩小，帮助更快看出反例结构。

## 当前支持范围

第一版支持这种输入格式：

```text
n
a1 a2 a3 ... an
```

也就是“第一行 n，第二行数组”的常见数组题。

## 基本用法

在题目目录中运行：

```bash
python3 ../../../scripts/problem-analysis-tools/shrink_failed.py
```

默认读取：

```text
duipai-failed/input.txt
```

默认输出：

```text
duipai-failed/input.shrunk.txt
duipai-failed/shrink-report.md
```

指定程序：

```bash
python3 scripts/problem-analysis-tools/shrink_failed.py \
  --failed-dir problems/luogu/P1001/duipai-failed \
  --user problems/luogu/P1001/main.cpp \
  --brute problems/luogu/P1001/brute.cpp
```

## 常用参数

- `--failed-dir`：失败样例目录，默认 `duipai-failed`。
- `--input`：指定输入文件。
- `--output`：指定缩小后的输出文件。
- `--user`：待验证程序，默认 `main.cpp`。
- `--brute`：朴素正确解，默认 `brute.cpp`。
- `--timeout`：单次运行时间限制。
- `--strict`：严格输出比较。
- `--eps`：浮点容差比较。

