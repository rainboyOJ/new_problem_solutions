   1| # luogu P3378 【模板】堆
   2| 
   3| > 原文摘录，非模型摘要。来源：`problems/luogu/P3378/index.md`（内容哈希 c43248bc92e00ca7）。
   4| > 摘录可能在 4000 字符处截断；作结论前必须能补读原文全文。
   5| 
   6| ## 元信息（frontmatter 摘录）
   7| - 难度：普及-；标签：['二叉堆', 'heapq', '模板题', 'python']
   8| 
   9| ## 题目解析（原文摘录）
  10| 
  11| [[TOC]]
  12| 
  13| ### 题意
  14| 
  15| 维护一个可重小根堆，支持插入、查询最小值和删除一个最小值。
  16| 
  17| ### 思路
  18| 
  19| Python 标准库 `heapq` 在普通列表上实现小根堆：`heappush` 插入，`heap[0]` 查看堆顶，`heappop` 删除堆顶，正好对应三种操作。
  20| 
  21| ### Python 知识
  22| 
  23| - `heapq` 原生是小根堆，重复值无需特殊处理。
  24| - 百万次操作逐行读取，避免一次 `split` 的内存峰值。
  25| - 查询结果追加到 `bytearray`，最后一次写出。
  26| 
  27| ### 代码
  28| 
  29| @include-code(./main.py, python)
  30| 
  31| ### 复杂度
  32| 
  33| 插入、删除 $O(\log n)$，查看最小值 $O(1)$，空间 $O(n)$。
  34| 
  35| ### 总结
  36| 
  37| Python OJ 的堆模板就是 `heapq` 三个基本接口，不必手写上浮下沉。
  38| 
  39| ## 代码位置
  40| - `problems/luogu/P3378/brute.cpp`
  41| - `problems/luogu/P3378/gen.py`
  42| - `problems/luogu/P3378/main.cpp`
  43| - `problems/luogu/P3378/main.py`