   1| # noi_openjudge ch0105-35 求出e的值
   2| 
   3| > 原文摘录，非模型摘要。来源：`problems/noi_openjudge/ch0105-35/index.md`（内容哈希 89932be8750f967c）。
   4| > 摘录可能在 4000 字符处截断；作结论前必须能补读原文全文。
   5| 
   6| ## 元信息（frontmatter 摘录）
   7| - 难度：入门；标签：['循环', '数学', '递推', 'python']
   8| 
   9| ## 题目解析（原文摘录）
  10| 
  11| [[TOC]]
  12| 
  13| ### 题意
  14| 
  15| 根据 $e=1+1/1!+1/2!+\cdots+1/n!$ 计算近似值，并输出十位小数。
  16| 
  17| ### 思路
  18| 
  19| 初始和为常数项 $1$。循环中递推当前的 `factorial`，再加入 `1 / factorial`。最后使用 `f"{total:.10f}"` 按题意固定保留十位小数。
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
  33| 时间复杂度为 $O(n)$，额外空间复杂度为 $O(1)$。
  34| 
  35| ### 总结
  36| 
  37| 同一个阶乘递推既可用于整数和，也可用于它的倒数级数。
  38| 
  39| ## 代码位置
  40| - `problems/noi_openjudge/ch0105-35/main-cout.cpp`
  41| - `problems/noi_openjudge/ch0105-35/main.cpp`
  42| - `problems/noi_openjudge/ch0105-35/main.py`