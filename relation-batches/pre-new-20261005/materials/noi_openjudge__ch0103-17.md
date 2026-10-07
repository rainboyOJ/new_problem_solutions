   1| # noi_openjudge ch0103-17 计算三角形面积
   2| 
   3| > 原文摘录，非模型摘要。来源：`problems/noi_openjudge/ch0103-17/index.md`（内容哈希 82771872e5f6ed65）。
   4| > 摘录可能在 4000 字符处截断；作结论前必须能补读原文全文。
   5| 
   6| ## 元信息（frontmatter 摘录）
   7| - 难度：入门；标签：['数学', '几何', 'python']
   8| 
   9| ## 题目解析（原文摘录）
  10| 
  11| [[TOC]]
  12| 
  13| ### 题意
  14| 
  15| 输入三角形三个顶点坐标，输出面积，保留 2 位小数。
  16| 
  17| ### 思路
  18| 
  19| 鞋带公式给出两倍有向面积：$x_1y_2+x_2y_3+x_3y_1-x_1y_3-x_2y_1-x_3y_2$。顶点顺逆时针会改变符号，面积必须非负，因此取绝对值后除以 2。
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
  33| 时间复杂度和额外空间复杂度均为 $O(1)$。
  34| 
  35| ### 总结
  36| 
  37| 坐标面积公式算出的是有向面积；求几何面积时别遗漏 `abs`。
  38| 
  39| ## 代码位置
  40| - `problems/noi_openjudge/ch0103-17/main-cout.cpp`
  41| - `problems/noi_openjudge/ch0103-17/main.cpp`
  42| - `problems/noi_openjudge/ch0103-17/main.py`