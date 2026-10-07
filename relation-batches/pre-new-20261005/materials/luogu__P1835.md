   1| # luogu P1835 素数密度
   2| 
   3| > 原文摘录，非模型摘要。来源：`problems/luogu/P1835/index.md`（内容哈希 076c340c1ab3dc18）。
   4| > 摘录可能在 4000 字符处截断；作结论前必须能补读原文全文。
   5| 
   6| ## 元信息（frontmatter 摘录）
   7| - 难度：普及+/提高；标签：['数论', '分段筛', '素数', 'bytearray', 'python']
   8| 
   9| ## 题目解析（原文摘录）
  10| 
  11| ### 题意
  12| 
  13| 统计 `[L,R]` 中素数个数。`R` 接近 `2^31`，但区间长度不超过 `10^6`。
  14| 
  15| ### 思路
  16| 
  17| 不能筛到 `R`。任何区间合数都至少有一个不超过 `sqrt(R)` 的质因子：
  18| 
  19| 1. 普通埃氏筛得到 `2..sqrt(R)` 的素数；
  20| 2. 建立长度 `R-L+1` 的区间标记；
  21| 3. 对每个基础素数 `p`，从 `max(p*p,ceil(L/p)*p)` 开始标记倍数；
  22| 4. 若 `L=1`，单独把 1 标为非素数。
  23| 
  24| 从 `p*p` 开始可避免把区间中的质数 `p` 自己误删。
  25| 
  26| ### Python 知识
  27| 
  28| - `bytearray` 适合百万长度 0/1 标记。
  29| - 扩展切片赋值一次标记同一质数的全部倍数。
  30| - `(left+p-1)//p*p` 是不小于 `left` 的第一个 `p` 倍数。
  31| - `sum(segment)` 直接统计仍为 1 的位置。
  32| - `/home/rainboy/mycode/hugo-blog/content/program_language/python/cpp_to_python_pitfalls.md`：紧凑标记和切片性能。
  33| - `/home/rainboy/mycode/hugo-blog/content/program_language/python/generator_expression.md`：区间按需处理思路。
  34| 
  35| ## 代码位置
  36| - `problems/luogu/P1835/main.cpp`
  37| - `problems/luogu/P1835/main.py`