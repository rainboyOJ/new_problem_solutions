   1| # leetcodecn largest-rectangle-in-histogram 柱状图中最大的矩形
   2| 
   3| > 原文摘录，非模型摘要。来源：`problems/leetcodecn/largest-rectangle-in-histogram/index.md`（内容哈希 0034f7e6f2f8cffd）。
   4| > 摘录可能在 4000 字符处截断；作结论前必须能补读原文全文。
   5| 
   6| ## 元信息（frontmatter 摘录）
   7| - 难度：提高+/省选-；标签：['单调栈', '栈']
   8| 
   9| ## 题目解析（原文摘录）
  10| 
  11| [[TOC]]
  12| 
  13| ### 题意
  14| 给定柱状图的高度数组，求能勾勒出的最大矩形面积。
  15| ### 思路
  16| 单调栈保存柱子下标，栈底到栈顶高度递增。弹出时，弹出的高度 `h` 就是被结算柱子的高度，左边界是弹出后新栈顶（第一个更矮的柱），右边界是当前扫描位置 `i`（第一个右边更矮的柱），宽度 = `i - l - 1`。
  17| 
  18| 末尾补一个虚拟的 `0` 高度柱，确保所有栈中剩余柱子都被结算。
  19| ### 代码
  20| @include-code(./main.cpp, cpp)
  21| @include-code(./main.py, python)
  22| ### 复杂度
  23| - 时间复杂度：$O(n)$，每个柱子最多入栈出栈一次。
  24| - 空间复杂度：$O(n)$，栈最多存所有下标。
  25| ### 总结
  26| 柱状图最大矩形是单调栈的经典应用：弹出时左右第一个更矮的位置决定宽度。末尾补 0 是关键技巧，确保结算所有柱子。
  27| 
  28| ## 代码位置
  29| - `problems/leetcodecn/largest-rectangle-in-histogram/main.cpp`
  30| - `problems/leetcodecn/largest-rectangle-in-histogram/main.py`