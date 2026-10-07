   1| # leetcodecn find-median-from-data-stream 数据流的中位数
   2| 
   3| > 原文摘录，非模型摘要。来源：`problems/leetcodecn/find-median-from-data-stream/index.md`（内容哈希 33e7eb2754bde8fc）。
   4| > 摘录可能在 4000 字符处截断；作结论前必须能补读原文全文。
   5| 
   6| ## 元信息（frontmatter 摘录）
   7| - 难度：提高+/省选-；标签：['堆', '优先队列', '数据结构']
   8| 
   9| ## 题目解析（原文摘录）
  10| 
  11| ### 题意
  12| 设计数据结构，支持动态添加数字和查询中位数。
  13| 
  14| ### 思路
  15| 用两个堆维护数据流：
  16| - `lo`（大顶堆）：存较小的一半，堆顶是这半的最大值。
  17| - `hi`（小顶堆）：存较大的一半，堆顶是这半的最小值。
  18| 
  19| 插入时先放入 `lo`，再弹出 `lo` 堆顶放入 `hi`（保证 `hi` 中所有值 $\geqslant$ `lo` 中所有值）。若 `lo` 比 `hi` 少，则从 `hi` 弹回 `lo`（保证 `lo` 元素数 $\geqslant$ `hi`）。
  20| 
  21| 两个不变式：`lo` 中所有值 $\leqslant$ `hi` 中所有值；`lo` 元素数比 `hi` 多 0 或 1。
  22| 
  23| 查询中位数：`lo` 多时取 `lo` 堆顶，否则取两堆顶平均值。
  24| 
  25| ## 代码位置
  26| - `problems/leetcodecn/find-median-from-data-stream/main.cpp`
  27| - `problems/leetcodecn/find-median-from-data-stream/main.py`