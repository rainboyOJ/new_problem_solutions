   1| # luogu P5705 【深基2.例7】数字反转
   2| 
   3| > 原文摘录，非模型摘要。来源：`problems/luogu/P5705/index.md`（内容哈希 085a01769d61e5e2）。
   4| > 摘录可能在 4000 字符处截断；作结论前必须能补读原文全文。
   5| 
   6| ## 元信息（frontmatter 摘录）
   7| - 难度：入门；标签：['python', '入门', '字符串', '输入输出']
   8| 
   9| ## 题目解析（原文摘录）
  10| 
  11| [[TOC]]
  12| 
  13| ### 题意
  14| 
  15| 输入一个形如 `123.4` 的一位小数，要求把所有字符倒过来，输出 `4.321`。
  16| 
  17| ### 思路
  18| 
  19| 虽然题面说这是浮点数，但真正要做的是“字符顺序反转”。如果先转成 `float`，可能引入不必要的格式问题；直接把输入当字符串处理最简单。
  20| 
  21| `brute.py` 不适合这题，因为没有算法优化过程；字符串切片反转就是完整解法。
  22| 
  23| ### Python 知识
  24| 
  25| - `input()` 读取一行文本，得到字符串。
  26| - `s[::-1]` 是切片写法，表示从后往前取完整字符串。
  27| - 题目要求保留小数点的位置随字符一起反转，所以不能把输入转成数字再处理。
  28| 
  29| 对应的本地 Python 笔记：
  30| 
  31| - `/home/rainboy/mycode/hugo-blog/content/program_language/python/input_output_and_strings.md`：字符串下标、切片和反转。
  32| - `/home/rainboy/mycode/hugo-blog/content/program_language/python/oj_input_output_cheatsheet.md`：读取字符串输入。
  33| 
  34| ### 代码
  35| 
  36| @include-code(./main.py, python)
  37| 
  38| @include-code(./main.cpp, cpp)
  39| 
  40| ### Guide 风格代码
  41| 
  42| cppbook《C++ 快速入门》教学风格的写法（`std::` 前缀、`i += 1` 循环、0 起始下标）：
  43| 
  44| @include-code(./main-guide.cpp, cpp)
  45| 
  46| ### Pythonic 写法
  47| 
  48| 切片反转：
  49| 
  50| @include-code(./main-pythonic.py, python)
  51| 
  52| 
  53| ### 复杂度
  54| 
  55| 字符串长度固定很小，时间复杂度 $O(1)$，空间复杂度 $O(1)$。
  56| 
  57| ### 总结
  58| 
  59| 看到“数字反转”不要急着转成数值类型。只要题目关心的是字符格式，Python 字符串切片通常更直接、更稳。
  60| 
  61| ## 代码位置
  62| - `problems/luogu/P5705/gen.py`
  63| - `problems/luogu/P5705/main-guide.cpp`
  64| - `problems/luogu/P5705/main-pythonic.py`
  65| - `problems/luogu/P5705/main.cpp`
  66| - `problems/luogu/P5705/main.py`