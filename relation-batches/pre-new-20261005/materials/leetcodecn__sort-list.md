   1| # leetcodecn sort-list 排序链表
   2| 
   3| > 原文摘录，非模型摘要。来源：`problems/leetcodecn/sort-list/index.md`（内容哈希 1a7b21ce7ba873cb）。
   4| > 摘录可能在 4000 字符处截断；作结论前必须能补读原文全文。
   5| 
   6| ## 元信息（frontmatter 摘录）
   7| - 难度：普及+/提高；标签：['链表', '排序', '归并排序', 'cpp', 'python']
   8| 
   9| ## 题目解析（原文摘录）
  10| 
  11| [[TOC]]
  12| 
  13| ### 题意
  14| 
  15| 对链表排序，要求 O(n log n) 时间、O(1) 额外空间。
  16| 
  17| ### 思路
  18| 
  19| 数组排序 O(n) 辅助空间。归并排序满足要求：快慢指针找中点分割，递归排序两半，合并两个有序链表。递归深度 O(log n)。
  20| 
  21| 
  22| ### 代码
  23| 
  24| @include-code(./main.cpp, cpp)
  25| @include-code(./main.py, python)
  26| ### 复杂度
  27| 
  28| - 时间复杂度：O(n log n)。
  29| - 空间复杂度：O(log n) 递归栈。
  30| 
  31| ### 总结
  32| 
  33| 链表归并排序是"寻中-递归-合并"三步曲，核心是利用链表 O(1) 拆分和 O(n) 合并的特性。
  34| 
  35| ## 代码位置
  36| - `problems/leetcodecn/sort-list/brute.cpp`
  37| - `problems/leetcodecn/sort-list/gen.py`
  38| - `problems/leetcodecn/sort-list/main.cpp`
  39| - `problems/leetcodecn/sort-list/main.py`