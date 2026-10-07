   1| # leetcodecn min-stack 最小栈
   2| 
   3| > 原文摘录，非模型摘要。来源：`problems/leetcodecn/min-stack/index.md`（内容哈希 5842619fa95b57c9）。
   4| > 摘录可能在 4000 字符处截断；作结论前必须能补读原文全文。
   5| 
   6| ## 元信息（frontmatter 摘录）
   7| - 难度：普及-；标签：['栈', '数据结构']
   8| 
   9| ## 题目解析（原文摘录）
  10| 
  11| [[TOC]]
  12| 
  13| ### 题意
  14| 
  15| 设计一个栈，支持 `push`、`pop`、`top`、`getMin` 四个操作，`getMin` 要求 $O(1)$。
  16| 
  17| ### 思路
  18| 
  19| 核心思路：栈中每个元素同时保存"当前值"和"截至该层的最小值"。`push` 时，`min` 字段取当前值与栈顶 `min` 的较小值；`getMin` 直接读栈顶的 `min` 字段。
  20| 
  21| 这样 `pop` 后新的栈顶 `min` 自然就是剩余元素的最小值，无需额外维护。
  22| 
  23| ### 代码
  24| 
  25| @include-code(./main.cpp, cpp)
  26| 
  27| @include-code(./main.py, python)
  28| 
  29| ### 复杂度
  30| 
  31| - 时间复杂度：每个操作 $O(1)$。
  32| - 空间复杂度：$O(n)$，每个元素存一对值。
  33| 
  34| ### 总结
  35| 
  36| 最小栈的关键是"每层同时保存当前值与截至该层的最小值"，使得 `pop` 后最小值自动更新，不需要辅助栈或重新扫描。
  37| 
  38| ## 代码位置
  39| - `problems/leetcodecn/min-stack/main.cpp`
  40| - `problems/leetcodecn/min-stack/main.py`