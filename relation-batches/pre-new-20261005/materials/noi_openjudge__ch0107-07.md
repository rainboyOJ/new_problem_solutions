   1| # noi_openjudge ch0107-07 配对碱基链
   2| 
   3| > 原文摘录，非模型摘要。来源：`problems/noi_openjudge/ch0107-07/index.md`（内容哈希 7e492c3d9da3b967）。
   4| > 摘录可能在 4000 字符处截断；作结论前必须能补读原文全文。
   5| 
   6| ## 元信息（frontmatter 摘录）
   7| - 难度：入门；标签：['字符串', '映射', 'python']
   8| 
   9| ## 题目解析（原文摘录）
  10| 
  11| [[TOC]]
  12| 
  13| ### 题意
  14| 
  15| 输出 DNA 单链的互补碱基链，其中 A 与 T 配对，G 与 C 配对。
  16| 
  17| ### 思路
  18| 
  19| 用 `str.maketrans` 建立四个字符的替换表，`translate` 一次转换整条链。
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
  33| 时间复杂度和输出空间均为 $O(n)$。
  34| 
  35| ### 总结
  36| 
  37| 固定的一对一字符替换可用翻译表清楚表示。
  38| 
  39| ## 代码位置
  40| - `problems/noi_openjudge/ch0107-07/main-cout.cpp`
  41| - `problems/noi_openjudge/ch0107-07/main.cpp`
  42| - `problems/noi_openjudge/ch0107-07/main.py`