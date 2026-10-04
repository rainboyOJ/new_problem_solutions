---
oj: "roj"
problem_id: "1139"
title: "整理药名"
description: "逐个药名独立规范化：首位用 w[:1].upper()，其余用 w[1:].lower() 拼接；数字和 - 因大小写方法恒等而自动原样保留。"
difficulty: "入门"
date: 2026-09-29 20:37
updated: 2026-10-04 10:23
toc: true
tags: ["入门", "字符串", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1139
---

[[TOC]]

## 形式化题目

给定 $n$ 个字符串 $w^{(1)}, w^{(2)}, \dots, w^{(n)}$，每个 $w^{(i)}$ 只由英文字母、数字和 `-` 组成。定义映射 $f$：

$$
f(w)_j =
\begin{cases}
\operatorname{upper}(w_0), & j = 0 \\
\operatorname{lower}(w_j), & j \geqslant 1
\end{cases}
$$

其中 $\operatorname{upper}$、$\operatorname{lower}$ 对**非字母字符**是恒等映射（数字和 `-` 保持不变）。要求按输入顺序输出 $f(w^{(1)}), \dots, f(w^{(n)})$，一行一个。

也就是说：每个字符串的首字符若是字母则改为大写，其余位置的字母一律改为小写，非字母字符原样保留。

### 样例

对样例输入 $w = (\text{AspiRin},\ \text{cisapride},\ \text{2-PENICILLIN},\ \text{Cefradine-6})$：

| 输入 | 首字符 `w[:1]` | 其余部分 `w[1:]` | 输出 |
| --- | --- | --- | --- |
| `AspiRin` | `A`（已是大写） | `spiRin` → `spirin` | `Aspirin` |
| `cisapride` | `c` → `C` | `isapride`（已小写） | `Cisapride` |
| `2-PENICILLIN` | `2`（数字，不动） | `-PENICILLIN` → `-penicillin` | `2-penicillin` |
| `Cefradine-6` | `C`（已是大写） | `efradine-6`（已小写） | `Cefradine-6` |

表格把每个单词拆成互不重叠的两段：第 2 列是长度为 1 的前缀，第 3 列是下标 $1$ 起的后缀。可以看到两段各自只经历一次映射，`-` 和数字落在哪一段都原样保留——`2-PENICILLIN` 这一行正是"首字符不是字母"的边界。

## 正解

### 思路

**关键观察一：每个单词互不影响。** 第 $i$ 行的输出只由第 $i$ 个输入单词决定，不依赖其它行，也不需要排序或去重。所以问题可以逐个单词独立解决，不存在全局结构。

**关键观察二：规则是逐字符、无上下文的。** 每个位置的字符该做什么变换，只由"它是不是首位"和"它是不是字母"决定，与相邻字符无关。这让我们可以用**切片**一次拿到两段，而不必写逐字符循环。

于是把 $w$ 切成 `w[:1]` 和 `w[1:]` 后分别套规则：

```python
w[:1].upper() + w[1:].lower()
```

**关键观察三：`isalpha()` 判断可以省掉。** 题面要求"非字母原样保留"，而 Python 的 `str.upper()` / `str.lower()` 对数字和 `-` 本来就返回原字符（`'2'.upper() == '2'`、`'-'.lower() == '-'`），所以这条规则**自动满足**，不需要写 `if c.isalpha()` 分支。

先用朴素的逐字符写法对照一下：

```python
ans = []
for i, c in enumerate(word):
    if i == 0:
        ans.append(c.upper())      # 首位：字母则大写，非字母恒等
    else:
        ans.append(c.lower())      # 其余：字母则小写，非字母恒等
```

两种写法复杂度同为 $O(L)$，差别在常数：切片 + 两个内建方法是 C 层实现的整体扫描，比 Python 层的 `for` + `append` 快一个数量级，代码也更短。

两个容易踩的坑：

- **不要用 `w.title()`**。它把每个非字母边界后的字母都大写，`"2-penicillin".title()` 得到 `"2-Penicillin"`，与要求的 `"2-penicillin"` 不符。
- **不要用 `w[0]`**。空串上 `w[0]` 会抛 `IndexError`，而 `w[:1]` 对空串返回 `''`，是全定义的，且不增加任何成本。

**正确性。** 设 $w$ 长度 $L$。输出的第 $0$ 个字符来自 `w[:1].upper()`：$w_0$ 是字母时得到它的大写（规则一），非字母时原样返回（非字母不转换）。输出的第 $i$ 个字符（$1 \leqslant i < L$）来自 `w[1:].lower()` 的第 $i-1$ 个字符，即 $w_i$ 的小写（规则二），非字母时原样保留。切片保序，拼接后长度仍为 $L$、字符顺序不变，故 $f(w)$ 恰好满足题面两条规则；又由观察一，对全部 $n$ 个单词同时成立。

### 代码

@include-code(./main.py, python)

### 复杂度

设所有单词总长度为 $S = \sum_{i} L_i$，本题 $S \leqslant 100 \times 20 = 2000$。

- 时间：每个单词的两次切片映射共扫描 $O(L_i)$ 个字符，合计 $O(S)$。
- 空间：读入的全部 token 与输出字符串共 $O(S)$。

实测单组最大数据约 0.019 s、峰值约 14.6 MB，相对 1000 ms / 128 MB 余量极大。

## 总结

- 本题是逐字符串的独立映射，不需要任何跨行结构，**逐个单词处理**即可。
- 把单词切成**首位**和**其余部分**两段，分别用 `upper()` 和 `lower()`，正好对应题面两条规则。
- 非字母字符的保留是 `upper()`/`lower()` 的**恒等性质**带来的，不必显式判断 `isalpha()`。
- 避开 `title()` 的边界陷阱，以及 `w[0]` 对空串的越界问题。
