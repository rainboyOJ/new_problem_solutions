   1| # atcoder abc088_b ABC088B - Card Game for Two
   2| 
   3| > 原文摘录，非模型摘要。来源：`problems/atcoder/abc088_b/index.md`（内容哈希 c0f2ced6d979b129）。
   4| > 摘录可能在 4000 字符处截断；作结论前必须能补读原文全文。
   5| 
   6| ## 元信息（frontmatter 摘录）
   7| - 难度：入门；标签：['贪心', '排序', 'c++', 'haskell']
   8| 
   9| ## 题目解析（原文摘录）
  10| 
  11| [[TOC]]
  12| 
  13| ### 题意
  14| 
  15| $N$ 张牌，Alice 和 Bob 轮流取最大的牌，Alice 先手。求 Alice 总分 - Bob 总分。
  16| 
  17| ### 思路
  18| 
  19| 降序排序后 Alice 取偶数位、Bob 取奇数位，差即为答案。
  20| 
  21| ### 代码
  22| 
  23| @include-code(./main.cpp, cpp)
  24| 
  25| @include-code(./main.hs, haskell)
  26| 
  27| ### 复杂度
  28| 
  29| 时间复杂度 $O(N \log N)$，空间复杂度 $O(N)$。
  30| 
  31| ### 总结
  32| 
  33| 贪心取最大 + 交替分配。
  34| 
  35| ## 代码位置
  36| - `problems/atcoder/abc088_b/brute.cpp`
  37| - `problems/atcoder/abc088_b/gen.py`
  38| - `problems/atcoder/abc088_b/main.cpp`