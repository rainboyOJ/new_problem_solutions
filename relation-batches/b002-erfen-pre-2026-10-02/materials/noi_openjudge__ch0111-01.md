# noi_openjudge ch0111-01 查找最接近的元素

> 原文摘录，非模型摘要。来源：`problems/noi_openjudge/ch0111-01/index.md`。

## 元信息（frontmatter 摘录）
- 难度：普及-；标签：['二分', '排序', 'python']

## 题目解析（原文摘录）

[[TOC]]

### 题意

在非降序列中回答多次查询：输出与查询值距离最小的元素；距离相同则选较小值。

### 思路

`bisect_left(numbers, target)` 找到第一个不小于查询值的位置。最接近的元素只可能是这个位置或其左邻居；处理越界后比较两边距离。相等时选择左边，正好满足取较小值的规则。

### 代码

## Python代码

@include-code(./main.py, python)

## C++代码

@include-code(./main.cpp, cpp)

### 复杂度

每次查询时间复杂度为 $O(\log n)$，额外空间复杂度为 $O(1)$。

### 总结

有序序列中的“最接近”问题，只需检查二分定位点附近的两个候选。

## 代码位置
- `problems/noi_openjudge/ch0111-01/main.cpp`
- `problems/noi_openjudge/ch0111-01/main.py`
