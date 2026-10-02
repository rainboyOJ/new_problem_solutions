# leetcodecn search-insert-position 搜索插入位置

> 原文摘录，非模型摘要。来源：`problems/leetcodecn/search-insert-position/index.md`。

## 元信息（frontmatter 摘录）
- 难度：普及-；标签：['二分查找', '数组']

## 题目解析（原文摘录）

### 题意

给定升序无重复数组 `nums` 和目标值 `target`，返回 `target` 在数组中的索引；若不存在，返回按顺序插入的位置。要求 $O(\log n)$。

### 思路

本题本质是求 `lower_bound`：区间内第一个 $\geqslant \text{target}$ 的位置。C++ 直接调用 `lower_bound`；Python 手写二分，谓词 `nums[m] >= target` 缩右区间，`nums[m] < target` 缩左区间。

关键理解：`lower_bound` 返回的位置既是"已存在元素的索引"（若该元素等于 `target`），也是"应插入的位置"（若不存在）。二者统一在同一次二分中。

## 代码位置
- `problems/leetcodecn/search-insert-position/brute.cpp`
- `problems/leetcodecn/search-insert-position/gen.py`
- `problems/leetcodecn/search-insert-position/main.cpp`
- `problems/leetcodecn/search-insert-position/main.py`
