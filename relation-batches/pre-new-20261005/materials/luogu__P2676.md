   1| # luogu P2676 [USACO07DEC] Bookshelf B
   2| 
   3| > 原文摘录，非模型摘要。来源：`problems/luogu/P2676/index.md`（内容哈希 2d63fd5fbc15a986）。
   4| > 摘录可能在 4000 字符处截断；作结论前必须能补读原文全文。
   5| 
   6| ## 元信息（frontmatter 摘录）
   7| - 难度：入门；标签：['贪心', '排序', 'python']
   8| 
   9| ## 题目解析（原文摘录）
  10| 
  11| [[TOC]]
  12| 
  13| ### 题意
  14| 
  15| 给出若干奶牛身高和目标高度 `B`。选择尽量少的奶牛，使身高总和至少为 `B`。
  16| 
  17| ### 思路
  18| 
  19| 要让奶牛数量尽量少，每次都应该优先选择最高的奶牛。因此：
  20| 
  21| 1. 将身高从高到低排序；
  22| 2. 从高到低累加；
  23| 3. 第一次达到 `B` 时，当前数量就是答案。
  24| 
  25| 这是直接的贪心排序题。
  26| 
  27| ### Python 知识
  28| 
  29| - `/home/rainboy/mycode/hugo-blog/content/program_language/python/sorting_and_ordering.md`：`sort(reverse=True)` 可以降序排序。
  30| - `/home/rainboy/mycode/hugo-blog/content/program_language/python/oj_input_output_cheatsheet.md`：多行整数可用 `sys.stdin.buffer.read()` 统一读取。
  31| - `break` 在达到目标后提前结束循环。
  32| 
  33| ### 代码
  34| 
  35| @include-code(./main.py, python)
  36| 
  37| @include-code(./main.cpp, cpp)
  38| 
  39| 
  40| ### 复杂度
  41| 
  42| 排序时间复杂度 $O(n\log n)$，空间复杂度 $O(n)$。
  43| 
  44| ### 总结
  45| 
  46| “最少个数达到总和”且每个元素贡献独立时，优先选最大的元素是自然贪心。
  47| 
  48| ## 代码位置
  49| - `problems/luogu/P2676/gen.py`
  50| - `problems/luogu/P2676/main.cpp`
  51| - `problems/luogu/P2676/main.py`