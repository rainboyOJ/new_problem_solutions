   1| # leetcodecn jump-game 跳跃游戏
   2| 
   3| > 原文摘录，非模型摘要。来源：`problems/leetcodecn/jump-game/index.md`（内容哈希 d36eb59cf0489054）。
   4| > 摘录可能在 4000 字符处截断；作结论前必须能补读原文全文。
   5| 
   6| ## 元信息（frontmatter 摘录）
   7| - 难度：普及/提高-；标签：['贪心', '数组']
   8| 
   9| ## 题目解析（原文摘录）
  10| 
  11| [[TOC]]
  12| 
  13| ### 题意
  14| 给定跳跃数组，判断能否到达末尾。
  15| 
  16| ### 思路
  17| 维护 `max_reach` 表示当前最远可达位置。扫描到 `i` 时，若 `i > max_reach` 说明无法到达位置 `i`，返回 false。否则更新 `max_reach = max(max_reach, i + nums[i])`。
  18| 
  19| `max_reach` 是单调不减的扫描不变式：每个可达位置都能进一步扩展可达范围。
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
  30| 跳跃可达性判断是贪心的典型：最远可达位置单调不减，扫描一遍即可。无需回溯或动态规划。
  31| 
  32| ## 代码位置
  33| - `problems/leetcodecn/jump-game/main.cpp`
  34| - `problems/leetcodecn/jump-game/main.py`