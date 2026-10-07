   1| # noi_openjudge ch0108-13 图像模糊处理
   2| 
   3| > 原文摘录，非模型摘要。来源：`problems/noi_openjudge/ch0108-13/index.md`（内容哈希 6bbdbe23d8ad37dd）。
   4| > 摘录可能在 4000 字符处截断；作结论前必须能补读原文全文。
   5| 
   6| ## 元信息（frontmatter 摘录）
   7| - 难度：入门；标签：['矩阵', '模拟', 'python']
   8| 
   9| ## 题目解析（原文摘录）
  10| 
  11| [[TOC]]
  12| 
  13| ### 题意
  14| 
  15| 模糊图像：边缘不变，内部像素取自身与上下左右原值的平均并四舍五入。
  16| 
  17| ### 思路
  18| 
  19| 新值必须全由原图计算，所以复制一份 `blurred` 保存结果。非负整数除以 $5$ 的四舍五入可写作 `(total + 2) // 5`。
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
  42| 时间和空间复杂度均为 $O(nm)$。
  43| 
  44| ### 总结
  45| 
  46| 邻域更新题不要原地写入，否则后续像素会读到本轮新值。
  47| 
  48| ## 代码位置
  49| - `problems/noi_openjudge/ch0108-13/main-cout.cpp`
  50| - `problems/noi_openjudge/ch0108-13/main.cpp`
  51| - `problems/noi_openjudge/ch0108-13/main.py`