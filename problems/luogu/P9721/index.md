---
oj: "luogu"
problem_id: "P9721"
title: "[EC Final 2022] Inversion"
description: "用 inv(l,r)^inv(l+1,r)^inv(l,r-1)^inv(l+1,r-1) 两次询问判断两个位置的大小，再做插入排序式的二分定位，总询问不超过 39906。"
difficulty: "提高+/省选-"
date: 2026-10-02 15:23
updated: 2026-10-03 12:47
toc: true
tags: ["交互题", "二分", "插入排序", "逆序对", "奇偶性"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P9721
---

[[TOC]]

## 形式化题目

有一个隐藏的排列 $p_1,p_2,\dots,p_n$，你只能通过询问获取信息：每次给出 $1\leqslant l\leqslant r\leqslant n$，对方回答

$$
\left(\sum_{l\leqslant i<j\leqslant r}[p_i>p_j]\right)\bmod 2,
$$

也就是区间 $p_l,\dots,p_r$ 内逆序对个数的奇偶性。询问次数不能超过 $4\times10^4$，最后要输出整个排列 $p_1,\dots,p_n$。

## 暴力解法

### 思路

最直接的做法是**逐个位置硬算大小关系**。

第一步，先把「任意区间内逆序对个数的奇偶性」全部搞到手。记

$$
\mathrm{inv}(l,r)=\left(\sum_{l\leqslant i<j\leqslant r}[p_i>p_j]\right)\bmod 2 .
$$

固定 $r$ 并让 $l$ 从 $r-1$ 递减，用变量 $\mathrm{cnt}$ 维护 $[l,r-1]$ 中比 $p_r$ 大的元素个数，就有递推

$$
\mathrm{inv}(l,r)=\mathrm{inv}(l,r-1)\oplus(\mathrm{cnt}\bmod 2).
$$

第二步，$p_i$ 恰好等于「比它大的元素个数」再加 $1$，于是只要得到两两大小关系就够了：

$$
p_i=n-\#\{j: p_j>p_i\}+1 .
$$

那么怎么用区间逆序对去问出两个单点的大小关系？关键恒等式是

$$
[p_l>p_r]=\mathrm{inv}(l,r)\oplus\mathrm{inv}(l+1,r)\oplus\mathrm{inv}(l,r-1)\oplus\mathrm{inv}(l+1,r-1),
$$

其中约定 $l\geqslant r$ 时 $\mathrm{inv}(l,r)=0$。把 $[l,r]$ 内的逆序对按「是否用到 $p_l$」「是否用到 $p_r$」分成四类，前三类分别是 $\mathrm{inv}(l+1,r)$、$\mathrm{inv}(l,r-1)$、$\mathrm{inv}(l+1,r-1)$，而第四类被异或了三次（每次都要用到 $p_l,p_r$，其贡献被算 $3$ 次后剩下 $1$ 次），加上 $p_l>p_r$ 本身的贡献正好拼成 $\mathrm{inv}(l,r)$。

所以暴力就是：对所有 $\binom{n}{2}$ 个位置对都按上面的式子判断一次大小关系，累加出每个位置的名次。做法**绝对正确**，但代价是 $\Theta(n^2)$ 次询问，$n=2000$ 时约 $2\times10^6$ 次，超限 $50$ 倍。

### 代码

@include-code(./brute.cpp, cpp)

### 复杂度

时间复杂度 $O(n^2)$（本地对拍时还要 $O(n^2)$ 打交互器答案表），询问次数 $\Theta(n^2)$。

### 瓶颈

询问次数是 $\Theta(n^2)$ 量级，远远超过 $4\times10^4$。而信息量其实足够：每次询问给出 $1$ bit，$4\times10^4$ 个 bit 早已超过还原 $2000!$ 种排列所需。**问题不在于信息不够，而在于暴力没有复用已经获得的信息。**

## 正解

### 思路

突破口在于：我们真正需要的是「每个元素在已确定前缀里排第几」，而这件事天然适合**插入排序 + 二分**。

**第一步：把「比大小」的代价压到 2 次询问。**

沿用前面推出的恒等式

$$
[p_l>p_r]=\mathrm{inv}(l,r)\oplus\mathrm{inv}(l+1,r)\oplus\mathrm{inv}(l,r-1)\oplus\mathrm{inv}(l+1,r-1).
$$

如果每比较一次都要现查 4 个值，代价就太高了。注意到插入排序是**逐个处理位置**的：处理到 $i$ 时，前面 $i-1$ 个位置已经排好。记

$$
E[l]=\mathrm{inv}(l,i-1),
$$

即「从位置 $l$ 到当前已插入前缀末尾」的逆序对奇偶性。那么恒等式中的后两项就变成了 $E[l]$ 与 $E[l+1]$，只剩下 $\mathrm{inv}(l,i)$ 和 $\mathrm{inv}(l+1,i)$ 需要现问：

$$
[p_l>p_i]=\mathrm{inv}(l,i)\oplus\mathrm{inv}(l+1,i)\oplus E[l]\oplus E[l+1].
$$

这里每次比较用掉 2 次询问；当 $l+1=i$ 时 $\mathrm{inv}(l+1,i)=\mathrm{inv}(i,i)=0$ 不必询问，只用 1 次。这正是全部代价的来源。

**第二步：二分找名次。**

插入 $p_i$ 时，维护一张有序表 $elem\_at[0..i-2]$，其中 $elem\_at[t]$ 是当前前缀里名次为 $t$（$0$ 起始）的元素下标。要确定 $p_i$ 的名次，就是找最小的 $r$ 使 $p_{elem\_at[r]}>p_i$。数组本身有序，可以直接二分：

```text
lo = 0, hi = i-1
while lo < hi:
    mid = (lo+hi)/2, j = elem_at[mid]
    if p_j > p_i:  hi = mid
    else:          lo = mid+1
r = lo
```

每轮迭代恰好比较一次，比较代价由第一步的公式给出，稳定在 1~2 次询问。

**第三步：用名次增量更新 $E$，不花一次询问。**

定位出名次 $r$ 之后，我们可以顺手算出每个 $l<i$ 的 $[p_l>p_i]$：因为 $E$ 里比较的全是**同一个前缀内**的名次，而名次是前缀内的相对大小，所以

$$
p_l>p_i \iff rank[l]\geqslant r .
$$

于是从 $l=i-1$ 递减扫到 $1$，用变量 $g$ 累积「$[l,i-1]$ 中比 $p_i$ 大的元素个数」的奇偶性：

$$
g\mathrel{\oplus}=[rank[l]\geqslant r],\qquad E[l]\mathrel{\oplus}=g .
$$

这一步只动数组、不发询问。最后把 $i$ 在有序表里的名次 $r$ 落实：名次 $\geqslant r$ 的元素整体后移一位，并令 $rank[i]=r$、$E[i]=0$（$\mathrm{inv}(i,i)=0$）。

循环 $n$ 轮之后，$rank[i]+1$ 就是 $p_i$，直接按位置输出即可。

### 询问次数为什么够用

插入 $p_i$ 时二分区间长度为 $i-1$，最坏迭代 $\lceil\log_2 i\rceil$ 次，每次 2 次询问，所以总询问次数不超过

$$
2\sum_{i=1}^{n}\lceil\log_2 i\rceil = 2\times 19953 = 39906 < 40000 \quad (n=2000).
$$

题面上限偏偏卡在 $4\times10^4$ 而不是 $2^k$ 之类的整数，正是为了逼出这个 $2$ 倍常数：只要一次比较花 3 次询问（$\approx 59859$）或比较次数再多一点就会被卡掉。另外注意 $p_1$ 不需要比较，$i=1$ 那一项贡献为 0。

### 代码

@include-code(./main.cpp, cpp)

### 复杂度

时间复杂度 $O(n^2)$（每轮插入的 $E$ 更新与有序表后移各是 $O(n)$，只有 $\log$ 次真的发询问），空间 $O(n)$ 辅助数组加 $O(n^2)$ 的本地对拍表；真实交互时询问次数 $\leqslant 39906$。

## 总结

- **核心恒等式**：$[p_l>p_r]=\mathrm{inv}(l,r)\oplus\mathrm{inv}(l+1,r)\oplus\mathrm{inv}(l,r-1)\oplus\mathrm{inv}(l+1,r-1)$，把「单点比较」化成「区间逆序对奇偶性」的四项异或。
- **降常数**：按位置顺序插入、维护 $E[l]=\mathrm{inv}(l,i-1)$，把恒等式中的两项变成已知，单次比较只要 2 次询问（$l=i-1$ 时 1 次）。
- **二分 + 增量更新**：在有序表里二分定名次，再用 $p_l>p_i \iff rank[l]\geqslant r$ 在 $O(n)$ 次数组操作内把 $E$ 从 $i-1$ 推进到 $i$，不额外消耗询问。
- **复杂度记账**：$2\sum_{i=1}^{n}\lceil\log_2 i\rceil=39906$，刚好卡在 $4\times10^4$ 上限之内——上限的数字本身就是「插入排序二分 + 2 次询问」这个做法的签名。
