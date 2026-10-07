   1| # luogu P3403 跳楼机
   2| 
   3| > 原文摘录，非模型摘要。来源：`problems/luogu/P3403/index.md`（内容哈希 c3acea516482ecbb）。
   4| > 摘录可能在 4000 字符处截断；作结论前必须能补读原文全文。
   5| 
   6| ## 元信息（frontmatter 摘录）
   7| - 难度：提高；标签：['同余最短路', 'Dijkstra', '数学', 'python']
   8| 
   9| ## 题目解析（原文摘录）
  10| 
  11| [[TOC]]
  12| 
  13| ### 题意
  14| 
  15| 从 1 楼反复增加 `x/y/z`，统计不超过 `h` 的可达楼层数。
  16| 
  17| ### 思路
  18| 
  19| 取最小步长 `base`。对每个模 `base` 的余数，Dijkstra 求能到达的最小楼层 `dist[r]`；此后反复加 `base`，同余且更高的楼层全部可达，贡献为 `(h-dist[r])//base+1`。
  20| 
  21| ### Python 知识
  22| 
  23| - 余数图只有 `min(x,y,z)` 个节点。
  24| - Python 整数直接支持 `2^63` 范围楼层。
  25| - 生成器求和只统计 `dist<=h` 的余数。
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
  37| 设 `b=min(x,y,z)`，时间 `O(b log b)`，空间 `O(b)`。
  38| 
  39| ### 总结
  40| 
  41| 巨大数值范围加少量固定步长，常压缩成“每个余数的最小代表”。
  42| 
  43| ## 代码位置
  44| - `problems/luogu/P3403/brute.cpp`
  45| - `problems/luogu/P3403/gen.py`
  46| - `problems/luogu/P3403/main.cpp`
  47| - `problems/luogu/P3403/main.py`