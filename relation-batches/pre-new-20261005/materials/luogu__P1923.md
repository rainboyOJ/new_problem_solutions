   1| # luogu P1923 【深基9.例4】求第 k 小的数
   2| 
   3| > 原文摘录，非模型摘要。来源：`problems/luogu/P1923/index.md`（内容哈希 943f2ecb99440a67）。
   4| > 摘录可能在 4000 字符处截断；作结论前必须能补读原文全文。
   5| 
   6| ## 元信息（frontmatter 摘录）
   7| - 难度：普及-；标签：['排序', '选择', 'python']
   8| 
   9| ## 题目解析（原文摘录）
  10| 
  11| [[TOC]]
  12| 
  13| ### 题意
  14| 
  15| 给出 `n` 个数，最小的数编号为第 `0` 小，要求输出第 `k` 小的数。
  16| 
  17| ### 思路
  18| 
  19| Python 竞赛中最稳的写法是先排序：
  20| 
  21| ```python
  22| numbers.sort()
  23| print(numbers[k])
  24| ```
  25| 
  26| 排序后，列表下标 `0` 是最小值，下标 `k` 正好是第 `k` 小。题面希望练习分治选择算法，但在本 Python 教学题单中，这题用来练习大量整数读入和内置排序。
  27| 
  28| ### Python 知识
  29| 
  30| - `/home/rainboy/mycode/hugo-blog/content/program_language/python/sorting_and_ordering.md`：`list.sort()` 原地升序排序。
  31| - `/home/rainboy/mycode/hugo-blog/content/program_language/python/oj_input_output_cheatsheet.md`：大量整数输入使用 `sys.stdin.buffer.read()`。
  32| - Python 列表下标从 `0` 开始，正好对应题目的“第 0 小”。
  33| 
  34| ### 代码
  35| 
  36| @include-code(./main.py, python)
  37| 
  38| @include-code(./main.cpp, cpp)
  39| 
  40| ### Pythonic 写法
  41| 
  42| sorted 第 k：
  43| 
  44| @include-code(./main-pythonic.py, python)
  45| 
  46| 
  47| ### 复杂度
  48| 
  49| 排序时间复杂度是 $O(n\log n)$，保存输入需要 $O(n)$ 空间。
  50| 
  51| ### 总结
  52| 
  53| 第 k 小可以用选择算法优化，但 Python 入门阶段先掌握“读入、排序、取下标”这条稳定路径。
  54| 
  55| ## 代码位置
  56| - `problems/luogu/P1923/1.cpp`
  57| - `problems/luogu/P1923/main-pythonic.py`
  58| - `problems/luogu/P1923/main.cpp`
  59| - `problems/luogu/P1923/main.py`