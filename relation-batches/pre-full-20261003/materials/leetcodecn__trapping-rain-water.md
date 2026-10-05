   1| # leetcodecn trapping-rain-water 接雨水
   2| 
   3| > 原文摘录，非模型摘要。来源：`problems/leetcodecn/trapping-rain-water/index.md`（内容哈希 9967bec5b00681a7）。
   4| > 摘录可能在 4000 字符处截断；作结论前必须能补读原文全文。
   5| 
   6| ## 元信息（frontmatter 摘录）
   7| - 难度：提高+/省选-；标签：['双指针', '栈', '动态规划', '数组', 'cpp', 'python']
   8| 
   9| ## 题目解析（原文摘录）
  10| 
  11| ### 题意
  12| 
  13| 给定 n 个非负整数表示柱状图高度，计算能接多少雨水。
  14| 
  15| ### 思路
  16| 
  17| 每个位置能接的水量 = min(左边最高柱, 右边最高柱) - 自身高度。
  18| 
  19| 暴力 O(n²) 每位置独立查左右最大值。优化方法有三种：
  20| 
  21| 1. **前后缀最大值**：预计算 left_max 和 right_max，O(n) 空间。
  22| 2. **单调栈**：按凹槽结算，遇到更高的柱子就弹出结算。
  23| 3. **双指针**：左右指针各维护一个当前最高柱，较矮侧的水量可立即确定，并移动该侧指针。无需额外数组。
  24| 
  25| 
  26| ### 代码
  27| 
  28| @include-code(./main.cpp, cpp)
  29| @include-code(./main.py, python)
  30| ### 复杂度
  31| 
  32| - 时间复杂度：O(n)，双指针各遍历一次。
  33| - 空间复杂度：O(1)，只使用几个变量。
  34| 
  35| ### 总结
  36| 
  37| 双指针解法的核心不变量是：`lmax` 是 `[0..l]` 的最大值，`rmax` 是 `[r..n-1]` 的最大值。`height[l] < height[r]` 时，`lmax < rmax` 不一定成立，但左侧水量由 `lmax` 决定已足够，因为 `rmax` 至少为 `height[r]`，而 `height[r] > height[l]` 保证了右侧有足够高的墙。
  38| 
  39| ## 代码位置
  40| - `problems/leetcodecn/trapping-rain-water/brute.cpp`
  41| - `problems/leetcodecn/trapping-rain-water/gen.py`
  42| - `problems/leetcodecn/trapping-rain-water/main.cpp`
  43| - `problems/leetcodecn/trapping-rain-water/main.py`