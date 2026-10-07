   1| # luogu P3406 海底高铁
   2| 
   3| > 原文摘录，非模型摘要。来源：`problems/luogu/P3406/index.md`（内容哈希 2a5fc4571af10edd）。
   4| > 摘录可能在 4000 字符处截断；作结论前必须能补读原文全文。
   5| 
   6| ## 元信息（frontmatter 摘录）
   7| - 难度：普及/提高-；标签：['差分', '贪心', 'python']
   8| 
   9| ## 题目解析（原文摘录）
  10| 
  11| [[TOC]]
  12| 
  13| ### 题意
  14| 
  15| 按给定城市顺序旅行。每段相邻铁路可每次买纸票，也可支付固定费用购卡后享受单次低价，求最小总费用。
  16| 
  17| ### 思路
  18| 
  19| 一次从 `start` 到 `end` 的移动，会经过编号 `[min(start,end), max(start,end))` 的铁路段。用差分给这段经过次数整体加一，前缀还原后即可得到每段的总使用次数 `count`。
  20| 
  21| 各铁路段互不影响，逐段选择 `min(count*A, count*B+C)` 并求和。
  22| 
  23| ### Python 知识
  24| 
  25| - `pairwise(route)` 直接枚举相邻访问城市。
  26| - `sorted((start, end))` 一行处理双向移动。
  27| - `accumulate(difference)` 还原每段经过次数，参见 `/home/rainboy/mycode/hugo-blog/content/program_language/python/itertools_recipes.md`。
  28| 
  29| ### 代码
  30| 
  31| @include-code(./main.py, python)
  32| 
  33| ### 复杂度
  34| 
  35| 时间复杂度 $O(N+M)$，空间复杂度 $O(N+M)$。
  36| 
  37| ### 总结
  38| 
  39| 先把整条路线压缩成每段使用次数，购卡决策就变成互相独立的局部取最小值。
  40| 
  41| ## 代码位置
  42| - `problems/luogu/P3406/brute.cpp`
  43| - `problems/luogu/P3406/gen.py`
  44| - `problems/luogu/P3406/main.cpp`
  45| - `problems/luogu/P3406/main.py`