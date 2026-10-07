   1| # luogu P1955 [NOI2015] 程序自动分析
   2| 
   3| > 原文摘录，非模型摘要。来源：`problems/luogu/P1955/index.md`（内容哈希 9b811734ba7ae281）。
   4| > 摘录可能在 4000 字符处截断；作结论前必须能补读原文全文。
   5| 
   6| ## 元信息（frontmatter 摘录）
   7| - 难度：普及+/提高；标签：['并查集', '离散化', 'python']
   8| 
   9| ## 题目解析（原文摘录）
  10| 
  11| ### 题意
  12| 
  13| 判断若干形如 $x_i=x_j$、$x_i\ne x_j$ 的约束能否同时成立。
  14| 
  15| ### 思路
  16| 
  17| 相等关系具有传递性，先把所有相等约束放进并查集。随后逐条检查不等约束：若两端已经属于同一集合，就产生矛盾。
  18| 
  19| 变量编号可达 $10^9$，但实际只出现 $O(n)$ 个。Python 可以直接用 `dict` 以原编号为键，相当于把离散化和并查集存储合在一起。
  20| 
  21| ### Python 知识
  22| 
  23| - 字典推导式从约束中收集实际出现的变量，参见 `/home/rainboy/mycode/hugo-blog/content/program_language/python/dict_usage.md`。
  24| - `all(...)` 会在第一个矛盾处短路，不会继续做无用检查。
  25| - `dict.fromkeys(parent, 1)` 为所有根初始化集合大小。
  26| 
  27| ## 代码位置
  28| - `problems/luogu/P1955/brute.cpp`
  29| - `problems/luogu/P1955/gen.py`
  30| - `problems/luogu/P1955/main.cpp`
  31| - `problems/luogu/P1955/main.py`