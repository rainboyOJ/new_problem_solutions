   1| # luogu P5736 【深基7.例2】质数筛
   2| 
   3| > 原文摘录，非模型摘要。来源：`problems/luogu/P5736/index.md`（内容哈希 dca47bb161ba2b47）。
   4| > 摘录可能在 4000 字符处截断；作结论前必须能补读原文全文。
   5| 
   6| ## 元信息（frontmatter 摘录）
   7| - 难度：入门；标签：['数学', '质数', '函数', 'python']
   8| 
   9| ## 题目解析（原文摘录）
  10| 
  11| ### 题意
  12| 
  13| 输入 `n` 个不超过 `100000` 的正整数，按原顺序输出其中所有质数。
  14| 
  15| ### 思路
  16| 
  17| 先写一个质数判断函数：
  18| 
  19| - 小于 2 的数不是质数；
  20| - 从 2 开始试除；
  21| - 只需要检查到 `divisor * divisor <= x`，因为如果 `x` 有大于平方根的因子，必然还有一个小于平方根的配对因子。
  22| 
  23| 然后扫描输入数组，保留所有满足 `is_prime(x)` 的数。
  24| 
  25| 数据只有 `n <= 100`，试除法足够。题目名叫“质数筛”，但这里直接判断每个数更适合初学函数练习。
  26| 
  27| ### Python 知识
  28| 
  29| - `/home/rainboy/mycode/hugo-blog/content/program_language/python/input_output_and_strings.md`：`list(map(int, input().split()))` 读取整数数组。
  30| - `/home/rainboy/mycode/hugo-blog/content/program_language/python/generator_expression.md`：列表推导式 `[x for x in numbers if ...]` 适合筛选结果。
  31| - `/home/rainboy/mycode/hugo-blog/content/program_language/python/math_tools.md`：用 `divisor * divisor <= x` 避免浮点平方根误差。
  32| - `print(*answer)` 按空格输出列表元素。
  33| 
  34| ### 代码
  35| 
  36| @include-code(./main.py, python)
  37| 
  38| @include-code(./main.cpp, cpp)
  39| 
  40| ### Guide 风格代码
  41| 
  42| cppbook《C++ 快速入门》教学风格的写法（`std::` 前缀、`i += 1` 循环、0 起始下标）：
  43| 
  44| @include-code(./main-guide.cpp, cpp)
  45| 
  46| ### 复杂度
  47| 
  48| 设最大数为 `A`，共有 `n` 个数。每个数试除到平方根，时间复杂度是 $O(n\sqrt A)$，空间复杂度是 $O(n)$。
  49| 
  50| ### 总结
  51| 
  52| 质数判断适合封装成函数。筛选数组时，列表推导式能清楚表达“保留满足条件的元素”。
  53| 
  54| ## 代码位置
  55| - `problems/luogu/P5736/gen.py`
  56| - `problems/luogu/P5736/main-guide.cpp`
  57| - `problems/luogu/P5736/main.cpp`
  58| - `problems/luogu/P5736/main.py`