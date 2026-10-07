   1| # leetcodecn find-the-duplicate-number 寻找重复数
   2| 
   3| > 原文摘录，非模型摘要。来源：`problems/leetcodecn/find-the-duplicate-number/index.md`（内容哈希 c0daa8c18efa06e1）。
   4| > 摘录可能在 4000 字符处截断；作结论前必须能补读原文全文。
   5| 
   6| ## 元信息（frontmatter 摘录）
   7| - 难度：提高+/省选-；标签：['快慢指针', '链表', '技巧']
   8| 
   9| ## 题目解析（原文摘录）
  10| 
  11| [[TOC]]
  12| 
  13| ### 题意
  14| 在 n+1 个元素（值域 [1,n]）中找重复数，不修改数组，O(1) 空间。
  15| 
  16| ### 思路
  17| 把 `nums[i]` 视为从 `i` 到 `nums[i]` 的 next 指针，数组构成一个有环链表（重复值导致两个节点指向同一后继）。Floyd 快慢指针找环入口即为重复数。
  18| 
  19| ### 代码
  20| @include-code(./main.cpp, cpp)
  21| @include-code(./main.py, python)
  22| 
  23| ### 复杂度
  24| - 时间复杂度：$O(n)$。
  25| - 空间复杂度：$O(1)$。
  26| 
  27| ### 总结
  28| 把数组值视为 next 指针是本题的关键映射。重复数意味着两个位置指向同一个后继，形成环。Floyd 找环入口的证明与链表环检测完全相同。
  29| 
  30| ## 代码位置
  31| - `problems/leetcodecn/find-the-duplicate-number/main.cpp`
  32| - `problems/leetcodecn/find-the-duplicate-number/main.py`