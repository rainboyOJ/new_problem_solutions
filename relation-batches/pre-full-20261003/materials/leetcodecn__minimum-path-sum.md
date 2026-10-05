   1| # leetcodecn minimum-path-sum 最小路径和
   2| 
   3| > 原文摘录，非模型摘要。来源：`problems/leetcodecn/minimum-path-sum/index.md`（内容哈希 eafa590c3a32b6a7）。
   4| > 摘录可能在 4000 字符处截断；作结论前必须能补读原文全文。
   5| 
   6| ## 元信息（frontmatter 摘录）
   7| - 难度：普及-；标签：['动态规划', '网格']
   8| 
   9| ## 题目解析（原文摘录）
  10| 
  11| [[TOC]]
  12| 
  13| ### 题意
  14| 网格从左上到右下，只能向右或向下，求最小路径和。
  15| 
  16| ### 思路
  17| `dp[j]` 表示到达当前行第 j 列的最小路径和。首行只累加，内部 `dp[j] = min(dp[j], dp[j-1]) + grid[i][j]`（上方和左方取较小值）。
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
  28| 最小路径和与不同路径的转移结构相同，只是把"加法计数"换成"取最小值加权重"。
  29| 
  30| ## 代码位置
  31| - `problems/leetcodecn/minimum-path-sum/main.cpp`
  32| - `problems/leetcodecn/minimum-path-sum/main.py`