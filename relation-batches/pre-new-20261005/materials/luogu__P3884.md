   1| # luogu P3884 [JLOI2009] 二叉树问题
   2| 
   3| > 原文摘录，非模型摘要。来源：`problems/luogu/P3884/index.md`（内容哈希 6af01aebd8a5a0f8）。
   4| > 摘录可能在 4000 字符处截断；作结论前必须能补读原文全文。
   5| 
   6| ## 元信息（frontmatter 摘录）
   7| - 难度：普及/提高-；标签：['二叉树', 'BFS', 'LCA', 'python']
   8| 
   9| ## 题目解析（原文摘录）
  10| 
  11| [[TOC]]
  12| 
  13| ### 题意
  14| 
  15| 给出根为 `1` 的树，求最大深度、最大层宽，以及指定 `x` 到 `y` 的特殊距离：向根方向每条边代价 `2`，向叶方向每条边代价 `1`。
  16| 
  17| ### 思路
  18| 
  19| BFS 从根计算每个节点深度；相同深度的节点数用 `Counter` 统计，最大频率就是宽度。
  20| 
  21| 求距离时，先把 `x` 到根的全部祖先放入集合，再让 `y` 沿父指针上升，第一个属于集合的节点就是 LCA。于是：
  22| 
  23| $$
  24| 2(depth_x-depth_{lca})+(depth_y-depth_{lca})
  25| $$
  26| 
  27| ### Python 知识
  28| 
  29| - `Counter(depth[1:])` 直接统计每层节点数。
  30| - 祖先集合提供平均 $O(1)$ 成员判断，适合 `n<=100` 的朴素 LCA。
  31| - `print(...,sep="\n")` 一次输出三个独立答案。
  32| - `/home/rainboy/mycode/hugo-blog/content/program_language/python/collections_toolkit.md`：`Counter`、集合与 `deque`。
  33| - `/home/rainboy/mycode/hugo-blog/content/program_language/python/bfs_shortest.md`：层次 BFS。
  34| 
  35| ### 代码
  36| 
  37| @include-code(./main.py, python)
  38| 
  39| @include-code(./main.cpp, cpp)
  40| 
  41| 
  42| ### 复杂度
  43| 
  44| BFS 与两条祖先链均为 $O(n)$，空间复杂度 $O(n)$。
  45| 
  46| ### 总结
  47| 
  48| 树上距离先找 LCA 再拆成“向上段”和“向下段”；本题两种方向权值不同，不能直接用普通边数公式。
  49| 
  50| ## 代码位置
  51| - `problems/luogu/P3884/main.cpp`
  52| - `problems/luogu/P3884/main.py`