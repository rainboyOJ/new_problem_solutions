# noi_openjudge ch0111-02 二分法求函数的零点

> 原文摘录，非模型摘要。来源：`problems/noi_openjudge/ch0111-02/index.md`。

## 元信息（frontmatter 摘录）
- 难度：入门；标签：['二分', '数学', 'python']

## 题目解析（原文摘录）

[[TOC]]

### 题意

已知五次函数在区间 $[1.5, 2.4]$ 内恰有一个零点，输出该零点并保留六位小数。

### 思路

区间端点函数值异号，且根唯一。每次取中点，根据中点函数值的符号保留仍包含零点的一半区间。固定迭代 100 次后误差远小于输出精度。

### 代码

## Python代码

@include-code(./main.py, python)

## C++代码

@include-code(./main.cpp, cpp)

### 复杂度

固定进行 100 次二分，时间复杂度为 $O(1)$，空间复杂度为 $O(1)$。

### 总结

连续函数的唯一零点可用端点异号性质定位，二分时无需显式求解方程。

## 代码位置
- `problems/noi_openjudge/ch0111-02/main-cout.cpp`
- `problems/noi_openjudge/ch0111-02/main.cpp`
- `problems/noi_openjudge/ch0111-02/main.py`
