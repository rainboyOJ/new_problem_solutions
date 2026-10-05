# leetcodecn median-of-two-sorted-arrays 寻找两个正序数组的中位数

> 原文摘录，非模型摘要。来源：`problems/leetcodecn/median-of-two-sorted-arrays/index.md`。

## 元信息（frontmatter 摘录）
- 难度：提高+/省选-；标签：['二分查找', '数组']

## 题目解析（原文摘录）

### 题意

给定两个正序数组，找中位数。要求 $O(\log(m+n))$。

### 思路

中位数等价于把合并后数组分成左右两半，使得左半最大 $\leqslant$ 右半最小，且左半元素数 $=$ 右半元素数（或恰好多一个）。

在较短数组 `a` 上二分分割线位置 `i`（`a` 左半取 `a[0..i-1]`），`b` 的分割位置 `j = (m+n+1)/2 - i` 自动确定。四个边界值 `al, ar, bl, br` 分别表示分割线两侧的值（越界用 $\pm\infty$）。

条件 `al <= br && bl <= ar` 满足时分割合法，中位数由 `max(al,bl)` 和 `min(ar,br)` 计算。`al > br` 时 `i` 太大，`bl > ar` 时 `i` 太小。

## 代码位置
- `problems/leetcodecn/median-of-two-sorted-arrays/main.cpp`
- `problems/leetcodecn/median-of-two-sorted-arrays/main.py`
