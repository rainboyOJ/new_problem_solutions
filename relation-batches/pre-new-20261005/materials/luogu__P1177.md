   1| # luogu P1177 【模板】排序
   2| 
   3| > 原文摘录，非模型摘要。来源：`problems/luogu/P1177/index.md`（内容哈希 e1162e3234c7a939）。
   4| > 摘录可能在 4000 字符处截断；作结论前必须能补读原文全文。
   5| 
   6| ## 元信息（frontmatter 摘录）
   7| - 难度：普及-；标签：['排序', '模板题', 'python']
   8| 
   9| ## 题目解析（原文摘录）
  10| 
  11| [[TOC]]
  12| 
  13| ### 题意
  14| 
  15| 给出 `n` 个整数，把它们从小到大排序后输出。
  16| 
  17| ### 思路
  18| 
  19| Python 列表自带排序方法：
  20| 
  21| ```python
  22| numbers.sort()
  23| ```
  24| 
  25| 它会原地把列表按升序排列。数据量 `n <= 10^5`，直接使用内置排序即可。
  26| 
  27| 历史目录中保留了 C++ 文件；本文以 Python 模板写法为准，不创建 `brute.py`。
  28| 
  29| ### Python 知识
  30| 
  31| - `/home/rainboy/mycode/hugo-blog/content/program_language/python/sorting_and_ordering.md`：`list.sort()` 原地排序，`sorted()` 返回新列表。
  32| - `/home/rainboy/mycode/hugo-blog/content/program_language/python/oj_input_output_cheatsheet.md`：大量整数可以用 `sys.stdin.buffer.read().split()` 读取。
  33| - `print(*numbers)` 默认用空格分隔输出。
  34| 
  35| ### 代码
  36| 
  37| @include-code(./main.py, python)
  38| 
  39| ### Pythonic 写法
  40| 
  41| sorted 快读：
  42| 
  43| @include-code(./main-pythonic.py, python)
  44| 
  45| 
  46| ### 复杂度
  47| 
  48| Python 内置排序时间复杂度是 $O(n\log n)$，空间复杂度由排序实现决定，保存输入需要 $O(n)$。
  49| 
  50| ### 总结
  51| 
  52| 排序模板题的 Python 写法就是读入列表、调用 `sort()`、输出。重点是分清 `sort()` 会修改原列表且返回 `None`。
  53| 
  54| ## 代码位置
  55| - `problems/luogu/P1177/brute.cpp`
  56| - `problems/luogu/P1177/brute.py`
  57| - `problems/luogu/P1177/gen.py`
  58| - `problems/luogu/P1177/main-pythonic.py`
  59| - `problems/luogu/P1177/main.cpp`
  60| - `problems/luogu/P1177/main.py`