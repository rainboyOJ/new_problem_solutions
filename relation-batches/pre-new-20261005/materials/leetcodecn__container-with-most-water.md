   1| # leetcodecn container-with-most-water 盛最多水的容器
   2| 
   3| > 原文摘录，非模型摘要。来源：`problems/leetcodecn/container-with-most-water/index.md`（内容哈希 b08ee53f956912f5）。
   4| > 摘录可能在 4000 字符处截断；作结论前必须能补读原文全文。
   5| 
   6| ## 元信息（frontmatter 摘录）
   7| - 难度：普及+/提高；标签：['双指针', '贪心', '数组', 'cpp', 'python']
   8| 
   9| ## 题目解析（原文摘录）
  10| 
  11| [[TOC]]
  12| 
  13| ### 题意
  14| 
  15| 给定 n 条垂线的高度，找出两条线，使它们与 x 轴构成的容器能容纳最多的水。
  16| 
  17| ### 思路
  18| 
  19| 暴力枚举所有 (i,j) 对 O(n²)。优化：左右指针从两端向中间移动，每次移动较矮的一侧。
  20| 
  21| 正确性证明：设当前左右指针为 l、r，面积 = (r-l) × min(h[l], h[r])。如果移动较高的一侧，新面积的高度不会超过 min(h[l], h[r])，而宽度变小，面积一定不会更大。所以只能移动较矮的一侧，才有可能获得更大的面积。
  22| 
  23| 
  24| ### 代码
  25| 
  26| @include-code(./main.cpp, cpp)
  27| @include-code(./main.py, python)
  28| ### 复杂度
  29| 
  30| - 时间复杂度：O(n)，指针各移动一次。
  31| - 空间复杂度：O(1)。
  32| 
  33| ### 总结
  34| 
  35| "短板决定、移动短板"是双指针求区间最值问题的经典模型。关键在于证明移动长板不可能得到更优解。
  36| 
  37| ## 代码位置
  38| - `problems/leetcodecn/container-with-most-water/brute.cpp`
  39| - `problems/leetcodecn/container-with-most-water/gen.py`
  40| - `problems/leetcodecn/container-with-most-water/main.cpp`
  41| - `problems/leetcodecn/container-with-most-water/main.py`