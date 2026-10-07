   1| # luogu P1075 [NOIP 2012 普及组] 质因数分解
   2| 
   3| > 原文摘录，非模型摘要。来源：`problems/luogu/P1075/index.md`（内容哈希 beae26556dcc8363）。
   4| > 摘录可能在 4000 字符处截断；作结论前必须能补读原文全文。
   5| 
   6| ## 元信息（frontmatter 摘录）
   7| - 难度：入门；标签：['数论', '枚举', 'python']
   8| 
   9| ## 题目解析（原文摘录）
  10| 
  11| ### 题意
  12| 
  13| 已知正整数 `n` 恰好是两个不同质数的乘积，要求输出这两个质数中较大的那个。
  14| 
  15| ### 思路
  16| 
  17| 如果 `d` 是 `n` 的一个因子，那么 `n // d` 也是另一个因子。两个因子一定一小一大，小的那个不会超过 `sqrt(n)`。
  18| 
  19| 题目保证 `n = p * q`，且 `p`、`q` 是不同质数。我们从 `2` 开始向上试除，遇到第一个能整除 `n` 的 `d`，它就是较小的质因数，于是较大的质数就是：
  20| 
  21| ```text
  22| n // d
  23| ```
  24| 
  25| 旧目录中保留了 C++ 暴力枚举版本；Python 教学版使用 `math.isqrt` 控制试除上界，不新增 `brute.py`。
  26| 
  27| ## 代码位置
  28| - `problems/luogu/P1075/brute.cpp`
  29| - `problems/luogu/P1075/brute.py`
  30| - `problems/luogu/P1075/gen.py`
  31| - `problems/luogu/P1075/main-pythonic.py`
  32| - `problems/luogu/P1075/main.cpp`
  33| - `problems/luogu/P1075/main.py`