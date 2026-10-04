---
oj: "roj"
problem_id: "1665"
title: "「一本通 6.7 例 3」移棋子游戏"
description: "将 DAG 上的多棋子移动博弈转化为独立游戏的和，拓扑排序逆序计算各节点的 SG 值，再根据各棋子位置的 SG 异或和判断胜负。"
difficulty: "普及+/提高-"
date: 2026-04-18 10:00
updated: 2026-04-18 10:00
toc: true
tags:
  - 博弈论
  - SG 函数
  - 拓扑排序
  - DAG
favorite: false
favorite_reason: ""
categories:
  - 博弈论
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1665
---

[[TOC]]

## 形式化题目

给定一个包含 $N$ 个节点、$M$ 条有向边的有向无环图（DAG），图上有 $K$ 个棋子，初始分别位于指定的节点上（同一个节点上允许多枚棋子，且各棋子移动相互独立）。

两名玩家轮流行动。在每一次行动中，当前玩家任选一枚棋子，沿其所在节点的一条有向出边移动到相邻的后继节点。无法进行任何移动的玩家判负。

假设双方均采取最优策略，判定先手必胜还是先手必败。若先手必胜输出 `win`，否则输出 `lose`。

## 正解

### 思路

本题是标准的**公平组合游戏**（Impartial Combinatorial Game，简称 ICG），且游戏在有向无环图上进行，必然在有限步内终止。

每次操作只能移动一枚棋子，且每个棋子的移动规则独立、互不干扰。因此，整个游戏可以看作 $K$ 个独立的单棋子游戏的**和（Sum of Games）**。根据 **Sprague-Grundy 定理**（SG 定理）：

1. **终端节点**：没有出边的节点无法继续移动，其 SG 值为 $0$：
   $$SG(u) = 0 \quad (\operatorname{out\_degree}(u) = 0)$$

2. **一般节点**：一个节点的 SG 值等于其所有出边后继节点 SG 值的集合的最小未出现非负整数（$\operatorname{mex}$ 运算）：
   $$SG(u) = \operatorname{mex}(\{ SG(v) \mid (u, v) \in E \})$$

3. **复合游戏判定**：整体游戏的胜负等价于各个棋子所在节点的 SG 值的按位异或和（Nim 和）：
   $$X = \bigoplus_{i=1}^{K} SG(p_i)$$
   - 若 $X \neq 0$，则先手必胜，输出 `win`；
   - 若 $X = 0$，则先手必败，输出 `lose`。

由于图是有向无环图（DAG），我们可以先对图进行**拓扑排序**，随后按照**拓扑逆序**自底向上倒推，依次求出每个节点的 SG 值，最后计算所有棋子初始位置的 SG 异或和即可。

下图展示了样例给出的 DAG 以及逆序推导出的每个节点的 SG 值：

```mermaid
graph LR
    subgraph SG=0
        5["节点 5 (SG=0)"]
        6["节点 6 (SG=0)"]
    end
    subgraph SG=1
        4["节点 4 (SG=1)"]
        3["节点 3 (SG=1)"]
    end
    subgraph SG=2
        1["节点 1 (SG=2)"]
    end
    subgraph SG=0_or_other
        2["节点 2 (SG=0)"]
    end

    2 --> 1
    2 --> 4
    1 --> 4
    1 --> 5
    1 --> 3
    4 --> 5
    3 --> 5
    3 --> 6
```

以样例为例：
- 节点 $5, 6$ 没有出边，$SG(5) = SG(6) = 0$；
- 节点 $4$ 只能到达 $5$，$SG(4) = \operatorname{mex}(\{0\}) = 1$；
- 节点 $3$ 可以到达 $5, 6$，$SG(3) = \operatorname{mex}(\{0\}) = 1$；
- 节点 $1$ 可以到达 $3, 4, 5$，$SG(1) = \operatorname{mex}(\{1, 0\}) = 2$；
- 节点 $2$ 可以到达 $1, 4$，$SG(2) = \operatorname{mex}(\{2, 1\}) = 0$。

初始棋子位于节点 $1, 2, 4, 6$，其 SG 异或和为：
$$SG(1) \oplus SG(2) \oplus SG(4) \oplus SG(6) = 2 \oplus 0 \oplus 1 \oplus 0 = 3 \neq 0$$
因此先手必胜，输出 `win`。

### 代码

@include-code(./main.py, python)

### 复杂度

- **时间复杂度**：$\mathcal{O}(N + M + K)$。拓扑排序与遍历每个节点的出边只需 $\mathcal{O}(N + M)$，求每个节点 mex 的集合操作总和亦为 $\mathcal{O}(N + M)$，最后对 $K$ 个棋子求异或和为 $\mathcal{O}(K)$。在 $N \leqslant 2000, M \leqslant 6000$ 范围内可毫秒级完成。
- **空间复杂度**：$\mathcal{O}(N + M)$。用于存储图的邻接表、入度、拓扑序列以及每个节点的 SG 值。

## 总结

1. **DAG 上的无偏博弈**：所有有限步终止的公平博弈都可以抽象为 DAG 上的转移问题，每个状态的值由 SG 定理完全刻画。
2. **多棋子独立游戏的和**：各棋子独立移动时，状态复合为 Nim 堆的异或和，避开了指数级组合状态空间的直接搜索。
3. **计算顺序**：利用 DAG 的拓扑逆序，可以以线性的时间自底向上高效求得每个节点的 SG 值。
