   1| # leetcodecn longest-common-subsequence 最长公共子序列
   2| 
   3| > 原文摘录，非模型摘要。来源：`problems/leetcodecn/longest-common-subsequence/index.md`（内容哈希 a7ac316b6e6387aa）。
   4| > 摘录可能在 4000 字符处截断；作结论前必须能补读原文全文。
   5| 
   6| ## 元信息（frontmatter 摘录）
   7| - 难度：普及+/提高；标签：['动态规划', '字符串']
   8| 
   9| ## 题目解析（原文摘录）
  10| 
  11| [[TOC]]
  12| 
  13| ### 题意
  14| 求两个字符串的最长公共子序列长度。
  15| 
  16| ### 思路
  17| `dp[i][j]` 表示 `text1[0..i-1]` 和 `text2[0..j-1]` 的 LCS 长度。若 `text1[i-1] == text2[j-1]`，则 `dp[i][j] = dp[i-1][j-1] + 1`；否则 `dp[i][j] = max(dp[i-1][j], dp[i][j-1])`。
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
  28| LCS 是二维 DP 的经典：相等时沿对角线延伸，不等时取上方或左方的较大值。
  29| 
  30| ## 代码位置
  31| - `problems/leetcodecn/longest-common-subsequence/main.cpp`
  32| - `problems/leetcodecn/longest-common-subsequence/main.py`