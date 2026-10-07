   1| # luogu P1104 生日
   2| 
   3| > 原文摘录，非模型摘要。来源：`problems/luogu/P1104/index.md`（内容哈希 116c38286f46efef）。
   4| > 摘录可能在 4000 字符处截断；作结论前必须能补读原文全文。
   5| 
   6| ## 元信息（frontmatter 摘录）
   7| - 难度：入门；标签：['排序', 'python']
   8| 
   9| ## 题目解析（原文摘录）
  10| 
  11| [[TOC]]
  12| 
  13| ### 题意
  14| 
  15| 输入若干同学的姓名和生日，按年龄从大到小输出姓名。年龄大等价于生日更早。
  16| 
  17| 如果两个人生日完全相同，后输入的人先输出。
  18| 
  19| ### 思路
  20| 
  21| 这是多关键字排序。
  22| 
  23| 对每个同学保存：
  24| 
  25| ```text
  26| (年, 月, 日, -输入顺序, 姓名)
  27| ```
  28| 
  29| Python 元组会从左到右比较。年月日越小，生日越早，年龄越大；同一天生日时，输入顺序越靠后，`-输入顺序` 越小，也就排得越前。
  30| 
  31| 排序后依次输出姓名即可。
  32| 
  33| ### Python 知识
  34| 
  35| - `name, year, month, day = input().split()` 可以同时读取一个字符串和三个数字字段。
  36| - 元组天然支持多关键字排序，`students.sort()` 会按第 1 项、第 2 项、第 3 项依次比较。
  37| - 字符串字段 `year/month/day` 要转成 `int`，否则字符串比较会按字典序，不是数字大小。
  38| 
  39| 参考笔记：
  40| 
  41| - `/home/rainboy/mycode/hugo-blog/content/program_language/python/input_output_and_strings.md`
  42| - `/home/rainboy/mycode/hugo-blog/content/program_language/python/sorting_and_ordering.md`
  43| 
  44| ### 代码
  45| 
  46| @include-code(./main.py, python)
  47| 
  48| ### Pythonic 写法
  49| 
  50| 元组排序：
  51| 
  52| @include-code(./main-pythonic.py, python)
  53| 
  54| 
  55| ### 复杂度
  56| 
  57| 时间复杂度为 $O(n \log n)$，空间复杂度为 $O(n)$。
  58| 
  59| ### 总结
  60| 
  61| 多关键字排序时，先把题目的比较规则逐项写出来，再把它翻译成一个元组排序键。
  62| 
  63| ## 代码位置
  64| - `problems/luogu/P1104/brute.cpp`
  65| - `problems/luogu/P1104/brute.py`
  66| - `problems/luogu/P1104/gen.py`
  67| - `problems/luogu/P1104/main-pythonic.py`
  68| - `problems/luogu/P1104/main.cpp`
  69| - `problems/luogu/P1104/main.py`