   1| # noi_openjudge ch0104-17 判断闰年
   2| 
   3| > 原文摘录，非模型摘要。来源：`problems/noi_openjudge/ch0104-17/index.md`（内容哈希 ade2f265184aa956）。
   4| > 摘录可能在 4000 字符处截断；作结论前必须能补读原文全文。
   5| 
   6| ## 元信息（frontmatter 摘录）
   7| - 难度：入门；标签：['数学', '条件判断', 'python']
   8| 
   9| ## 题目解析（原文摘录）
  10| 
  11| [[TOC]]
  12| 
  13| ### 题意
  14| 
  15| 按题设公历规则判断年份是否是闰年，输出 `Y` 或 `N`。
  16| 
  17| ### 思路
  18| 
  19| 普通规则是“能被 4 整除且不能被 100 整除，或能被 400 整除”。题面额外规定 3200 的倍数不是闰年，因此最后再加 `year % 3200 != 0`。
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
  33| 时间复杂度和额外空间复杂度均为 $O(1)$。
  34| 
  35| ### 总结
  36| 
  37| 闰年题的难点在例外规则；用带括号的布尔表达式把优先级写清楚。
  38| 
  39| ## 代码位置
  40| - `problems/noi_openjudge/ch0104-17/main-cout.cpp`
  41| - `problems/noi_openjudge/ch0104-17/main.cpp`
  42| - `problems/noi_openjudge/ch0104-17/main.py`