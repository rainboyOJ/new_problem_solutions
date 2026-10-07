   1| # noi_openjudge ch0105-34 求阶乘的和
   2| 
   3| > 原文摘录，非模型摘要。来源：`problems/noi_openjudge/ch0105-34/index.md`（内容哈希 9f6253b595daaba1）。
   4| > 摘录可能在 4000 字符处截断；作结论前必须能补读原文全文。
   5| 
   6| ## 元信息（frontmatter 摘录）
   7| - 难度：入门；标签：['循环', '数学', '递推', 'python']
   8| 
   9| ## 题目解析（原文摘录）
  10| 
  11| [[TOC]]
  12| 
  13| ### 题意
  14| 
  15| 求 $1!+2!+\cdots+n!$。
  16| 
  17| ### 思路
  18| 
  19| 不必每次从头计算阶乘。若 `factorial` 已经是 $(i-1)!$，乘上 $i$ 就得到 $i!$；把它加入 `total` 后继续下一轮即可。
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
  33| 时间复杂度为 $O(n)$，额外空间复杂度为 $O(1)$。
  34| 
  35| ### 总结
  36| 
  37| 相邻阶乘只差一次乘法，维护递推值比重复计算更清晰也更高效。
  38| 
  39| ## 代码位置
  40| - `problems/noi_openjudge/ch0105-34/main-cout.cpp`
  41| - `problems/noi_openjudge/ch0105-34/main.cpp`
  42| - `problems/noi_openjudge/ch0105-34/main.py`