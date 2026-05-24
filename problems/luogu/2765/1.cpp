/**
 * Author by Rainboy blog: https://rainboylv.com github : https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * date: 2026-01-16 14:18:54
 */

#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e6+5; // 点
const int maxe = 2e6+5; // 边
const long long INF = 1e18;

// 存图的模板
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

#ifdef __cpp_range_based_for
    struct UseEdge {
        using ReturnType = edge&; 
        static ReturnType get(linkList* p, int i) { return p->e[i]; }
    };
    struct UseAdj {
        using ReturnType = int;
        static ReturnType get(linkList* p, int i) { return p->e[i].v; }
    };

    template<typename Getter>
    struct BaseIterator {
        int i; linkList* p;
        BaseIterator(linkList* p, int i) : p(p), i(i) {}
        BaseIterator& operator++() { i = p->e[i].next; return *this; }
        bool operator!=(const BaseIterator& oth) { return i != oth.i; }
        typename Getter::ReturnType operator*() { return Getter::get(p, i); }
    };

    using Iterator    = BaseIterator<UseEdge>;
    using AdjIterator = BaseIterator<UseAdj>;

    template<typename IterT>
    struct BaseRange {
        int start; linkList* p;
        BaseRange(linkList* p, int start) : p(p), start(start) {}
        IterT begin() { return IterT(p, p->h[start]); }
        IterT end()   { return IterT(p, -1); }
    };

    BaseRange<Iterator> operator()(int u) { return BaseRange<Iterator>(this, u); }
    BaseRange<AdjIterator> adj(int u) { return BaseRange<AdjIterator>(this, u); }
#endif
} e;

// Dinic算法最大流模板
struct Dinic {
    vector<int> level, cur;
    int n;
    
    void init(int n) {
        e.edge_cnt = 0;
        memset(e.h, -1, sizeof(e.h));
        level.resize(n+5);
        cur.resize(n+5);
        this->n = n;
    }
    
    void addEdge(int u, int v, int cap) {
        e.add(u, v, cap);    
        e.add(v, u, 0);      
    }
    
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
    
    long long dfs(int u, int t, long long preFlow) {
        if (u == t || preFlow == 0) return preFlow;
        long long flow = 0;
        for (int& cid = cur[u]; cid != -1; cid = e[cid].next) {
            auto& edge = e[cid]; 
            int to = edge.v;
            long long cap = edge.w;
            if (level[u] + 1 != level[to] || cap <= 0) continue;
            long long tr = dfs(to, t, min(preFlow, cap));
            e[cid].w -= tr ;     
            e[cid ^ 1].w += tr; 
            flow += tr;
            preFlow -= tr;
            if (preFlow == 0) break;
        }
        if (flow == 0) level[u] = -1;
        return flow;
    }
    
    long long maxFlow(int s, int t) {
        long long flow = 0;
        while (bfs(s, t)) { 
            for (int i = 0; i <= n; i++) {
                cur[i] = e.h[i]; 
            }
            flow += dfs(s, t, LLONG_MAX);
        }
        return flow;
    }
} dinic;

// --- 针对 P2765 的逻辑部分 ---

// 判断完全平方数
bool is_sq(int x) {
    int r = sqrt(x);
    return r * r == x;
}

// 记录每个球的下一个球是谁，用于输出
int nxt_ball[5005]; 
bool has_prev[5005]; // 标记球是否有前驱

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    
    int n;
    cin >> n;

    // 设定偏移量，用于构建二分图
    // 球 i 拆分为: 左边点 i, 右边点 i + OFFSET
    const int OFFSET = 2000; 
    const int S = 0;
    const int T = 4005;

    // 初始化Dinic，设置足够大的空间
    dinic.init(T + 10);

    int num_balls = 0;
    int total_flow = 0;

    while (true) {
        num_balls++;
        
        // 1. 在二分图中添加新球的相关边
        // 源点 -> 左部点 i
        dinic.addEdge(S, num_balls, 1);
        // 右部点 i -> 汇点
        dinic.addEdge(num_balls + OFFSET, T, 1);

        // 2. 尝试与之前的球建立连接
        for (int i = 1; i < num_balls; i++) {
            if (is_sq(i + num_balls)) {
                // 如果 i+num_balls 是完全平方数，
                // 则球 num_balls 可以放在球 i 上面
                // 对应二分图边: 左部点 i -> 右部点 num_balls
                dinic.addEdge(i, num_balls + OFFSET, 1);
            }
        }

        // 3. 在残量网络上继续跑最大流
        total_flow += dinic.maxFlow(S, T);

        // 4. 计算需要的最小柱子数
        // 最小路径覆盖 = 节点数 - 最大匹配数(最大流)
        int pillars_needed = num_balls - total_flow;

        if (pillars_needed > n) {
            num_balls--; // 恢复到上一个合法的状态
            break;
        }
    }

    cout << num_balls << "\n";

    // --- 恢复路径用于输出 ---
    // 遍历所有左部点 i
    memset(nxt_ball, 0, sizeof(nxt_ball));
    memset(has_prev, 0, sizeof(has_prev));

    for (int u = 1; u <= num_balls; u++) {
        // 遍历 u 的所有出边，找到流量为0（被占用）且指向右部点的边
        for (int i = e.h[u]; ~i; i = e[i].next) {
            int v = e[i].v;
            // 这是一个正向边(偶数索引) 且 满流(剩余容量w==0) 且 v是右部点
            if (i % 2 == 0 && e[i].w == 0 && v > OFFSET && v != T) {
                int real_v = v - OFFSET;
                nxt_ball[u] = real_v;
                has_prev[real_v] = true;
                break; // 一个点只能连一条出边
            }
        }
    }

    // 输出每根柱子
    for (int i = 1; i <= num_balls; i++) {
        // 如果 i 没有前驱，说明它是柱子最下面的球
        if (!has_prev[i]) {
            int curr = i;
            while (curr != 0) {
                cout << curr << (nxt_ball[curr] == 0 ? "" : " ");
                curr = nxt_ball[curr];
            }
            cout << "\n";
        }
    }

    return 0;
}
