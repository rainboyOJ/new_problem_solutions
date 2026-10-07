   1| # luogu P1614 爱与愁的心痛
   2| 
   3| > 原文摘录，非模型摘要。来源：`problems/luogu/P1614/index.md`（内容哈希 85b19d36a86c79db）。
   4| > 摘录可能在 4000 字符处截断；作结论前必须能补读原文全文。
   5| 
   6| ## 元信息（frontmatter 摘录）
   7| - 难度：入门；标签：['滑动窗口', '枚举', '列表', 'python']
   8| 
   9| ## 题目解析（原文摘录）
  10| 
  11| ### 题意
  12| 
  13| 给定长度为 `n` 的正整数序列，求所有长度恰好为 `m` 的连续子段中，子段和的最小值。
  14| 
  15| ### 思路
  16| 
  17| 朴素做法是枚举每个长度为 `m` 的区间，并重新求一次和。相邻两个固定长度窗口只差两个元素：
  18| 
  19| - 右边新进入一个元素；
  20| - 左边旧移出一个元素。
  21| 
  22| 所以可以维护当前窗口和 `window_sum`。窗口右移一格时：
  23| 
  24| ```text
  25| window_sum += 新进入的元素
  26| window_sum -= 旧移出的元素
  27| ```
  28| 
  29| 先计算第一个窗口 `values[:m]` 的和，再从下标 `m` 开始把窗口向右滑动，并维护最小值。
  30| 
  31| 旧目录中保留了 C++ 朴素区间枚举版本；Python 教学版聚焦滑动窗口，不新增 `brute.py`。
  32| 
  33| ## 代码位置
  34| - `problems/luogu/P1614/brute.cpp`
  35| - `problems/luogu/P1614/brute.py`
  36| - `problems/luogu/P1614/gen.py`
  37| - `problems/luogu/P1614/main-pythonic.py`
  38| - `problems/luogu/P1614/main.cpp`
  39| - `problems/luogu/P1614/main.py`