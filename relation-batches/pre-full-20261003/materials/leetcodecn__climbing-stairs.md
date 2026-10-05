   1| # leetcodecn climbing-stairs 爬楼梯
   2| 
   3| > 原文摘录，非模型摘要。来源：`problems/leetcodecn/climbing-stairs/index.md`（内容哈希 fdfd5e25eee95e1b）。
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
  14| 爬 n 阶楼梯，每次可走 1 或 2 步，求方法数。
  15| 
  16| ### 思路
  17| 到达第 `i` 阶的方法数 = 从第 `i-1` 阶走 1 步 + 从第 `i-2` 阶走 2 步，即 `dp[i] = dp[i-1] + dp[i-2]`。初值 `dp[1] = 1`，`dp[2] = 2`。
  18| 
  19| 这是 Fibonacci 数列的平移形式。
  20| 
  21| ### 代码
  22| @include-code(./main.cpp, cpp)
  23| @include-code(./main.py, python)
  24| 
  25| ### 复杂度
  26| - 时间复杂度：$O(n)$。
  27| - 空间复杂度：$O(1)$，只需前两个值。
  28| 
  29| ### 总结
  30| 爬楼梯是动态规划入门题：状态定义、转移方程、初值三者缺一不可。`dp[i] = dp[i-1] + dp[i-2]` 是 Fibonacci 型递推，空间可优化到 $O(1)$。
  31| 
  32| ## 代码位置
  33| - `problems/leetcodecn/climbing-stairs/main.cpp`
  34| - `problems/leetcodecn/climbing-stairs/main.py`