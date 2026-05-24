---
oj: "luogu"
problem_id: "P2863"
title: "[USACO06JAN] The Cow Prom S"
date: 2025-12-29 11:07
toc: true
tags: ["scc","模板题目"]
desc: ""
source: https://www.luogu.com.cn/problem/P2863
pre:
 - luogu,P1314
book:
 - bookid
---

[[TOC]]




## 题目解析

这道题是 **Tarjan 求 SCC 基础性质** 的直接应用。

1. **核心任务**：
题目要求找出 **“点数大于 1 的强连通分量”** 的个数。
2. **什么是点数大于 1 的 SCC？**
* 强连通分量（SCC）是指图中任意两点互通的子图。
* 如果一个 SCC 包含 2 个或以上的节点，意味着这些点之间至少构成了一个环（或者复杂的环网）。
* 孤立点（或仅带自环的单个点）构成的 SCC 大小为 1，不符合题目要求。


3. **解题思路**：
* 运行 Tarjan 算法求出所有的 SCC。
* 在算法过程中（或者结束后），记录每个 SCC 中包含的节点数量（`size`）。
* 最后遍历所有 SCC，统计 `size > 1` 的个数即可。


---

## 完整代码


```cpp
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

int n, m;

struct linkList {
    typedef struct {int u,v,w,next;} edge;
    edge e[maxe];
    int h[maxn], edge_cnt = 0;
    linkList(){
        reset();
    }

    void reset() {
        edge_cnt = 0;
        memset(h, -1, sizeof(h));
    }

    void add(int u,int v,int w=0){
        e[edge_cnt] = {u,v,w,h[u]};
        h[u] = edge_cnt++;
    }

    int operator()(int u){ return h[u]; }
    edge& operator[](int i){ return e[i]; }
} e;

struct TarjanScc {
    int n, timer;
    std::stack<int> st;
    bool in_stack[maxn];
    int dfn[maxn], low[maxn], scc_id[maxn];
    int scc_cnt; 
    int sz[maxn]; // 记录每个 SCC 的大小

    void set(int _n) {
        n = _n;
        timer = scc_cnt = 0;
        memset(dfn, 0, sizeof(dfn));
        memset(in_stack, 0, sizeof(in_stack));
        memset(sz, 0, sizeof(sz)); // 初始化大小数组
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
                sz[scc_cnt]++; // 核心逻辑：统计当前 SCC 的节点数
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

signed main () {
    ios::sync_with_stdio(false); cin.tie(0);
    
    cin >> n >> m;
    for(int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        e.add(u, v);
    }

    tscc.set(n);
    tscc.solve();

    int ans = 0;
    // 遍历所有找到的 SCC
    for(int i = 1; i <= tscc.scc_cnt; i++) {
        // 题目要求：点数大于 1
        if(tscc.sz[i] > 1) {
            ans++;
        }
    }

    cout << ans << endl;
    
    return 0;
}

```

### 关键点说明

1. **`tscc.sz[scc_cnt]++`**: 这是这道题唯一的逻辑增量。在 Tarjan 算法回溯并弹出栈构建 SCC 时，我们顺便统计了这个 SCC 里有多少个节点。
2. **判定条件**: 最后的循环 `if(tscc.sz[i] > 1)` 严格对应题目要求的“点数大于 1”。

这道题是 Tarjan 模板的直接验证题，非常适合用来测试模板的正确性。
