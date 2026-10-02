# leetcodecn search-in-rotated-sorted-array 搜索旋转排序数组

> 原文摘录，非模型摘要。来源：`problems/leetcodecn/search-in-rotated-sorted-array/index.md`。

## 元信息（frontmatter 摘录）
- 难度：普及+/提高；标签：['二分查找', '数组']

## 题目解析（原文摘录）

### 题意

给定旋转一次的升序无重复数组，查找 `target` 的下标，不存在返回 `-1`。要求 $O(\log n)$。

### 思路

虽然数组整体无序，但二分后必有一半是有序的。判断方法：若 `nums[l] <= nums[mid]`，左半有序；否则右半有序。

确定有序半区后，判断 `target` 是否落在该半区的值域内：

- 左半有序且 `nums[l] <= target < nums[mid]`：`r = mid - 1`，搜索左半。
- 左半有序但 `target` 不在左半：`l = mid + 1`，搜索右半。
- 右半有序且 `nums[mid] < target <= nums[r]`：`l = mid + 1`，搜索右半。
- 右半有序但 `target` 不在右半：`r = mid - 1`，搜索左半。

每轮排除一半，保证 $O(\log n)$。

## 代码位置
- `problems/leetcodecn/search-in-rotated-sorted-array/main.cpp`
- `problems/leetcodecn/search-in-rotated-sorted-array/main.py`
