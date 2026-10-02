# luogu P2423 [HEOI2012] 朋友圈

> 原文摘录，非模型摘要。来源：`problems/luogu/P2423/index.md`。

## 元信息（frontmatter 摘录）
- 难度：省选/NOI-；标签：['二分图']

## 题目解析（原文摘录）

## 题目大意

我们有两个国家 A 和 B，每个国家有若干人，每个人有一个友善值（整数）。朋友关系定义如下：

1. **A 国内部**：两人友善值 \(a, b\) 满足 \((a \oplus b) \bmod 2 = 1\)（即奇偶性不同）时是朋友。
2. **B 国内部**：两人友善值 \(a, b\) 满足 \((a \oplus b) \bmod 2 = 0\) 或 \((a \operatorname{or} b)\) 的二进制表示有奇数个 1 时是朋友。
3. **A 与 B 之间**：给出 M 对朋友关系（双向）。

“朋友圈”是一个点集，其中任意两人都是朋友。求最大的朋友圈大小。

**多组数据**，\(T \leqslant 6\)。

数据范围有两类：

- 第一类：\(A \leqslant 200,\ B \leqslant 200\)
- 第二类：\(A \leqslant 10,\ B \leqslant 3000\)

## 算法思路

## 代码位置
- `problems/luogu/P2423/1.cpp`
- `problems/luogu/P2423/2.cpp`
