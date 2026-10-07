   1| # luogu P1364 医院设置
   2| 
   3| > 原文摘录，非模型摘要。来源：`problems/luogu/P1364/index.md`（内容哈希 5b48789f71f41f27）。
   4| > 摘录可能在 4000 字符处截断；作结论前必须能补读原文全文。
   5| 
   6| ## 元信息（frontmatter 摘录）
   7| - 难度：普及/提高-；标签：['树', 'BFS', '枚举', 'python']
   8| 
   9| ## 题目解析（原文摘录）
  10| 
  11| ### 题意
  12| 
  13| 树上每个节点有居民数。选择一个节点建医院，代价是所有节点人口乘到医院距离之和，求最小代价。
  14| 
  15| ### 思路
  16| 
  17| `n<=100`，直接枚举医院位置。对每个候选点 BFS 求到全树距离，再计算：
  18| 
  19| $$
  20| \sum population_i\times distance_i
  21| $$
  22| 
  23| 树中两点路径唯一，BFS 第一次到达的层数就是边数距离。取所有候选代价的最小值即可。
  24| 
  25| ### Python 知识
  26| 
  27| - 邻接表用列表推导式创建，每条父子边双向加入。
  28| - `map(total_distance,range(1,n+1))` 产生每个候选医院的代价，`min` 直接聚合。
  29| - `deque` 与距离列表完成单源 BFS。
  30| - `/home/rainboy/mycode/hugo-blog/content/program_language/python/bfs_shortest.md`：树也可视为无权图进行 BFS。
  31| - `/home/rainboy/mycode/hugo-blog/content/program_language/python/map_reduce_filter.md`：命名函数与 `map/min` 组合。
  32| 
  33| ## 代码位置
  34| - `problems/luogu/P1364/main.cpp`
  35| - `problems/luogu/P1364/main.py`