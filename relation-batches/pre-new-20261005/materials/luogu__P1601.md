   1| # luogu P1601 高精度加法
   2| 
   3| > 原文摘录，非模型摘要。来源：`problems/luogu/P1601/index.md`（内容哈希 67f7dd99d875a3ed）。
   4| > 摘录可能在 4000 字符处截断；作结论前必须能补读原文全文。
   5| 
   6| ## 元信息（frontmatter 摘录）
   7| - 难度：入门；标签：['高精度', '数学', 'python']
   8| 
   9| ## 题目解析（原文摘录）
  10| 
  11| [[TOC]]
  12| 
  13| ### 题意
  14| 
  15| 输入两个不超过 $10^{500}$ 的非负整数，输出它们的和。
  16| 
  17| ### 思路
  18| 
  19| 在 C++ 中，这通常需要手写高精度加法。但 Python 的 `int` 是任意精度整数，可以直接保存远大于 `long long` 的整数。
  20| 
  21| 所以本题 Python 解法就是：
  22| 
  23| 1. `int(input())` 读入两个大整数；
  24| 2. 输出 `a + b`。
  25| 
  26| 这题的教学目标是认识 Python 大整数，不创建 `brute.py`。
  27| 
  28| ### Python 知识
  29| 
  30| - `/home/rainboy/mycode/hugo-blog/content/program_language/python/math_tools.md`：Python 的 `int` 不会按 64 位整数溢出。
  31| - `/home/rainboy/mycode/hugo-blog/content/program_language/python/input_output_and_strings.md`：单行整数输入用 `int(input())`。
  32| - 对大整数做 `+` 运算时，Python 会自动处理进位。
  33| 
  34| ### 代码
  35| 
  36| @include-code(./main.py, python)
  37| 
  38| @include-code(./main.cpp, cpp)
  39| 
  40| ### Pythonic 写法
  41| 
  42| 大整数加法：
  43| 
  44| @include-code(./main-pythonic.py, python)
  45| 
  46| 
  47| ### 复杂度
  48| 
  49| 设数字位数为 `L`，大整数加法时间复杂度是 $O(L)$，空间复杂度是 $O(L)$。
  50| 
  51| ### 总结
  52| 
  53| Python 写高精度模板题时，可以先直接使用内置 `int`。学习重点是知道它的优势和复杂度，而不是手写进位。
  54| 
  55| ## 代码位置
  56| - `problems/luogu/P1601/gen.py`
  57| - `problems/luogu/P1601/main-pythonic.py`
  58| - `problems/luogu/P1601/main.cpp`
  59| - `problems/luogu/P1601/main.py`