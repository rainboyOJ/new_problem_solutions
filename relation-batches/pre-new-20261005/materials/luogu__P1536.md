   1| # luogu P1536 村村通
   2| 
   3| > 原文摘录，非模型摘要。来源：`problems/luogu/P1536/index.md`（内容哈希 31fd43dd3743d2a5）。
   4| > 摘录可能在 4000 字符处截断；作结论前必须能补读原文全文。
   5| 
   6| ## 元信息（frontmatter 摘录）
   7| - 难度：入门；标签：['并查集', '图论', '连通块', 'python']
   8| 
   9| ## 题目解析（原文摘录）
  10| 
  11| [[TOC]]
  12| 
  13| ### 题意
  14| 
  15| 多组数据中给出 `n` 个城镇和已有道路，求最少再建多少条道路，才能让任意两个城镇互相到达。输入以单独的 `0` 结束。
  16| 
  17| ### 思路
  18| 
  19| 已有道路把城镇分成若干连通块。若有 `k` 个连通块，每建一条连接不同块的道路最多使块数减少一，因此至少需要 `k-1` 条；把各块依次连接起来也恰好只需 `k-1` 条。
  20| 
  21| 用并查集维护已有道路：
  22| 
  23| 1. 初始每个城镇单独成块，`blocks=n`；
  24| 2. 一条道路连接两个不同代表元时合并，并令 `blocks-=1`；
  25| 3. 重边或块内道路不会改变块数；
  26| 4. 输出 `blocks-1`。
  27| 
  28| ### Python 知识
  29| 
  30| - 用一个下标 `pos` 顺序消费批量读取的整数，便于处理组数未知、以 `0` 结束的输入。
  31| - 在 `union` 成功时直接减少 `blocks`，省去最后再次扫描所有节点。
  32| - `answer` 收集每组结果，最后 `"\n".join(answer)` 一次输出。
  33| - 循环版 `find` 配合路径减半 `parent[x]=parent[parent[x]]`，短且不依赖递归深度。
  34| - `/home/rainboy/mycode/hugo-blog/content/program_language/python/oj_input_output_cheatsheet.md`：多组和终止标记输入。
  35| - `/home/rainboy/mycode/hugo-blog/content/program_language/python/cpp_to_python_pitfalls.md`：递归深度与批量输出。
  36| 
  37| ### 代码
  38| 
  39| @include-code(./main.py, python)
  40| 
  41| 
  42| ### 复杂度
  43| 
  44| 一组数据有 `n` 个点、`m` 条路，时间复杂度 $O((n+m)\alpha(n))$，空间复杂度 $O(n)$。
  45| 
  46| ### 总结
  47| 
  48| 答案只取决于已有图的连通块数。并查集合并成功时实时计数，是比“最后逐点数根”更直接的写法。
  49| 
  50| ## 代码位置
  51| - `problems/luogu/P1536/brute.cpp`
  52| - `problems/luogu/P1536/gen.py`
  53| - `problems/luogu/P1536/main.cpp`
  54| - `problems/luogu/P1536/main.py`