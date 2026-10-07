   1| # leetcodecn maximum-depth-of-binary-tree 二叉树的最大深度
   2| 
   3| > 原文摘录，非模型摘要。来源：`problems/leetcodecn/maximum-depth-of-binary-tree/index.md`（内容哈希 546cd53356c0e3f5）。
   4| > 摘录可能在 4000 字符处截断；作结论前必须能补读原文全文。
   5| 
   6| ## 元信息（frontmatter 摘录）
   7| - 难度：入门；标签：['二叉树', '递归', 'BFS', 'cpp', 'python']
   8| 
   9| ## 题目解析（原文摘录）
  10| 
  11| [[TOC]]
  12| 
  13| ### 题意
  14| 
  15| 返回二叉树的最大深度（根到最远叶子节点的路径长度）。
  16| 
  17| ### 思路
  18| 
  19| 递归：空节点深度 0，非空节点深度 = 1 + max(左子树深度, 右子树深度)。
  20| 
  21| BFS 层序遍历也可以统计深度。
  22| 
  23| 
  24| ### 代码
  25| 
  26| @include-code(./main.cpp, cpp)
  27| @include-code(./main.py, python)
  28| ### 复杂度
  29| 
  30| - 时间复杂度：O(n)。
  31| - 空间复杂度：O(height) 递归栈。
  32| 
  33| ### 总结
  34| 
  35| 树的最大深度是树形 DP 的最简单例子——通过子问题定义"以某节点为根的子树深度"。
  36| 
  37| ## 代码位置
  38| - `problems/leetcodecn/maximum-depth-of-binary-tree/brute.cpp`
  39| - `problems/leetcodecn/maximum-depth-of-binary-tree/gen.py`
  40| - `problems/leetcodecn/maximum-depth-of-binary-tree/main.cpp`
  41| - `problems/leetcodecn/maximum-depth-of-binary-tree/main.py`