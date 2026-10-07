   1| # luogu P3372 【模板】线段树 1
   2| 
   3| > 原文摘录，非模型摘要。来源：`problems/luogu/P3372/index.md`（内容哈希 df5364f648fcdcd8）。
   4| > 摘录可能在 4000 字符处截断；作结论前必须能补读原文全文。
   5| 
   6| ## 元信息（frontmatter 摘录）
   7| - 难度：普及/提高-；标签：['线段树', '懒标记', '树状数组', '区间加', '区间求和', 'python']
   8| 
   9| ## 题目解析（原文摘录）
  10| 
  11| ### 题意
  12| 
  13| 维护数列，支持区间加法和区间求和。
  14| 
  15| ### 思路
  16| 
  17| #### 懒标记线段树
  18| 
  19| 节点保存覆盖区间的和。整段加 `value` 时，区间和增加 `length * value`，并把 `value` 记在懒标记中；只有在需要访问孩子时才下传。区间查询和修改都只访问对数个节点。
  20| 
  21| #### 双树状数组
  22| 
  23| 设差分数组 `d[i] = a[i] - a[i-1]`。区间 `[l,r]` 加 `value` 只改变 `d[l]` 和 `d[r+1]`。
  24| 
  25| 一棵 Fenwick 维护 `d[i]`，另一棵维护 `i*d[i]`。原数组前缀和满足：
  26| 
  27| $$
  28| \begin{aligned}
  29| prefix(x)
  30| &=\sum_{i=1}^{x}a_i \\
  31| &=(x+1)\sum_{i=1}^{x}d_i-\sum_{i=1}^{x}i\cdot d_i
  32| \end{aligned}
  33| $$
  34| 
  35| 因此区间和仍为 `prefix(r) - prefix(l-1)`。这个做法只适用于本题的区间加与区间和；如果还要处理区间赋值或乘法，应使用线段树。
  36| 
  37| ## 代码位置
  38| - `problems/luogu/P3372/baoli.cpp`
  39| - `problems/luogu/P3372/brute.cpp`
  40| - `problems/luogu/P3372/fenkuai.cpp`
  41| - `problems/luogu/P3372/fenwick.cpp`
  42| - `problems/luogu/P3372/gen.py`
  43| - `problems/luogu/P3372/main.cpp`
  44| - `problems/luogu/P3372/main.py`
  45| - `problems/luogu/P3372/rnd.cpp`