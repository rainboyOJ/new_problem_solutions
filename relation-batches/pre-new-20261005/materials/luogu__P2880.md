   1| # luogu P2880 [USACO07JAN] Balanced Lineup G
   2| 
   3| > 原文摘录，非模型摘要。来源：`problems/luogu/P2880/index.md`（内容哈希 93c0327ed607b0d8）。
   4| > 摘录可能在 4000 字符处截断；作结论前必须能补读原文全文。
   5| 
   6| ## 元信息（frontmatter 摘录）
   7| - 难度：普及/提高-；标签：['ST表', '区间最值', 'python']
   8| 
   9| ## 题目解析（原文摘录）
  10| 
  11| [[TOC]]
  12| 
  13| ### 题意
  14| 
  15| 静态数组上回答大量区间最高值减最低值。
  16| 
  17| ### 思路
  18| 
  19| ST 表第 `level` 层保存长度 $2^{level}$ 区间的最小值或最大值。查询 `[l,r]` 时取 `level=floor(log2(length))`，用左右两个允许重叠的长度 $2^{level}$ 区间覆盖查询范围；`min/max` 满足幂等性，重叠不会影响答案。
  20| 
  21| ### Python 知识
  22| 
  23| - `array("i")` 紧凑保存各层数据，两个 ST 表总共只需 $O(n\log n)$ 个 32 位整数。
  24| - 生成器直接构造下一层数组，不创建额外列表。
  25| - 预处理 `logs[length]` 后，每次询问只做常数次下标访问。
  26| 
  27| ### 代码
  28| 
  29| @include-code(./main.py, python)
  30| 
  31| ### 复杂度
  32| 
  33| 预处理 $O(n\log n)$，每次查询 $O(1)$，空间 $O(n\log n)$。
  34| 
  35| ### 总结
  36| 
  37| 静态、可重叠的区间最值查询是 ST 表的标准使用场景。
  38| 
  39| ## 代码位置
  40| - `problems/luogu/P2880/1.cpp`
  41| - `problems/luogu/P2880/brute.cpp`
  42| - `problems/luogu/P2880/gen.py`
  43| - `problems/luogu/P2880/main.cpp`
  44| - `problems/luogu/P2880/main.py`