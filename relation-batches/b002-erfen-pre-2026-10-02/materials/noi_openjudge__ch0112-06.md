# noi_openjudge ch0112-06 寻宝

> 原文摘录，非模型摘要。来源：`problems/noi_openjudge/ch0112-06/index.md`。

## 元信息（frontmatter 摘录）
- 难度：普及+/提高；标签：['模拟', '二分', 'python']

## 题目解析（原文摘录）

[[TOC]]

### 题意

从底层给定房间出发，每层按门牌数字选择循环方向上的第 $x$ 个有楼梯房间，并累加每层进入房间的门牌数。

### 思路

每层预处理所有楼梯房间编号。`bisect_left` 找到从当前房间开始遇到的第一个楼梯，其在楼梯列表中的位置加上 `x - 1` 再对楼梯数取模，就是目标房间。这样无需逐个数到 $x$，适合门牌数字很大的情况。

### 代码

## Python代码

@include-code(./main.py, python)

## C++代码

@include-code(./main.cpp, cpp)

### 复杂度

预处理时间和空间为 $O(NM)$，每层定位为 $O(\log M)$。

### 总结

循环选择第 $x$ 个元素时，转化为下标加法和取模可避免线性模拟。

## 代码位置
- `problems/noi_openjudge/ch0112-06/main-cout.cpp`
- `problems/noi_openjudge/ch0112-06/main.cpp`
- `problems/noi_openjudge/ch0112-06/main.py`
