   1| # luogu P1226 【模板】快速幂
   2| 
   3| > 原文摘录，非模型摘要。来源：`problems/luogu/P1226/index.md`（内容哈希 960184a9e779fdc2）。
   4| > 摘录可能在 4000 字符处截断；作结论前必须能补读原文全文。
   5| 
   6| ## 元信息（frontmatter 摘录）
   7| - 难度：普及-；标签：['数学', '快速幂', 'python']
   8| 
   9| ## 题目解析（原文摘录）
  10| 
  11| [[TOC]]
  12| 
  13| ### 题意
  14| 
  15| 计算 $a^b\bmod p$，并按指定格式输出。
  16| 
  17| ### 思路
  18| 
  19| 快速幂把指数写成二进制，只使用 $O(\log b)$ 次平方和乘法。Python 已经在内置函数中实现了这一算法：
  20| 
  21| ```python
  22| pow(a, b, modulus)
  23| ```
  24| 
  25| 三参数版本会在运算过程中持续取模，不会先构造可能极大的 `a ** b`。OJ 中应优先使用它，而不是写成 `a ** b % modulus`。
  26| 
  27| ### Python 知识
  28| 
  29| - `pow(base, exponent, modulus)` 是模快速幂，复杂度为 $O(\log exponent)$。
  30| - f-string 可以直接拼出题目要求的固定格式。
  31| - Python 内置 `pow` 由底层高效实现，模板题没有必要手写循环来代替它。
  32| 
  33| ### 代码
  34| 
  35| @include-code(./main.py, python)
  36| 
  37| 原有手写 C++ 快速幂仍可用于理解二进制拆分：
  38| 
  39| @include-code(./main.cpp, cpp)
  40| 
  41| ### 复杂度
  42| 
  43| 时间 $O(\log b)$，除大整数运算内部空间外只使用 $O(1)$ 个变量。
  44| 
  45| ### 总结
  46| 
  47| 这题最能体现 Python 相对 C++ 的语言特性：三参数 `pow` 就是可直接提交的标准模快速幂。
  48| 
  49| ## 代码位置
  50| - `problems/luogu/P1226/brute.cpp`
  51| - `problems/luogu/P1226/gen.py`
  52| - `problems/luogu/P1226/main.cpp`
  53| - `problems/luogu/P1226/main.py`