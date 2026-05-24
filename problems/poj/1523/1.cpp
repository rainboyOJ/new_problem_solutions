/**
 * Author by Rainboy blog: https://rainboylv.com github : https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * date: 2025-12-29 15:26:51
 * 使用 割点 算法
 */
#include <iostream
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
} e;

//oisnip_begincut_node.cpp
struct TarjanCut {
    int n, timer; // timer 对应你代码中的 cnt
    int dfn[maxn], low[maxn];
    bool is_cut[maxn]; // 标记是否为割点 (对应 cut[])
    int root; // 当前 DFS 树的根节点

    // 记录 删除这个点后的子网的数量
    int subnet_cnt[maxn]; 

    void set(int _n) {
        n = _n;
        timer = 0;
        memset(dfn, 0, sizeof(dfn));
        memset(low, 0, sizeof(low));
        memset(subnet_cnt,0,sizeof(subnet_cnt));
        memset(is_cut, 0, sizeof(is_cut));
    }

    /*
     * u: 当前节点
     * fa: u 的父节点 (防止走回头路)
     */
    void dfs(int u, int fa = -1) {
        dfn[u] = low[u] = ++timer;

        // 至少是1
        subnet_cnt[u] = 1;

        int child = 0; // 记录 root 在 DFS 树中的子节点数量

        for (int i = e(u); ~i; i = e[i].next) {
            int v = e[i].v;

            // 不走父子边
            if (v == fa) continue;

            // v 没有被访问过，是树边
            if (!dfn[v]) { 
                child++;
                dfs(v, u); // 【注意】这里必须传 u，表示 v 的父亲是 u

                // 回溯时用子节点的 low 更新当前节点的 low
                low[u] = std::min(low[u], low[v]);

                // 割点判定情况 2: 非根节点
                // 如果子节点 v 无法回到 u 的祖先 (low[v] >= dfn[u])
                // 说明 u 是连接 v 子树和其他部分的必经点
                if (low[v] >= dfn[u] && u != root) {
                    is_cut[u] = true;
                    subnet_cnt[u]++;
                }

                // 处理返祖边
                // 注意:v可能是u的父亲,但没有关系,最多low[u] == dfn[fa[u]]
                // dfn[v] < dfn[u] 说明v是u的祖先,
                // 在无向图上其实不可能 dfn[v] > dfn[u]
                // 因为: v 是一个已经访问过的点, 如果dfn[v] > dfn[u] 说明u是v的祖先, 那么v在u的子树上,
                // 根据dfs 的性质, 应该先访问u, 再访问v,但此时v已经被访问, 所以不可能出现dfn[v] > dfn[u]的情况
            } else if( dfn[v] < dfn[u] ) {
                // v 已经被访问过，是返祖边 (Back Edge)
                // 用 v 的 dfn 更新 u 的 low
                low[u] = std::min(low[u], dfn[v]);
                // 注意：有些版本写成 min(low[u], low[v]) (对于已访问的 v) 是错误的。
                // 对于返祖边，只能取 dfn[v]，因为 low[v] 可能包含从 v 回到更上层的路径，
                // 而边 (u, v) 并不代表 u 可以通过 v 再跳跃回去（除非有其他边）。
            }
        }

        // 割点判定情况 1: 根节点
        // 如果根节点在 DFS 树中有两个及以上的子节点，则它是割点
        if (u == root && child > 1) {
            is_cut[u] = true;
            subnet_cnt[u] = child;
        }
    }

    void solve() {
        // 遍历所有点，防止图不连通
        for (int i = 1; i <= n; i++) {
            // 图可能不连通  点 不连续
            if (!dfn[i] && e.h[i] != -1) {
                root = i; // 记录当前连通块的 DFS 根
                dfs(i, 0); 
            }
        }
    }
    
    // 辅助函数：获取所有割点
    std::vector<int> get_cuts() {
        std::vector<int> cuts;
        for (int i = 1; i <= n; i++) {
            if (is_cut[i]) cuts.push_back(i);
        }
        return cuts;
    }
};
//oisnip_end

TarjanCut tjcut;


void init(){

}

signed main () {
    ios::sync_with_stdio(false); cin.tie(0);

    int u,v;
    int case_id = 0;

    int max_n = 0;
    while (1) {
        std::cin >> u;
        if( u == 0 ) break;
        std::cin >> v;
        
        if(max_n < u) max_n = u;
        if(max_n < v) max_n = v;

        e.reset();
        e.add2(u, v);

        while (cin >> u && u != 0) {
            std::cin >> v;
            e.add2(u, v);

            if(max_n < u) max_n = u;
            if(max_n < v) max_n = v;
        }
        tjcut.set(max_n);

        tjcut.solve();

        std::cout << "Network #" << ++case_id << "\n";

         bool has_spf = false;
         for (int i = 1; i <= max_n; i++) {
             // std::cout << i << " : " << tjcut.subnet_cnt[i] << "\n";
             if (tjcut.subnet_cnt[i] >= 2) { // 至少分成两块才叫 SPF
                 has_spf = true;
                 std::cout << "  SPF node " << i << " leaves " << tjcut.subnet_cnt[i] << " subnets\n";
             }
         }
         if (!has_spf) std::cout << "  No SPF nodes\n";
         std::cout << "\n";


    }

    
    return 0;
}
