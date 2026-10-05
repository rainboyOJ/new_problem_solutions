# leetcodecn find-first-and-last-position-of-element-in-sorted-array 在排序数组中查找元素的第一个和最后一个位置

> 原文摘录，非模型摘要。来源：`problems/leetcodecn/find-first-and-last-position-of-element-in-sorted-array/index.md`。

## 元信息（frontmatter 摘录）
- 难度：普及+/提高；标签：['二分查找', '数组']

## 题目解析（原文摘录）

### 题意

给定非递减排序的整数数组 `nums` 和整数 `target`，返回 `target` 在数组中的起止下标 `[first, last]`；不存在则返回 `[-1, -1]`。

要求时间复杂度 $O(\log n)$。

### 思路

线性扫描可以找到答案，但需要 $O(n)$ 时间。利用数组有序性，可以用两次二分将复杂度降到 $O(\log n)$：

先看一个可以直接验证想法的朴素解：

@include-code(./brute.cpp, cpp)

朴素解线性扫描整个数组，时间 $O(n)$，不满足进阶要求。

优化的关键是：`lower_bound` 返回第一个 $\geqslant \text{target}$ 的位置，`upper_bound` 返回第一个 $> \text{target}$ 的位置。若 `lower_bound` 所指元素恰好等于 `target`，则 `lower_bound` 就是起始下标，`upper_bound - 1` 就是终止下标；若不等于，说明 `target` 不存在，返回 `[-1, -1]`。

判断条件 `l > r`（即 `lower_bound > upper_bound - 1`）统一覆盖了空数组、`target` 不存在和 `target` 越界三种情况。

Python 实现用同一个 `bs` 函数，参数 `left=True` 时行为同 `lower_bound`（$\geqslant$），`left=False` 时行为同 `upper_bound`（$>$）。谓词 `nums[m] > target or (left and nums[m] == target)` 在左界模式下把等于也视为"往左缩"，右界模式下只有严格大于才缩左。

## 代码位置
- `problems/leetcodecn/find-first-and-last-position-of-element-in-sorted-array/brute.cpp`
- `problems/leetcodecn/find-first-and-last-position-of-element-in-sorted-array/gen.py`
- `problems/leetcodecn/find-first-and-last-position-of-element-in-sorted-array/main.cpp`
- `problems/leetcodecn/find-first-and-last-position-of-element-in-sorted-array/main.py`
