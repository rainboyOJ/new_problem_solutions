# usaco 1326 Milk Sum

> 原文摘录，非模型摘要。来源：`problems/usaco/1326/index.md`。

## 元信息（frontmatter 摘录）
- 难度：普及+/提高；标签：['排序', '前缀和', '二分', 'usaco']

## 题目解析（原文摘录）

### 题意

有 $N$ 头牛，第 $i$ 头牛每分钟产奶量是 $a_i$。

如果第 $k$ 个被移出挤奶机的牛产奶量是 $x$，它会贡献 $k\cdot x$。为了让总产奶量最大，显然应该让产奶量小的牛先离开，产奶量大的牛后离开。

现在有 $Q$ 个互相独立的询问：如果临时把 $a_i$ 改成 $j$，最大总产奶量是多少？

### 思路

先看一个小数据暴力。每次询问直接修改一个值，重新排序，再计算 $\sum i\cdot a'_i$。

@include-code(./brute.cpp, cpp)

暴力每次都排序，复杂度太高。满分做法只分析“一个元素移动”带来的贡献变化。

先把原数组排序成 `b[1..n]`，基础答案是：

$$
S=\sum_{i=1}^{n} i\cdot b_i
$$

同时记录原来的第 `idx` 个数在排序数组中的位置 `old_pos`。

一次询问把旧值 `old_val` 改成 `val`，等价于：

1. 从排序数组中删除 `old_pos` 位置的旧值；
2. 把新值 `val` 插入到它应该在的新位置 `new_pos`。

`new_pos` 可以用 `lower_bound` 找到。需要注意：如果 `val > old_val`，旧值被删除后，新值的插入位置要向左修正一格。

删除旧值后，如果 $new_pos >= old_pos$，说明旧值右侧的一段数会整体左移一格：

```text
old_pos + 1 ... new_pos
```

这些数的系数都减少 `1`，所以总贡献减少这一段的元素和。

如果 `new_pos < old_pos`，说明左侧的一段数会整体右移一格：

```text
new_pos ... old_pos - 1
```

这些数的系数都增加 `1`，所以总贡献增加这一段的元素和。

区间和用排序数组的前缀和 `prefix_sum[]` 在 $O(1)$ 内求出，整次询问只剩下二分的 $O(\log N)$。

## 代码位置
- `problems/usaco/1326/brute.cpp`
- `problems/usaco/1326/gen.py`
- `problems/usaco/1326/main.cpp`
