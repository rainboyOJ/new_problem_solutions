   1| # luogu P3374 【模板】树状数组 1
   2| 
   3| > 原文摘录，非模型摘要。来源：`problems/luogu/P3374/index.md`（内容哈希 e622986d7d18e39b）。
   4| > 摘录可能在 4000 字符处截断；作结论前必须能补读原文全文。
   5| 
   6| ## 元信息（frontmatter 摘录）
   7| - 难度：普及/提高-；标签：['树状数组', '前缀和', '模板题', 'python']
   8| 
   9| ## 题目解析（原文摘录）
  10| 
  11| [[TOC]]
  12| 
  13| ### 题意
  14| 
  15| 支持某一项加值，以及查询任意闭区间元素和。
  16| 
  17| ### 思路
  18| 
  19| Fenwick 节点保存一段由 `lowbit` 决定的后缀和。修改下标时不断加 `lowbit`，查询前缀时不断减 `lowbit`；区间 `[l,r]` 等于 `prefix(r)-prefix(l-1)`。
  20| 
  21| ### Python 知识
  22| 
  23| - 自定义 `os.read` 分块整数生成器避免 150 万级 token 的 `split` 内存峰值。
  24| - `array("q")` 用 64 位整数紧凑保存树。
  25| - `i & -i` 取得最低位 1。
  26| 
  27| ### 代码
  28| 
  29| @include-code(./main.py, python)
  30| 
  31| ### 复杂度
  32| 
  33| 初始化与每次操作 $O(\log n)$，空间 $O(n)$。
  34| 
  35| ### 总结
  36| 
  37| Fenwick 是动态前缀和的最短模板，区间查询仍通过前缀差完成。
  38| 
  39| ## 代码位置
  40| - `problems/luogu/P3374/brute.cpp`
  41| - `problems/luogu/P3374/gen.py`
  42| - `problems/luogu/P3374/main.cpp`
  43| - `problems/luogu/P3374/main.py`