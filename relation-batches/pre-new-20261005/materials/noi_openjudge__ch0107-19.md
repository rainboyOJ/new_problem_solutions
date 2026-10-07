   1| # noi_openjudge ch0107-19 字符串移位包含问题
   2| 
   3| > 原文摘录，非模型摘要。来源：`problems/noi_openjudge/ch0107-19/index.md`（内容哈希 992afe137441394a）。
   4| > 摘录可能在 4000 字符处截断；作结论前必须能补读原文全文。
   5| 
   6| ## 元信息（frontmatter 摘录）
   7| - 难度：普及-；标签：['字符串', '匹配', '模拟', 'python']
   8| 
   9| ## 题目解析（原文摘录）
  10| 
  11| [[TOC]]
  12| 
  13| ### 题意
  14| 
  15| 判断两串中是否有一串是另一串循环移位若干次后得到的字符串的子串。
  16| 
  17| ### 思路
  18| 
  19| 选较长串为 `longer`，较短串为 `shorter`。所有 `longer` 的循环移位都能作为 `longer + longer` 中长度与原串相同的连续片段出现，因此只需判断 `shorter in longer + longer`。
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
  33| 设较长串与较短串长度为 $n,m$，朴素匹配最坏时间复杂度为 $O(nm)$，额外空间为 $O(n)$。
  34| 
  35| ### 总结
  36| 
  37| 循环移位问题常可通过“原串拼接自身”转化为普通子串问题。
  38| 
  39| ## 代码位置
  40| - `problems/noi_openjudge/ch0107-19/main-cout.cpp`
  41| - `problems/noi_openjudge/ch0107-19/main.cpp`
  42| - `problems/noi_openjudge/ch0107-19/main.py`