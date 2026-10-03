   1| # leetcodecn pascals-triangle 杨辉三角
   2| 
   3| > 原文摘录，非模型摘要。来源：`problems/leetcodecn/pascals-triangle/index.md`（内容哈希 19d652a73130b652）。
   4| > 摘录可能在 4000 字符处截断；作结论前必须能补读原文全文。
   5| 
   6| ## 元信息（frontmatter 摘录）
   7| - 难度：入门；标签：['动态规划', '递推']
   8| 
   9| ## 题目解析（原文摘录）
  10| 
  11| [[TOC]]
  12| 
  13| ### 题意
  14| 生成杨辉三角的前 n 行。
  15| 
  16| ### 思路
  17| 每行边界为 1，内部 `ans[i][j] = ans[i-1][j-1] + ans[i-1][j]`。逐行从上到下填充。
  18| 
  19| ### 代码
  20| @include-code(./main.cpp, cpp)
  21| @include-code(./main.py, python)
  22| 
  23| ### 复杂度
  24| - 时间复杂度：$O(n^2)$。
  25| - 空间复杂度：$O(n^2)$，存储结果。
  26| 
  27| ### 总结
  28| 杨辉三角是二维递推的基础：每行依赖上一行，边界初始化为 1，内部由相邻两个值相加。
  29| 
  30| ## 代码位置
  31| - `problems/leetcodecn/pascals-triangle/main.cpp`
  32| - `problems/leetcodecn/pascals-triangle/main.py`