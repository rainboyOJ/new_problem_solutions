   1| # luogu P2910 [USACO08OPEN] Clear And Present Danger S
   2| 
   3| > 原文摘录，非模型摘要。来源：`problems/luogu/P2910/index.md`（内容哈希 dc7105b5c1157004）。
   4| > 摘录可能在 4000 字符处截断；作结论前必须能补读原文全文。
   5| 
   6| ## 元信息（frontmatter 摘录）
   7| - 难度：普及；标签：['Floyd', '最短路', 'python']
   8| 
   9| ## 题目解析（原文摘录）
  10| 
  11| [[TOC]]
  12| 
  13| ### 题意
  14| 
  15| 必须按给定顺序经过岛屿，求允许经过其他岛屿时的最小总危险值。
  16| 
  17| ### 思路
  18| 
  19| `n<=100`，用 Floyd 得到任意两岛最短路。序列相邻要求之间彼此独立，答案就是所有 `dist[A_i][A_{i+1}]` 之和。
  20| 
  21| ### Python 知识
  22| 
  23| - 一次 `read().split()` 配合整数迭代器读取矩阵。
  24| - 缓存 `row`、`through` 减少三重循环索引开销。
  25| - `zip(required, required[1:])` 枚举相邻序列元素。
  26| 
  27| ### 代码
  28| 
  29| @include-code(./main.py, python)
  30| 
  31| 原有 C++ 版本仍保留：
  32| 
  33| @include-code(./main.cpp, cpp)
  34| 
  35| ### 复杂度
  36| 
  37| 时间 `O(n^3+M)`，空间 `O(n^2)`。
  38| 
  39| ### 总结
  40| 
  41| 访问顺序固定时，先把每一段替换为两点最短路即可独立求和。
  42| 
  43| ## 代码位置
  44| - `problems/luogu/P2910/brute.cpp`
  45| - `problems/luogu/P2910/gen.py`
  46| - `problems/luogu/P2910/main.cpp`
  47| - `problems/luogu/P2910/main.py`