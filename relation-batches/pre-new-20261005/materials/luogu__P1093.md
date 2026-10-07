   1| # luogu P1093 [NOIP 2007 普及组] 奖学金
   2| 
   3| > 原文摘录，非模型摘要。来源：`problems/luogu/P1093/index.md`（内容哈希 5614843ff883619d）。
   4| > 摘录可能在 4000 字符处截断；作结论前必须能补读原文全文。
   5| 
   6| ## 元信息（frontmatter 摘录）
   7| - 难度：入门；标签：['排序', '模拟', 'python']
   8| 
   9| ## 题目解析（原文摘录）
  10| 
  11| [[TOC]]
  12| 
  13| ### 题意
  14| 
  15| 每个学生有语文、数学、英语三科成绩。先计算总分，再按总分高、语文高、学号小的顺序排序，输出前五名的学号和总分。
  16| 
  17| ### 思路
  18| 
  19| 每个学生保存为：
  20| 
  21| ```python
  22| (student_id, total, chinese)
  23| ```
  24| 
  25| 排序规则可以直接写成 `key` 元组：
  26| 
  27| ```python
  28| (-total, -chinese, student_id)
  29| ```
  30| 
  31| 总分和语文要降序，所以加负号；学号要升序，直接使用原值。
  32| 
  33| ### Python 知识
  34| 
  35| - `/home/rainboy/mycode/hugo-blog/content/program_language/python/sorting_and_ordering.md`：多关键字排序可以用元组 `key`。
  36| - `/home/rainboy/mycode/hugo-blog/content/program_language/python/input_output_and_strings.md`：每行三个整数用 `map(int, input().split())`。
  37| - `students[:5]` 取排序后的前五名。
  38| 
  39| ### 代码
  40| 
  41| @include-code(./main.py, python)
  42| 
  43| ### Pythonic 写法
  44| 
  45| 多关键字 sort：
  46| 
  47| @include-code(./main-pythonic.py, python)
  48| 
  49| 
  50| ### 复杂度
  51| 
  52| 排序 `n` 名学生，时间复杂度 $O(n\log n)$，空间复杂度 $O(n)$。
  53| 
  54| ### 总结
  55| 
  56| 排序题最重要的是把关键字顺序写对。降序字段取负，升序字段保持原值，是 Python 多关键字排序的常用写法。
  57| 
  58| ## 代码位置
  59| - `problems/luogu/P1093/brute.cpp`
  60| - `problems/luogu/P1093/brute.py`
  61| - `problems/luogu/P1093/gen.py`
  62| - `problems/luogu/P1093/main-pythonic.py`
  63| - `problems/luogu/P1093/main.cpp`
  64| - `problems/luogu/P1093/main.py`