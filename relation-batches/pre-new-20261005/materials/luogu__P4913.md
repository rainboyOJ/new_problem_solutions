   1| # luogu P4913 【深基16.例3】二叉树深度
   2| 
   3| > 原文摘录，非模型摘要。来源：`problems/luogu/P4913/index.md`（内容哈希 f808e3535cd544ba）。
   4| > 摘录可能在 4000 字符处截断；作结论前必须能补读原文全文。
   5| 
   6| ## 元信息（frontmatter 摘录）
   7| - 难度：普及-；标签：['二叉树', 'DFS', '栈', 'python']
   8| 
   9| ## 题目解析（原文摘录）
  10| 
  11| [[TOC]]
  12| 
  13| ### 题意
  14| 
  15| 给出最多一百万节点二叉树的左右儿子编号，根为 `1`，求最大层数。
  16| 
  17| ### 思路
  18| 
  19| 递归公式是 `depth(node)=1+max(depth(left),depth(right))`，但极端链形树会超过 Python 递归深度。
  20| 
  21| 使用显式栈保存待访问节点和它的层数。每弹出一个节点就更新最大值，并把非空孩子以 `depth+1` 入栈。
  22| 
  23| ### Python 知识
  24| 
  25| - `array('i')` 以紧凑 C 整数保存百万编号，避免普通 Python 整数列表的较大对象开销。
  26| - 两个 `array` 分别保存节点和深度，最坏链形树也不会递归爆栈。
  27| - `pop/append` 把数组当后进先出栈。
  28| - `/home/rainboy/mycode/hugo-blog/content/program_language/python/cpp_to_python_pitfalls.md`：Python 递归深度限制。
  29| - `/home/rainboy/mycode/hugo-blog/content/program_language/python/brute_force_validation.md`：显式状态遍历。
  30| 
  31| ### 代码
  32| 
  33| @include-code(./main.py, python)
  34| 
  35| @include-code(./main.cpp, cpp)
  36| 
  37| 
  38| ### 复杂度
  39| 
  40| 每个节点访问一次，时间复杂度 $O(n)$；左右儿子和显式栈空间为 $O(n)$。
  41| 
  42| ### 总结
  43| 
  44| 百万节点时，算法仍是普通 DFS，但 Python 实现必须同时关注递归深度和整数对象内存，`array` 加显式栈更稳。
  45| 
  46| ## 代码位置
  47| - `problems/luogu/P4913/main.cpp`
  48| - `problems/luogu/P4913/main.py`