# luogu P1163 银行贷款

> 原文摘录，非模型摘要。来源：`problems/luogu/P1163/index.md`（内容哈希 d37bb7b7c25c1a23）。

## 元信息（frontmatter 摘录）
- 难度：普及/提高-；标签：["二分答案", "模拟", "数学", "python"]

## 题目解析（原文摘录）

[[TOC]]

### 题意

已知贷款本金、每月还款额和还清所需月数，求按月累计的利率，以百分数输出并保留一位小数。

### 思路

给定小数形式的月利率 `rate`，每个月结束后的余额是：

```text
balance = balance * (1 + rate) - payment
```

利率越高，最后剩余余额越大。于是可在题目保证的 `[0,3]` 范围内二分：最终余额不大于零时利率还可以提高，否则应降低。

浮点二分固定执行 100 次，精度足够覆盖 `0.1%` 的输出要求。

### Python 知识

- Python 可以直接混合整数输入和浮点计算，无需显式类型转换本金。
- 固定次数浮点二分结构稳定，不依赖 `while right-left > eps` 的阈值选择。
- `f"{left * 100:.1f}"` 同时完成小数转百分数和保留一位小数。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/oj_input_output_cheatsheet.md`：浮点格式化输出。

### 代码

@include-code(./main.py, python)

@include-code(./main.cpp, cpp)

### 复杂度

每次判定模拟 `m` 个月，总时间复杂度为 $O(100m)=O(m)$，空间复杂度为 $O(1)$。

### 总结

先写出“给定利率后余额如何变化”，再观察最终余额对利率单调递增，就能把反求利率转成浮点二分。

## 代码位置
- `problems/luogu/P1163/main.cpp`
- `problems/luogu/P1163/main.py`
