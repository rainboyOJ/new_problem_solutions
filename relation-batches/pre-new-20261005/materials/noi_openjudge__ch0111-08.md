   1| # noi_openjudge ch0111-08 不重复地输出数
   2| 
   3| > 原文摘录，非模型摘要。来源：`problems/noi_openjudge/ch0111-08/index.md`（内容哈希 18bc5488d03914fe）。
   4| > 摘录可能在 4000 字符处截断；作结论前必须能补读原文全文。
   5| 
   6| ## 元信息（frontmatter 摘录）
   7| - 难度：入门；标签：['排序', '集合', 'python']
   8| 
   9| ## 题目解析（原文摘录）
  10| 
  11| [[TOC]]
  12| 
  13| ### 题意
  14| 
  15| 读入大量整数，按从小到大顺序输出每个不同整数一次。
  16| 
  17| ### 思路
  18| 
  19| 集合自动去重，`sorted(numbers)` 得到严格递增列表。最后使用 `print(*...)` 以单个空格分隔输出。
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
  33| 设不同整数有 $m$ 个，时间复杂度为 $O(n + m \log m)$，空间复杂度为 $O(m)$。
  34| 
  35| ### 总结
  36| 
  37| 当只关心不同元素的有序集合时，`set` 加 `sorted` 足够直接。
  38| 
  39| ## 代码位置
  40| - `problems/noi_openjudge/ch0111-08/main-cout.cpp`
  41| - `problems/noi_openjudge/ch0111-08/main.cpp`
  42| - `problems/noi_openjudge/ch0111-08/main.py`