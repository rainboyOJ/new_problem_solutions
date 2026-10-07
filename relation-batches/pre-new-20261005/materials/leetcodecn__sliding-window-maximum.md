   1| # leetcodecn sliding-window-maximum 滑动窗口最大值
   2| 
   3| > 原文摘录，非模型摘要。来源：`problems/leetcodecn/sliding-window-maximum/index.md`（内容哈希 e5c133678d067ab1）。
   4| > 摘录可能在 4000 字符处截断；作结论前必须能补读原文全文。
   5| 
   6| ## 元信息（frontmatter 摘录）
   7| - 难度：提高+/省选-；标签：['队列', '单调队列', '滑动窗口', '数组', 'cpp', 'python']
   8| 
   9| ## 题目解析（原文摘录）
  10| 
  11| [[TOC]]
  12| 
  13| ### 题意
  14| 
  15| 给定数组和滑动窗口大小 k，返回每个窗口的最大值。
  16| 
  17| ### 思路
  18| 
  19| 暴力 O(nk) 每个窗口扫一遍最大值。优化：用单调递减队列保存窗口内可能成为最大值的元素下标。
  20| 
  21| - 队首始终是当前窗口的最大值。
  22| - 新元素入队时，从队尾弹出所有比它小的元素（它们再也不可能成为最大值）。
  23| - 队首超出窗口范围时弹出。
  24| 
  25| 每个元素至多入队出队一次，均摊 O(n)。
  26| 
  27| 
  28| ### 代码
  29| 
  30| @include-code(./main.cpp, cpp)
  31| @include-code(./main.py, python)
  32| ### 复杂度
  33| 
  34| - 时间复杂度：O(n)，每个元素入队出队各一次。
  35| - 空间复杂度：O(k)，队列最多存 k 个元素。
  36| 
  37| ### 总结
  38| 
  39| 单调队列适用于"滑动窗口最值"问题，"被更大值淘汰"的永久性是保证 O(n) 的关键。该模型与单调栈对称：栈处理的是固定端点向一侧扩展，队列处理的是连续滑动窗口。
  40| 
  41| ## 代码位置
  42| - `problems/leetcodecn/sliding-window-maximum/brute.cpp`
  43| - `problems/leetcodecn/sliding-window-maximum/gen.py`
  44| - `problems/leetcodecn/sliding-window-maximum/main.cpp`
  45| - `problems/leetcodecn/sliding-window-maximum/main.py`