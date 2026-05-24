---
oj: "POJ"
problem_id: "1523"
title: "SPF"
date: 2025-12-29 15:09
toc: true
tags: ["割点","v-bcc"]
desc: "cut-code vbcc 两种解法"
source: https://vjudge.net/problem/POJ-1523#author=DeepSeek_zh
pre:
 - luogu,P1314
book:
 - bookid
---

[[TOC]]



这篇题解结合了 **直接 Tarjan 判定法** 和 **v-BCC（点双连通分量）分解法** 两种视角，不仅解决当前题目，更帮助你理解图论中“割点”与“点双”的本质联系。

------

# 题目解析：Network (SPF / 割点判定)

## 1. 题目大意

给定一个无向图（网络），定义 SPF (Single Point of Failure) 节点为：如果删除该节点，会导致剩余网络不再连通（即连通分量增加）。

我们需要：

1. 找出所有的 SPF 节点（即**割点**）。
2. 计算删除该节点后，剩余的全连通子网（连通分量）数量。

## 2. 核心理论

### 割点 (Articulation Point)

在无向连通图中，若删除节点 $u$ 及其相连的边，图的连通分量数量增加，则 $u$ 为割点。

### Tarjan 算法基础

利用 DFS 生成树维护两个核心数组：

- **`dfn[u]`**：节点 $u$ 被访问的时间戳。
- **`low[u]`**：节点 $u$ 通过**DFS 树边**或**返祖边**（不经过父节点）所能追溯到的最小时间戳。

判定法则：

对于边 $u \to v$（$u$ 是 $v$ 的父节点）：

若 low[v] >= dfn[u]，说明 $v$ 及其子树无法回到 $u$ 的祖先，必须经过 $u$，因此 $u$ 是割点。

------

## 方法一：直接 Tarjan 判定法 (经典解法)

这种方法直接在 DFS 过程中统计分量变化，空间极小，逻辑紧凑。

### 算法逻辑

我们用 `subnet_cnt[u]` 记录删除 $u$ 后产生的连通块数量。

1. **根节点 (Root)**：
- 在 DFS 树中，根节点每有一个“DFS 树子节点”（即 `!dfn[v]` 进入的分支），就是一个独立的连通块。
- 若子节点数 $\ge 2$，则根是割点。
- **子网数** = DFS 树中实际子节点的数量。
2. **非根节点 (Non-Root)**：
- 每发现一个子节点 $v$ 满足 `low[v] >= dfn[u]`，说明切断 $u$ 后，$v$ 所在分支会掉落，`subnet_cnt` 加 1。
- 除了掉落的子树外，**$u$ 的父节点方向**还连着一大块网络。只要 $u$ 切断了任意一个子节点，父节点方向的那块也算作一个独立的剩余子网。
- **子网数** = (满足条件的子节点数) + 1。

### 代码实现

C++

@incclude-code(./2.cpp,cpp)


## 方法二：v-BCC 分解法 (结构化解法)

这种方法基于**点双连通分量 (v-BCC)** 的定义。它更加抽象，但能揭示图的内部结构（即圆方树的雏形）。

### 算法逻辑

1. **v-BCC 定义**：极大的不包含割点的子图（任意两点间至少有两条不相交路径）。
2. **割点与 BCC 的关系**：
- 割点是多个 v-BCC 的“公共交点”。
- 如果把每个 BCC 想象成一个“房间”，割点就是连接不同房间的“门”。
3. **计算子网数**：
- 统计每个点 $u$ 出现在了多少个不同的 BCC 中。
- $Count(u) =$ 包含 $u$ 的 BCC 数量。
- 如果 $Count(u) > 1$，则 $u$ 是割点，且删除 $u$ 后，这 $Count(u)$ 个 BCC 会散开成为独立的连通块。

### 代码实现

C++

```
/*
* 方法二：v-BCC 分解法
* 优点：结构清晰，根节点无需特殊逻辑，适用于后续构建圆方树
* 核心：统计每个点属于多少个 BCC
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <stack>

// ... Edge 结构体同上 ...
// ... add_edge 函数同上 ...

struct TarjanBCC {
 int n, timer;
 std::stack<int> st;
 int dfn[maxn], low[maxn];
 int bcc_cnt; 
 std::vector<int> bcc[maxn]; // 存储每个 BCC 中的点

 void set(int _n) {
     n = _n;
     timer = bcc_cnt = 0;
     memset(dfn, 0, sizeof(dfn));
     memset(low, 0, sizeof(low));
     while (!st.empty()) st.pop();
     for (int i = 0; i <= n; i++) bcc[i].clear();
 }

 void dfs(int u, int fa) {
     dfn[u] = low[u] = ++timer;
     st.push(u);

     for (int i = head[u]; i; i = e[i].next) {
         int v = e[i].v;
         if (v == fa) continue;

         if (!dfn[v]) {
             dfs(v, u);
             low[u] = std::min(low[u], low[v]);

             // 发现 BCC 的闭环条件
             if (low[v] >= dfn[u]) {
                 bcc_cnt++;
                 while (true) {
                     int node = st.top(); st.pop();
                     bcc[bcc_cnt].push_back(node);
                     if (node == v) break;
                 }
                 // u 也是这个 BCC 的一部分
                 bcc[bcc_cnt].push_back(u);
             }
         } else if (dfn[v] < dfn[u]) {
             low[u] = std::min(low[u], dfn[v]);
         }
     }
 }

 void solve() {
     for (int i = 1; i <= 1000; i++) {
         if (!dfn[i] && head[i]) dfs(i, 0);
     }
 }
};

TarjanBCC solver;
int node_bcc_count[maxn]; // 统计数组

int main() {
 // ... 输入读取部分同上 ...
 // ... (在 while 循环内) ...

 solver.solve();

 // 统计频率
 memset(node_bcc_count, 0, sizeof(node_bcc_count));
 for (int i = 1; i <= solver.bcc_cnt; i++) {
     for (int node : solver.bcc[i]) {
         node_bcc_count[node]++;
     }
 }

 // 输出结果
 std::cout << "Network#" << ++case_id << "\n";
 bool has_spf = false;
 for (int i = 1; i <= 1000; i++) {
     // 只要属于超过 1 个 BCC，就是割点
     if (node_bcc_count[i] > 1) { 
         has_spf = true;
         std::cout << "  SPF node " << i << " leaves " << node_bcc_count[i] << " subnets\n";
     }
 }
 // ... 后续输出同上 ...
}
```

 ------

## 总结与对比

| **维度**     | **方法一：直接 Tarjan**                | **方法二：v-BCC 分解**                                    |
| ------------ | -------------------------------------- | --------------------------------------------------------- |
| **思维模型** | **剪切视角**：把点抠掉，看树分叉了几枝 | **积木视角**：图是由 BCC 积木搭成的，割点是连接积木的关节 |
| **根节点**   | 需要特判 `child_count`                 | **无需特判**，算法自然归纳                                |
| **复杂度**   | $O(N+M)$，常数极小                     | $O(N+M)$，`vector` 操作略带常数                           |
| **适用场景** | 仅需判定割点或求连通块数               | 需构建圆方树、求路径必经点、树上 DP 等复杂问题            |

**建议**：

- 在比赛中如果只是单纯求 SPF，**方法一** 写法更快。
- 如果题目涉及“从 A 到 B 的路径上必须经过的点”或“两点间路径的并集”等，建议使用 **方法二** 的思想，因为这往往是圆方树题目的前置步骤。
