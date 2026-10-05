# noi_openjudge ch0111-10 河中跳房子

> 原文摘录，非模型摘要。来源：`problems/noi_openjudge/ch0111-10/index.md`（内容哈希 a1b915980a82db20）。

## 元信息（frontmatter 摘录）
- 难度：普及+/提高；标签：["二分", "贪心", "python"]

## 题目解析（原文摘录）

[[TOC]]

### 题意

最多移走 $M$ 块中间石头，使从起点到终点的最短一次跳跃距离尽量大。

### 思路

二分候选最短距离 `distance`。从左到右扫描，当前石头与上一个保留位置的距离不足时必须删除一个，贪心地计数即可得到满足该距离至少需要删多少块。若不超过 $M$，该距离可行。

### 代码

## Python代码

@include-code(./main.py, python)

## C++代码

@include-code(./main.cpp, cpp)

### 复杂度

时间复杂度为 $O(n \log L)$，空间复杂度为 $O(n)$。

### 总结

最大化最小跳跃距离是典型的二分答案问题，判定过程由局部贪心完成。

## 代码位置
- `problems/noi_openjudge/ch0111-10/main.cpp`
- `problems/noi_openjudge/ch0111-10/main.py`
