   1| # noi_openjudge ch0110-09 明明的随机数
   2| 
   3| > 原文摘录，非模型摘要。来源：`problems/noi_openjudge/ch0110-09/index.md`（内容哈希 1a8384d0ccb76a4e）。
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
  15| 删除随机数中的重复值，再将剩余数字从小到大输出，并先输出不同数字的个数。
  16| 
  17| ### 思路
  18| 
  19| `set` 会自动只保留每个整数的一份，`sorted(set(...))` 再把无序集合转为升序列表。列表长度就是不同数字的个数。
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
  33| 去重平均时间为 $O(n)$，排序时间为 $O(m \log m)$，其中 $m$ 是不同数字的个数；空间复杂度为 $O(m)$。
  34| 
  35| ### 总结
  36| 
  37| 只需要“去重后再排序”时，`sorted(set(values))` 是清楚且常用的组合。
  38| 
  39| ## 代码位置
  40| - `problems/noi_openjudge/ch0110-09/main-cout.cpp`
  41| - `problems/noi_openjudge/ch0110-09/main.cpp`
  42| - `problems/noi_openjudge/ch0110-09/main.py`