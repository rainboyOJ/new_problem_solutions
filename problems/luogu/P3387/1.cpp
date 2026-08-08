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

int n,m;
int a[maxn];

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

    //遍历点u 周围点
    template<typename U>
    void for_each(int u,U func){
        for(int i = h[u] ; i !=-1;i = e[i].next)
            func(e[i].u,e[i].v,e[i].w); //u v w
    }

    void add(int u,int v,int w=0){
        e[edge_cnt] = {u,v,w,h[u]};
        h[u] = edge_cnt++;
    }
    void add2(int u,int v,int w=0){
        add(u,v,w);
        add(v,u,w);
    }
    //下标访问
    edge& operator[](int i){ return e[i]; }
    //返回head[u]
    int operator()(int u){ return h[u]; }
} e, e2; // e是原图，e2是缩点后的DAG

//oisnip_beginscc.cpp
struct TarjanScc {
    int n, timer;
    std::stack<int> st;
    bool in_stack[maxn];
    int dfn[maxn], low[maxn], scc_id[maxn];
    int scc_cnt; // SCC 的总数

    void set(int _n) {
        n = _n;
        timer = scc_cnt = 0;
        memset(dfn, 0, sizeof(dfn));
        memset(in_stack, 0, sizeof(in_stack));
    }

    // 有向图,不要加father参数
    void dfs(int u) {
        dfn[u] = low[u] = ++timer;
        st.push(u);
        in_stack[u] = true;

        for (int i = e(u); ~i ; i = e[i].next) {
            int v = e[i].v;
            if (!dfn[v]) { // 如果 v 没被访问过
                dfs(v);
                
                // 根据子节点的 low 值更新当前节点的 low 值
                low[u] = std::min(low[u], low[v]);
            } else if (in_stack[v]) { //返祖边, 如果 v 在栈中，说明构成了环
                low[u] = std::min(low[u], dfn[v]);
            }
        }

        // 如果 dfn == low，说明找到了一个 SCC 的起始点
        if (low[u] == dfn[u]) {
            scc_cnt++;
            while (1) {
                int v = st.top(); st.pop();
                in_stack[v] = 0;
                scc_id[v] = scc_cnt; // 标记所属 SCC 编号
                if (v == u) break; // 直到找到起始点
            }
        }
    }

    void solve() {
        for (int i = 1; i <= n; i++) {
            if (!dfn[i]) dfs(i);
        }
    }
} tscc;
//oisnip_end

ll scc_weight[maxn]; // 存储每个 SCC 的点权总和
int in_degree[maxn]; // 存储 DAG 节点的入度
ll f[maxn];         // DP 数组

signed main () {
    ios::sync_with_stdio(false); cin.tie(0);
    
    cin >> n >> m;
    for(int i = 1; i <= n; i++) cin >> a[i];
    
    for(int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        e.add(u, v);
    }

    // 1. 求强连通分量
    tscc.set(n);
    tscc.solve();

    // 2. 缩点：遍历原图所有边，建立新图 DAG
    for(int i = 0; i < e.edge_cnt; i++) {
        int u = e[i].u;
        int v = e[i].v;
        if(tscc.scc_id[u] != tscc.scc_id[v]) {
            e2.add(tscc.scc_id[u], tscc.scc_id[v]);
            in_degree[tscc.scc_id[v]]++;
        }
    }
    
    // 累加每个 SCC 的权值
    for(int i = 1; i <= n; i++) {
        scc_weight[tscc.scc_id[i]] += a[i];
    }

    // 3. DAG 上求最长路 (拓扑排序 + DP)
    queue<int> q;
    for(int i = 1; i <= tscc.scc_cnt; i++) {
        f[i] = scc_weight[i];
        if(in_degree[i] == 0) q.push(i);
    }

    while(!q.empty()) {
        int u = q.front(); q.pop();
        for(int i = e2(u); ~i; i = e2[i].next) {
            int v = e2[i].v;
            // u -->v 
            // 用前驱 u 更新 后继v
            f[v] = max(f[v], f[u] + scc_weight[v]);
            if(--in_degree[v] == 0) q.push(v);
        }
    }

    // 4. 结果是所有 SCC 中 DP 值的最大值
    ll ans = 0;
    for(int i = 1; i <= tscc.scc_cnt; i++) ans = max(ans, f[i]);
    cout << ans << endl;

    return 0;
}
