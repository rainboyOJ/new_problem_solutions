# problem_status.py

位置：

```text
scripts/problem-analysis-tools/problem_status.py
```

作用：在一个题目目录中汇总当前写题状态，并给出下一步建议。

## 基本用法

在题目目录中运行：

```bash
python3 ../../../scripts/problem-analysis-tools/problem_status.py
```

从项目根目录指定题目：

```bash
python3 scripts/problem-analysis-tools/problem_status.py problems/luogu/P1001
```

同时运行样例检查：

```bash
python3 scripts/problem-analysis-tools/problem_status.py problems/luogu/P1001 --run-sample
```

## 检查内容

- `index.md`
- `main.cpp`
- `brute.cpp`
- `gen.py`
- `problem-analysis-workspace/`
- 根目录 `in/out` 或 `data/*.in`
- `check_problem.py` 规范检查结果

## 常用参数

- `--run-sample`：额外调用 `check_sample.py`。
- `--timeout`：传给样例检查的时间限制。
- `--memory-mb`：传给样例检查的内存限制。

