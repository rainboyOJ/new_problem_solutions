/**
 * Author by Rainboy blog: https://rainboylv.com github : https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * date: 2025-12-25 08:31:48
 */
#include <bits/stdc++.h>
using namespace std;
typedef  long long ll;
typedef  unsigned long long ull;

const int maxn = 1e4+5; // 题目点数 1e4
const int maxe = 1e5+5; // 题目边数 5e4 * 2 (双向)
const ll INF_LL = 1e18; // 距离初始化无穷大

int n, m;
ll max_blood; // 总血量 b
int city_fee[maxn]; // 每个城市的过路费

// 链式前向星模板
struct linkList {
    typedef struct {int u,v,w,next;} edge;
    edge e[maxe];
    int h[maxn],edge_cnt=0;
    linkList(){
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

// Dijkstra 变量
ll dist[maxn];
bool vis[maxn];

// ------------------- 核心逻辑 -------------------

// 检查函数：限制最大单次收费为 limit，总血量能否 <= val (b)
bool check(int limit, ll val) {
    // 1. 基本判断：起点或终点本身的费用如果超过限制，直接不可达
    if (city_fee[1] > limit || city_fee[n] > limit) return false;

    // 2. 初始化 Dijkstra
    for(int i = 1; i <= n; i++) {
        dist[i] = INF_LL;
        vis[i] = false;
    }

    // 优先队列优化 Dijkstra
    // pair<当前掉血量, 城市编号>
    priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> pq;

    dist[1] = 0;
    pq.push({0, 1});

    while(!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        if(vis[u]) continue;
        vis[u] = true;

        if(u == n) break; // 提前退出（可选）

        // 使用模板的遍历方式，这里为了方便控制逻辑，稍微展开写
        for(int i = e(u); i != -1; i = e[i].next) {
            int v = e[i].v;
            int w = e[i].w; // 掉血量

            // --- 核心剪枝 ---
            // 如果目标城市的费用 > limit，视为此路不通
            if(city_fee[v] > limit) continue;

            if(dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }

    // 判断到达 n 点的最小掉血量是否在允许范围内
    return dist[n] <= val;
}

// 二分模板辅助函数
int mid(int l,int r) { return (l+r) >> 1; }

// bs_find = binary search find
// l 和 r 是费用的范围 [0, 1e9]
// val 是最大血量 b
int bs_find(int l, int r, ll val) {
    while( l < r) {
        int m = mid(l,r);
        // 如果以 m 为费用上限，可以活着走到终点 -> 尝试更小的费用
        if( check(m, val)) 
            r = m;
        else // 费用限制太死，导致无法到达或掉血过多 -> 需要放宽费用限制
            l = m+1;
    }
    return l;
}

signed main () {
    ios::sync_with_stdio(false); cin.tie(0);
    
    cin >> n >> m >> max_blood;

    // 读入城市费用
    int max_possible_fee = 0;
    for(int i = 1; i <= n; i++) {
        cin >> city_fee[i];
        max_possible_fee = max(max_possible_fee, city_fee[i]);
    }

    // 读入边
    for(int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        e.add2(u, v, w);
    }

    // 二分查找
    // 费用的范围是 [0, 1e9]，为了防止边界问题，右边界设大一点作为"哨兵"
    // 如果返回的值等于 sentinel，说明无解
    int sentinel = 1000000001; 
    
    // 如果连所有点都开放都走不到（check sentinel），直接 AFK，避免二分浪费时间
    if (!check(sentinel, max_blood)) {
        cout << "AFK" << endl;
        return 0;
    }

    int ans = bs_find(0, sentinel, max_blood);

    if (ans == sentinel) {
        cout << "AFK" << endl;
    } else {
        cout << ans << endl;
    }
    
    return 0;
}
