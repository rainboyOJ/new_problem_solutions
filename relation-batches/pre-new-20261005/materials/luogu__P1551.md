   1| # luogu P1551 亲戚
   2| 
   3| > 原文摘录，非模型摘要。来源：`problems/luogu/P1551/index.md`（内容哈希 a484d5c1c13c87e7）。
   4| > 摘录可能在 4000 字符处截断；作结论前必须能补读原文全文。
   5| 
   6| ## 元信息（frontmatter 摘录）
   7| - 难度：入门；标签：['并查集', '连通性', 'python']
   8| 
   9| ## 题目解析（原文摘录）
  10| 
  11| [[TOC]]
  12| 
  13| ### 题意
  14| 
  15| 给出 `n` 个人之间的 `m` 条亲戚关系。亲戚关系可以传递，回答 `p` 次询问：两个人是否属于同一个亲戚群体。
  16| 
  17| ### 思路
  18| 
  19| 把每个人看成一个集合。读到关系 `(a,b)` 时合并两人的集合；询问时比较两人的代表元：
  20| 
  21| - 代表元相同，说明存在一条关系链把两人连在一起，输出 `Yes`；
  22| - 代表元不同，输出 `No`。
  23| 
  24| 代码同时使用路径压缩和按集合大小合并，使并查集操作的均摊代价接近常数。
  25| 
  26| ### Python 知识
  27| 
  28| - `parent = list(range(n + 1))` 简洁地建立“每个人最初以自己为根”的数组。
  29| - `a, b = find(a), find(b)` 用解包同时取得两个代表元。
  30| - `"Yes" if 条件 else "No"` 适合表达二选一答案，再用列表收集后一次输出。
  31| - `/home/rainboy/mycode/hugo-blog/content/program_language/python/input_output_and_strings.md`：批量读入和字符串输出。
  32| - `/home/rainboy/mycode/hugo-blog/content/program_language/python/cpp_to_python_pitfalls.md`：避免深递归，使用循环版 `find`。
  33| 
  34| ### 代码
  35| 
  36| @include-code(./main.py, python)
  37| 
  38| @include-code(./main.cpp, cpp)
  39| 
  40| 
  41| ### 复杂度
  42| 
  43| 共有 `m+p` 次并查集操作，时间复杂度为 $O((m+p)\alpha(n))$，空间复杂度为 $O(n)$。
  44| 
  45| ### 总结
  46| 
  47| “关系可以传递，反复询问是否属于同一组”是并查集的直接使用场景。查询的关键不是保存完整关系链，而是比较最终代表元。
  48| 
  49| ## 代码位置
  50| - `problems/luogu/P1551/main.cpp`
  51| - `problems/luogu/P1551/main.py`