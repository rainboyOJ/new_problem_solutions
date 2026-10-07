   1| # leetcodecn jump-game-ii 跳跃游戏 II
   2| 
   3| > 原文摘录，非模型摘要。来源：`problems/leetcodecn/jump-game-ii/index.md`（内容哈希 11a2033e1d7650dd）。
   4| > 摘录可能在 4000 字符处截断；作结论前必须能补读原文全文。
   5| 
   6| ## 元信息（frontmatter 摘录）
   7| - 难度：普及+/提高；标签：['贪心', '数组']
   8| 
   9| ## 题目解析（原文摘录）
  10| 
  11| [[TOC]]
  12| 
  13| ### 题意
  14| 给定跳跃数组（保证可达），求最少跳跃次数。
  15| 
  16| ### 思路
  17| 用 BFS 层次遍历的思想：每跳一步，当前"层"的范围是 `[l, r]`，下一层最远可达 `next = max(i + nums[i])` for `i` in `[l, r]`。当 `r` 到达末尾时停止。
  18| 
  19| 每层对应一次跳跃，`next` 是下一层的右边界。
  20| 
  21| ### 代码
  22| @include-code(./main.cpp, cpp)
  23| @include-code(./main.py, python)
  24| 
  25| ### 复杂度
  26| - 时间复杂度：$O(n)$。
  27| - 空间复杂度：$O(1)$。
  28| 
  29| ### 总结
  30| 最少跳跃次数 = BFS 层数。每层扩展最远可达位置，贪心选择下一层边界。与跳跃游戏 I 的区别是：I 只判断可达性，II 要最小化步数。
  31| 
  32| ## 代码位置
  33| - `problems/leetcodecn/jump-game-ii/main.cpp`
  34| - `problems/leetcodecn/jump-game-ii/main.py`