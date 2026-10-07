   1| # noi_openjudge ch0110-03 成绩排序
   2| 
   3| > 原文摘录，非模型摘要。来源：`problems/noi_openjudge/ch0110-03/index.md`（内容哈希 d5671230da67ea0e）。
   4| > 摘录可能在 4000 字符处截断；作结论前必须能补读原文全文。
   5| 
   6| ## 元信息（frontmatter 摘录）
   7| - 难度：入门；标签：['排序', '字符串', 'python']
   8| 
   9| ## 题目解析（原文摘录）
  10| 
  11| [[TOC]]
  12| 
  13| ### 题意
  14| 
  15| 将成绩单按分数从高到低排列；同分时姓名字典序较小的学生在前。
  16| 
  17| ### 思路
  18| 
  19| Python 的元组会从左到右比较。排序键写成 `(-分数, 姓名)`：负号把分数的升序改为降序，姓名仍按默认字典序升序比较。这样一条 `sort` 就表达了两级规则。
  20| 
  21| ### 代码
  22| 
  23| ## Python代码
  24| 
  25| @include-code(./main.py, python)
  26| 
  27| ## C++代码
  28| 
  29| @include-code(./main.cpp, cpp)
  30| 
  31| ### 复杂度
  32| 
  33| 时间复杂度为 $O(n \log n)$，排序额外空间复杂度为 $O(n)$。
  34| 
  35| ### 总结
  36| 
  37| 多关键字排序的关键是把每层规则依次写进元组键中。
  38| 
  39| ## 代码位置
  40| - `problems/noi_openjudge/ch0110-03/main-cout.cpp`
  41| - `problems/noi_openjudge/ch0110-03/main.cpp`
  42| - `problems/noi_openjudge/ch0110-03/main.py`