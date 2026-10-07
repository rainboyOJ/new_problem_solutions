   1| # noi_openjudge ch0106-06 校门外的树
   2| 
   3| > 原文摘录，非模型摘要。来源：`problems/noi_openjudge/ch0106-06/index.md`（内容哈希 8a486b59b4de45d7）。
   4| > 摘录可能在 4000 字符处截断；作结论前必须能补读原文全文。
   5| 
   6| ## 元信息（frontmatter 摘录）
   7| - 难度：普及-；标签：['数组', '模拟', '区间', 'python']
   8| 
   9| ## 题目解析（原文摘录）
  10| 
  11| [[TOC]]
  12| 
  13| ### 题意
  14| 
  15| 数轴 $0$ 到 $L$ 的每个整数位置都有树。多个闭区间内的树被移走，求剩余树数。
  16| 
  17| ### 思路
  18| 
  19| 布尔数组 `removed[position]` 表示该位置的树是否被移走。对每个闭区间 `left` 到 `right` 标记为真，重叠区间重复标记不会影响结果，最后统计为假的位置。
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
  33| 设所有区间长度总和为 $S$，时间复杂度为 $O(L+S)$，空间复杂度为 $O(L)$。
  34| 
  35| ### 总结
  36| 
  37| 范围不大且只需覆盖与否时，直接标记比处理区间重叠关系更直观。
  38| 
  39| ## 代码位置
  40| - `problems/noi_openjudge/ch0106-06/main-cout.cpp`
  41| - `problems/noi_openjudge/ch0106-06/main.cpp`
  42| - `problems/noi_openjudge/ch0106-06/main.py`