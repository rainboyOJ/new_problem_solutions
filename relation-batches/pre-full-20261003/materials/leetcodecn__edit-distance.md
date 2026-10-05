   1| # leetcodecn edit-distance 编辑距离
   2| 
   3| > 原文摘录，非模型摘要。来源：`problems/leetcodecn/edit-distance/index.md`（内容哈希 2fda32c0f52dd338）。
   4| > 摘录可能在 4000 字符处截断；作结论前必须能补读原文全文。
   5| 
   6| ## 元信息（frontmatter 摘录）
   7| - 难度：提高+/省选-；标签：['动态规划', '字符串']
   8| 
   9| ## 题目解析（原文摘录）
  10| 
  11| [[TOC]]
  12| 
  13| ### 题意
  14| 求两个字符串之间的最小编辑距离（插入、删除、替换）。
  15| 
  16| ### 思路
  17| `dp[i][j]` 表示 `word1[0..i-1]` 变成 `word2[0..j-1]` 的最少操作数。若 `word1[i-1] == word2[j-1]`，则 `dp[i][j] = dp[i-1][j-1]`；否则 `dp[i][j] = 1 + min(dp[i-1][j], dp[i][j-1], dp[i-1][j-1])`，分别对应删除、插入、替换。
  18| 
  19| ### 代码
  20| @include-code(./main.cpp, cpp)
  21| @include-code(./main.py, python)
  22| 
  23| ### 复杂度
  24| - 时间复杂度：$O(mn)$。
  25| - 空间复杂度：$O(mn)$。
  26| 
  27| ### 总结
  28| 编辑距离的三个操作对应三个相邻状态：删除从 `dp[i-1][j]` 转移，插入从 `dp[i][j-1]` 转移，替换从 `dp[i-1][j-1]` 转移。
  29| 
  30| ## 代码位置
  31| - `problems/leetcodecn/edit-distance/main.cpp`
  32| - `problems/leetcodecn/edit-distance/main.py`