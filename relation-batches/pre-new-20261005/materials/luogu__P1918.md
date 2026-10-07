   1| # luogu P1918 保龄球
   2| 
   3| > 原文摘录，非模型摘要。来源：`problems/luogu/P1918/index.md`（内容哈希 1be2bc1d2836bdd6）。
   4| > 摘录可能在 4000 字符处截断；作结论前必须能补读原文全文。
   5| 
   6| ## 元信息（frontmatter 摘录）
   7| - 难度：入门；标签：['哈希', '字典', '查询', 'python']
   8| 
   9| ## 题目解析（原文摘录）
  10| 
  11| ### 题意
  12| 
  13| 第 `i` 个位置有 `a[i]` 个瓶子，所有 `a[i]` 互不相同。每次询问一个瓶子数，输出对应位置，不存在则输出 `0`。
  14| 
  15| ### 思路
  16| 
  17| 瓶子数互不相同，所以一个瓶子数最多对应一个位置。预处理映射：
  18| 
  19| ```text
  20| 瓶子数 -> 位置
  21| ```
  22| 
  23| 之后每次询问直接查字典；`position.get(count,0)` 在键不存在时返回题目要求的 `0`。
  24| 
  25| 也可以排序后二分，但 Python 字典更贴合“由唯一值查原位置”的模型，预处理和询问的期望复杂度都更低，代码也更短。
  26| 
  27| ### Python 知识
  28| 
  29| - `{count: i for i,count in enumerate(values,1)}` 用字典推导式建立反向索引。
  30| - `enumerate(sequence,1)` 让位置直接从题目的 `1` 开始。
  31| - `dict.get(key,default)` 适合“查询不到时输出固定默认值”。
  32| - 生成器表达式逐个生成答案字符串，再交给 `join` 连接，不额外建立答案整数列表。
  33| - `/home/rainboy/mycode/hugo-blog/content/program_language/python/collections_toolkit.md`：字典反向索引与 `get`。
  34| - `/home/rainboy/mycode/hugo-blog/content/program_language/python/generator_expression.md`：生成器配合 `join`。
  35| 
  36| ## 代码位置
  37| - `problems/luogu/P1918/brute.cpp`
  38| - `problems/luogu/P1918/gen.py`
  39| - `problems/luogu/P1918/main.cpp`
  40| - `problems/luogu/P1918/main.py`