   1| # luogu P1116 车厢重组
   2| 
   3| > 原文摘录，非模型摘要。来源：`problems/luogu/P1116/index.md`（内容哈希 d1ab995dbfeed542）。
   4| > 摘录可能在 4000 字符处截断；作结论前必须能补读原文全文。
   5| 
   6| ## 元信息（frontmatter 摘录）
   7| - 难度：入门；标签：['排序', '逆序对', 'python']
   8| 
   9| ## 题目解析（原文摘录）
  10| 
  11| [[TOC]]
  12| 
  13| ### 题意
  14| 
  15| 有一列车厢，每次操作只能交换相邻两节车厢。问最少交换多少次，才能把车厢编号排成从小到大。
  16| 
  17| ### 思路
  18| 
  19| 一次相邻交换最多只能消掉一对顺序错误的车厢。
  20| 
  21| 如果 `cars[i] > cars[j]` 且 `i < j`，这两节车厢就是一对逆序对。最终升序排列时，较小的那节一定要越过较大的那节，所以每一对逆序对都至少需要一次相邻交换。
  22| 
  23| 反过来，冒泡排序每交换一次相邻逆序元素，就恰好减少一个逆序对，直到逆序对数量变成 `0`。因此最少操作次数就是初始逆序对数量。
  24| 
  25| 本题 `n <= 1000`，直接两层循环统计即可。
  26| 
  27| ### Python 知识
  28| 
  29| - `sys.stdin.buffer.read().split()` 适合这种“全是整数，换行不重要”的输入。
  30| - `list(map(int, ...))` 一次把所有 token 转成整数，后面按下标切出数组。
  31| - 双层 `for` 循环直接枚举所有 `i < j` 的数对，写法和 C++ 中的两层循环一一对应。
  32| 
  33| 参考笔记：
  34| 
  35| - `/home/rainboy/mycode/hugo-blog/content/program_language/python/input_output_and_strings.md`
  36| - `/home/rainboy/mycode/hugo-blog/content/program_language/python/oj_input_output_cheatsheet.md`
  37| 
  38| ### 代码
  39| 
  40| @include-code(./main.py, python)
  41| 
  42| @include-code(./main.cpp, cpp)
  43| 
  44| 
  45| ### 复杂度
  46| 
  47| 时间复杂度为 $O(n^2)$，空间复杂度为 $O(n)$。
  48| 
  49| ### 总结
  50| 
  51| 看到“只能相邻交换，问最少交换次数”，要立刻联想到逆序对。这里数据范围很小，不需要树状数组或归并排序。
  52| 
  53| ## 代码位置
  54| - `problems/luogu/P1116/gen.py`
  55| - `problems/luogu/P1116/main.cpp`
  56| - `problems/luogu/P1116/main.py`