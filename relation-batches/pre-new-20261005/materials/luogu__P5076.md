   1| # luogu P5076 【深基16.例7】普通二叉树（简化版）
   2| 
   3| > 原文摘录，非模型摘要。来源：`problems/luogu/P5076/index.md`（内容哈希 1ef064a42130687e）。
   4| > 摘录可能在 4000 字符处截断；作结论前必须能补读原文全文。
   5| 
   6| ## 元信息（frontmatter 摘录）
   7| - 难度：普及-；标签：['二分', '有序集合', 'python']
   8| 
   9| ## 题目解析（原文摘录）
  10| 
  11| [[TOC]]
  12| 
  13| ### 题意
  14| 
  15| 维护一个无重复整数集合，支持排名、第 k 小、前驱、后继和插入，共不超过 `10^4` 次操作。
  16| 
  17| ### 思路
  18| 
  19| 始终保持列表升序：
  20| 
  21| - `bisect_left(x)+1` 是 `x` 的排名；
  22| - 第 `k` 小直接访问 `numbers[k-1]`；
  23| - `bisect_left(x)-1` 是前驱位置；
  24| - `bisect_right(x)` 是后继位置；
  25| - `insort` 在正确位置插入。
  26| 
  27| 查询都是 $O(\log q)$，列表中间插入需要移动后缀，是 $O(q)$。本题只有 `10^4` 次操作，标准库写法足够简洁可靠；更大范围才需要平衡树。
  28| 
  29| ### Python 知识
  30| 
  31| - `bisect_left/right` 分别定位左、右插入边界。
  32| - `insort` 等价于先二分位置再 `list.insert`。
  33| - 边界不存在时按题目输出固定哨兵值。
  34| - `/home/rainboy/mycode/hugo-blog/content/program_language/python/sorting_and_ordering.md`：维护和使用有序序列。
  35| - `/home/rainboy/mycode/hugo-blog/content/program_language/python/oj_input_output_cheatsheet.md`：多行操作与批量输出。
  36| 
  37| ### 代码
  38| 
  39| @include-code(./main.py, python)
  40| 
  41| @include-code(./main.cpp, cpp)
  42| 
  43| 
  44| ### 复杂度
  45| 
  46| 查询 $O(\log q)$，插入最坏 $O(q)$，总时间最坏 $O(q^2)$，空间 $O(q)$。
  47| 
  48| ### 总结
  49| 
  50| 题目规模决定实现：`bisect` 负责边界语义，列表负责第 k 小；在一万次操作下可用更短的标准库方案。
  51| 
  52| ## 代码位置
  53| - `problems/luogu/P5076/main.cpp`
  54| - `problems/luogu/P5076/main.py`