   1| # leetcodecn minimum-window-substring 最小覆盖子串
   2| 
   3| > 原文摘录，非模型摘要。来源：`problems/leetcodecn/minimum-window-substring/index.md`（内容哈希 2c505c7cf63c32a5）。
   4| > 摘录可能在 4000 字符处截断；作结论前必须能补读原文全文。
   5| 
   6| ## 元信息（frontmatter 摘录）
   7| - 难度：提高+/省选-；标签：['哈希表', '字符串', '滑动窗口', 'cpp', 'python']
   8| 
   9| ## 题目解析（原文摘录）
  10| 
  11| [[TOC]]
  12| 
  13| ### 题意
  14| 
  15| 给定字符串 s 和 t，找出 s 中包含 t 所有字符的最短子串。
  16| 
  17| ### 思路
  18| 
  19| 滑动窗口：右指针不断扩展直到覆盖 t 的所有字符，然后左指针收缩到刚好不满足，记录最短长度。
  20| 
  21| 用 `need[128]` 计数 t 中各字符的需求，`need` 表示仍有需求的字符种类数。窗口滑动时：
  22| - 右指针字符入窗口，若其需求变为 0，`have` 加一。
  23| - 当 `have == need` 时说明当前窗口满足要求，尝试收缩左指针。
  24| - 左指针字符出窗口，若其需求变为 1，`have` 减一，窗口不再满足。
  25| 
  26| 
  27| ### 代码
  28| 
  29| @include-code(./main.cpp, cpp)
  30| @include-code(./main.py, python)
  31| ### 复杂度
  32| 
  33| - 时间复杂度：O(n)，左右指针各移动一次。
  34| - 空间复杂度：O(|Σ|)，字符集大小。
  35| 
  36| ### 总结
  37| 
  38| 最小覆盖子串是滑动窗口的进阶模型：右端扩张满足约束，左端收缩寻找最优。用 `need/have` 变量代替每次比较整个计数数组，将 O(n·|Σ|) 优化到 O(n)。
  39| 
  40| ## 代码位置
  41| - `problems/leetcodecn/minimum-window-substring/brute.cpp`
  42| - `problems/leetcodecn/minimum-window-substring/gen.py`
  43| - `problems/leetcodecn/minimum-window-substring/main.cpp`
  44| - `problems/leetcodecn/minimum-window-substring/main.py`