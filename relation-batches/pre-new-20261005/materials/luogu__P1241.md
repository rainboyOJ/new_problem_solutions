   1| # luogu P1241 括号序列
   2| 
   3| > 原文摘录，非模型摘要。来源：`problems/luogu/P1241/index.md`（内容哈希 0cf79d4ce31adfaf）。
   4| > 摘录可能在 4000 字符处截断；作结论前必须能补读原文全文。
   5| 
   6| ## 元信息（frontmatter 摘录）
   7| - 难度：普及-；标签：['栈', '字符串', '模拟', 'python']
   8| 
   9| ## 题目解析（原文摘录）
  10| 
  11| [[TOC]]
  12| 
  13| ### 题意
  14| 
  15| 按指定规则从左到右给括号配对：右括号只检查左侧最近的未匹配左括号，类型相同才匹配。最后为每个未匹配括号在旁边补一个对应括号。
  16| 
  17| ### 思路
  18| 
  19| 栈保存尚未匹配的左括号下标。遇到右括号时，只看栈顶：类型相同则弹栈并标记两个位置；类型不同则当前右括号匹配失败，栈顶左括号仍保持未匹配，不能越过它去找更早括号。
  20| 
  21| 扫描结束后按原顺序输出。已匹配字符原样保留；未匹配的 `(` 或 `)` 输出 `()`，未匹配的 `[` 或 `]` 输出 `[]`。
  22| 
  23| ### Python 知识
  24| 
  25| - 列表保存下标栈，`stack[-1]` 取得最近未匹配左括号。
  26| - 字典 `opening_for` 表示右括号所需的左括号，`completion` 表示每种未匹配字符的补全结果。
  27| - `matched[index] = matched[stack.pop()] = True` 同时标记一对位置。
  28| - 最终用生成器和 `"".join` 构造字符串，避免循环中反复拼接。
  29| - `/home/rainboy/mycode/hugo-blog/content/program_language/python/input_output_and_strings.md`：字符串不可变与 `join`。
  30| - `/home/rainboy/mycode/hugo-blog/content/program_language/python/generator_expression.md`：按条件生成输出片段。
  31| 
  32| ### 代码
  33| 
  34| @include-code(./main.py, python)
  35| 
  36| @include-code(./main.cpp, cpp)
  37| 
  38| 
  39| ### 复杂度
  40| 
  41| 每个字符最多入栈、出栈一次，时间和空间复杂度均为 $O(|s|)$。
  42| 
  43| ### 总结
  44| 
  45| 本题规则与普通“遇到不匹配就弹栈”不同：右括号只能检查最近未匹配左括号，类型不符时两者都保留为未匹配。
  46| 
  47| ## 代码位置
  48| - `problems/luogu/P1241/main.cpp`
  49| - `problems/luogu/P1241/main.py`