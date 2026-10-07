   1| # luogu P3654 First Step (ファーストステップ)
   2| 
   3| > 原文摘录，非模型摘要。来源：`problems/luogu/P3654/index.md`（内容哈希 033c68c349f0f5aa）。
   4| > 摘录可能在 4000 字符处截断；作结论前必须能补读原文全文。
   5| 
   6| ## 元信息（frontmatter 摘录）
   7| - 难度：入门；标签：['枚举', '矩阵', 'python']
   8| 
   9| ## 题目解析（原文摘录）
  10| 
  11| [[TOC]]
  12| 
  13| ### 题意
  14| 
  15| 给定一个 `R x C` 的矩阵，`.` 表示空地，`#` 表示障碍。要找出有多少种方法放下一条长度为 `K` 的直线队伍，方向可以横向或纵向，所有位置都必须是空地。
  16| 
  17| ### 思路
  18| 
  19| 直接枚举每个可能的起点。
  20| 
  21| 横向放置时，起点 `(row, col)` 需要满足 `col + K - 1 < C`，然后检查这一段是否全是 `.`。
  22| 
  23| 纵向放置时，起点 `(row, col)` 需要满足 `row + K - 1 < R`，然后检查这一段是否全是 `.`。
  24| 
  25| 需要特别注意 `K = 1`。此时横向和纵向的同一个空格表示同一种站位，不能重复计数，所以直接统计空地数量。
  26| 
  27| ### Python 知识
  28| 
  29| - `all(...)` 可以判断一段格子是否全部满足条件，并且遇到第一个不满足的格子会短路。
  30| - `row.count(".")` 可以统计一行中的空地数量。
  31| - 用 `range(c - k + 1)` 控制横向起点，避免越界。
  32| 
  33| 参考笔记：
  34| 
  35| - `/home/rainboy/mycode/hugo-blog/content/program_language/python/generator_expression.md`
  36| - `/home/rainboy/mycode/hugo-blog/content/program_language/python/input_output_and_strings.md`
  37| 
  38| ### 代码
  39| 
  40| @include-code(./main.py, python)
  41| 
  42| @include-code(./main.cpp, cpp)
  43| 
  44| ### 复杂度
  45| 
  46| 每个起点最多检查 `K` 个格子，时间复杂度为 $O(RCK)$，空间复杂度为 $O(RC)$。
  47| 
  48| ### 总结
  49| 
  50| 矩阵枚举题先确定“起点范围”，再写合法性检查。`K=1` 的重复计数是本题最容易漏掉的边界。
  51| 
  52| ## 代码位置
  53| - `problems/luogu/P3654/gen.py`
  54| - `problems/luogu/P3654/main.cpp`
  55| - `problems/luogu/P3654/main.py`