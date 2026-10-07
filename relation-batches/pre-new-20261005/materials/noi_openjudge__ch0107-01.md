   1| # noi_openjudge ch0107-01 统计数字字符个数
   2| 
   3| > 原文摘录，非模型摘要。来源：`problems/noi_openjudge/ch0107-01/index.md`（内容哈希 b30eb42f6927c06d）。
   4| > 摘录可能在 4000 字符处截断；作结论前必须能补读原文全文。
   5| 
   6| ## 元信息（frontmatter 摘录）
   7| - 难度：入门；标签：['字符串', '计数', 'python']
   8| 
   9| ## 题目解析（原文摘录）
  10| 
  11| [[TOC]]
  12| 
  13| ### 题意
  14| 
  15| 统计一行字符串中数字字符的个数。
  16| 
  17| ### 思路
  18| 
  19| 对每个字符调用 `isdigit()`；布尔值可以直接求和，真值贡献 $1$。
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
  33| 设字符串长度为 $n$，时间复杂度为 $O(n)$，额外空间复杂度为 $O(1)$。
  34| 
  35| ### 总结
  36| 
  37| 字符分类统计可直接配合生成器表达式和 `sum`。
  38| 
  39| ## 代码位置
  40| - `problems/noi_openjudge/ch0107-01/main-cout.cpp`
  41| - `problems/noi_openjudge/ch0107-01/main.cpp`
  42| - `problems/noi_openjudge/ch0107-01/main.py`