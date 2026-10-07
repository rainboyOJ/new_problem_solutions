   1| # luogu P5722 【深基4.例11】数列求和
   2| 
   3| > 原文摘录，非模型摘要。来源：`problems/luogu/P5722/index.md`（内容哈希 66753d406199c48e）。
   4| > 摘录可能在 4000 字符处截断；作结论前必须能补读原文全文。
   5| 
   6| ## 元信息（frontmatter 摘录）
   7| - 难度：入门；标签：['入门', '循环', '模拟', 'python']
   8| 
   9| ## 题目解析（原文摘录）
  10| 
  11| [[TOC]]
  12| 
  13| ### 题意
  14| 
  15| 输入正整数 `n`，求：
  16| 
  17| $$
  18| 1+2+3+\cdots+n
  19| $$
  20| 
  21| 题目明确要求不要直接使用等差数列求和公式，所以这里练习循环累加。
  22| 
  23| ### 思路
  24| 
  25| 用变量 `answer` 保存当前已经累加出来的和。
  26| 
  27| 从 `1` 到 `n` 依次枚举每个数 `x`，每次执行：
  28| 
  29| ```text
  30| answer = answer + x
  31| ```
  32| 
  33| 循环结束后，`answer` 就是 `1` 到 `n` 的总和。
  34| 
  35| 这题本身就是循环语法练习，`brute.py` 会和正解完全相同，因此不创建额外暴力文件。
  36| 
  37| ### Python 知识
  38| 
  39| - `/home/rainboy/mycode/hugo-blog/content/program_language/python/input_output_and_strings.md`：用 `int(input())` 读取一个整数。
  40| - `range(1, n + 1)` 会生成 `1, 2, ..., n`，右端点 `n + 1` 不会被取到。
  41| - `answer += x` 是 `answer = answer + x` 的简写，适合表达累加。
  42| - `print(answer, end="")` 输出最终答案。
  43| 
  44| ### 代码
  45| 
  46| @include-code(./main.py, python)
  47| 
  48| @include-code(./main.cpp, cpp)
  49| 
  50| ### Guide 风格代码
  51| 
  52| cppbook《C++ 快速入门》教学风格的写法（`std::` 前缀、`i += 1` 循环、0 起始下标）：
  53| 
  54| @include-code(./main-guide.cpp, cpp)
  55| 
  56| ### Pythonic 写法
  57| 
  58| 等差公式：
  59| 
  60| @include-code(./main-pythonic.py, python)
  61| 
  62| 
  63| ### 复杂度
  64| 
  65| 循环执行 `n` 次，时间复杂度是 $O(n)$；只使用一个累加变量，空间复杂度是 $O(1)$。
  66| 
  67| ### 总结
  68| 
  69| 这题要训练的是“从左到右逐项累加”的基本循环模式。以后遇到前缀和、计数、统计类问题，也会反复用到这个写法。
  70| 
  71| ## 代码位置
  72| - `problems/luogu/P5722/gen.py`
  73| - `problems/luogu/P5722/main-guide.cpp`
  74| - `problems/luogu/P5722/main-pythonic.py`
  75| - `problems/luogu/P5722/main.cpp`
  76| - `problems/luogu/P5722/main.py`