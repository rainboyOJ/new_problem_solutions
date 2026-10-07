   1| # leetcodecn reverse-linked-list 反转链表
   2| 
   3| > 原文摘录，非模型摘要。来源：`problems/leetcodecn/reverse-linked-list/index.md`（内容哈希 3f888e91d06b7c98）。
   4| > 摘录可能在 4000 字符处截断；作结论前必须能补读原文全文。
   5| 
   6| ## 元信息（frontmatter 摘录）
   7| - 难度：入门；标签：['链表', '递归', 'cpp', 'python']
   8| 
   9| ## 题目解析（原文摘录）
  10| 
  11| [[TOC]]
  12| 
  13| ### 题意
  14| 
  15| 反转单链表。
  16| 
  17| ### 思路
  18| 
  19| 迭代：用 `prev` 和 `cur` 两个指针，每次保存 `cur->next` 后反转指向。递归：`head->next` 后的链表已反转，将 `head` 接到末尾。
  20| 
  21| 
  22| ### 代码
  23| 
  24| @include-code(./main.cpp, cpp)
  25| @include-code(./main.py, python)
  26| ### 复杂度
  27| 
  28| - 时间复杂度：O(n)。
  29| - 空间复杂度：O(1) 迭代，O(n) 递归栈。
  30| 
  31| ### 总结
  32| 
  33| 反转链表是链表操作的基本功。迭代三指针是基础版本，递归反转的核心在于"相信子问题已被解决"。
  34| 
  35| ## 代码位置
  36| - `problems/leetcodecn/reverse-linked-list/brute.cpp`
  37| - `problems/leetcodecn/reverse-linked-list/gen.py`
  38| - `problems/leetcodecn/reverse-linked-list/main.cpp`
  39| - `problems/leetcodecn/reverse-linked-list/main.py`