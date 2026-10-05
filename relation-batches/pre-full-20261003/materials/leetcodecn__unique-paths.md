   1| # leetcodecn unique-paths 不同路径
   2| 
   3| > 原文摘录，非模型摘要。来源：`problems/leetcodecn/unique-paths/index.md`（内容哈希 eba7587150562291）。
   4| > 摘录可能在 4000 字符处截断；作结论前必须能补读原文全文。
   5| 
   6| ## 元信息（frontmatter 摘录）
   7| - 难度：普及-；标签：['动态规划', '组合数学']
   8| 
   9| ## 题目解析（原文摘录）
  10| 
  11| [[TOC]]
  12| 
  13| ### 题意
  14| 从左上到右下，只能向右或向下，求路径数。
  15| 
  16| ### 思路
  17| `dp[j]` 表示到达当前行第 `j` 列的路径数。首行全为 1，每行从左到右 `dp[j] += dp[j-1]`（上方 + 左方）。空间优化到一维。
  18| 
  19| ### 代码
  20| @include-code(./main.cpp, cpp)
  21| @include-code(./main.py, python)
  22| 
  23| ### 复杂度
  24| - 时间复杂度：$O(mn)$。
  25| - 空间复杂度：$O(n)$。
  26| 
  27| ### 总结
  28| 网格路径计数是二维 DP 的入门题。首行首列初始化为 1，转移方程 `dp[i][j] = dp[i-1][j] + dp[i][j-1]`，空间可优化到一维。
  29| 
  30| ## 代码位置
  31| - `problems/leetcodecn/unique-paths/main.cpp`
  32| - `problems/leetcodecn/unique-paths/main.py`