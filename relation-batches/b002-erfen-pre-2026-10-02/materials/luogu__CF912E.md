# luogu CF912E Prime Gift

> 原文摘录，非模型摘要。来源：`problems/luogu/cf912e/index.md`。

## 元信息（frontmatter 摘录）
- 难度：省选/NOI-；标签：['Meet-in-the-Middle', '二分答案', '数论']

## 题目解析（原文摘录）

### 题意

给定至多 16 个质数，求所有质因子都来自该集合的第 `k` 小正整数，答案不超过 $10^{18}$。完整教学解析（含 Python 版本与思考过程）已迁移至：

- [[problem: codeforces,912E]] · [CF912E Prime Gift 题解](https://codeforces.com/problemset/problem/912/E)

### 思路

把质数交错分到两组，分别 DFS 枚举不超过 $10^{18}$ 的乘积；二分答案 `limit`，用只向左移动的右指针统计 `left[i] * right[j] <= limit` 的配对数。乘法比较写成 `left > limit / right`，避免 64 位溢出。

## 代码位置
- `problems/luogu/cf912e/brute.cpp`
- `problems/luogu/cf912e/gen.py`
- `problems/luogu/cf912e/main.cpp`
