   1| # noi_openjudge ch0108-10 矩阵转置
   2| 
   3| > 原文摘录，非模型摘要。来源：`problems/noi_openjudge/ch0108-10/index.md`（内容哈希 f0954b6a58f161a2）。
   4| > 摘录可能在 4000 字符处截断；作结论前必须能补读原文全文。
   5| 
   6| ## 元信息（frontmatter 摘录）
   7| - 难度：入门；标签：['矩阵', '数组', 'python']
   8| 
   9| ## 题目解析（原文摘录）
  10| 
  11| [[TOC]]
  12| 
  13| ### 题意
  14| 
  15| 输出 $n\times m$ 矩阵的转置，即将行和列互换。
  16| 
  17| ### 思路
  18| 
  19| `zip(*matrix)` 将所有行解包并按相同列下标组合，每个得到的元组就是转置矩阵的一行。
  20| 
  21| ### 代码
  22| 
  23| @include-code(./main.cpp, cpp)
  24| 
  25| ### 复杂度
  26| 
  27| <!-- 原解析未提供复杂度说明时，后续人工补充。 -->
  28| 
  29| ### 总结
  30| 
  31| <!-- 保留原解析内容，不额外编造结论。 -->
  32| ## Python代码
  33| 
  34| @include-code(./main.py, python)
  35| 
  36| ## C++代码
  37| 
  38| @include-code(./main.cpp, cpp)
  39| 
  40| ### 复杂度
  41| 
  42| 时间复杂度为 $O(nm)$，矩阵输入空间为 $O(nm)$。
  43| 
  44| ### 总结
  45| 
  46| `zip(*matrix)` 是规则二维列表转置的简洁 Python 写法。
  47| 
  48| ## 代码位置
  49| - `problems/noi_openjudge/ch0108-10/main-cout.cpp`
  50| - `problems/noi_openjudge/ch0108-10/main.cpp`
  51| - `problems/noi_openjudge/ch0108-10/main.py`