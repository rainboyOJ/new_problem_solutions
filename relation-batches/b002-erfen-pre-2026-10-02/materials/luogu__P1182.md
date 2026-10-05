# luogu P1182 数列分段 Section II

> 原文摘录，非模型摘要。来源：`problems/luogu/P1182/index.md`。

## 元信息（frontmatter 摘录）
- 难度：普及/提高-；标签：['二分答案', '贪心', 'python']

## 题目解析（原文摘录）

### 题意

给定一个正整数序列，要把它分成 `M` 段，每段连续。

要求最小化所有段中最大的段和。

### 思路

先看一个可以直接验证想法的朴素解：

@include-code(./brute.cpp, cpp)

暴力 DP 可以枚举分段点，但数据范围更适合二分答案。

设答案上限为 `limit`。我们只需要判断：能否把序列分成不超过 `M` 段，并且每段和都不超过 `limit`。

检查方法很简单：从左到右扫描，当前段能放就继续放；如果再放会超过 `limit`，就新开一段。

这样得到的是在 `limit` 限制下的最少段数。如果最少段数不超过 `M`，说明 `limit` 可行；否则不可行。

可行性随 `limit` 增大而单调变好，所以可以二分最小可行值。

## 代码位置
- `problems/luogu/P1182/brute.cpp`
- `problems/luogu/P1182/gen.py`
- `problems/luogu/P1182/main.cpp`
- `problems/luogu/P1182/main.py`
