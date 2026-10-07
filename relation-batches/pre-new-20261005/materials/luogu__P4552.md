   1| # luogu P4552 [Poetize6] IncDec Sequence
   2| 
   3| > 原文摘录，非模型摘要。来源：`problems/luogu/P4552/index.md`（内容哈希 ac975dc4f8ebe7d1）。
   4| > 摘录可能在 4000 字符处截断；作结论前必须能补读原文全文。
   5| 
   6| ## 元信息（frontmatter 摘录）
   7| - 难度：普及+/提高；标签：['差分', '贪心', 'python']
   8| 
   9| ## 题目解析（原文摘录）
  10| 
  11| [[TOC]]
  12| 
  13| ### 题意
  14| 
  15| 每次给一个区间整体加一或减一，求把序列变成常数序列的最少操作数，以及最少操作下可能的最终常数个数。
  16| 
  17| ### 思路
  18| 
  19| 只看相邻差 `a[i]-a[i-1]`。设所有正差之和为 `positive`，所有负差绝对值之和为 `negative`。一次操作最多同时消去一份正差和一份负差，剩余部分再与序列外侧配对，因此最少操作是两者最大值。
  20| 
  21| 未配对的 `abs(positive-negative)` 份操作可以分配到左右边界，最终常数共有 `abs(positive-negative)+1` 种。
  22| 
  23| ### Python 知识
  24| 
  25| - `pairwise(sequence)` 直接产生所有相邻元素对。
  26| - 两个生成器分别求正向、负向变化量，公式与代码一一对应。
  27| - Python 整数自动扩容，不需要 C++ 的 `long long` 类型选择。
  28| 
  29| ### 代码
  30| 
  31| @include-code(./main.py, python)
  32| 
  33| ### 复杂度
  34| 
  35| 时间复杂度 $O(n)$，空间复杂度 $O(n)$。
  36| 
  37| ### 总结
  38| 
  39| 区间整体变化在差分数组中只影响边界，问题最终只剩正负变化量如何配对。
  40| 
  41| ## 代码位置
  42| - `problems/luogu/P4552/brute.cpp`
  43| - `problems/luogu/P4552/gen.py`
  44| - `problems/luogu/P4552/main.cpp`
  45| - `problems/luogu/P4552/main.py`