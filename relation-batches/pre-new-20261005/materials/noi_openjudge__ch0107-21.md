   1| # noi_openjudge ch0107-21 单词替换
   2| 
   3| > 原文摘录，非模型摘要。来源：`problems/noi_openjudge/ch0107-21/index.md`（内容哈希 0553813f0ac9ac64）。
   4| > 摘录可能在 4000 字符处截断；作结论前必须能补读原文全文。
   5| 
   6| ## 元信息（frontmatter 摘录）
   7| - 难度：入门；标签：['字符串', '模拟', 'python']
   8| 
   9| ## 题目解析（原文摘录）
  10| 
  11| [[TOC]]
  12| 
  13| ### 题意
  14| 
  15| 将句子中所有与指定单词完全相同的单词替换为新单词。
  16| 
  17| ### 思路
  18| 
  19| 按空格切分为单词，生成新单词序列后用空格连接。只对完整单词做相等比较，不会误替换单词内部的子串。
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
  33| 设句子长度为 $n$，时间和输出空间复杂度均为 $O(n)$。
  34| 
  35| ### 总结
  36| 
  37| 按单词替换应先切词，再比较完整词。
  38| 
  39| ## 代码位置
  40| - `problems/noi_openjudge/ch0107-21/main-cout.cpp`
  41| - `problems/noi_openjudge/ch0107-21/main.cpp`
  42| - `problems/noi_openjudge/ch0107-21/main.py`