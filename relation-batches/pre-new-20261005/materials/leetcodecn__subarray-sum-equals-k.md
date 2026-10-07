   1| # leetcodecn subarray-sum-equals-k 和为 K 的子数组
   2| 
   3| > 原文摘录，非模型摘要。来源：`problems/leetcodecn/subarray-sum-equals-k/index.md`（内容哈希 6522b794b5a9f01f）。
   4| > 摘录可能在 4000 字符处截断；作结论前必须能补读原文全文。
   5| 
   6| ## 元信息（frontmatter 摘录）
   7| - 难度：普及+/提高；标签：['前缀和', '哈希表', '数组', 'cpp', 'python']
   8| 
   9| ## 题目解析（原文摘录）
  10| 
  11| [[TOC]]
  12| 
  13| ### 题意
  14| 
  15| 给定整数数组 nums 和整数 k，统计和为 k 的连续子数组的个数。
  16| 
  17| ### 思路
  18| 
  19| 暴力 O(n²) 枚举所有子数组。优化：前缀和 `s[i]` 表示 `[0..i)` 的和，子数组 `[l..r]` 的和为 `s[r+1] - s[l]`。遍历时用哈希表记录每个前缀和出现的次数，对当前位置 `sum`，查 `sum - k` 的出现次数即为以当前位置结尾的合法子数组个数。
  20| 
  21| 注意：先查询后插入，且初始插入 `{0: 1}` 表示空前缀。
  22| 
  23| 
  24| ### 代码
  25| 
  26| @include-code(./main.cpp, cpp)
  27| @include-code(./main.py, python)
  28| ### 复杂度
  29| 
  30| - 时间复杂度：O(n)，每个元素处理一次。
  31| - 空间复杂度：O(n)，哈希表最多存 n 个前缀和。
  32| 
  33| ### 总结
  34| 
  35| 前缀和配合哈希表是子数组统计问题的标准模型。与两数之和的配对计数本质相同：固定右端点，查历史信息的数量。有负数时双指针失效，但前缀和哈希表仍然正确。
  36| 
  37| ## 代码位置
  38| - `problems/leetcodecn/subarray-sum-equals-k/brute.cpp`
  39| - `problems/leetcodecn/subarray-sum-equals-k/gen.py`
  40| - `problems/leetcodecn/subarray-sum-equals-k/main.cpp`
  41| - `problems/leetcodecn/subarray-sum-equals-k/main.py`