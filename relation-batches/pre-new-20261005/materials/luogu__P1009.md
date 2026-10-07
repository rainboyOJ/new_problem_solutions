   1| # luogu P1009 [NOIP 1998 普及组] 阶乘之和
   2| 
   3| > 原文摘录，非模型摘要。来源：`problems/luogu/P1009/index.md`（内容哈希 b77b86400912538d）。
   4| > 摘录可能在 4000 字符处截断；作结论前必须能补读原文全文。
   5| 
   6| ## 元信息（frontmatter 摘录）
   7| - 难度：普及-；标签：['python', '入门', '循环', '高精度', '数学']
   8| 
   9| ## 题目解析（原文摘录）
  10| 
  11| ### 题意
  12| 
  13| 输入 `n`，计算：
  14| 
  15| $$
  16| 1!+2!+3!+\cdots+n!
  17| $$
  18| 
  19| 其中 `n <= 50`，结果可能超过普通 64 位整数范围。
  20| 
  21| ### 思路
  22| 
  23| Python 的 `int` 是任意精度整数，所以不需要手写高精度数组。可以一边维护当前阶乘，一边累加答案：
  24| 
  25| ```python
  26| factorial *= x
  27| answer += factorial
  28| ```
  29| 
  30| 当 `x` 从 `1` 到 `n` 递增时，`factorial` 依次变成 `1!, 2!, 3!, ...`。
  31| 
  32| 旧目录中只有空 C++ 模板；本篇补成 Python 教学，重点是 Python 大整数和递推式循环。`brute.py` 不单独写，因为递推累加就是完整解法。
  33| 
  34| ## 代码位置
  35| - `problems/luogu/P1009/brute.cpp`
  36| - `problems/luogu/P1009/brute.py`
  37| - `problems/luogu/P1009/gen.py`
  38| - `problems/luogu/P1009/main-pythonic.py`
  39| - `problems/luogu/P1009/main.cpp`
  40| - `problems/luogu/P1009/main.py`