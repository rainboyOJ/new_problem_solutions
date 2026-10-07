   1| # luogu P3370 【模板】字符串哈希
   2| 
   3| > 原文摘录，非模型摘要。来源：`problems/luogu/P3370/index.md`（内容哈希 cb1efa98477a9340）。
   4| > 摘录可能在 4000 字符处截断；作结论前必须能补读原文全文。
   5| 
   6| ## 元信息（frontmatter 摘录）
   7| - 难度：入门；标签：['字符串', '哈希', '集合', 'python']
   8| 
   9| ## 题目解析（原文摘录）
  10| 
  11| [[TOC]]
  12| 
  13| ### 题意
  14| 
  15| 给出 `n` 个大小写敏感的字符串，求不同字符串的个数。
  16| 
  17| ### 思路
  18| 
  19| 虽然题名是字符串哈希模板，但在 Python 中无需手写滚动哈希。把完整字符串放进 `set`，重复字符串只会保留一份，集合长度就是答案。
  20| 
  21| `set` 内部使用哈希表加速查找，但发生哈希冲突时还会比较对象是否真正相等，所以这里按完整字符串判等，不承担手写单哈希的碰撞风险。
  22| 
  23| 输入的第一个 token 是 `n`，后面的 token 全是字符串，因此核心表达式就是 `len(set(data[1:]))`。
  24| 
  25| ### Python 知识
  26| 
  27| - `set(iterable)` 从可迭代对象建立集合并自动去重。
  28| - `len(set(...))` 是“只关心不同元素数量”时很常用的 Python 模式。
  29| - `sys.stdin.buffer.read().split()` 返回 `bytes` 列表；字符串只需比较、不需拼接时可以保持字节串。
  30| - Python 集合不保证题目输入顺序；本题只求数量，所以没有影响。
  31| - `/home/rainboy/mycode/hugo-blog/content/program_language/python/collections_toolkit.md`：`set` 去重和哈希容器。
  32| - `/home/rainboy/mycode/hugo-blog/content/program_language/python/input_output_and_strings.md`：字节输入与字符串处理。
  33| 
  34| ### 代码
  35| 
  36| @include-code(./main.py, python)
  37| 
  38| 
  39| 
  40| ### 复杂度
  41| 
  42| 设所有字符串总长度为 `L`，建立集合的期望时间复杂度 $O(L)$，空间复杂度 $O(L)$。
  43| 
  44| ### 总结
  45| 
  46| 在 Python OJ 中，标准哈希容器通常比手写字符串哈希更短、更可靠。只有题目明确要求子串哈希等能力时，才需要实现滚动哈希。
  47| 
  48| ## 代码位置
  49| - `problems/luogu/P3370/1.cpp`
  50| - `problems/luogu/P3370/brute.cpp`
  51| - `problems/luogu/P3370/gen.py`
  52| - `problems/luogu/P3370/main.cpp`
  53| - `problems/luogu/P3370/main.py`