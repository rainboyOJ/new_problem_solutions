   1| # leetcodecn coin-change 零钱兑换
   2| 
   3| > 原文摘录，非模型摘要。来源：`problems/leetcodecn/coin-change/index.md`（内容哈希 45cb7aa8261d304e）。
   4| > 摘录可能在 4000 字符处截断；作结论前必须能补读原文全文。
   5| 
   6| ## 元信息（frontmatter 摘录）
   7| - 难度：普及+/提高；标签：['动态规划', '完全背包']
   8| 
   9| ## 题目解析（原文摘录）
  10| 
  11| [[TOC]]
  12| 
  13| ### 题意
  14| 给定硬币面额和金额，求最少硬币数。每种硬币无限使用。
  15| 
  16| ### 思路
  17| `dp[i]` 表示凑成金额 `i` 的最少硬币数。`dp[i] = min(dp[i-c] + 1)` 对所有 `c <= i`。初值 `dp[0] = 0`，其余 `amount + 1`（不可达哨兵）。最终 `dp[amount] > amount` 则无解。
  18| 
  19| ### 代码
  20| @include-code(./main.cpp, cpp)
  21| @include-code(./main.py, python)
  22| 
  23| ### 复杂度
  24| - 时间复杂度：$O(n \cdot \text{amount})$。
  25| - 空间复杂度：$O(\text{amount})$。
  26| 
  27| ### 总结
  28| 零钱兑换是完全背包求最少物品数的经典题。不可达哨兵用 `amount + 1`（而非 `INF`），因为最多用 `amount` 个 1 元硬币。
  29| 
  30| ## 代码位置
  31| - `problems/leetcodecn/coin-change/main.cpp`
  32| - `problems/leetcodecn/coin-change/main.py`