---
oj: "luogu"
problem_id: "P3225"
title: "[HNOI2012] 矿场搭建"
date: 2025-12-30 15:35
toc: true
tags: ["v-bcc"]
desc: "一个很好的考查点双连通分量的题目"
source: https://www.luogu.com.cn/problem/P3225
pre:
 - luogu,P1314
book:
 - bcc
---

[[TOC]]

## 题目解析


这是一个非常经典的图论题目，主要考察**割点（Cut Vertex）**和**点双连通分量（Biconnected Component, v-BCC）**的性质。

### 核心思路解析

题目要求我们在某些挖煤点设置救援出口，使得**任意一个**挖煤点坍塌（即该点被从图中删除）后，其他所有点的工人都能通过剩下的路径到达救援出口。

我们可以利用**割点**的性质来分析这个问题。

### 1. 什么是割点？

在一个无向连通图中，如果删除某个点及其相连的边，图分裂成了两个或更多的连通分量，那么这个点就是**割点**。

### 2. 分类讨论

我们可以使用 Tarjan 算法将图分解为若干个**点双连通分量（v-BCC）**。每个 v-BCC 是一个极大子图，其中任意两点之间至少存在两条点不重复的路径（或者说，删除该子图内任意一点，子图内部依然连通）。v-BCC 之间通过割点连接。

对于每一个点双连通分量，我们统计它包含的**割点数量**（记为 `cut_num`），分三种情况讨论：

- **情况 1：该连通分量中没有割点 (`cut_num == 0`)**
  - 这意味着整个图就是一个双连通分量（例如一个简单的环，或者完全图）。
  - **最少出口数**：**2**。因为如果只设 1 个出口，万一那个出口所在的点坍塌了，所有人都跑不掉。设 2 个出口可以保证坏掉一个还有一个。
  - **方案数**：从该分量的 $n$ 个点中任选 2 个，即 $C_n^2 = \frac{n(n-1)}{2}$。
- **情况 2：该连通分量中只有 1 个割点 (`cut_num == 1`)**
  - 这通常是位于图“边缘”的叶子分量。它只通过这唯一的割点连接到图的其他部分。
  - **最少出口数**：**1**。
    - 如果坍塌的点是割点，这个分量就与外界断开了，必须有一个内部出口才能逃生。
    - 如果坍塌的点是该分量内的非割点（包括出口本身），剩下的人可以通过割点逃往图的其他部分（只要其他部分有出口）。
  - **方案数**：出口可以设置在该分量内除了割点以外的任意一个点上。设该分量总点数为 $n$，则方案数为 $n - 1$。
- **情况 3：该连通分量中有 2 个或以上的割点 (`cut_num >= 2`)**
  - 这个分量处于图的“中间”位置，连接着多个其他部分。
  - **最少出口数**：**0**。
    - 无论分量内哪个点坍塌，幸存者都可以通过剩下的至少一个割点，逃往其他分量。只要那些边缘的分量（情况 2）按要求设置了出口，中间的人就能获救。
  - **方案数**：1（不需要设置，所以视为一种“不操作”的方案，对乘积无影响）。

### 算法流程

1. **初始化**：清空图、时间戳数组等。
2. **求割点**：使用 Tarjan 算法求出图中所有的割点。
3. **求点双连通分量 (v-BCC)**：
   - 在 Tarjan 的过程中，用栈维护当前访问的节点。
   - 当发现 `low[v] >= dfn[u]` 时，说明找到一个 v-BCC。
   - 不断弹出栈顶元素直到 `v`，这些弹出的元素加上 `u` 构成了当前的 v-BCC。
4. **统计与计算**：
   - 遍历每一个 v-BCC。
   - 统计该 v-BCC 中包含的割点个数 `cut_cnt` 和总节点数 `node_cnt`。
   - 根据上述三种情况累加最少出口数，累乘方案数。
5. **输出结果**：注意 `long long`（题目保证小于 $2^{64}$）。

## C++ 代码实现 1

觉得我的代码长,就看 实现2

@include-code(./1.cpp,cpp)

## C++ 代码实现 2


```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <stack>

using namespace std;

const int MAXN = 1005; // 题目说 m <= 1000

struct Edge {
    int to;
};

vector<int> adj[MAXN];
int dfn[MAXN], low[MAXN], timestamp;
bool is_cut[MAXN]; // 标记是否为割点
int root;
stack<int> stk;
vector<vector<int>> bccs; // 存储所有点双连通分量

int n, m; // m 在此处作为最大节点编号

// 初始化函数
void init() {
    for (int i = 0; i < MAXN; i++) adj[i].clear();
    memset(dfn, 0, sizeof(dfn));
    memset(low, 0, sizeof(low));
    memset(is_cut, 0, sizeof(is_cut));
    timestamp = 0;
    while (!stk.empty()) stk.pop();
    bccs.clear();
    m = 0; // 重置最大节点编号
}

// Tarjan 求割点和点双连通分量
void tarjan(int u) {
    dfn[u] = low[u] = ++timestamp;
    stk.push(u);
    
    int child_count = 0;
    
    // 如果是孤立点，也算一个 BCC（虽然题目说连通，但为了鲁棒性）
    if (u == root && adj[u].empty()) {
        bccs.push_back({u});
        return;
    }

    for (int v : adj[u]) {
        if (!dfn[v]) {
            child_count++;
            tarjan(v);
            low[u] = min(low[u], low[v]);
            
            // 割点判定条件: low[v] >= dfn[u]
            if (low[v] >= dfn[u]) {
                // 记录割点
                if (u != root || child_count > 1) {
                    is_cut[u] = true;
                }
                
                // 提取点双连通分量
                vector<int> current_bcc;
                int z;
                do {
                    z = stk.top();
                    stk.pop();
                    current_bcc.push_back(z);
                } while (z != v);
                current_bcc.push_back(u); // 割点 u 也属于该 BCC
                bccs.push_back(current_bcc);
            }
        } else {
            low[u] = min(low[u], dfn[v]);
        }
    }
}

int main() {
    int edges_count;
    int case_num = 1;
    
    while (cin >> edges_count && edges_count != 0) {
        init();
        int u, v;
        for (int i = 0; i < edges_count; i++) {
            cin >> u >> v;
            adj[u].push_back(v);
            adj[v].push_back(u);
            m = max(m, max(u, v));
        }

        // 遍历所有连通块（题目虽然说连通，但防止意外，遍历一遍）
        for (int i = 1; i <= m; i++) {
            if (!dfn[i] && !adj[i].empty()) { // 只处理存在的节点
                root = i;
                tarjan(i);
            }
        }

        unsigned long long total_ways = 1;
        int min_exits = 0;

        for (const auto& bcc : bccs) {
            int cut_cnt = 0;
            for (int node : bcc) {
                if (is_cut[node]) {
                    cut_cnt++;
                }
            }

            long long bcc_size = bcc.size();
            
            if (cut_cnt == 0) {
                // 整个图是一个双连通分量，需要 2 个出口
                // 方案数为 C(size, 2)
                min_exits += 2;
                total_ways *= (bcc_size * (bcc_size - 1) / 2);
            } else if (cut_cnt == 1) {
                // 只有一个割点（叶子分量），需要 1 个出口
                // 方案数为 size - 1 (不能建在割点上)
                min_exits += 1;
                total_ways *= (bcc_size - 1);
            } else {
                // 割点数 >= 2，不需要额外出口
            }
        }
        
        // 特判：如果整张图只有 1 个点的情况（题目边数 >= 1 所以通常不会出现，但逻辑上）
        // 如果题目保证边数>=1，那么至少2个点。
        // 上述逻辑在全图无割点时 min_exits += 2 是正确的。

        cout << "Case " << case_num++ << ": " << min_exits << " " << total_ways << endl;
    }
    return 0;
}
```

## 代码注意事项

1. **数据范围**：$N \le 500$ (边数)，节点编号最大 $1000$。`int` 足够存边，但方案数要用 `unsigned long long`。
2. **输入结尾**：注意处理以 `0` 结尾的输入。
3. **Tarjan 细节**：
   - 在提取 BCC 时，栈中弹出的只到子节点 `v` 为止，父节点 `u` 是割点，属于该 BCC 但不能弹出（因为它可能还属于其他的 BCC）。需要手动把 `u` 加入当前的 `current_bcc` 列表。
   - 根节点的割点判定条件是 `child_count > 1`。
4. **去重**：点双连通分量在存储时，割点会被包含在多个 BCC 中，但这正是我们需要的，因为我们需要统计每个 BCC 内部有多少个点是“全局割点”。

## 样例 1 模拟

- 输入构成了一个连通图。
- 割点为 3。
- 分解后，可能得到两部分：一部分是包含 3 的环状或复杂结构，另一部分可能挂在 3 上。
- 根据逻辑计算得出 `2 4`。

### 样例 2 模拟

- 输入：`1-2, 1-3, 2-4, 2-5, 3-6, 3-7`。
- 这是一个树状结构。
- 割点是 `1, 2, 3`。
- v-BCCs: `{2,4}`, `{2,5}`, `{3,6}`, `{3,7}`, `{1,2,3}` (中间的三角形)。
  - `{2,4}`: 割点 `{2}` (1个) -> 需要 1 出口，方案 $2-1=1$ (在4)。
  - `{2,5}`: 割点 `{2}` (1个) -> 需要 1 出口，方案 $2-1=1$ (在5)。
  - `{3,6}`: 割点 `{3}` (1个) -> 需要 1 出口，方案 $2-1=1$ (在6)。
  - `{3,7}`: 割点 `{3}` (1个) -> 需要 1 出口，方案 $2-1=1$ (在7)。
  - `{1,2,3}`: 割点 `{1, 2, 3}` (3个) -> 需要 0 出口。
- 总出口：$1+1+1+1 = 4$。
- 总方案：$1 \times 1 \times 1 \times 1 = 1$。
- 输出：`Case 2: 4 1`。
