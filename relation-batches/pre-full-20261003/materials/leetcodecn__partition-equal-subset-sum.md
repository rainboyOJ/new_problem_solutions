   1| # leetcodecn partition-equal-subset-sum 分割等和子集
   2| 
   3| > 原文摘录，非模型摘要。来源：`problems/leetcodecn/partition-equal-subset-sum/index.md`（内容哈希 ec380a8b6656d105）。
   4| > 摘录可能在 4000 字符处截断；作结论前必须能补读原文全文。
   5| 
   6| ## 元信息（frontmatter 摘录）
   7| - 难度：普及+/提高；标签：['动态规划', '0/1背包']
   8| 
   9| ## 题目解析（原文摘录）
  10| 
  11| [[TOC]]
  12| 
  13| ### 题意
  14| 判断数组能否分成两个和相等的子集。
  15| 
  16| ### 思路
  17| 若总和为奇数，不可能。否则目标为 `sum/2`，转化为 0/1 背包：从 `nums` 中选若干数，和恰好为 `target`。`dp[i]` 表示和 `i` 是否可达，倒序更新避免重复使用同一元素。
  18| 
  19| ### 代码
  20| @include-code(./main.cpp, cpp)
  21| @include-code(./main.py, python)
  22| 
  23| ### 复杂度
  24| - 时间复杂度：$O(n \cdot \text{target})$。
  25| - 空间复杂度：$O(\text{target})$。
  26| 
  27| ### 总结
  28| 分割等和子集是 0/1 背包的判定版本。倒序更新是关键：正序更新会导致同一元素被多次选取。
  29| 
  30| ## 代码位置
  31| - `problems/leetcodecn/partition-equal-subset-sum/main.cpp`
  32| - `problems/leetcodecn/partition-equal-subset-sum/main.py`