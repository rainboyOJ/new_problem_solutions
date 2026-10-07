   1| # leetcodecn binary-tree-inorder-traversal 二叉树的中序遍历
   2| 
   3| > 原文摘录，非模型摘要。来源：`problems/leetcodecn/binary-tree-inorder-traversal/index.md`（内容哈希 a8db9b438dc1b267）。
   4| > 摘录可能在 4000 字符处截断；作结论前必须能补读原文全文。
   5| 
   6| ## 元信息（frontmatter 摘录）
   7| - 难度：入门；标签：['二叉树', '栈', '递归', 'cpp', 'python']
   8| 
   9| ## 题目解析（原文摘录）
  10| 
  11| [[TOC]]
  12| 
  13| ### 题意
  14| 
  15| 返回二叉树中序遍历的节点值序列。
  16| 
  17| ### 思路
  18| 
  19| 递归：左-根-右。迭代：显式栈模拟递归，先把左链全部入栈，弹出访问后转向右子树。
  20| 
  21| 
  22| ### 代码
  23| 
  24| @include-code(./main.cpp, cpp)
  25| @include-code(./main.py, python)
  26| ### 复杂度
  27| 
  28| - 时间复杂度：O(n)。
  29| - 空间复杂度：O(n) 递归栈/显式栈。
  30| 
  31| ### 总结
  32| 
  33| 中序迭代栈是"沿左链入栈 → 弹出访问 → 转向右子树"三部曲，是后续很多树操作的基础。
  34| 
  35| ## 代码位置
  36| - `problems/leetcodecn/binary-tree-inorder-traversal/brute.cpp`
  37| - `problems/leetcodecn/binary-tree-inorder-traversal/gen.py`
  38| - `problems/leetcodecn/binary-tree-inorder-traversal/main.cpp`
  39| - `problems/leetcodecn/binary-tree-inorder-traversal/main.py`