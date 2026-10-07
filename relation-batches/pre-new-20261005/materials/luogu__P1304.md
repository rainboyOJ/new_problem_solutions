   1| # luogu P1304 哥德巴赫猜想
   2| 
   3| > 原文摘录，非模型摘要。来源：`problems/luogu/P1304/index.md`（内容哈希 4eefc19b350851c7）。
   4| > 摘录可能在 4000 字符处截断；作结论前必须能补读原文全文。
   5| 
   6| ## 元信息（frontmatter 摘录）
   7| - 难度：普及-；标签：['数学', '质数', '枚举', 'python']
   8| 
   9| ## 题目解析（原文摘录）
  10| 
  11| [[TOC]]
  12| 
  13| ### 题意
  14| 
  15| 输入偶数 `N`，对 `4,6,8,...,N` 中的每个偶数，输出它写成两个质数之和的一种方案。若有多种方案，要求第一个加数最小。
  16| 
  17| ### 思路
  18| 
  19| 先用埃氏筛预处理 `0..N` 的质数表 `is_prime`。
  20| 
  21| 对每个偶数 `even`，从小到大枚举第一个加数 `first`，令：
  22| 
  23| ```text
  24| second = even - first
  25| ```
  26| 
  27| 如果 `first` 和 `second` 都是质数，就输出这一组并停止枚举。因为 `first` 是从小到大枚举的，所以第一次找到的方案就是第一个加数最小的方案。
  28| 
  29| ### Python 知识
  30| 
  31| - `/home/rainboy/mycode/hugo-blog/content/program_language/python/brute_force_validation.md`：用 `range(4, n+1, 2)` 可以按步长枚举偶数。
  32| - `/home/rainboy/mycode/hugo-blog/content/program_language/python/math_tools.md`：质数相关判断适合用整数运算。
  33| - 列表 `is_prime[x]` 可以作为快速查询表。
  34| - f-string `f"{even}={first}+{second}"` 适合按题目格式输出。
  35| 
  36| ### 代码
  37| 
  38| @include-code(./main.py, python)
  39| 
  40| @include-code(./main.cpp, cpp)
  41| 
  42| 
  43| ### 复杂度
  44| 
  45| 埃氏筛复杂度约为 $O(N \log\log N)$。之后对每个偶数枚举加数，最坏 $O(N^2)$，但 `N <= 10000` 可以通过。空间复杂度是 $O(N)$。
  46| 
  47| ### 总结
  48| 
  49| 需要反复判断质数时，先预处理质数表。要求“第一个加数最小”时，从小到大枚举并在第一次成功时停止。
  50| 
  51| ## 代码位置
  52| - `problems/luogu/P1304/gen.py`
  53| - `problems/luogu/P1304/main.cpp`
  54| - `problems/luogu/P1304/main.py`