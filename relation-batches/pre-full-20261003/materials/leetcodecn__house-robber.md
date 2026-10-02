   1| # leetcodecn house-robber 打家劫舍
   2| 
   3| > 原文摘录，非模型摘要。来源：`problems/leetcodecn/house-robber/index.md`（内容哈希 a3c3dfd799a6071e）。
   4| > 摘录可能在 4000 字符处截断；作结论前必须能补读原文全文。
   5| 
   6| ## 元信息（frontmatter 摘录）
   7| - 难度：普及-；标签：['动态规划', '递推']
   8| 
   9| ## 题目解析（原文摘录）
  10| 
  11| [[TOC]]
  12| 
  13| ### 题意
  14| 不能偷相邻房屋，求最大金额。
  15| 
  16| ### 思路
  17| 用 `a` 和 `b` 分别表示"不偷当前"和"偷当前"的最大金额。`a = b`（上一轮的偷），`b = max(b, a + nums[i])`（取偷与不偷的较大值）。空间优化到 $O(1)$。
  18| 
  19| ### 代码
  20| @include-code(./main.cpp, cpp)
  21| @include-code(./main.py, python)
  22| 
  23| ### 复杂度
  24| - 时间复杂度：$O(n)$。
  25| - 空间复杂度：$O(1)$。
  26| 
  27| ### 总结
  28| 打家劫舍是线性 DP 的典型：状态只需"前一个"和"前两个"，空间优化到 $O(1)$。
  29| 
  30| ## 代码位置
  31| - `problems/leetcodecn/house-robber/main.cpp`
  32| - `problems/leetcodecn/house-robber/main.py`