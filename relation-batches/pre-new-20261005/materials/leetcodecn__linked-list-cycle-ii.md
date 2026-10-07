   1| # leetcodecn linked-list-cycle-ii 环形链表 II
   2| 
   3| > 原文摘录，非模型摘要。来源：`problems/leetcodecn/linked-list-cycle-ii/index.md`（内容哈希 5a760e387fd4a7a7）。
   4| > 摘录可能在 4000 字符处截断；作结论前必须能补读原文全文。
   5| 
   6| ## 元信息（frontmatter 摘录）
   7| - 难度：普及+/提高；标签：['链表', '双指针', '哈希表', 'cpp', 'python']
   8| 
   9| ## 题目解析（原文摘录）
  10| 
  11| [[TOC]]
  12| 
  13| ### 题意
  14| 
  15| 返回链表开始入环的第一个节点。无环返回 nullptr。
  16| 
  17| ### 思路
  18| 
  19| 快慢指针相遇后，慢指针从头重新走，快指针从相遇点继续走（每次一步），再次相遇处即入环节点。
  20| 
  21| 数学推导：设环前长度 a，环长 b，相遇时 slow 走了 a + x，fast 走了 a + x + kb。由 `2(a+x) = a+x+kb` 得 `a = (k-1)b + (b-x)`，所以从头和相遇点同步走一定在入环点相遇。
  22| 
  23| 
  24| ### 代码
  25| 
  26| @include-code(./main.cpp, cpp)
  27| @include-code(./main.py, python)
  28| ### 复杂度
  29| 
  30| - 时间复杂度：O(n)。
  31| - 空间复杂度：O(1)。
  32| 
  33| ### 总结
  34| 
  35| Floyd 判环的进阶版，利用距离关系找到环的入口。
  36| 
  37| ## 代码位置
  38| - `problems/leetcodecn/linked-list-cycle-ii/brute.cpp`
  39| - `problems/leetcodecn/linked-list-cycle-ii/gen.py`
  40| - `problems/leetcodecn/linked-list-cycle-ii/main.cpp`
  41| - `problems/leetcodecn/linked-list-cycle-ii/main.py`