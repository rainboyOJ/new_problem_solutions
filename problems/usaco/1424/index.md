---
oj: "usaco"
problem_id: "1424"
title: "The 'Winning' Gene"
description: "固定候选起点和长度，用 LCP 与单调指针求最大可行 K，再用差分统计每个 pair 的 winner 数。"
difficulty: "普及+/提高"
date: 2026-07-11 20:58
toc: true
tags: ["字符串", "LCP", "差分", "usaco"]
categories: []
pre: []
common: []
recommend: []
source: https://usaco.org/index.php?page=viewproblem2&cpid=1424
---

[[TOC]]

### 题意

给定字符串 $S$，长度为 $N$。

对每一对 $(K,L)$，其中 $1\leqslant L\leqslant K\leqslant N$：

- 枚举所有长度为 $K$ 的子串；
- 在每个长度为 $K$ 的子串中，找字典序最小的长度为 $L$ 的子串；
- 如果有多个最小值，取最左边的那个；
- 把这些 winner 在原串里的起点加入集合 $P$。

要求对每个 $v=1..N$，统计有多少对 $(K,L)$ 满足 $|P|=v$。

### 思路

先看一个直接模拟题意的暴力：

@include-code(./brute.cpp, cpp)

暴力枚举每个 $(K,L)$，再枚举每个 `K-mer` 内的所有长度 $L$ 子串。它很适合确认题意，但复杂度过高。

换一个方向：不直接问某个 $(K,L)$ 有多少 winner，而是固定一个位置 $p$ 和长度 $L$，问它能在哪些窗口长度 $K$ 下成为 winner。

设当前候选串为：

```text
T = S[p..p+L-1]
```

如果某个窗口要让 $p$ 成为 winner，它不能包含下面这些阻挡位置：

| 位置 | 阻挡条件 | 原因 |
| --- | --- | --- |
| 左侧 $a<p$ | $S[a..a+L-1]\leqslant T$ | 更小会赢；相等时最左边会赢 |
| 右侧 $b>p$ | $S[b..b+L-1]<T$ | 只有严格更小时才会抢走 winner |

只需要看最近的两个阻挡位置：

- `a`：左侧最大的阻挡位置；
- `b`：右侧最小的阻挡位置。

为了避开左阻挡，可以把窗口起点放在 `a+1`。这个窗口中最后一个长度 $L$ 子串的起点是：

```text
a + 1 + K - L
```

它必须在 `b` 左边：

```text
a + 1 + K - L < b
```

整理得到：

```text
K <= b + L - a - 2
```

所以固定 $p,L$ 后，它会对所有窗口长度：

```text
L <= K <= maxK
```

贡献一个 winner。

接下来要快速求左右阻挡位置。先预处理 LCP：

```text
lcp[i][j] = S[i..] 和 S[j..] 的最长公共前缀长度
```

倒序转移：

```text
S[i] == S[j] 时，lcp[i][j] = lcp[i+1][j+1] + 1
```

有了 LCP，两个长度为 $L$ 的子串比较可以做到 $O(1)$。

对固定 `p`，随着 `L` 变化，左右阻挡位置可以用单调指针维护。于是所有 `p,L` 的贡献可以在 $O(N^2)$ 内处理。

最后用 `delta_cnt[L][maxK]++` 记录区间 `[L,maxK]` 的贡献。对每个 `L` 从大到小扫 `K`：

```text
winners += delta_cnt[L][K]
answer_cnt[winners]++
```

此时 `winners` 就是当前 pair `(K,L)` 的 $|P|$。

### 代码

@include-code(./main.cpp, cpp)

### 复杂度

预处理 LCP 为 $O(N^2)$。

枚举每个位置并用单调指针统计贡献，总复杂度为 $O(N^2)$。

最后汇总 `delta_cnt` 也是 $O(N^2)$。

空间复杂度为 $O(N^2)$。

### 总结

本题的关键转化是：从“一个 $(K,L)$ 有哪些 winner”，改成“一个位置 $p$ 能为哪些 $(K,L)$ 贡献 winner”。

左侧相等会抢走 winner，右侧相等不会抢走 winner，这是最容易写错的地方。处理好左右阻挡后，每个位置的贡献就是一段连续的窗口长度区间，再用差分统计即可。
