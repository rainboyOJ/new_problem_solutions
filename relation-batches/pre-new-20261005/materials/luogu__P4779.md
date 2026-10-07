   1| # luogu P4779 【模板】单源最短路径（标准版）
   2| 
   3| > 原文摘录，非模型摘要。来源：`problems/luogu/P4779/index.md`（内容哈希 805b5bbd14e70fce）。
   4| > 摘录可能在 4000 字符处截断；作结论前必须能补读原文全文。
   5| 
   6| ## 元信息（frontmatter 摘录）
   7| - 难度：普及+/提高-；标签：['Dijkstra', '最短路', 'heapq', 'python']
   8| 
   9| ## 题目解析（原文摘录）
  10| 
  11| [[TOC]]
  12| 
  13| ### 题意
  14| 
  15| 求非负权有向图中起点到每个节点的最短距离。
  16| 
  17| ### 思路
  18| 
  19| Dijkstra 每次从堆中取当前距离最小的状态，尝试松弛所有出边。堆中可能保留旧状态，若弹出的距离不等于数组中的最新距离就跳过。
  20| 
  21| ### Python 知识
  22| 
  23| - `heapq` 是最小堆，元组按距离优先比较。
  24| - `current != distance[node]` 是无 decrease-key 堆的标准过期判断。
  25| - `print(*distance[1:])` 直接输出一行结果。
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
  37| 时间 `O((n+m)log n)`，空间 `O(n+m)`。
  38| 
  39| ### 总结
  40| 
  41| 非负边权优先使用堆优化 Dijkstra。
  42| 
  43| ## 代码位置
  44| - `problems/luogu/P4779/brute.cpp`
  45| - `problems/luogu/P4779/gen.py`
  46| - `problems/luogu/P4779/main.cpp`
  47| - `problems/luogu/P4779/main.py`