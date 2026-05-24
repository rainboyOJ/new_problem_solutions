/**
 * Author by Rainboy blog: https://rainboylv.com github : https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * date: 2026-01-10 21:18:55
 * desc: 对1.1.cpp 的复刻: 优化, 不用 on_ring_edge, 
 * 使用最简单的dfs 找环上所有点的代码
 * * 核心思路：
 * 1. 对于树 (m=n-1)，贪心策略是每次走编号最小的子节点。
 * 2. 对于基环树 (m=n)，需要断掉环上的一条边使其变为树。
 * 3. 策略：当我们在环上从 u 走向 v 时，如果 v 的值比“如果我们此时回头能访问到的最小点(target)”还要大，
 * 说明走 v 这条路不划算，应该在这里断开 (u, v)。
 */
#include <bits/stdc++.h>
using namespace std;
typedef  long long ll;
typedef  unsigned long long ull;

const int maxn = 5e5+5;

// --- 存图
std::vector<int> adj[maxn];
// 添加无向边
void add_edge(int u,int v) {
    adj[u].push_back(v);
    adj[v].push_back(u);
}
// --- 存图 -- end

int n,m;
bool on_ring[maxn]; // 标记点u是否在环上
int del_edge[2];    // 记录最终决定逻辑删除的边 (del_edge[0], del_edge[1])

// 判断当前边 (u, v) 是否是被标记为删除的那条边
inline bool is_del_edge(int u,int v) {
    if( u == del_edge[0] && v == del_edge[1] ) return 1;
    if( u == del_edge[1] && v == del_edge[0] ) return 1;
    return 0;
}

// 初始化函数：读入并预处理
void init(){
    std::cin >> n >> m;
    for(int i = 1;i <= m ;++i ) // i: 1->m
    {
        int u,v;
        std::cin >> u >> v;
        add_edge(u, v);
    }

    // 关键步骤：对每个点的邻接表进行排序
    // 保证在 DFS 遍历时，总是优先尝试访问编号更小的节点，满足字典序最小的要求
    for(int i = 1;i <= n ;++i ) // i: 1->n
    {
        std::sort(adj[i].begin(),adj[i].end());
    }
}


int parent[maxn];   // 记录 DFS 路径上的父节点，用于回溯找环
bool finded_loop = 0; // 标记是否已经找到了环
bool vis[maxn];     // 访问标记

// 找环函数：利用 DFS 找到基环树中唯一的环，并标记环上的点
void dfs_find_loop(int u,int fa) {
    if( finded_loop) return;
    vis[u] = 1;

    for( auto v : adj[u]) {
        if( v == fa ) continue; // 防止走回头路

        // 如果访问到了已经访问过的点，说明找到了环（返祖边）
        if( vis[v]) {
            finded_loop = 1;

            int cur = u;
            on_ring[v] = 1; // 标记 v 在环上
            // 回溯 parent 数组，将环路径上的点全部标记
            while( cur != v) {
                on_ring[cur] = 1;
                cur = parent[cur];
            }

            return;
        }
        
        parent[v] = u; // 记录父节点
        dfs_find_loop(v, u);
        if( finded_loop) return;
    }

}

std::vector<int> ans; // 存储最终的遍历序列
// 最终的遍历函数：生成答案序列
void dfs(int u,int fa) {
    
    ans.push_back(u);

    for( auto v : adj[u]) {
        if( v == fa) continue;
        // 如果遇到被标记删除的边，则跳过不走（物理断边效果）
        if( is_del_edge(u, v) ) continue;
        dfs(v,u);
    }
}


/**
 * 核心贪心函数：寻找应该断开哪条环边
 * u: 当前节点
 * fa: 父节点
 * target: “后悔药”值。即如果我不走当前的 v，而是回溯(回头)，紧接着能访问到的最小节点值是多少。
 */
bool find_del_edge(int u,int fa,int target){
    vis[u] = 1;

    for(int i = 0 ;i< adj[u].size() ;i++)
    {
        int v = adj[u][i];
        if( v == fa) continue;

        // 特殊情况：如果再次访问到了已访问过的点（说明绕环一圈回到了环的另一端）
        // 此时默认这条边就是最后闭合环的边，暂时标记为删除对象
        // 如果后面没有触发更优的断边条件，就断这一条
        if( vis[v]) {
            del_edge[0] = u;
            del_edge[1] = v;
            continue;
        }

        // 计算新的 target (回溯后能到达的最佳备选点)
        // 初始继承自父节点传下来的 target
        int next_point = target;

        // 只有当前点在环上时，才需要更新 target
        // 因为只有在环上我们才有“回头”的选择权
        if( on_ring[u]) {
            // 如果 u 还有下一个邻居（且不是父节点），那么如果不走 v，回头后紧接着就会走这个邻居
            // 注意：adj 已经排序过，所以 adj[u][i+1] 是比 v 大的最小邻居
            if( i+ 1 < adj[u].size() && adj[u][i+1] != fa)
                next_point = adj[u][i+1];
        }

        // --- 贪心决策核心 ---
        // 1. 当前边 (u, v) 是环上的边 (u和v都在环上)
        // 2. 目标点 v 的值 > 回溯后的备选点 next_point
        // 含义：眼前这条路(v)太大了，不如回头去走那个更小的(next_point)，所以在这里断开最划算。
        if(on_ring[u] &&  on_ring[v] && v > next_point) {
            del_edge[0] = u;
            del_edge[1] = v;
            return 1; // 找到了最优断点，直接返回
        }

        // 继续递归寻找
        if( find_del_edge(v, u, next_point) )
            return 1;
        
    }

    return 0;

    
}

signed main () {
    ios::sync_with_stdio(false); cin.tie(0);
    init();
    
    // 情况1：这是一棵普通的树 (边数 = 点数 - 1)
    // 直接 DFS 即可，因为不需要断边
    if( n -1 == m)
    {
        dfs(1,0);
        for( auto u : ans) std::cout << u << " ";
        return 0;
    }

    // 情况2：基环树 (边数 = 点数)
    
    // 第一步：找出环上的所有点
    dfs_find_loop(1,0);
    
    #ifdef DEBUG
    std::cout << "on_ring node :" << "\n";
    for(int i = 1;i <= n ;++i ) // i: 1->n
    {
        if( on_ring[i] )
            std::cout << i << " ";
    }
    #endif

    // 第二步：运行贪心逻辑，找到需要断开的那条边
    // 初始 target 设为无穷大，因为根节点无法回溯
    memset(vis,0,sizeof(vis));
    find_del_edge(1,0,1e9);


    // 第三步：利用找到的 del_edge，逻辑断开该边，进行最终的 DFS 输出序列
    dfs(1,0);
    for( auto u : ans) std::cout << u << " ";
    
    return 0;
}
