   1| # luogu CF912E Prime Gift
   2| 
   3| > 原文摘录，非模型摘要。来源：`problems/luogu/cf912e/index.md`（内容哈希 a76cc095b3ffe444）。
   4| > 摘录可能在 4000 字符处截断；作结论前必须能补读原文全文。
   5| 
   6| ## 元信息（frontmatter 摘录）
   7| - 难度：省选/NOI-；标签：['Meet-in-the-Middle', '二分答案', '数论']
   8| 
   9| ## 题目解析（原文摘录）
  10| 
  11| ### 题意
  12| 
  13| 给定至多 16 个质数，求所有质因子都来自该集合的第 `k` 小正整数，答案不超过 $10^{18}$。完整教学解析（含 Python 版本与思考过程）已迁移至：
  14| 
  15| - [[problem: codeforces,912E]] · [CF912E Prime Gift 题解](https://codeforces.com/problemset/problem/912/E)
  16| 
  17| ### 思路
  18| 
  19| 把质数交错分到两组，分别 DFS 枚举不超过 $10^{18}$ 的乘积；二分答案 `limit`，用只向左移动的右指针统计 `left[i] * right[j] <= limit` 的配对数。乘法比较写成 `left > limit / right`，避免 64 位溢出。
  20| 
  21| ## 代码位置
  22| - `problems/luogu/cf912e/brute.cpp`
  23| - `problems/luogu/cf912e/gen.py`
  24| - `problems/luogu/cf912e/main.cpp`