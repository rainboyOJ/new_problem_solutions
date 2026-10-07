   1| # noi_openjudge ch0107-18 验证子串
   2| 
   3| > 原文摘录，非模型摘要。来源：`problems/noi_openjudge/ch0107-18/index.md`（内容哈希 db912bc69aeccc28）。
   4| > 摘录可能在 4000 字符处截断；作结论前必须能补读原文全文。
   5| 
   6| ## 元信息（frontmatter 摘录）
   7| - 难度：入门；标签：['字符串', '匹配', 'python']
   8| 
   9| ## 题目解析（原文摘录）
  10| 
  11| [[TOC]]
  12| 
  13| ### 题意
  14| 
  15| 判断两条字符串中是否有一条是另一条的子串，并按指定格式输出关系。
  16| 
  17| ### 思路
  18| 
  19| `first in second` 直接判断第一串是否为第二串子串；若不成立，再检查相反方向。两个方向都不成立时输出 `No substring`。
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
  33| 朴素子串匹配最坏时间复杂度为 $O(nm)$，额外空间复杂度为 $O(1)$。
  34| 
  35| ### 总结
  36| 
  37| Python 的 `in` 是最直观的子串存在性写法。
  38| 
  39| ## 代码位置
  40| - `problems/noi_openjudge/ch0107-18/main-cout.cpp`
  41| - `problems/noi_openjudge/ch0107-18/main.cpp`
  42| - `problems/noi_openjudge/ch0107-18/main.py`