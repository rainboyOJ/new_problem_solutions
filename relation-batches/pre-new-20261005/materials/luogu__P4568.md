   1| # luogu P4568 [JLOI2011] 飞行路线
   2| 
   3| > 原文摘录，非模型摘要。来源：`problems/luogu/P4568/index.md`（内容哈希 07b44e9d368adbce）。
   4| > 摘录可能在 4000 字符处截断；作结论前必须能补读原文全文。
   5| 
   6| ## 元信息（frontmatter 摘录）
   7| - 难度：提高；标签：['分层图', 'Dijkstra', '状态扩展', 'python']
   8| 
   9| ## 题目解析（原文摘录）
  10| 
  11| [[TOC]]
  12| 
  13| ### 题意
  14| 
  15| 无向图中最多让 `k` 条边免费，求起点到终点的最低花费。
  16| 
  17| ### 思路
  18| 
  19| 状态 `(city, used)` 表示已使用 `used` 次免费机会。走一条边既可付费留在本层，也可花一次机会以 0 代价进入下一层；所有新边权仍非负，直接运行 Dijkstra。
  20| 
  21| ### Python 知识
  22| 
  23| - 二维列表 `distance[used][city]` 对应分层图。
  24| - 堆元组 `(cost, city, used)` 自然按费用排序。
  25| - `min(layer[target] for layer in distance)` 允许免费次数少于 `k`。
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
  37| 时间 `O(k(n+m)log(kn))`，空间 `O(kn+m)`。
  38| 
  39| ### 总结
  40| 
  41| “最多使用若干次能力”通常把使用次数加入状态分层。
  42| 
  43| ## 代码位置
  44| - `problems/luogu/P4568/brute.cpp`
  45| - `problems/luogu/P4568/gen.py`
  46| - `problems/luogu/P4568/main.cpp`
  47| - `problems/luogu/P4568/main.py`