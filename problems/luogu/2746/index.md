---
oj: "luogu"
problem_id: "P2746"
title: "[IOI 1996 / USACO5.3] 校园网 Network of Schools"
date: 2025-12-29 11:17
toc: true
tags: ["scc","dag"]
desc: "考察dag的性质: 最少添加多少条边 可以使DAG 缩成一点"
source: https://www.luogu.com.cn/problem/P2746
pre:
 - luogu,P1314
book:
 - scc
---

[[TOC]]


这道题是 **Tarjan 缩点 + DAG性质分析** 的经典题（IOI 1996 真题）。它考察了如何将有向图转化为 DAG，并通过分析 DAG 的 **入度 (In-degree)** 和 **出度 (Out-degree)** 来解决连通性问题。

### 题目解析

首先，我们将图中的强连通分量（SCC）缩成一个点，得到一个有向无环图（DAG）。

1. **问题 1：至少需要向几个学校下发新软件？**
   - **分析**：在 DAG 中，如果有边 $A \to B$，软件给了 $A$，$B$ 自然就有。唯一“接收不到”别人的软件的，就是那些**入度为 0** 的点（源点）。
   - **结论**：只要给所有 **入度为 0 的 SCC** 发软件，所有人都能收到。答案 = **入度为 0 的 SCC 数量**。
2. **问题 2：至少添加几条边，使整个图变成强连通图？**
   - **分析**：强连通图意味着任意两点互达（相当于一个大环）。
   - **模型**：在 DAG 中，我们有 $P$ 个入度为 0 的点（源点），$Q$ 个出度为 0 的点（汇点）。
   - **策略**：为了让图连通，我们需要消灭所有的源点和汇点（除了由它们合并成的那个大环）。我们可以把一个汇点连向一个源点，这样就同时减少了一个汇点和一个源点。
   - **结论**：
     - 如果图本身就是强连通的（SCC数量为1），答案是 0。
     - 否则，答案 = **$\max(\text{入度为0的SCC数}, \text{出度为0的SCC数})$**。

------

### 完整代码

C++

```
/**
 * Author by Rainboy blog: https://rainboylv.com github : https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * date: 2025-12-29 10:52:38
 */
#include <bits/stdc++.h>
using namespace std;
typedef  long long ll;
typedef  unsigned long long ull;

const int maxn = 2e6+5;
const int maxe = 4e6+5;
const int mod = 1e9+7;

int n;

struct linkList {
    typedef struct {int u,v,w,next;} edge;
    edge e[maxe];
    int h[maxn],edge_cnt=0;
    linkList(){
        reset();
    }

    void reset() {
        edge_cnt=0;
        memset(h,-1,sizeof(h));
    }

    void add(int u,int v,int w=0){
        e[edge_cnt] = {u,v,w,h[u]};
        h[u] = edge_cnt++;
    }
    
    //下标访问
    edge& operator[](int i){ return e[i]; }
    //返回head[u]
    int operator()(int u){ return h[u]; }
} e;

struct TarjanScc {
    int n, timer;
    std::stack<int> st;
    bool in_stack[maxn];
    int dfn[maxn], low[maxn], scc_id[maxn];
    int scc_cnt; 

    void set(int _n) {
        n = _n;
        timer = scc_cnt = 0;
        memset(dfn, 0, sizeof(dfn));
        memset(in_stack, 0, sizeof(in_stack));
    }

    void dfs(int u) {
        dfn[u] = low[u] = ++timer;
        st.push(u);
        in_stack[u] = true;

        for (int i = e(u); ~i ; i = e[i].next) {
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
} tscc;

// 统计 SCC 的入度和出度
int din[maxn], dout[maxn];

signed main () {
    ios::sync_with_stdio(false); cin.tie(0);
    
    cin >> n;
    for(int i = 1; i <= n; i++) {
        int v;
        while(cin >> v && v != 0) {
            e.add(i, v);
        }
    }

    // 1. 求 SCC
    tscc.set(n);
    tscc.solve();

    // 特判：如果整个图只有一个 SCC，说明已经是强连通的
    if(tscc.scc_cnt == 1) {
        cout << 1 << endl; // 问题1：至少给1个学校（任意一个）
        cout << 0 << endl; // 问题2：不需要加边
        return 0;
    }

    // 2. 统计缩点后的 DAG 的入度和出度
    for(int u = 1; u <= n; u++) {
        for(int i = e(u); ~i; i = e[i].next) {
            int v = e[i].v;
            // 如果边连接的是两个不同的 SCC
            if(tscc.scc_id[u] != tscc.scc_id[v]) {
                dout[tscc.scc_id[u]]++; // u 所在的 SCC 出度+1
                din[tscc.scc_id[v]]++;  // v 所在的 SCC 入度+1
            }
        }
    }

    int p = 0; // 入度为 0 的 SCC 数量 (source)
    int q = 0; // 出度为 0 的 SCC 数量 (sink)

    for(int i = 1; i <= tscc.scc_cnt; i++) {
        if(din[i] == 0) p++;
        if(dout[i] == 0) q++;
    }

    // 输出结果
    cout << p << endl;              // 问题 1
    cout << max(p, q) << endl;      // 问题 2

    return 0;
}
```

### 关键细节说明

1. **输入格式**：注意题目是每行以 `0` 结束，所以用了 `while(cin >> v && v != 0)`。
2. **特判 `scc_cnt == 1`**：这是这道题最容易掉进去的坑。
   - 如果不特判，按照公式算，当 `scc_cnt == 1` 时，入度为 0 的点有 1 个，出度为 0 的点有 1 个，`max(1, 1) = 1`。但实际上如果已经是强连通图，不需要加任何边，答案应为 0。
3. **变量含义**：
   - `din[i]`：第 $i$ 个强连通分量的入度。
   - `dout[i]`：第 $i$ 个强连通分量的出度。
   - 问题 1 答案即为源点个数 $P$。
   - 问题 2 答案即为 $\max(P, Q)$，其中 $Q$ 为汇点个数。
