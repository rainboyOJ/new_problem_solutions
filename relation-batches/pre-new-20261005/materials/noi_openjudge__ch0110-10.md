   1| # noi_openjudge ch0110-10 单词排序
   2| 
   3| > 原文摘录，非模型摘要。来源：`problems/noi_openjudge/ch0110-10/index.md`（内容哈希 79f677aa57024b56）。
   4| > 摘录可能在 4000 字符处截断；作结论前必须能补读原文全文。
   5| 
   6| ## 元信息（frontmatter 摘录）
   7| - 难度：入门；标签：['排序', '字符串', '集合', 'python']
   8| 
   9| ## 题目解析（原文摘录）
  10| 
  11| [[TOC]]
  12| 
  13| ### 题意
  14| 
  15| 输入一行由一个或多个空格分隔的单词，区分大小写，去重后按字典序逐行输出。
  16| 
  17| ### 思路
  18| 
  19| `split()` 会把连续空白都视为分隔符，正好适合本题。先用 `set` 去重，再对集合调用 `sorted`。Python 字符串默认按字典序比较，并区分大小写。
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
  33| 设不同单词数为 $m$，时间复杂度为 $O(n + m \log m)$，空间复杂度为 $O(m)$。
  34| 
  35| ### 总结
  36| 
  37| `split`、`set`、`sorted` 依次对应切分、去重、排序三个独立步骤。
  38| 
  39| ## 代码位置
  40| - `problems/noi_openjudge/ch0110-10/main-cout.cpp`
  41| - `problems/noi_openjudge/ch0110-10/main.cpp`
  42| - `problems/noi_openjudge/ch0110-10/main.py`