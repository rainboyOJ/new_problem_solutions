/**
 * Author by Rainboy blog: https://rainboylv.com github : https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * date: 2025-12-30 07:57:11
 */
#include <bits/stdc++.h>
using namespace std;
typedef  long long ll;
typedef  unsigned long long ull;

const int maxn = 2e6+5;
const int maxe = 4e6+5;
int mod;

int n,m;
int in_degree[maxn];
int _size[maxn]; // size[i] scc 点 的数量
int g[maxn],f[maxn];


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
} e,e_dag;


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
                _size[scc_cnt]++;
                if (v == u) break; // 直到找到起始点
            }
        }
    }

    void solve() {
        for (int i = 1; i <= n; i++) {
            if (!dfn[i]) dfs(i);
        }
    }
};

TarjanScc tjscc;
//oisnip_end

void init(){
    std::cin >> n >> m >> mod;
    for(int i = 1;i <= m ;++i ) // i: 1->m
    {
        int u,v;
        std::cin >> u >> v;
        e.add(u, v);
    }
}

std::vector<int> top_sort;
// dag
void dag() {
    std::queue<int> q;
    for(int i = 1;i <= tjscc.scc_cnt;i++)
    {
        if( in_degree[i] == 0) q.push(i);
    }

    while( q.empty() == false ) {
        int u = q.front();
        q.pop();
        top_sort.push_back(u);
        for(int i =  e_dag(u) ; ~i; i = e_dag[i].next) {
            int v = e_dag[i].v;
            in_degree[v]--;
            if( in_degree[v] == 0)
                q.push(v);
        }
    }
}

signed main () {
    ios::sync_with_stdio(false); cin.tie(0);
    init();
    //缩点
    tjscc.set(n);
    tjscc.solve();

    // 建立 dag 的图,并去重

    // 2. 建 DAG (去重)
    // 使用 pair 数组存储边，方便去重
    vector<pair<int, int>> distinct_edges;
    for (int u = 1; u <= n; u++) {
        for (int i = e.h[u]; ~i; i = e[i].next) {
            int v = e[i].v;
            if (tjscc.scc_id[u] != tjscc.scc_id[v]) {
                distinct_edges.push_back({tjscc.scc_id[u], tjscc.scc_id[v]});
            }
        }
    }
    
    // 排序并去重
    sort(distinct_edges.begin(), distinct_edges.end());
    distinct_edges.erase(unique(distinct_edges.begin(), distinct_edges.end()), distinct_edges.end());

    for(auto & edge : distinct_edges) {

        int u = edge.first;
        int v = edge.second;
        e_dag.add( u,v );
        in_degree[v]++;
    }

    // 初始化 dp的边界
    for(int u = 1 ; u <= tjscc.scc_cnt ; u++ )
    {
        if( in_degree[u] == 0 )
        {
            f[u] = _size[u];
            g[u] = 1; //初始化, 这个至少数量是1
        }
    }

    dag();
    int max_k = 0;
    int max_c = 0;

    // dp
    for( auto u : top_sort) {
        // std::cout << u << "\n";
        // f[v] = max(f[v] , f[u] + _size[v]);

        for(int i = e_dag(u) ; ~i ;i = e_dag[i].next) {
            int v = e_dag[i].v;
            f[v] = max(f[v] , f[u] +_size[v]);

            // 放在这个更新 可能会错
            // 因为一个简单的图: 比如只有一个点 u
            // u它没有后继,那么就会错
            // if( f[u] > max_k) max_k = f[u];
        }

        //这里
        if( f[u] > max_k) max_k = f[u];
    }
    for( auto u : top_sort) {
        // f[v] = max(f[v] , f[u] + _size[v]);

        for(int i = e_dag(u) ; ~i ;i = e_dag[i].next) {
            int v = e_dag[i].v;
            if( f[v] == f[u] + _size[v])
            {
                // std::cout << u  <<  "->" << v << "\n";
                g[v] += g[u];
                g[v] %= mod;
            }
        }
        if( f[u] == max_k)
        {
            max_c += g[u];
            max_c %= mod;
        }
        // std::cout << u << " gu : " << g[u] << "\n";
    }

    // std::cout << "---------------" << "\n";
    std::cout << max_k << "\n";
    std::cout << max_c << "\n";

    
    return 0;
}
