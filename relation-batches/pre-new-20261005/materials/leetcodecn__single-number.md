   1| # leetcodecn single-number 只出现一次的数字
   2| 
   3| > 原文摘录，非模型摘要。来源：`problems/leetcodecn/single-number/index.md`（内容哈希 48828b91ec299b84）。
   4| > 摘录可能在 4000 字符处截断；作结论前必须能补读原文全文。
   5| 
   6| ## 元信息（frontmatter 摘录）
   7| - 难度：入门；标签：['位运算', '技巧']
   8| 
   9| ## 题目解析（原文摘录）
  10| 
  11| [[TOC]]
  12| 
  13| ### 题意
  14| 找出数组中唯一只出现一次的数（其余均出现两次）。
  15| 
  16| ### 思路
  17| 利用异或性质：`x ^ x = 0`，`x ^ 0 = x`，异或满足交换律和结合律。将所有元素异或起来，成对元素互相抵消，结果就是只出现一次的数。
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
  28| 异或去重是位运算的经典技巧：`x ^ x = 0` 保证成对元素消除，`x ^ 0 = x` 保证结果保留。
  29| 
  30| ## 代码位置
  31| - `problems/leetcodecn/single-number/main.cpp`
  32| - `problems/leetcodecn/single-number/main.py`