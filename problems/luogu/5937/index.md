---
oj: "luogu"
problem_id: "P5937"
title: "[CEOI 1999] Parity Game"
description: "把区间奇偶转成两个前缀异或值的关系，用带异或权并查集在线定位第一条矛盾回答。"
difficulty: "普及+/提高"
date: 2026-07-16 17:48
toc: true
tags: ["并查集", "前缀和", "离散化", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P5937
---

[[TOC]]

### 题意

依次给出若干区间中 $1$ 的个数为奇数或偶数的回答，求第一条必然与此前回答矛盾的回答之前有多少条正确回答。

### 思路

#### 1. 关键转换——用前缀和表示区间

定义**前缀异或和** `prefix[i]` = 前 i 个数中 1 的个数的奇偶性（0=偶数，1=奇数）。

```
位置:    1   2   3   4   5
序列:    0   1   1   0   1
prefix:  0   1   0   0   1
         ↑
    prefix[0]=0（空序列）
```

区间 [l, r] 里 1 的奇偶性 = **prefix[r] XOR prefix[l-1]**：

```
prefix[l-1]    ┌───区间[l,r]───┐    prefix[r]
    ├─────────┼───────────────┼────────┤
    前 l-1 个                   前 r 个

    prefix[r] XOR prefix[l-1] = 区间内1的奇偶性
```

所以每个回答变成两个前缀变量之间的**关系**：

| 回答 | 翻译 |
|---|---|
| `[l, r] even` | `prefix[r] == prefix[l-1]` |
| `[l, r] odd`  | `prefix[r] != prefix[l-1]` |

#### 2. 用图来表示关系

把每个 prefix[i] 看成一个**节点**（值 0 或 1，未知），每条回答是一条边（`==` 相等 或 `!=` 不等）。

样例：

```
回答1: 1 2 even   → prefix[0] == prefix[2]
回答2: 3 4 odd    → prefix[2] != prefix[4]
回答3: 5 6 even   → prefix[4] == prefix[6]
回答4: 1 6 even   → prefix[0] == prefix[6]
回答5: 7 10 odd   → prefix[6] != prefix[10]
```

回答1~3 建好的图：

```
                   ==              !=               ==
  prefix[0] ────────── prefix[2] ───────── prefix[4] ───────── prefix[6]
```

回答4 来了：说 prefix[0] == prefix[6]。但沿着已有链推算：

```
prefix[0] == prefix[2]     （回答1）
prefix[2] != prefix[4]     （回答2）
prefix[4] == prefix[6]     （回答3）

→ prefix[0] != prefix[6]   （沿着链，相反！）
```

回答4 说相等，矛盾！所以第 4 条回答是第一条有问题的，输出 `3`。

#### 3. 带权并查集

普通并查集只能判断"在不在同一集合"，这里还要维护**关系是什么**（相同 0 / 相反 1）。

每个节点多存一个 `parity[x]`：

```
parity[x] = 节点 x 和它的根 root[x] 的关系
          0 → 相同
          1 → 相反
```

```
   root
    ↑ par=0           A 的值 = root 的值
    A
    ↑ par=1
    B                 B 的值 = root 的值 取反
```

**路径压缩时折叠关系：**

```
压缩前：                    压缩后：
   root                       root
    ↑ par=0                 ↙  ↑  par=1 (0 XOR 1)
    A                   A     │
    ↑ par=1            ↗      │
    B                B       par=0

公式：parity[B] ^= parity[A]
```

**合并两棵树：**

已知 A 和 B 的期望关系 = `expected`（0=相同, 1=相反），
从公式推出 `parity[root_B] = expected XOR parity[A] XOR parity[B]`。

**判冲突：**

如果 A 和 B 已在同一集合，检查 `parity[A] XOR parity[B] == expected`。

#### 4. 示例跟踪

```
回答1: unite(0, 2, 0)  分属不同集合 → parent[2]=0, parity[2]=0
回答2: unite(2, 4, 1)  分属不同集合 → parent[4]=0, parity[4]=1
回答3: unite(4, 6, 0)  分属不同集合 → parent[6]=0, parity[6]=1
```

此时并查集结构：

```
    0 ← root
   ↗ ↑  ↖
  2   4   6
par:0  1   1
      (4 和 6 都跟 root 相反 → 4 和 6 相同 ✓)
```

```
回答4: unite(0, 6, 0)
  find(0)→root=0, par=0
  find(6)→root=0, par=1
  已在同一集合！检查：0 XOR 1 = 1 ≠ 0 → 矛盾！
```

输出 `3` ✅

### Python 知识

- 三个字典分别保存 `parent`、`size`、`parity`，n 到 1e9 但只需存实际出现的前缀位置。
- 递归 `find` 在回溯时做路径压缩并同步折叠 parity 值。
- `word == b"odd"` 得到 `True`（值为 1），可参与异或运算。

### 代码

@include-code(./main.py, python)

### 复杂度

时间复杂度 $O(m\alpha(m))$，空间复杂度 $O(m)$。

### 总结

**区间奇偶 → 前缀 XOR 关系 → 带权并查集判冲突。** parity[x] 记录节点与根的异同，路径压缩时折叠关系；若两点已在同一集合，用 parity[A] XOR parity[B] 验证是否与回答一致。

---

## 2N并查集解法

另一种更直观的做法：**"敌人的敌人是朋友"**——不关心 XOR 权重，纯靠并查集。

### 核心思想

对每个前缀位置 `i`，建**两个节点**分别代表两种可能的取值：

```
节点 i     → prefix[i] = 0
节点 i+N   → prefix[i] = 1   （N = 出现过的不同前缀位置数）
```

每条回答就是一次"拉帮结派"：

| 回答 | 约束 | 操作 |
|---|---|---|
| `[l,r] even` | prefix[A] == prefix[B] | `union(A, B)` 且 `union(A+N, B+N)` |
| `[l,r] odd`  | prefix[A] != prefix[B] | `union(A, B+N)` 且 `union(A+N, B)` |

- **even**（相等）：A 和 B 必须是同类 → A0 跟 B0 一伙，A1 跟 B1 一伙
- **odd**（不等）：A 和 B 必须是异类 → A0 跟 B1 一伙，A1 跟 B0 一伙

最后检查：如果 `find(A) == find(A+N)`，说明 prefix[A] 被逼得必须同时等于 0 和 1 → **矛盾**。

### 直觉："敌人的敌人是朋友"

```
回答1: A != B    →  A0─B1   A1─B0      (A 和 B 是敌人)
回答2: B != C    →  B0─C1   B1─C0      (B 和 C 是敌人)

连起来看：
  A0 ─── B1 ─── C0          → A0 和 C0 在同一个集合！
  A1 ─── B0 ─── C1          → A1 和 C1 在同一个集合！

→ A == C （敌人的敌人是朋友）
```

这就是并查集自动推导出的结果。

### 示例跟踪

样例前缀位置：0, 2, 4, 6, 10 → 共 5 个不同位置，N=5。
节点：0..4 为"=0"，5..9 为"=1"。

```
回答1: 1 2 even → union(0,1), union(5,6)
        前缀0和前缀2归为同类
```

```
回答2: 3 4 odd → union(1, 2+5=7), union(1+5=6, 2)
        前缀2和前缀4归为异类（0↔1互连）
```

```
回答3: 5 6 even → union(2,3), union(7,8)
        前缀4和前缀6归为同类
```

到目前为止，形成的连通关系：

```
前缀0 ── 前缀2 ── 前缀4=1 ── 前缀6=1
  0        1        7         8       （=0的节点）
  │                 │
  5        6        2         3       （=1的节点）
前缀0=1 前缀2=1    前缀4    前缀6

还没有 find(A) == find(A+N) 出现 → 没矛盾
```

```
回答4: 1 6 even → union(0, 3), union(5, 8)
        前缀0和前缀6归为同类

现在节点0（前缀0=0）连上了节点3（前缀6=0）……
但节点3又通过回答3连到节点7（前缀4=1），又通过回答2连到节点6（前缀2=1），
又通过回答1连到节点5（前缀0=1）。

最终：find(0) == find(5) → 前缀0同时是0和1 → 矛盾！
```

输出 `3` ✅

### 代码

@include-code(./main-2N-dsu.py, python)

### 对比

| | 带权并查集 | 2N 并查集 |
|---|---|---|
| 节点数 | N（每个位置1个） | 2N（每个位置两个角色） |
| 合并逻辑 | 算 parity XOR | 纯 union，无计算 |
| 判冲突 | `parity[A] ^ parity[B] != expected` | `find(A) == find(A+N)` |
| 直觉 | 数学推导 | "敌人的敌人是朋友" |
