   1| # codeforces 19D Points
   2| 
   3| > 原文摘录，非模型摘要。来源：`problems/codeforces/19D/index.md`（内容哈希 9ce09de089888943）。
   4| > 摘录可能在 4000 字符处截断；作结论前必须能补读原文全文。
   5| 
   6| ## 元信息（frontmatter 摘录）
   7| - 难度：提高+/省选-；标签：['线段树', '树状数组', '坐标压缩', '二维查询', 'python']
   8| 
   9| ## 题目解析（原文摘录）
  10| 
  11| ### 题意
  12| 
  13| 动态加入、删除点；查询严格右上方的点，要求先取最小 `x`，再取该 `x` 下最小 `y`。
  14| 
  15| ### 思路
  16| 
  17| 先读完所有操作，压缩所有可能出现的 `x`，并为每个 `x` 收集可能的 `y`。每个 `x` 组用 Fenwick 维护当前点，外层线段树保存该组当前最大 `y`。查询时在线段树中找第一个 `x > query_x` 且最大 `y > query_y` 的组，再用组内 Fenwick 的前缀计数定位第一个大于 `query_y` 的 `y`。
  18| 
  19| ### Python 知识
  20| 
  21| - 离线读取请求后用 `sorted(set(...))` 和字典推导式完成坐标压缩。
  22| - Fenwick 的 `kth` 二进制提升可在计数树中找第 `k` 个活跃坐标。
  23| - `bisect_right` 表达严格大于边界，避免手写二分。
  24| 
  25| ## 代码位置
  26| - `problems/codeforces/19D/brute.cpp`
  27| - `problems/codeforces/19D/gen.py`
  28| - `problems/codeforces/19D/main.cpp`
  29| - `problems/codeforces/19D/main.py`