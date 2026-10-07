   1| # luogu P1914 小书童——凯撒密码
   2| 
   3| > 原文摘录，非模型摘要。来源：`problems/luogu/P1914/index.md`（内容哈希 36caee6ef601bde8）。
   4| > 摘录可能在 4000 字符处截断；作结论前必须能补读原文全文。
   5| 
   6| ## 元信息（frontmatter 摘录）
   7| - 难度：入门；标签：['字符串', '模拟', 'python']
   8| 
   9| ## 题目解析（原文摘录）
  10| 
  11| [[TOC]]
  12| 
  13| ### 题意
  14| 
  15| 给定一个位移量 `n` 和一个只含小写字母的字符串。每个字母向后移动 `n` 位，超过 `z` 后从 `a` 继续循环，输出移动后的密码。
  16| 
  17| ### 思路
  18| 
  19| 把字符看成字母表中的编号：
  20| 
  21| ```text
  22| a -> 0, b -> 1, ..., z -> 25
  23| ```
  24| 
  25| 一个字符 `ch` 平移 `n` 位后，新编号是：
  26| 
  27| ```text
  28| (old + n) % 26
  29| ```
  30| 
  31| 再把新编号加回到 `'a'` 的 ASCII 编码，就能得到新字符。
  32| 
  33| 这题是字符编码和取模循环练习，不创建 `brute.py`。
  34| 
  35| ### Python 知识
  36| 
  37| - `/home/rainboy/mycode/hugo-blog/content/program_language/python/input_output_and_strings.md`：用 `input()` 读取字符串，用列表收集结果后 `"".join(...)` 输出。
  38| - `/home/rainboy/mycode/hugo-blog/content/program_language/python/oj_input_output_cheatsheet.md`：第一行整数、第二行字符串可以分别读取。
  39| - `ord(ch)` 把字符转成编码，`chr(x)` 把编码转回字符。
  40| - `% 26` 表达字母表循环。
  41| 
  42| ### 代码
  43| 
  44| @include-code(./main.py, python)
  45| 
  46| @include-code(./main.cpp, cpp)
  47| 
  48| ### Guide 风格代码
  49| 
  50| cppbook《C++ 快速入门》教学风格的写法（`std::` 前缀、`i += 1` 循环、0 起始下标）：
  51| 
  52| @include-code(./main-guide.cpp, cpp)
  53| 
  54| ### Pythonic 写法
  55| 
  56| 用 `str.maketrans` / `translate` 做凯撒位移：
  57| 
  58| @include-code(./main-pythonic.py, python)
  59| 
  60| ### 复杂度
  61| 
  62| 设字符串长度为 `m`，时间复杂度是 $O(m)$，空间复杂度是 $O(m)$。
  63| 
  64| ### 总结
  65| 
  66| 凯撒密码的关键是先把字母映射成数字，再用取模处理循环。
  67| 
  68| ## 代码位置
  69| - `problems/luogu/P1914/gen.py`
  70| - `problems/luogu/P1914/main-guide.cpp`
  71| - `problems/luogu/P1914/main-pythonic.py`
  72| - `problems/luogu/P1914/main.cpp`
  73| - `problems/luogu/P1914/main.py`