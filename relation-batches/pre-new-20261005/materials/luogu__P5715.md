   1| # luogu P5715 【深基3.例8】三位数排序
   2| 
   3| > 原文摘录，非模型摘要。来源：`problems/luogu/P5715/index.md`（内容哈希 ff67f68ade2dc1f6）。
   4| > 摘录可能在 4000 字符处截断；作结论前必须能补读原文全文。
   5| 
   6| ## 元信息（frontmatter 摘录）
   7| - 难度：入门；标签：['python', '入门', '排序', '输入输出']
   8| 
   9| ## 题目解析（原文摘录）
  10| 
  11| [[TOC]]
  12| 
  13| ### 题意
  14| 
  15| 输入三个整数，按从小到大输出。
  16| 
  17| ### 思路
  18| 
  19| Python 已经提供排序工具。把输入的三个数读成列表，调用 `sorted(numbers)` 得到升序新列表，然后空格分隔输出。
  20| 
  21| `brute.py` 不适合这题，因为排序工具直接表达了完整解法。
  22| 
  23| ### Python 知识
  24| 
  25| - `list(map(int, input().split()))` 把输入转成整数列表。
  26| - `sorted(numbers)` 返回一个新的升序列表，不修改原列表。
  27| - `print(*numbers)` 会把列表元素展开，默认用空格分隔输出。
  28| - 不要直接 `print(numbers)`，那会输出 Python 列表格式，如 `[1, 5, 14]`。
  29| 
  30| 对应的本地 Python 笔记：
  31| 
  32| - `/home/rainboy/mycode/hugo-blog/content/program_language/python/sorting_and_ordering.md`：`sorted` 与 `list.sort`。
  33| - `/home/rainboy/mycode/hugo-blog/content/program_language/python/input_output_and_strings.md`：列表输入和多值输出。
  34| - `/home/rainboy/mycode/hugo-blog/content/program_language/python/oj_input_output_cheatsheet.md`：输出数组。
  35| 
  36| ### 代码
  37| 
  38| @include-code(./main.py, python)
  39| 
  40| @include-code(./main.cpp, cpp)
  41| 
  42| ### Guide 风格代码
  43| 
  44| cppbook《C++ 快速入门》教学风格的写法（`std::` 前缀、`i += 1` 循环、0 起始下标）：
  45| 
  46| @include-code(./main-guide.cpp, cpp)
  47| 
  48| ### Pythonic 写法
  49| 
  50| sorted：
  51| 
  52| @include-code(./main-pythonic.py, python)
  53| 
  54| 
  55| ### 复杂度
  56| 
  57| 这里只有三个数，可以看成时间复杂度 $O(1)$，空间复杂度 $O(1)$。如果推广到 $n$ 个数，排序时间复杂度是 $O(n\log n)$。
  58| 
  59| ### 总结
  60| 
  61| Python 排序题先想到 `sorted`。输出列表时用 `print(*a)`，让格式变成 OJ 需要的空格分隔整数。
  62| 
  63| ## 代码位置
  64| - `problems/luogu/P5715/gen.py`
  65| - `problems/luogu/P5715/main-guide.cpp`
  66| - `problems/luogu/P5715/main-pythonic.py`
  67| - `problems/luogu/P5715/main.cpp`
  68| - `problems/luogu/P5715/main.py`