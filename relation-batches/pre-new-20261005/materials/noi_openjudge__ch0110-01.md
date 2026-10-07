   1| # noi_openjudge ch0110-01 谁考了第k名
   2| 
   3| > 原文摘录，非模型摘要。来源：`problems/noi_openjudge/ch0110-01/index.md`（内容哈希 a618ed3949a105bd）。
   4| > 摘录可能在 4000 字符处截断；作结论前必须能补读原文全文。
   5| 
   6| ## 元信息（frontmatter 摘录）
   7| - 难度：入门；标签：['排序', 'python']
   8| 
   9| ## 题目解析（原文摘录）
  10| 
  11| [[TOC]]
  12| 
  13| ### 题意
  14| 
  15| 给出每位学生互不相同的成绩，输出成绩第 $k$ 高的学号和分数。题目要求分数按 `%g` 的效果输出，不能固定小数位。
  16| 
  17| ### 思路
  18| 
  19| 把每位学生记成 `(学号, 成绩)`，按成绩降序排列。Python 列表下标从 `0` 开始，因此第 $k$ 名位于 `rank - 1`。
  20| 
  21| `f"{score:g}"` 与 C/C++ 的 `%g` 类似，会去掉不必要的小数末尾零。
  22| 
  23| ### 代码
  24| 
  25| ## Python代码
  26| 
  27| @include-code(./main.py, python)
  28| 
  29| ## C++代码
  30| 
  31| @include-code(./main.cpp, cpp)
  32| 
  33| ### 复杂度
  34| 
  35| 排序时间复杂度为 $O(n \log n)$，额外空间复杂度为 $O(n)$。
  36| 
  37| ### 总结
  38| 
  39| 排序后直接按排名取元素。需要注意的是，名次从 `1` 开始而列表下标从 `0` 开始。
  40| 
  41| ## 代码位置
  42| - `problems/noi_openjudge/ch0110-01/main-cout.cpp`
  43| - `problems/noi_openjudge/ch0110-01/main.cpp`
  44| - `problems/noi_openjudge/ch0110-01/main.py`