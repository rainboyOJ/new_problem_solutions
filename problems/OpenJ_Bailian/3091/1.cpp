/**
 * Author by Rainboy blog: https://rainboylv.com github : https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * date: 2026-01-09 08:41:46
 */
#include <bits/stdc++.h>
using namespace std;
typedef  long long ll;
typedef  unsigned long long ull;

const int maxn = 2e6+5;
const int maxe = 2e6+5;
int n,m;
int a[maxn];
int deg[maxn];

struct tarjanebcc {
    // ---------------- 图存储 ----------------
    struct edge {
        int u,v,next;
    } e[maxe * 2];
    int head[maxn], e_cnt;
    
    // ---------------- 找桥变量 ----------------
    int dfn[maxn], low[maxn], timer;
    bool is_bridge[maxe * 2]; // 标记边是否为桥 (下标对应边的编号)

    // ---------------- 染色变量 ----------------
    int bcc_id[maxn]; // 每个点所属的分量编号 (1 ~ bcc_cnt)
    int bcc_cnt;      // 边双连通分量总数

    void init(int n) {
        e_cnt = 0;
        timer = 0;
        bcc_cnt = 0;
        for (int i = 0; i <= n; i++) {
            head[i] = -1;
            dfn[i] = low[i] = 0;
            bcc_id[i] = 0;
        }
        // 注意：is_bridge 需要清空到最大边数
        // 如果多组数据且边数变化大，建议用 loop 清空或 vector
        memset(is_bridge, 0, sizeof(is_bridge)); 
    }

    void add_edge(int u, int v) {
        e[e_cnt] = {u,v, head[u]};
        head[u] = e_cnt++;
        
        e[e_cnt] = {v,u, head[v]};
        head[v] = e_cnt++;
    }

    // pass 1: tarjan 找桥
    // in_edge: 进入 u 的那条边的编号 (用于处理重边)
    void tarjan(int u, int fa) {
        // std::cout << u << "\n";
        dfn[u] = low[u] = ++timer;
        for (int i = head[u]; ~i; i = e[i].next) {
            int v = e[i].v;
            if( v == fa) continue;
            
            // 只要不是反向边 (即不走刚才来的路)
            if (!dfn[v]) {
                tarjan(v, u);
                low[u] = min(low[u], low[v]);
                if (low[v] > dfn[u]) {
                    is_bridge[i] = is_bridge[i ^ 1] = true;
                }
            } else {
                low[u] = min(low[u], dfn[v]);
            }
        }
    }

    // pass 2: dfs 染色
    void dfs_color(int u, int id) {
        bcc_id[u] = id;
        for (int i = head[u]; ~i; i = e[i].next) {
            int v = e[i].v;
            // 如果该边不是桥，且对面没被染过色，则继续
            if (!is_bridge[i] && !bcc_id[v]) {
                dfs_color(v, id);
            }
        }
    }

    // 主过程
    void solve(int n) {
        // 1. 找桥
        for (int i = 1; i <= n; i++) {
            if (!dfn[i]) tarjan(i, -1);
        }

        // 2. 染色
        for (int i = 1; i <= n; i++) {
            if (!bcc_id[i]) {
                bcc_cnt++;
                dfs_color(i, bcc_cnt);
            }
        }
    }

} ebcc;


void init(){
    std::cin >> n >> m;
    ebcc.init(n);
    for(int i = 1;i <= m ;++i ) // i: 1->m
    {
        int u,v;
        std::cin >> u >> v;
        ebcc.add_edge(u, v);
    }
}

signed main () {
    ios::sync_with_stdio(false); cin.tie(0);
    init();
    ebcc.solve(n);

    if(ebcc.bcc_cnt == 1) {
        std::cout << 0 << "\n";
        return 0;
    }

    for(int i = 0 ;i < ebcc.e_cnt ; i+=2) {
        int u  = ebcc.e[i].u;
        int v  = ebcc.e[i].v;
        if( ebcc.bcc_id[u] == ebcc.bcc_id[v]) continue;
        deg[ ebcc.bcc_id[u] ]++;
        deg[ ebcc.bcc_id[v] ]++;
    }

    int leaf_cnt = 0;
    for(int i = 1 ;i<=ebcc.bcc_cnt;i++) {
        if( deg[i] == 1)
            leaf_cnt++;
    }
    std::cout << (leaf_cnt+1) /2 << "\n";
    
    return 0;
}
