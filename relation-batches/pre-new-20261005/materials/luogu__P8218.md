   1| # luogu P8218 【深进1.例1】求区间和
   2| 
   3| > 原文摘录，非模型摘要。来源：`problems/luogu/P8218/index.md`（内容哈希 af9e9e0c6febddb5）。
   4| > 摘录可能在 4000 字符处截断；作结论前必须能补读原文全文。
   5| 
   6| ## 元信息（frontmatter 摘录）
   7| - 难度：普及-；标签：['前缀和', 'python']
   8| 
   9| ## 题目解析（原文摘录）
  10| 
  11| [[TOC]]
  12| 
  13| ### 题意
  14| 
  15| 给定一个长度为 $n$ 的序列，回答 $m$ 个闭区间 $[l,r]$ 的元素和。
  16| 
  17| ### 思路
  18| 
  19| 令 `prefix[i]` 表示前 `i` 个数之和，则区间和为 `prefix[r] - prefix[l - 1]`。预处理一次后，每个询问只做一次减法。
  20| 
  21| ### Python 知识
  22| 
  23| - `accumulate(a, initial=0)` 直接产生长度为 $n+1$ 的前缀和，参见 `/home/rainboy/mycode/hugo-blog/content/program_language/python/itertools_recipes.md`。
  24| - `"\n".join(...)` 一次输出多行答案，参见 `/home/rainboy/mycode/hugo-blog/content/program_language/python/input_output_and_strings.md`。
  25| - 嵌套生成器按需读取每组 `l, r`，不必保存全部询问。
  26| 
  27| ### 代码
  28| 
  29| @include-code(./main.py, python)
  30| 
  31| ### 复杂度
  32| 
  33| 时间复杂度 $O(n+m)$，空间复杂度 $O(n)$。
  34| 
  35| ### 总结
  36| 
  37| 固定数组上的大量区间和询问，是前缀和最直接的应用。
  38| 
  39| ## 代码位置
  40| - `problems/luogu/P8218/brute.cpp`
  41| - `problems/luogu/P8218/gen.py`
  42| - `problems/luogu/P8218/main.cpp`
  43| - `problems/luogu/P8218/main.py`