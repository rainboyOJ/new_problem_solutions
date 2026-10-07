   1| # luogu P1157 组合的输出
   2| 
   3| > 原文摘录，非模型摘要。来源：`problems/luogu/P1157/index.md`（内容哈希 3ed3845fb210193f）。
   4| > 摘录可能在 4000 字符处截断；作结论前必须能补读原文全文。
   5| 
   6| ## 元信息（frontmatter 摘录）
   7| - 难度：入门；标签：['枚举', '组合', 'python']
   8| 
   9| ## 题目解析（原文摘录）
  10| 
  11| [[TOC]]
  12| 
  13| ### 题意
  14| 
  15| 从 `1..n` 中选出 `r` 个数，按字典序输出所有组合。每个数字输出时占 `3` 个字符宽度。
  16| 
  17| ### 思路
  18| 
  19| 组合要求：
  20| 
  21| - 每行内部数字递增；
  22| - 所有行按字典序排列；
  23| - 不关心选择顺序，只关心选出的集合。
  24| 
  25| `itertools.combinations(range(1, n + 1), r)` 正好满足这些条件。它会按照输入序列的顺序生成组合，所以输出顺序就是题目要求的字典序。
  26| 
  27| 每个数占 `3` 个字符，可以写成：
  28| 
  29| ```python
  30| f"{number:3d}"
  31| ```
  32| 
  33| 再把一行中的字段拼接起来输出。
  34| 
  35| ### Python 知识
  36| 
  37| - `combinations(range(1, n + 1), r)` 表示从 `1..n` 中选 `r` 个。
  38| - `f"{number:3d}"` 是格式化字符串，含义是整数右对齐，占 `3` 个字符宽度。
  39| - `"".join(...)` 把一行的多个格式化字段拼成一个字符串。
  40| 
  41| 参考笔记：
  42| 
  43| - `/home/rainboy/mycode/hugo-blog/content/program_language/python/brute_force_validation.md`
  44| - `/home/rainboy/mycode/hugo-blog/content/program_language/python/itertools_recipes.md`
  45| - `/home/rainboy/mycode/hugo-blog/content/program_language/python/input_output_and_strings.md`
  46| 
  47| ### 代码
  48| 
  49| @include-code(./main.py, python)
  50| 
  51| @include-code(./main.cpp, cpp)
  52| 
  53| ### 复杂度
  54| 
  55| 会输出 $\binom{n}{r}$ 行，每行有 `r` 个数。时间复杂度为 $O(r\binom{n}{r})$，空间复杂度为 $O(r)$。
  56| 
  57| ### 总结
  58| 
  59| 这题的重点不是手写递归，而是学会把“按字典序输出组合”直接交给 `itertools.combinations`。
  60| 
  61| ## 代码位置
  62| - `problems/luogu/P1157/gen.py`
  63| - `problems/luogu/P1157/main.cpp`
  64| - `problems/luogu/P1157/main.py`