   1| # noi_openjudge ch0107-16 忽略大小写的字符串比较
   2| 
   3| > 原文摘录，非模型摘要。来源：`problems/noi_openjudge/ch0107-16/index.md`（内容哈希 1d7f1a0031a48267）。
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
  15| 忽略字母大小写，比较两行字符串的字典序并输出 `<`、`>` 或 `=`。
  16| 
  17| ### 思路
  18| 
  19| 先对两串调用 `lower()` 消除大小写差异，Python 的字符串比较会按字典序完成逐字符比较。
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
  33| 设较长字符串长度为 $n$，时间复杂度为 $O(n)$，额外空间复杂度为 $O(n)$。
  34| 
  35| ### 总结
  36| 
  37| 忽略大小写的比较先做统一规范化，再复用普通字符串比较。
  38| 
  39| ## 代码位置
  40| - `problems/noi_openjudge/ch0107-16/main-cout.cpp`
  41| - `problems/noi_openjudge/ch0107-16/main.cpp`
  42| - `problems/noi_openjudge/ch0107-16/main.py`