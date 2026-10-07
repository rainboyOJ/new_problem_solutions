   1| # leetcodecn kth-largest-element-in-an-array 数组中的第K个最大元素
   2| 
   3| > 原文摘录，非模型摘要。来源：`problems/leetcodecn/kth-largest-element-in-an-array/index.md`（内容哈希 6ebc0b85afe24c65）。
   4| > 摘录可能在 4000 字符处截断；作结论前必须能补读原文全文。
   5| 
   6| ## 元信息（frontmatter 摘录）
   7| - 难度：普及+/提高；标签：['堆', '优先队列', '排序']
   8| 
   9| ## 题目解析（原文摘录）
  10| 
  11| [[TOC]]
  12| 
  13| ### 题意
  14| 
  15| 找出数组中第 `k` 大的元素（排序后倒数第 `k` 个）。
  16| 
  17| ### 思路
  18| 
  19| 维护一个大小为 `k` 的最小堆。每次插入元素后，若堆大小超过 `k`，弹出堆顶最小值。最终堆中保留最大的 `k` 个元素，堆顶就是第 `k` 大。
  20| 
  21| 最小堆而非最大堆的关键理解：我们要保留最大的 `k` 个元素，所以每次弹出的是堆中最小的那个——即这 `k` 个中"最不够格"的。
  22| 
  23| ### 代码
  24| 
  25| @include-code(./main.cpp, cpp)
  26| 
  27| @include-code(./main.py, python)
  28| 
  29| ### 复杂度
  30| 
  31| - 时间复杂度：$O(n \log k)$，每个元素堆操作 $O(\log k)$。
  32| - 空间复杂度：$O(k)$，堆最多存 `k` 个元素。
  33| 
  34| ### 总结
  35| 
  36| 第 `k` 大/小元素用大小为 `k` 的堆：第 `k` 大用最小堆（弹小留大），第 `k` 小用最大堆（弹大留小）。堆顶即答案。
  37| 
  38| ## 代码位置
  39| - `problems/leetcodecn/kth-largest-element-in-an-array/main.cpp`
  40| - `problems/leetcodecn/kth-largest-element-in-an-array/main.py`