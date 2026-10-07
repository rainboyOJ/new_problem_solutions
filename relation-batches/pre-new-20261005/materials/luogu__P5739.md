   1| # luogu P5739 【深基7.例7】计算阶乘
   2| 
   3| > 原文摘录，非模型摘要。来源：`problems/luogu/P5739/index.md`（内容哈希 53bec54b541ff560）。
   4| > 摘录可能在 4000 字符处截断；作结论前必须能补读原文全文。
   5| 
   6| ## 元信息（frontmatter 摘录）
   7| - 难度：入门；标签：['递归', '数学', '函数', 'python']
   8| 
   9| ## 题目解析（原文摘录）
  10| 
  11| [[TOC]]
  12| 
  13| ### 题意
  14| 
  15| 输入一个正整数 `n`，输出 `n!`。题目挑战尝试不使用循环完成。
  16| 
  17| ### 思路
  18| 
  19| 阶乘的递归定义是：
  20| 
  21| ```text
  22| 1! = 1
  23| n! = n * (n-1)!  (n > 1)
  24| ```
  25| 
  26| 把这个定义直接写成函数：
  27| 
  28| ```python
  29| def factorial(n):
  30|     if n == 1:
  31|         return 1
  32|     return n * factorial(n - 1)
  33| ```
  34| 
  35| 因为 `n <= 12`，递归深度很小，不需要调整递归限制。
  36| 
  37| 这题是递归函数练习，不创建 `brute.py`。
  38| 
  39| ### Python 知识
  40| 
  41| - `/home/rainboy/mycode/hugo-blog/content/program_language/python/math_tools.md`：Python 整数不会溢出，适合直接计算小范围阶乘。
  42| - `/home/rainboy/mycode/hugo-blog/content/program_language/python/input_output_and_strings.md`：单个整数输入用 `int(input())`。
  43| - 递归函数必须有明确的终止条件，否则会无限调用。
  44| - Python 函数用 `return` 把计算结果交回上一层。
  45| 
  46| ### 代码
  47| 
  48| @include-code(./main.py, python)
  49| 
  50| @include-code(./main.cpp, cpp)
  51| 
  52| ### Guide 风格代码
  53| 
  54| cppbook《C++ 快速入门》教学风格的写法（`std::` 前缀、`i += 1` 循环、0 起始下标）：
  55| 
  56| @include-code(./main-guide.cpp, cpp)
  57| 
  58| ### Pythonic 写法
  59| 
  60| math.factorial：
  61| 
  62| @include-code(./main-pythonic.py, python)
  63| 
  64| 
  65| ### 复杂度
  66| 
  67| 递归调用 `n` 层，时间复杂度是 $O(n)$，递归栈空间复杂度是 $O(n)$。
  68| 
  69| ### 总结
  70| 
  71| 递归适合直接表达“当前问题依赖更小的同类问题”。阶乘是最基础的递归例子：先写终止条件，再写递推关系。
  72| 
  73| ## 代码位置
  74| - `problems/luogu/P5739/gen.py`
  75| - `problems/luogu/P5739/main-guide.cpp`
  76| - `problems/luogu/P5739/main-pythonic.py`
  77| - `problems/luogu/P5739/main.cpp`
  78| - `problems/luogu/P5739/main.py`