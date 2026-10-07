   1| # noi_openjudge ch0107-02 找第一个只出现一次的字符
   2| 
   3| > 原文摘录，非模型摘要。来源：`problems/noi_openjudge/ch0107-02/index.md`（内容哈希 59050375bc914b79）。
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
  15| 找出小写字符串中第一个只出现一次的字符，没有则输出 `no`。
  16| 
  17| ### 思路
  18| 
  19| 先用 `Counter` 统计频率，再按原字符串顺序寻找频率为 $1$ 的字符，才能保证“第一个”。`next(..., "no")` 在找不到时给出默认结果。
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
  33| 时间复杂度为 $O(n)$，频次表使用 $O(n)$ 空间。
  34| 
  35| ### 总结
  36| 
  37| 先统计、再按原顺序扫描，是“第一个满足频率条件元素”的通用做法。
  38| 
  39| ## 代码位置
  40| - `problems/noi_openjudge/ch0107-02/main-cout.cpp`
  41| - `problems/noi_openjudge/ch0107-02/main.cpp`
  42| - `problems/noi_openjudge/ch0107-02/main.py`