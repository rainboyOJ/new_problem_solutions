   1| # leetcodecn remove-nth-node-from-end-of-list 删除链表的倒数第 N 个结点
   2| 
   3| > 原文摘录，非模型摘要。来源：`problems/leetcodecn/remove-nth-node-from-end-of-list/index.md`（内容哈希 a22ac9b8ca252752）。
   4| > 摘录可能在 4000 字符处截断；作结论前必须能补读原文全文。
   5| 
   6| ## 元信息（frontmatter 摘录）
   7| - 难度：普及+/提高；标签：['链表', '双指针', 'cpp', 'python']
   8| 
   9| ## 题目解析（原文摘录）
  10| 
  11| [[TOC]]
  12| 
  13| ### 题意
  14| 
  15| 删除链表倒数第 n 个节点，返回头节点。
  16| 
  17| ### 思路
  18| 
  19| 两次遍历版：先求长度再删除。一次遍历版：dummy + 快慢指针，快指针先走 n 步，然后两指针同步走，快指针到尾部时慢指针刚好在待删节点的前一个节点。
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
  33| 快慢指针定位倒数第 k 个元素是链表的经典技巧。dummy 节点统一处理删头节点的边界情况。
  34| 
  35| ## 代码位置
  36| - `problems/leetcodecn/remove-nth-node-from-end-of-list/brute.cpp`
  37| - `problems/leetcodecn/remove-nth-node-from-end-of-list/gen.py`
  38| - `problems/leetcodecn/remove-nth-node-from-end-of-list/main.cpp`
  39| - `problems/leetcodecn/remove-nth-node-from-end-of-list/main.py`