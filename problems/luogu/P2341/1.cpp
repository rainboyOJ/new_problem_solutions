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
    int sz[maxn]; // 新增：记录每个 SCC 包含的节点数量

    void set(int _n) {
        n = _n;
        timer = scc_cnt = 0;
        memset(dfn, 0, sizeof(dfn));
        memset(in_stack, 0, sizeof(in_stack));
        memset(sz, 0, sizeof(sz));
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
                sz[scc_cnt]++; // 累加该 SCC 的大小
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

int out_degree[maxn]; // 记录每个 SCC 的出度

signed main () {
    ios::sync_with_stdio(false); cin.tie(0);
    
    if(!(cin >> n >> m)) return 0;
    
    for(int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        e.add(u, v);
    }

    tscc.set(n);
    tscc.solve();

    // 遍历所有原图的边，统计 SCC 的出度
    for(int i = 0; i < e.edge_cnt; i++) {
        int u = e.e[i].u;
        int v = e.e[i].v;
        // 如果边连接了两个不同的 SCC
        if(tscc.scc_id[u] != tscc.scc_id[v]) {
            out_degree[tscc.scc_id[u]]++;
        }
    }

    int zero_out_cnt = 0; // 出度为 0 的 SCC 数量
    int star_scc_idx = 0; // 记录出度为 0 的 SCC 编号

    for(int i = 1; i <= tscc.scc_cnt; i++) {
        if(out_degree[i] == 0) {
            zero_out_cnt++;
            star_scc_idx = i;
        }
    }

    // 判定：如果有且仅有一个出度为 0 的 SCC
    if(zero_out_cnt == 1) {
        cout << tscc.sz[star_scc_idx] << endl;
    } else {
        // 如果有多个出度为 0 的 SCC，或者没有点（n=0），则没有明星
        cout << 0 << endl;
    }

    return 0;
}

