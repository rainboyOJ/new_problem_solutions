/**
 * Author by Rainboy blog: https://rainboylv.com github : https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * date: 2025-12-29 21:00:20
 */
#include <bits/stdc++.h>
#include <utility>
using namespace std;
typedef  long long ll;
typedef  unsigned long long ull;

const int maxn = 2e6+5;
const int maxe = 4e6+5;
const int mod = 1e9+7;

int n,m;
int a[maxn];
std::map<string,int> name2id;


std::vector< std::pair<int,int>> couples;


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
} e;


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

    void print_scc_id() {
        for(int i = 1;i <= n ;++i ) // i: 1->n
        {
            std::cout << i << " " << scc_id[i] <<  "\n";
        }
    }

    void solve() {
        for (int i = 1; i <= n; i++) {
            if (!dfn[i]) dfs(i);
        }

    }
};
//oisnip_end

TarjanScc tjscc;


void init(){
    std::cin >> n;
    int cnt = 0;
    for(int i = 1;i <= n ;++i ) // i: 1->n
    {
        string gname,bname;
        std::cin >> gname >> bname;
        // std::cout << gname << " ";
        // std::cout << bname << "\n";
        name2id[gname] = ++cnt;
        name2id[bname] = ++cnt;

        int u = name2id[gname];
        int v = name2id[bname];

        // 建图核心：女 -> 男
        e.add(u,v);

        //存下夫妻关系
        couples.push_back( std::make_pair(u, v));
    }

    // 处理旧情（旧情边：男 -> 女）
    std::cin >> m;
    for(int i = 1;i <= m ;++i ) // i: 1->m
    {
        string gname,bname;
        std::cin >> gname >> bname;
        // std::cout << gname << " ";
        // std::cout << bname << "\n";

        int u = name2id[bname];
        int v = name2id[gname];

        // 建图核心：男 -> 女
        e.add(u,v);
    }

}

signed main () {
    ios::sync_with_stdio(false); cin.tie(0);
    init();

    tjscc.set(2*n);
    tjscc.solve();
    // tjscc.print_scc_id();

    for( auto p : couples) {
        if( tjscc.scc_id[p.first] == tjscc.scc_id[p.second])
            std::cout << "Unsafe" << "\n";
        else
            std::cout << "Safe" << "\n";
    }
    
    return 0;
}
