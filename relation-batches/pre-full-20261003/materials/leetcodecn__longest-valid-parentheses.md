   1| # leetcodecn longest-valid-parentheses 最长有效括号
   2| 
   3| > 原文摘录，非模型摘要。来源：`problems/leetcodecn/longest-valid-parentheses/index.md`（内容哈希 d56cbbbb2e9539f6）。
   4| > 摘录可能在 4000 字符处截断；作结论前必须能补读原文全文。
   5| 
   6| ## 元信息（frontmatter 摘录）
   7| - 难度：提高+/省选-；标签：['栈', '动态规划', '字符串']
   8| 
   9| ## 题目解析（原文摘录）
  10| 
  11| [[TOC]]
  12| 
  13| ### 题意
  14| 求最长有效括号子串的长度。
  15| 
  16| ### 思路
  17| 栈中保存下标。初始压入 `-1` 作为虚拟边界。遇到 `(` 压入下标；遇到 `)` 弹出栈顶，若栈空则压入当前下标作为新边界，否则用当前下标减去栈顶计算有效长度。
  18| 
  19| ### 代码
  20| @include-code(./main.cpp, cpp)
  21| @include-code(./main.py, python)
  22| 
  23| ### 复杂度
  24| - 时间复杂度：$O(n)$。
  25| - 空间复杂度：$O(n)$。
  26| 
  27| ### 总结
  28| 栈解法的关键是栈中始终保存"最后一个未被匹配的右括号下标"作为边界。弹出后栈顶就是有效子串的起点前一个位置，差值即为长度。
  29| 
  30| ## 代码位置
  31| - `problems/leetcodecn/longest-valid-parentheses/main.cpp`
  32| - `problems/leetcodecn/longest-valid-parentheses/main.py`