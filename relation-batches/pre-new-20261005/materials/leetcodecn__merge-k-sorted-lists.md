   1| # leetcodecn merge-k-sorted-lists 合并 K 个升序链表
   2| 
   3| > 原文摘录，非模型摘要。来源：`problems/leetcodecn/merge-k-sorted-lists/index.md`（内容哈希 1f4bc8ce8d0e0cf1）。
   4| > 摘录可能在 4000 字符处截断；作结论前必须能补读原文全文。
   5| 
   6| ## 元信息（frontmatter 摘录）
   7| - 难度：提高+/省选-；标签：['链表', '堆', '分治', 'cpp', 'python']
   8| 
   9| ## 题目解析（原文摘录）
  10| 
  11| [[TOC]]
  12| 
  13| ### 题意
  14| 
  15| 合并 k 个升序链表，返回一个升序链表。
  16| 
  17| ### 思路
  18| 
  19| 分治两两合并 O(N log K)。堆方法：把所有链表的头节点放入小根堆，每次弹出最小值节点加入结果，并将该节点的 next 入堆。每个节点入堆出堆各一次，O(N log K)。
  20| 
  21| 
  22| ### 代码
  23| 
  24| @include-code(./main.cpp, cpp)
  25| @include-code(./main.py, python)
  26| ### 复杂度
  27| 
  28| - 时间复杂度：O(N log K)，N 为总节点数，K 为链表数。
  29| - 空间复杂度：O(K)，堆的大小。
  30| 
  31| ### 总结
  32| 
  33| "多路归并用小根堆维护 k 个候选"是处理多路有序数据合并的标准模型。
  34| 
  35| ## 代码位置
  36| - `problems/leetcodecn/merge-k-sorted-lists/brute.cpp`
  37| - `problems/leetcodecn/merge-k-sorted-lists/gen.py`
  38| - `problems/leetcodecn/merge-k-sorted-lists/main.cpp`
  39| - `problems/leetcodecn/merge-k-sorted-lists/main.py`