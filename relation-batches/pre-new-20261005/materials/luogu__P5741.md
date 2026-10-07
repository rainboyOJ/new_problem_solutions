   1| # luogu P5741 【深基7.例10】旗鼓相当的对手 - 加强版
   2| 
   3| > 原文摘录，非模型摘要。来源：`problems/luogu/P5741/index.md`（内容哈希 e315fada557229e6）。
   4| > 摘录可能在 4000 字符处截断；作结论前必须能补读原文全文。
   5| 
   6| ## 元信息（frontmatter 摘录）
   7| - 难度：普及-；标签：['模拟', '枚举', '结构体', 'python']
   8| 
   9| ## 题目解析（原文摘录）
  10| 
  11| [[TOC]]
  12| 
  13| ### 题意
  14| 
  15| 给出按字典序排列的学生信息。如果两个学生每一科分差都不超过 `5`，且总分分差不超过 `10`，就输出这对学生姓名。输出顺序也要按字典序组合顺序。
  16| 
  17| ### 思路
  18| 
  19| 输入姓名已经按字典序排列。因此只要按下标枚举 `i < j` 的学生对，输出顺序就满足题目要求。
  20| 
  21| 把判断封装成函数：
  22| 
  23| ```python
  24| is_close(left, right)
  25| ```
  26| 
  27| 它检查：
  28| 
  29| - 三科分差都不超过 `5`；
  30| - 总分分差不超过 `10`。
  31| 
  32| `N <= 1000`，枚举所有学生对是 $O(N^2)$，可以接受。
  33| 
  34| ### Python 知识
  35| 
  36| - `/home/rainboy/mycode/hugo-blog/content/program_language/python/brute_force_validation.md`：`for i in range(n)` 与 `for j in range(i+1, n)` 是枚举无序点对的常用写法。
  37| - `/home/rainboy/mycode/hugo-blog/content/program_language/python/collections_toolkit.md`：元组可保存固定字段记录。
  38| - `abs(a - b)` 计算分差。
  39| - 把总分和判断逻辑封装成函数，可以让双重循环更清楚。
  40| 
  41| ### 代码
  42| 
  43| @include-code(./main.py, python)
  44| 
  45| @include-code(./main.cpp, cpp)
  46| 
  47| ### Guide 风格代码
  48| 
  49| cppbook《C++ 快速入门》教学风格的写法（`std::` 前缀、`i += 1` 循环、0 起始下标）：
  50| 
  51| @include-code(./main-guide.cpp, cpp)
  52| 
  53| ### 复杂度
  54| 
  55| 枚举所有学生对，时间复杂度是 $O(N^2)$，保存学生信息空间复杂度是 $O(N)$。
  56| 
  57| ### 总结
  58| 
  59| 当输入顺序已经满足输出顺序时，不必额外排序。直接按 `i < j` 枚举学生对，既避免重复，也保证姓名顺序。
  60| 
  61| ## 代码位置
  62| - `problems/luogu/P5741/gen.py`
  63| - `problems/luogu/P5741/main-guide.cpp`
  64| - `problems/luogu/P5741/main.cpp`
  65| - `problems/luogu/P5741/main.py`