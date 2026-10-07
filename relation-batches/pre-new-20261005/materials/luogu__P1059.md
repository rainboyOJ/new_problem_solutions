   1| # luogu P1059 [NOIP 2006 普及组] 明明的随机数
   2| 
   3| > 原文摘录，非模型摘要。来源：`problems/luogu/P1059/index.md`（内容哈希 65c20d502c3d509b）。
   4| > 摘录可能在 4000 字符处截断；作结论前必须能补读原文全文。
   5| 
   6| ## 元信息（frontmatter 摘录）
   7| - 难度：入门；标签：['排序', '去重', 'python']
   8| 
   9| ## 题目解析（原文摘录）
  10| 
  11| [[TOC]]
  12| 
  13| ### 题意
  14| 
  15| 给出 `N` 个 `1..1000` 的随机整数。去掉重复数字后，按从小到大输出。
  16| 
  17| ### 思路
  18| 
  19| Python 中 `set(numbers)` 可以去重，但集合本身没有固定顺序。再用 `sorted(...)` 排序：
  20| 
  21| ```python
  22| unique_numbers = sorted(set(numbers))
  23| ```
  24| 
  25| 然后输出不同数字个数和排序后的列表即可。
  26| 
  27| ### Python 知识
  28| 
  29| - `/home/rainboy/mycode/hugo-blog/content/program_language/python/collections_toolkit.md`：`set` 适合判重和去重。
  30| - `/home/rainboy/mycode/hugo-blog/content/program_language/python/sorting_and_ordering.md`：`sorted()` 返回一个新的有序列表。
  31| - `print(*unique_numbers)` 按空格展开输出列表。
  32| 
  33| ### 代码
  34| 
  35| @include-code(./main.py, python)
  36| 
  37| ### Guide 风格代码
  38| 
  39| cppbook《C++ 快速入门》教学风格的写法（`std::` 前缀、`i += 1` 循环、0 起始下标）：
  40| 
  41| @include-code(./main-guide.cpp, cpp)
  42| 
  43| ### Pythonic 写法
  44| 
  45| set 去重 sorted：
  46| 
  47| @include-code(./main-pythonic.py, python)
  48| 
  49| 
  50| ### 复杂度
  51| 
  52| 设输入数量为 `N`，去重和排序总复杂度为 $O(N\log N)$，空间复杂度为 $O(N)$。
  53| 
  54| ### 总结
  55| 
  56| 去重后排序是 Python 的常见组合：`sorted(set(a))`。注意集合去重后要排序，不能直接输出集合。
  57| 
  58| ## 代码位置
  59| - `problems/luogu/P1059/brute.cpp`
  60| - `problems/luogu/P1059/brute.py`
  61| - `problems/luogu/P1059/gen.py`
  62| - `problems/luogu/P1059/main-guide.cpp`
  63| - `problems/luogu/P1059/main-pythonic.py`
  64| - `problems/luogu/P1059/main.cpp`
  65| - `problems/luogu/P1059/main.py`