   1| # luogu P3916 图的遍历
   2| 
   3| > 原文摘录，非模型摘要。来源：`problems/luogu/P3916/index.md`（内容哈希 d779fa58389be87d）。
   4| > 摘录可能在 4000 字符处截断；作结论前必须能补读原文全文。
   5| 
   6| ## 元信息（frontmatter 摘录）
   7| - 难度：普及-；标签：['图论', '反图', 'DFS', 'python']
   8| 
   9| ## 题目解析（原文摘录）
  10| 
  11| [[TOC]]
  12| 
  13| ### 题意
  14| 
  15| 对有向图中的每个点 `v`，求从 `v` 出发能够到达的最大编号。
  16| 
  17| ### 思路
  18| 
  19| 从每个点各做一次搜索会达到 $O(n(n+m))$。把问题反过来：原图中 `v` 能到达 `x`，等价于反图中 `x` 能到达 `v`。
  20| 
  21| 按 `n,n-1,...,1` 枚举候选最大编号 `largest`，从它在反图中搜索。凡是首次访问到的点，其答案就是 `largest`：
  22| 
  23| - 它在原图中可以到达 `largest`；
  24| - 更大的候选已经先处理过却没有访问到它，所以它不可能到达更大编号。
  25| 
  26| 一个点写入答案后不再入栈，因此所有搜索合计只访问每个点、每条反向边常数次。
  27| 
  28| ### Python 知识
  29| 
  30| - `reverse_graph[v].append(u)` 直接建立反边 `v -> u`。
  31| - `range(n,0,-1)` 表达从大到小的处理顺序。
  32| - `answer[node]==0` 同时表示“尚未访问”，无需单独的 `visited`。
  33| - 显式 `stack` 避免最长链导致递归层数超限。
  34| - `/home/rainboy/mycode/hugo-blog/content/program_language/python/brute_force_validation.md`：显式栈图遍历。
  35| - `/home/rainboy/mycode/hugo-blog/content/program_language/python/cpp_to_python_pitfalls.md`：递归深度注意点。
  36| 
  37| ### 代码
  38| 
  39| @include-code(./main.py, python)
  40| 
  41| @include-code(./main.cpp, cpp)
  42| 
  43| 
  44| ### 复杂度
  45| 
  46| 时间复杂度 $O(n+m)$，反图、答案和栈的空间复杂度 $O(n+m)$。
  47| 
  48| ### 总结
  49| 
  50| “每个起点能到达的最大目标”可以反转成“每个目标能覆盖哪些起点”。再按目标从大到小染色，就能一次确定所有答案。
  51| 
  52| ## 代码位置
  53| - `problems/luogu/P3916/main.cpp`
  54| - `problems/luogu/P3916/main.py`