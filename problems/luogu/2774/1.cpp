/**
 * Author by Rainboy blog: https://rainboylv.com github : https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * date: 2026-01-18 20:12:26
 */

#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e6+5; // 点 (N*M 最大 10000, 够用)
const int maxe = 2e6+5; // 边 (网格图边数约为 4*N*M, 够用)
const long long INF = 1e18;

// 存图的模板开始 ==========================================

struct linkList {
    typedef struct {int u,v; long long w; int next;} edge; // 注意 w 改为 long long
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

    void add(int u,int v, long long w=0){ // w 改为 long long
        e[edge_cnt] = {u,v,w,h[u]};
        h[u] = edge_cnt++;
    }
    
    //下标访问
    edge& operator[](int i){ return e[i]; }

#ifdef __cpp_range_based_for
    // 策略A: 获取整条边
    struct UseEdge {
        using ReturnType = edge&;
        static ReturnType get(linkList* p, int i) { return p->e[i]; }
    };
    // 策略B: 只获取邻接点v
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
        e.reset(); // 重置边
        level.resize(n+5);
        cur.resize(n+5);
        this->n = n;
    }
    
    void addEdge(int u, int v, long long cap) {
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
                int v = e[i].v; 
                long long cap = e[i].w;
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
            flow += dfs(s, t, INF);
        }
        return flow;
    }
} dinic;

// 模板结束 ==========================================

int m, n; // m行 n列
int s, t; // 源点 汇点
long long total_sum = 0; // 所有数字之和
int grid[105][105];

// 坐标转换：将二维坐标 (x, y) 转换为一维编号
// x: 1..m, y: 1..n
int get_id(int x, int y) {
    return (x - 1) * n + y;
}

// 方向数组
int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};

int main() {
    ios::sync_with_stdio(0); cin.tie(0);

    cin >> m >> n; // 注意先读行数 m，再读列数 n

    s = 0;
    t = m * n + 1;
    
    // 初始化 Dinic，总点数约为 m*n + 2
    dinic.init(t + 1);

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> grid[i][j];
            total_sum += grid[i][j];
        }
    }

    // 建图
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            int u = get_id(i, j);

            // 根据 (i+j) 的奇偶性判断是二分图的哪一侧
            if ((i + j) % 2 == 0) {
                // 偶数点（黑色）：源点 -> u
                dinic.addEdge(s, u, grid[i][j]);

                // 黑色点向四周相邻点连边 (容量无穷大)
                for (int k = 0; k < 4; k++) {
                    int nx = i + dx[k];
                    int ny = j + dy[k];
                    if (nx >= 1 && nx <= m && ny >= 1 && ny <= n) {
                        int v = get_id(nx, ny);
                        dinic.addEdge(u, v, INF);
                    }
                }
            } else {
                // 奇数点（白色）：u -> 汇点
                dinic.addEdge(u, t, grid[i][j]);
            }
        }
    }

    // 最大权独立集 = 总权值 - 最小割(最大流)
    long long min_cut = dinic.maxFlow(s, t);
    cout << total_sum - min_cut << "\n";

    return 0;
}
