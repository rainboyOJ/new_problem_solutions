   1| # leetcodecn reverse-nodes-in-k-group K 个一组翻转链表
   2| 
   3| > 原文摘录，非模型摘要。来源：`problems/leetcodecn/reverse-nodes-in-k-group/index.md`（内容哈希 5ff763adc89f671b）。
   4| > 摘录可能在 4000 字符处截断；作结论前必须能补读原文全文。
   5| 
   6| ## 元信息（frontmatter 摘录）
   7| - 难度：提高+/省选-；标签：['链表', '递归', 'cpp', 'python']
   8| 
   9| ## 题目解析（原文摘录）
  10| 
  11| [[TOC]]
  12| 
  13| ### 题意
  14| 
  15| 每 k 个节点一组翻转链表，不足 k 的保持原样。
  16| 
  17| ### 思路
  18| 
  19| 递归版：先检查是否有 k 个节点，有则递归处理后续部分，再翻转当前段。迭代版更节省空间：用 dummy 和 prev 指针维护已翻转到未处理的边界，每轮找到第 k 个节点后翻转段内指针。
  20| 
  21| 
  22| ### 代码
  23| 
  24| @include-code(./main.cpp, cpp)
  25| @include-code(./main.py, python)
  26| ### 复杂度
  27| 
  28| - 时间复杂度：O(n)。
  29| - 空间复杂度：O(1) 迭代，O(n/k) 递归。
  30| 
  31| ### 总结
  32| 
  33| K 个一组翻转是链表操作的综合练习，需要同时处理"寻找段尾"、"段内翻转"、"衔接前后"三个子任务。
  34| 
  35| ## 代码位置
  36| - `problems/leetcodecn/reverse-nodes-in-k-group/brute.cpp`
  37| - `problems/leetcodecn/reverse-nodes-in-k-group/gen.py`
  38| - `problems/leetcodecn/reverse-nodes-in-k-group/main.cpp`
  39| - `problems/leetcodecn/reverse-nodes-in-k-group/main.py`