   1| # leetcodecn perfect-squares 完全平方数
   2| 
   3| > 原文摘录，非模型摘要。来源：`problems/leetcodecn/perfect-squares/index.md`（内容哈希 206bc79bee0a3ea3）。
   4| > 摘录可能在 4000 字符处截断；作结论前必须能补读原文全文。
   5| 
   6| ## 元信息（frontmatter 摘录）
   7| - 难度：普及/提高-；标签：['动态规划', '完全背包']
   8| 
   9| ## 题目解析（原文摘录）
  10| 
  11| [[TOC]]
  12| 
  13| ### 题意
  14| 求和为 n 的完全平方数的最少个数。
  15| 
  16| ### 思路
  17| `dp[i]` 表示和为 `i` 的最少完全平方数个数。`dp[i] = min(dp[i - j*j] + 1)` 对所有 `j*j <= i`。初值 `dp[0] = 0`，其余 `INF`。
  18| 
  19| ### 代码
  20| @include-code(./main.cpp, cpp)
  21| @include-code(./main.py, python)
  22| 
  23| ### 复杂度
  24| - 时间复杂度：$O(n \sqrt{n})$。
  25| - 空间复杂度：$O(n)$。
  26| 
  27| ### 总结
  28| 完全平方数是完全背包的变形：物品是所有平方数，每个可无限使用，求凑满目标的最少物品数。
  29| 
  30| ## 代码位置
  31| - `problems/leetcodecn/perfect-squares/main.cpp`
  32| - `problems/leetcodecn/perfect-squares/main.py`