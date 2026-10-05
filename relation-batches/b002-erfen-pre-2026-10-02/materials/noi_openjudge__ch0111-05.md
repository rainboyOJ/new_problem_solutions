# noi_openjudge ch0111-05 派

> 原文摘录，非模型摘要。来源：`problems/noi_openjudge/ch0111-05/index.md`。

## 元信息（frontmatter 摘录）
- 难度：普及-；标签：['二分', '几何', 'python']

## 题目解析（原文摘录）

[[TOC]]

### 题意

把若干圆形派分给所有朋友和自己，每人得到一块面积相同的派，求这块派的最大面积。

### 思路

半径为 $r$ 的派面积为 $\pi r^2$。假设每块面积为 $x$，一张派能切出 `int(面积 / x)` 块；所有派合计至少有 `F + 1` 块时，$x$ 可行。面积越小可切块数越多，因此可以在 $[0, 最大派面积]$ 上二分。

### 代码

## Python代码

@include-code(./main.py, python)

## C++代码

@include-code(./main.cpp, cpp)

### 复杂度

二分固定 100 次，时间复杂度为 $O(n)$，空间复杂度为 $O(n)$。

### 总结

实数二分不必等到端点相等，迭代足够多次即可保证输出精度。

## 代码位置
- `problems/noi_openjudge/ch0111-05/main-cout.cpp`
- `problems/noi_openjudge/ch0111-05/main.cpp`
- `problems/noi_openjudge/ch0111-05/main.py`
