   1| # luogu P1168 中位数
   2| 
   3| > 原文摘录，非模型摘要。来源：`problems/luogu/P1168/index.md`（内容哈希 f6ef68f51f9583d9）。
   4| > 摘录可能在 4000 字符处截断；作结论前必须能补读原文全文。
   5| 
   6| ## 元信息（frontmatter 摘录）
   7| - 难度：普及/提高-；标签：['双堆', '中位数', 'heapq', 'python']
   8| 
   9| ## 题目解析（原文摘录）
  10| 
  11| [[TOC]]
  12| 
  13| ### 题意
  14| 
  15| 依次读入序列，对每个奇数长度前缀输出中位数。
  16| 
  17| ### 思路
  18| 
  19| `lower` 负数最大堆保存较小一半，`upper` 小根堆保存较大一半。每次插入后调整到 `len(lower)` 等于或比 `upper` 多 1，奇数长度时中位数就是 `-lower[0]`。
  20| 
  21| ### Python 知识
  22| 
  23| - `-value` 是 Python 3.14 以前通用的最大堆写法。
  24| - `enumerate` 的偶数下标对应已读奇数个元素。
  25| - 两个 `heappop/heappush` 完成跨堆再平衡。
  26| 
  27| ### 代码
  28| 
  29| @include-code(./main.py, python)
  30| 
  31| ### 复杂度
  32| 
  33| 每项 $O(\log n)$，空间 $O(n)$。
  34| 
  35| ### 总结
  36| 
  37| 动态中位数的本质是维持有序序列在中点处的两半，而不是每次重新排序。
  38| 
  39| ## 代码位置
  40| - `problems/luogu/P1168/brute.cpp`
  41| - `problems/luogu/P1168/gen.py`
  42| - `problems/luogu/P1168/main.cpp`
  43| - `problems/luogu/P1168/main.py`