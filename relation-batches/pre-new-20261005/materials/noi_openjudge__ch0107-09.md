   1| # noi_openjudge ch0107-09 密码翻译
   2| 
   3| > 原文摘录，非模型摘要。来源：`problems/noi_openjudge/ch0107-09/index.md`（内容哈希 53471746999adaa7）。
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
  15| 将字母替换为字母表后继，`z` 循环到 `a`，`Z` 循环到 `A`，其他字符不变。
  16| 
  17| ### 思路
  18| 
  19| 普通字母可用 ASCII 码加一；`z`、`Z` 是循环边界，要单独映射。生成器逐字符调用 `encrypt` 后拼接输出。
  20| 
  21| ### 代码
  22| 
  23| ## Python代码
  24| 
  25| @include-code(./main.py, python)
  26| 
  27| ## C++代码
  28| 
  29| @include-code(./main.cpp, cpp)
  30| 
  31| ### 复杂度
  32| 
  33| 时间复杂度和输出空间均为 $O(n)$。
  34| 
  35| ### 总结
  36| 
  37| 字符平移题最重要的边界是字母表末尾的回绕。
  38| 
  39| ## 代码位置
  40| - `problems/noi_openjudge/ch0107-09/main-cout.cpp`
  41| - `problems/noi_openjudge/ch0107-09/main.cpp`
  42| - `problems/noi_openjudge/ch0107-09/main.py`