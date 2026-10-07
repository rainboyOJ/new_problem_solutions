   1| # luogu P3375 【模板】KMP
   2| 
   3| > 原文摘录，非模型摘要。来源：`problems/luogu/P3375/index.md`（内容哈希 fdf6d262cf9b6839）。
   4| > 摘录可能在 4000 字符处截断；作结论前必须能补读原文全文。
   5| 
   6| ## 元信息（frontmatter 摘录）
   7| - 难度：普及+/提高；标签：['KMP', '前缀函数', '字符串', 'python']
   8| 
   9| ## 题目解析（原文摘录）
  10| 
  11| ### 题意
  12| 
  13| 输出模式串在文本中的所有出现位置，以及模式串每个前缀的最长真前后缀长度。
  14| 
  15| ### 思路
  16| 
  17| `prefix[i]` 表示 `pattern[:i+1]` 的最长 border 长度。计算新位置时，若字符失配，就令 `j = prefix[j-1]`，沿 border 链退到下一个可能长度；每次指针的增加和回退总量都是线性的。
  18| 
  19| 匹配文本时使用相同回退规则。`j == m` 表示找到一次完整匹配，输出位置后退到模式串的次长 border，从而允许重叠匹配。
  20| 
  21| ### Python 知识
  22| 
  23| - 字符串按 `bytes` 处理时，下标访问直接得到整数，百万字符扫描更省内存。
  24| - `array("i")` 只用 4 字节保存一个前缀函数值。
  25| - 匹配位置先写入 `bytearray`，前缀数组再按 8192 个一块输出，避免创建百万个字符串对象。
  26| - `enumerate(text)` 同时取得文本下标和字符。
  27| 
  28| ### 代码
  29| 
  30| @include-code(./main.py, python)
  31| 
  32| @include-code(./main1.py, python)
  33| 
  34| `main1.py` 用 `str.find` 做匹配，逻辑正确但有两个点会 TLE（全 `A` 的长串反复调用 `find` 退化到 $O(n^2)$）。
  35| 
  36| 纯 Python 实现的 KMP：
  37| 
  38| @include-code(./main-kmp.py, python)
  39| 
  40| `main-kmp.py` 用标准 KMP 算法做匹配，代码可读性好，但未做内存优化，百万字符下 Python 对象开销比 `main.py` 大。
  41| 
  42| ### 复杂度
  43| 
  44| | 做法 | 时间 | 空间 |
  45| |------|------|------|
  46| | main.py（KMP + array + 缓冲） | $O(\|text\|+\|pattern\|)$ | $O(\|pattern\|)$ 加输出缓冲 |
  47| | main-kmp.py（纯 Python KMP） | $O(\|text\|+\|pattern\|)$ | $O(\|text\|+\|pattern\|)$ |
  48| | main1.py（str.find） | $O(n^2)$ 退化（2 TLE） | $O(1)$ |
  49| 
  50| ### 总结
  51| 
  52| KMP 的核心不是背循环，而是理解 `prefix[j-1]` 给出了失配后仍可能匹配的最长前缀。
  53| 
  54| ## 代码位置
  55| - `problems/luogu/P3375/brute.cpp`
  56| - `problems/luogu/P3375/gen.py`
  57| - `problems/luogu/P3375/main-kmp.py`
  58| - `problems/luogu/P3375/main.cpp`
  59| - `problems/luogu/P3375/main.py`
  60| - `problems/luogu/P3375/main1.py`