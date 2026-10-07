   1| # luogu P1816 忠诚
   2| 
   3| > 原文摘录，非模型摘要。来源：`problems/luogu/P1816/index.md`（内容哈希 e88f7a9367942a45）。
   4| > 摘录可能在 4000 字符处截断；作结论前必须能补读原文全文。
   5| 
   6| ## 元信息（frontmatter 摘录）
   7| - 难度：普及/提高-；标签：['ST表', 'RMQ', '倍增', 'python']
   8| 
   9| ## 题目解析（原文摘录）
  10| 
  11| [[TOC]]
  12| 
  13| ### 题意
  14| 
  15| 给定一个不再修改的数组，多次询问闭区间 `[left, right]` 内的最小值。
  16| 
  17| ### 思路
  18| 
  19| `table[level][i]` 保存从 `i` 开始、长度为 $2^{level}$ 的区间最小值。相邻两块长度 $2^{level-1}$ 的区间合并即可得到下一层。
  20| 
  21| 查询长度为 `length` 的区间时，令 `level = floor(log2(length))`。取查询区间最左和最右的两个长度 $2^{level}$ 的块；它们可能重叠，但 `min` 重复计算元素不会改变结果。
  22| 
  23| ### Python 知识
  24| 
  25| - `array("i")` 比 Python 整数列表紧凑，适合保存 $O(n\log n)$ 个 ST 表值。
  26| - `logs[i] = logs[i // 2] + 1` 可线性预处理所有整数对数。
  27| - 生成器表达式直接交给 `array`，避免先创建中间列表。
  28| - `print(*answers)` 自动按空格输出所有询问答案。
  29| 
  30| ### 代码
  31| 
  32| @include-code(./main.py, python)
  33| 
  34| 原有 C++ 版本保留如下：
  35| 
  36| @include-code(./1.cpp, cpp)
  37| 
  38| ### 复杂度
  39| 
  40| 预处理时间与空间均为 $O(n\log n)$，每次询问 $O(1)$。
  41| 
  42| ### 总结
  43| 
  44| 数组静态、询问很多、运算允许区间重叠时，ST 表是比线段树更直接的选择。
  45| 
  46| ## 代码位置
  47| - `problems/luogu/P1816/1.cpp`
  48| - `problems/luogu/P1816/brute.cpp`
  49| - `problems/luogu/P1816/gen.py`
  50| - `problems/luogu/P1816/main.cpp`
  51| - `problems/luogu/P1816/main.py`