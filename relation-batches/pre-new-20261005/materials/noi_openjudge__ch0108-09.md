   1| # noi_openjudge ch0108-09 矩阵乘法
   2| 
   3| > 原文摘录，非模型摘要。来源：`problems/noi_openjudge/ch0108-09/index.md`（内容哈希 6df787098f6359ff）。
   4| > 摘录可能在 4000 字符处截断；作结论前必须能补读原文全文。
   5| 
   6| ## 元信息（frontmatter 摘录）
   7| - 难度：普及-；标签：['矩阵', '模拟', 'python']
   8| 
   9| ## 题目解析（原文摘录）
  10| 
  11| [[TOC]]
  12| 
  13| ### 题意
  14| 
  15| 计算 $n\times m$ 矩阵 $A$ 与 $m\times k$ 矩阵 $B$ 的乘积。
  16| 
  17| ### 思路
  18| 
  19| 结果的第 $i,j$ 项是 `A[i]` 与 $B$ 的第 $j$ 列对应元素乘积之和。外层枚举 $A$ 的行和结果列，内层枚举公共维度。
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
  42| 时间复杂度为 $O(nmk)$，输入矩阵空间为 $O(nm+mk)$。
  43| 
  44| ### 总结
  45| 
  46| 矩阵乘法不是对应相乘，而是“一行乘一列”的内积。
  47| 
  48| ## 代码位置
  49| - `problems/noi_openjudge/ch0108-09/main-cout.cpp`
  50| - `problems/noi_openjudge/ch0108-09/main.cpp`
  51| - `problems/noi_openjudge/ch0108-09/main.py`