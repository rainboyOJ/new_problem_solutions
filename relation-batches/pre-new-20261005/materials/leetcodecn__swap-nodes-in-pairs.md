   1| # leetcodecn swap-nodes-in-pairs 两两交换链表中的节点
   2| 
   3| > 原文摘录，非模型摘要。来源：`problems/leetcodecn/swap-nodes-in-pairs/index.md`（内容哈希 5454f4b2d510ac56）。
   4| > 摘录可能在 4000 字符处截断；作结论前必须能补读原文全文。
   5| 
   6| ## 元信息（frontmatter 摘录）
   7| - 难度：普及+/提高；标签：['链表', '递归', 'cpp', 'python']
   8| 
   9| ## 题目解析（原文摘录）
  10| 
  11| [[TOC]]
  12| 
  13| ### 题意
  14| 
  15| 两两交换链表中的相邻节点，返回头节点。不能只交换值。
  16| 
  17| ### 思路
  18| 
  19| dummy 头结点下，每轮维护 `prev -> a -> b -> next` 四个指针，把 a 和 b 交换后接入。注意最后 `prev` 移动到 a 的位置，因为 a 已成为已交换段的尾节点。
  20| 
  21| 
  22| ### 代码
  23| 
  24| @include-code(./main.cpp, cpp)
  25| @include-code(./main.py, python)
  26| ### 复杂度
  27| 
  28| - 时间复杂度：O(n)。
  29| - 空间复杂度：O(1)。
  30| 
  31| ### 总结
  32| 
  33| 两两交换是"K 个一组翻转"的特例（k=2），掌握 k=2 的指针重连后推广到一般 k。
  34| 
  35| ## 代码位置
  36| - `problems/leetcodecn/swap-nodes-in-pairs/brute.cpp`
  37| - `problems/leetcodecn/swap-nodes-in-pairs/gen.py`
  38| - `problems/leetcodecn/swap-nodes-in-pairs/main.cpp`
  39| - `problems/leetcodecn/swap-nodes-in-pairs/main.py`