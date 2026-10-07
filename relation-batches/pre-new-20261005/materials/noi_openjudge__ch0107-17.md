   1| # noi_openjudge ch0107-17 字符串判等
   2| 
   3| > 原文摘录，非模型摘要。来源：`problems/noi_openjudge/ch0107-17/index.md`（内容哈希 c275fa89d839aa6e）。
   4| > 摘录可能在 4000 字符处截断；作结论前必须能补读原文全文。
   5| 
   6| ## 元信息（frontmatter 摘录）
   7| - 难度：入门；标签：['字符串', '比较', 'python']
   8| 
   9| ## 题目解析（原文摘录）
  10| 
  11| [[TOC]]
  12| 
  13| ### 题意
  14| 
  15| 判断两行只含字母和空格的字符串在忽略大小写与空格后是否相等。
  16| 
  17| ### 思路
  18| 
  19| 每行先用 `replace(" ", "")` 删除空格，再调用 `lower()`，比较规范化后的两个结果。
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
  33| 设总输入长度为 $n$，时间和额外空间复杂度均为 $O(n)$。
  34| 
  35| ### 总结
  36| 
  37| 多个“忽略规则”可依次规范化，再做一次普通相等比较。
  38| 
  39| ## 代码位置
  40| - `problems/noi_openjudge/ch0107-17/main-cout.cpp`
  41| - `problems/noi_openjudge/ch0107-17/main.cpp`
  42| - `problems/noi_openjudge/ch0107-17/main.py`