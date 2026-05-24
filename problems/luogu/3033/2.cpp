/**
 * Author by Rainboy blog: https://rainboylv.com github : https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * date: 2026-01-13 20:56:51
 * Problem: P3033 [USACO11NOV] Cow Steeplechase G
 * Algorithm: Bipartite Matching (Max Flow) -> Max Independent Set
 */

#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5+5; // 节点数 N <= 250，开大点无所谓
const int maxe = 2e6+5; // 边数
const long long INF = 1e18;

// 全局变量
int n, m; 
int s, t; // 源点 汇点

// --- 存图模板 ---
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
    
    //下标访问
    edge& operator[](int i){ return e[i]; }
} e;

// --- Dinic算法模板 ---
struct Dinic {
    vector<int> level, cur;
    int n;
    
    void init(int n) {
        e.reset(); // 清空边
        level.assign(n+5, -1);
        cur.assign(n+5, 0);
        this->n = n;
    }
    
    // 添加边：从u到v，容量为cap
    void addEdge(int u, int v, int cap) {
        e.add(u, v, cap);    // 正向边
        e.add(v, u, 0);      // 反向边
    }
    
    // BFS分层
    bool bfs(int s, int t) {
        fill(level.begin(), level.end(), -1);
        queue<int> q;
        level[s] = 0;
        q.push(s);
        
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            
            for(int i = e.h[u] ; ~i ;i = e[i].next) {
                int v = e[i].v, cap = e[i].w;
                if (cap > 0 && level[v] < 0) {
                    level[v] = level[u] + 1;
                    q.push(v);
                }
            }
        }
        return level[t] >= 0;
    }
    
    // DFS增广
    long long dfs(int u, int t, long long preFlow) {
        if (u == t || preFlow == 0) return preFlow;
        long long flow = 0;
        
        for (int& cid = cur[u]; cid != -1; cid = e[cid].next) {
            int v = e[cid].v;
            int cap = e[cid].w;
            
            if (level[u] + 1 != level[v] || cap <= 0) continue;
            
            long long tr = dfs(v, t, min(preFlow, (long long)cap));
            
            if (tr == 0) continue;

            e[cid].w -= tr;
            e[cid ^ 1].w += tr;
            flow += tr;
            preFlow -= tr;
            if (preFlow == 0) break;
        }
        return flow;
    }
    
    long long maxFlow(int s, int t) {
        long long flow = 0;
        while (bfs(s, t)) {
            for (int i = 0; i <= n; i++) cur[i] = e.h[i];
            flow += dfs(s, t, LLONG_MAX);
        }
        return flow;
    }
} dinic;

// --- 题目特定逻辑 ---

// 定义线段结构体
struct Segment {
    int x1, y1, x2, y2;
    int id; // 在网络流图中的节点编号
};

// 判断水平线段和垂直线段是否相交
// h: horizontal (y1 == y2), v: vertical (x1 == x2)
bool is_intersect(const Segment& h, const Segment& v) {
    // 题目保证水平互不相交，垂直互不相交，所以只判断水平和垂直
    // 相交条件：
    // 1. 垂直线段的 X 坐标在水平线段的 X 范围内 [x1, x2]
    // 2. 水平线段的 Y 坐标在垂直线段的 Y 范围内 [y1, y2]
    return (v.x1 >= h.x1 && v.x1 <= h.x2) && 
           (h.y1 >= v.y1 && h.y1 <= v.y2);
}

void solve() {
    int N;
    std::cin >> N;

    vector<Segment> horiz, vert;

    for(int i = 0; i < N; ++i) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        
        // 规范化坐标，保证 x1 <= x2, y1 <= y2
        if (x1 > x2) swap(x1, x2);
        if (y1 > y2) swap(y1, y2);

        if (y1 == y2) {
            // 水平线段
            horiz.push_back({x1, y1, x2, y2, 0});
        } else {
            // 垂直线段
            vert.push_back({x1, y1, x2, y2, 0});
        }
    }

    // 节点编号规划：
    // S = 0
    // 水平线段节点: 1 ~ horiz.size()
    // 垂直线段节点: horiz.size() + 1 ~ N
    // T = N + 1
    
    int n_h = horiz.size();
    int n_v = vert.size();
    
    s = 0;
    t = N + 1;
    
    dinic.init(t + 1);

    // 1. 源点 -> 水平线段
    for(int i = 0; i < n_h; ++i) {
        horiz[i].id = i + 1;
        dinic.addEdge(s, horiz[i].id, 1);
    }

    // 2. 垂直线段 -> 汇点
    for(int i = 0; i < n_v; ++i) {
        vert[i].id = n_h + i + 1;
        dinic.addEdge(vert[i].id, t, 1);
    }

    // 3. 构建冲突边：水平线段 -> 垂直线段
    // 如果两条线段相交，则连边（代表冲突）
    for(const auto& h : horiz) {
        for(const auto& v : vert) {
            if (is_intersect(h, v)) {
                dinic.addEdge(h.id, v.id, 1);
            }
        }
    }

    // 二分图最大独立集 = 总点数 - 最大匹配数
    long long max_matching = dinic.maxFlow(s, t);
    cout << N - max_matching << endl;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    solve();
    return 0;
}
