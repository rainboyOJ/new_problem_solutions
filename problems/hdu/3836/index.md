---
oj: "HDU"
problem_id: "3836"
title: "Equivalent Sets"
date: 2026-01-09 11:24
toc: true
tags: ["强连通分量"]
desc: "最小添加多少条边变成强连通图"
source: https://vjudge.net/problem/HDU-3836
---

[[TOC]]

## 题目解析
这也是一个非常经典的图论问题：**给一个有向图，最少加几条边，能让它变成强连通图 (Strongly Connected Graph)**。

## 题目解析

1. **模型转换**：

   - 题目要求所有集合“彼此等价”，即对于任意 $X, Y$，都有 $X \subseteq Y$ 和 $Y \subseteq X$。
   - 这在图论中等价于：**图中任意两点互相可达**。
   - 这正是 **强连通分量 (Strongly Connected Component, SCC)** 的定义。
   - 题目问“最少证明步骤”，就是问 **最少添加多少条有向边，使得整个图变成一个 SCC**。

2. **算法逻辑**：

   - **步骤 1**：求 SCC 并缩点。将图转换成 DAG（有向无环图）。
   - **步骤 2**：计算 DAG 中每个节点的 **入度** 和 **出度**。
   - **步骤 3**：统计入度为 0 的节点数（记为 $P$）和出度为 0 的节点数（记为 $Q$）。
   - **结论**：
     - 如果只有一个 SCC（`scc_cnt == 1`），则不需要加边，答案为 0。
     - 否则，答案为 **$\max(P, Q)$**。

   > **直观理解**：为了连通，我们需要把所有的“源头”（入度0）消灭掉，也要把所有的“尽头”（出度0）消灭掉。最佳策略是将“尽头”连向“源头”。最少需要的边数就是源头数量和尽头数量中的较大者。

------

## 代码实现

```cpp
/**
 * Author by Rainboy blog: https://rainboylv.com github : https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * date: 2026-01-09 10:51:03
 */
#include <bits/stdc++.h>
using namespace std;
typedef  long long ll;
typedef  unsigned long long ull;

const int maxn = 2e4+5; // N <= 20000
const int maxe = 5e4+5; // M <= 50000
int n, m;

//oisnip_beginlinklist.cpp
struct linkList {
    typedef struct {int u,v,w,next;} edge;
    edge e[maxe];
    int h[maxn], edge_cnt=0;
    
    linkList(){ edge_cnt = 0; /* init在main中调用 */ }

    // 优化：只清空 0~n 的部分
    void init(int _n) {
        edge_cnt = 0;
        for(int i = 0; i <= _n; ++i) h[i] = -1;
    }

    //遍历点u 周围点
    template<typename U>
    void for_each(int u,U func){
        for(int i = h[u] ; i !=-1;i = e[i].next)
            func(e[i].u,e[i].v,e[i].w); 
    }

    void add(int u,int v,int w=0){
        e[edge_cnt] = {u,v,w,h[u]};
        h[u] = edge_cnt++;
    }
    
    edge& operator[](int i){ return e[i]; }

#ifdef __cpp_range_based_for
    struct UseEdge {
        using ReturnType = edge&; 
        static ReturnType get(linkList* p, int i) { return p->e[i]; }
    };
    struct UseAdj {
        using ReturnType = int;   
        static ReturnType get(linkList* p, int i) { return p->e[i].v; }
    };
    template<typename Getter>
    struct BaseIterator {
        int i; linkList* p;    
        BaseIterator(linkList* p, int i) : p(p), i(i) {}
        BaseIterator& operator++() { i = p->e[i].next; return *this; }
        bool operator!=(const BaseIterator& oth) { return i != oth.i; }
        typename Getter::ReturnType operator*() { return Getter::get(p, i); }
    };
    using Iterator    = BaseIterator<UseEdge>;
    using AdjIterator = BaseIterator<UseAdj>;
    template<typename IterT>
    struct BaseRange {
        int start; linkList* p;
        BaseRange(linkList* p, int start) : p(p), start(start) {}
        IterT begin() { return IterT(p, p->h[start]); }
        IterT end()   { return IterT(p, -1); }
    };
    BaseRange<Iterator> operator()(int u) { return BaseRange<Iterator>(this, u); }
    BaseRange<AdjIterator> adj(int u) { return BaseRange<AdjIterator>(this, u); }
#endif
} e;
//oisnip_end

//oisnip_beginscc.cpp
struct TarjanScc {
    int n, timer;
    std::stack<int> st;
    bool in_stack[maxn];
    int dfn[maxn], low[maxn], scc_id[maxn];
    int scc_cnt; 

    void set(int _n) {
        n = _n;
        timer = scc_cnt = 0;
        for(int i = 0; i <= n; ++i) {
            dfn[i] = 0;
            low[i] = 0;
            in_stack[i] = false;
            scc_id[i] = 0;
        }
        while (!st.empty()) st.pop();
    }

    void dfs(int u) {
        dfn[u] = low[u] = ++timer;
        st.push(u);
        in_stack[u] = true;

        for (int i = e.h[u]; ~i ; i = e[i].next) {
            int v = e[i].v;
            if (!dfn[v]) { 
                dfs(v);
                low[u] = std::min(low[u], low[v]);
            } else if (in_stack[v]) { 
                low[u] = std::min(low[u], dfn[v]);
            }
        }

        if (low[u] == dfn[u]) {
            scc_cnt++;
            while (1) {
                int v = st.top(); st.pop();
                in_stack[v] = 0;
                scc_id[v] = scc_cnt; 
                if (v == u) break; 
            }
        }
    }

    void solve() {
        for (int i = 1; i <= n; i++) {
            if (!dfn[i]) dfs(i);
        }
    }
} scc;
//oisnip_end

// DAG 统计数组
int in_deg[maxn];  // 入度
int out_deg[maxn]; // 出度

signed main () {
    ios::sync_with_stdio(false); cin.tie(0);
    
    while(cin >> n >> m) {
        // 1. 初始化
        e.init(n);
        
        // 2. 建图
        for(int i = 0; i < m; ++i) {
            int u, v;
            cin >> u >> v;
            e.add(u, v);
        }

        // 3. Tarjan 求 SCC
        scc.set(n);
        scc.solve();

        // 4. 特判：如果已经是一个强连通图，不需要加边
        if (scc.scc_cnt == 1) {
            cout << 0 << "\n";
            continue;
        }

        // 5. 缩点，统计入度和出度
        // 初始化度数数组 (注意 scc_cnt 从 1 开始)
        for(int i = 1; i <= scc.scc_cnt; ++i) {
            in_deg[i] = 0;
            out_deg[i] = 0;
        }

        // 遍历原图的所有点和边
        for(int u = 1; u <= n; ++u) {
            for(int v : e.adj(u)) { // 使用语法糖遍历邻接点
                int su = scc.scc_id[u];
                int sv = scc.scc_id[v];
                
                if (su != sv) {
                    out_deg[su]++;
                    in_deg[sv]++;
                }
            }
        }

        // 6. 计算入度为0(P) 和 出度为0(Q) 的SCC数量
        int P = 0, Q = 0;
        for(int i = 1; i <= scc.scc_cnt; ++i) {
            if (in_deg[i] == 0) P++;
            if (out_deg[i] == 0) Q++;
        }

        // 7. 输出 max(P, Q)
        cout << max(P, Q) << "\n";
    }

    return 0;
}
```



## 证明



这是一个非常经典的结论。我们可以从**“下界（必要性）”**和**“构造方法（充分性）”**两个角度来证明为什么答案是 $\max(P, Q)$。

首先，前提是图中的强连通分量数 `scc_cnt > 1`（如果只有1个，答案是0）。

## 1. 变量定义

将原图进行 SCC 缩点后，我们得到一个 **DAG（有向无环图）**。在这个 DAG 中：

- **$P$ (Sources/源点)**：入度为 0 的点。也就是“只有出去的路，没有回来的路”的点。
- **$Q$ (Sinks/汇点)**：出度为 0 的点。也就是“只有进来的路，死胡同”的点。

------

## 2. 原理证明：为什么至少是 $\max(P, Q)$？

### 角度一：必要性（Lower Bound）

我们要让整个图变成强连通图（SC），意味着**任意两点互通**，也就是整个图变成一个巨大的环。

1. **解决源点问题**：
   - 对于每一个入度为 0 的源点（Source），它必须有边连入，否则别的点无法到达它。
   - 如果有 $P$ 个源点，我们**至少**需要添加 $P$ 条边分别指向这 $P$ 个点，才能消灭所有的“0入度”。
   - 所以，边数 $\ge P$。
2. **解决汇点问题**：
   - 对于每一个出度为 0 的汇点（Sink），它必须有边连出，否则它无法到达别的点。
   - 如果有 $Q$ 个汇点，我们**至少**需要添加 $Q$ 条边分别从这 $Q$ 个点出发，才能消灭所有的“0出度”。
   - 所以，边数 $\ge Q$。

**结论**：既然边数必须同时满足 $\ge P$ 和 $\ge Q$，那么边数至少是 $\max(P, Q)$。

------

## 3. 构造证明：如何只用 $\max(P, Q)$ 条边完成？

只要我们能给出一种加边方案，恰好用了 $\max(P, Q)$ 条边就把图连通了，那就证明了这是充分的。

### 构造策略（链式拼接法）：

想象一下，缩点后的 DAG 其实是由若干条“长链”或者“树枝”组成的。

- 每一条“链”都始于一个**源点 ($S$)**，终于一个**汇点 ($T$)**。

假设 $P \le Q$（即源点少，汇点多，反之同理）：

1. 配对阶段：

   我们可以找到 $P$ 条路径，每条路径都是从一个独特的源点 $S_i$ 到一个独特的汇点 $T_i$。

   虽然中间的节点可能共用，但头尾是对应的。

2. 首尾相连（Chain the Paths）：

   我们按照顺序，把第 1 条路径的终点（汇点 $T_1$）连向第 2 条路径的起点（源点 $S_2$）；把 $T_2$ 连向 $S_3$，以此类推……直到 $T_{P-1} \to S_P$。

   - **消耗边数**：$P-1$ 条。
   - **效果**：现在这 $P$ 条路径串成了一条超长的路径（或者说把所有的源点合并成了一个大源点，所有的汇点还没完全解决）。

3. 闭合回路（Close the Cycle）：

   我们要把最后剩下的那个汇点（属于主链的末端），连回最开始的源点 $S_1$ 吗？先别急。

   此时我们还剩下 $Q - P$ 个“多余”的汇点（它们属于一些从主干分叉出去的死胡同）。

4. 处理剩余的汇点：

   现在的结构是：一条巨大的长链 + 若干个挂在上面的“多余汇点”。

   为了让整个图强连通，我们只需把所有剩余的汇点，以及主链的最后一个汇点 ($T_P$)，全部连向主链的起点 ($S_1$)。

   - 但这样只是为了证明。更优的连法是：

     把 $T_P$ 连向某个多余汇点的起点（如果有独立源点的话，但这里所有源点都用完了），或者直接从多余汇点 $T_{extra}$ 连向 $S_1$。

   **简单通用的构造法**：

   1. 将 $P$ 个源点和 $Q$ 个汇点尽可能配对成 $k = \min(P, Q)$ 组 $(S_i, T_i)$。
   2. 像穿针引线一样：$T_1 \to S_2, T_2 \to S_3, \dots, T_{k-1} \to S_k$。
   3. 连接 $T_k \to S_1$（形成一个大环）。
   4. 此时，可能还剩下 $|P - Q|$ 个孤立的源点或汇点。
      - 如果是多余的源点（$P > Q$）：让任意一个环上的点指向它。
      - 如果是多余的汇点（$Q > P$）：让它指向任意一个环上的点。

   实际上，我们可以把那 $|P-Q|$ 个多余的点也融入到大环的连线过程中。

   - **总共需要的边**：
     - 连接 $k$ 对核心路径需要 $k$ 条边（包含封口）。
     - 解决剩余的 $|P-Q|$ 个点需要 $|P-Q|$ 条边。
     - Total = $k + |P-Q| = \min(P,Q) + |P-Q| = \max(P, Q)$。

## 4. 总结

- **P (Sources)**: 需要被别人指（入度+1）。
- **Q (Sinks)**: 需要指别人（出度+1）。
- **最少边数**: $\max(P, Q)$。

## 5. 代码实现细节提醒

在你的代码中，这部分逻辑已经体现了：



```cpp
        // 统计 P 和 Q
        int P = 0, Q = 0;
        for(int i = 1; i <= scc.scc_cnt; ++i) {
            if (in_deg[i] == 0) P++;
            if (out_deg[i] == 0) Q++;
        }

        // 输出 max(P, Q)
        cout << max(P, Q) << "\n";
```

唯独要注意的特判：

如果原图本来就是强连通的（缩点后只有一个点 scc_cnt == 1），此时 $P=1, Q=1$（既是源也是汇），公式会算出 $\max(1, 1) = 1$，但实际上需要加 0 条边。所以必须保留代码里的特判：



```cpp
        if (scc.scc_cnt == 1) {
            cout << 0 << "\n";
            continue;
        }
```
