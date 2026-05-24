/**
 * Author by Rainboy blog: https://rainboylv.com github : https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * date: 2025-12-29 10:52:38
 */
#include <iostream>
#include <cstring>   // 必须包含：用于 memset
#include <stack>     // 必须包含：用于 stack
#include <algorithm> // 必须包含：用于 std::min
#include <vector>

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
    int h[maxn];
    int edge_cnt; // C++98 错误修复：不能在这里写 = 0

    linkList(){
        edge_cnt = 0; // 必须在构造函数中初始化
        reset();
    }

    void reset() {
        edge_cnt = 0;
        memset(h, -1, sizeof(h));
    }

    void add(int u,int v,int w=0){
        // C++98 下，手动赋值最安全
        e[edge_cnt].u = u;
        e[edge_cnt].v = v;
        e[edge_cnt].w = w;
        e[edge_cnt].next = h[u];
        h[u] = edge_cnt++;
    }

    int operator()(int u){ return h[u]; }
    edge& operator[](int i){ return e[i]; }
} e;

struct TarjanScc {
    int n, timer;
    std::stack<int> st; // 修复：需要 #include <stack>
    bool in_stack[maxn];
    int dfn[maxn], low[maxn], scc_id[maxn];
    int scc_cnt; 
    int sz[maxn]; 

    void set(int _n) {
        n = _n;
        timer = scc_cnt = 0;
        memset(dfn, 0, sizeof(dfn));     // 修复：需要 #include <cstring>
        memset(in_stack, 0, sizeof(in_stack));
        memset(sz, 0, sizeof(sz));
        // 清空栈，防止多组数据残留
        while (!st.empty()) st.pop();
    }

    void dfs(int u) {
        dfn[u] = low[u] = ++timer;
        st.push(u);
        in_stack[u] = true;

        for (int i = e(u); ~i ; i = e[i].next) {
            int v = e[i].v;
            if (!dfn[v]) {
                dfs(v);
                low[u] = std::min(low[u], low[v]); // 需要 <algorithm>
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
                sz[scc_cnt]++; 
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

int out_degree[maxn]; 

int main () {
    // 建议在 C++98 中显式包含 stdio 相关的同步关闭，虽然这里用了 iostream
    ios::sync_with_stdio(false); 
    cin.tie(NULL); // C++98 用 NULL 或 0，不要用 nullptr
    
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

    if(zero_out_cnt == 1) {
        cout << tscc.sz[star_scc_idx] << endl;
    } else {
        cout << 0 << endl;
    }

    return 0;
}
