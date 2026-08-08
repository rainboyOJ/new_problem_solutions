/**
 * Author by Rainboy blog: https://rainboylv.com github : https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * date: 2026-01-28 14:04:07
 */

#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e6+5; // 点
const int maxe = 2e6+5; // 边 (注意：要是题目边数的2倍)
const long long INF = 1e18; // 无穷大容量

// 全局变量定义
int n, m; 
int a[105];         // 寿司代号
int d[105][105];    // 美味度
int id[105][105];   // 区间[i,j]对应的图节点编号
int type_id[1005];  // 代号x对应的图节点编号
int s, t;           // 源点 汇点

// 存图的模板
//oisnip_begin code/graph/linklist.cpp 内容开始
struct linkList {
    typedef struct {int u,v; long long w; int next;} edge; // 修改: w改为long long防溢出
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

    void add(int u,int v,long long w=0){
        e[edge_cnt] = {u,v,w,h[u]};
        h[u] = edge_cnt++;
    }
    void add2(int u,int v,long long w=0){
        add(u,v,w);
        add(v,u,w);
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
        int i;          
        linkList* p;    
        BaseIterator(linkList* p, int i) : p(p), i(i) {}
        BaseIterator& operator++() { i = p->e[i].next; return *this; }
        bool operator!=(const BaseIterator& oth) { return i != oth.i; }
        typename Getter::ReturnType operator*() { return Getter::get(p, i); }
    };
    using Iterator    = BaseIterator<UseEdge>;
    using AdjIterator = BaseIterator<UseAdj>;
    template<typename IterT>
    struct BaseRange {
        int start;
        linkList* p;
        BaseRange(linkList* p, int start) : p(p), start(start) {}
        IterT begin() { return IterT(p, p->h[start]); }
        IterT end()   { return IterT(p, -1); }
    };
    BaseRange<Iterator> operator()(int u) { return BaseRange<Iterator>(this, u); }
    BaseRange<AdjIterator> adj(int u) { return BaseRange<AdjIterator>(this, u); }
#endif
} e;
//oisnip_end code/graph/linklist.cpp 内容结束


// Dinic算法最大流模板 - 基于linkList存图
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
            flow += dfs(s, t, INF); // 修改: 使用 long long INF
        }
        return flow;
    }
} dinic;

// 全局变量用于统计所有正权值的总和
long long total_positive_weight = 0;

void init(){
    // 1. 输入处理
    cin >> n >> m;
    for(int i = 1; i <= n; i++) cin >> a[i];
    for(int i = 1; i <= n; i++){
        for(int j = i; j <= n; j++){
            cin >> d[i][j];
        }
    }

    // 2. 节点编号分配
    // S=0, T由最后决定
    // 1..CNT 为区间节点
    // 之后为代号节点
    int node_cnt = 0;
    
    // 给所有区间 [i,j] 分配节点ID
    for(int i = 1; i <= n; i++){
        for(int j = i; j <= n; j++){
            id[i][j] = ++node_cnt;
        }
    }
    
    // 给所有出现的代号分配节点ID
    // 代号范围是1-1000，可以用数组映射
    memset(type_id, 0, sizeof(type_id));
    for(int i = 1; i <= n; i++){
        if(type_id[a[i]] == 0) {
            type_id[a[i]] = ++node_cnt;
        }
    }

    s = 0;
    t = node_cnt + 1;
    dinic.init(t); // 初始化Dinic，大小为总节点数

    // 3. 建图 (最大权闭合子图模型)
    
    // 处理区间节点
    for(int i = 1; i <= n; i++){
        for(int j = i; j <= n; j++){
            int u = id[i][j];
            int val = d[i][j];
            
            // 特殊处理单点：减去常数项成本 a[i]
            // 题目公式成本 = m*x^2 + c*x。
            // 这里处理 c*x 部分：每吃一种代号为x的寿司，就减去x
            if(i == j) {
                val -= a[i];
            }

            // 正权连S，负权连T
            if(val > 0) {
                total_positive_weight += val;
                dinic.addEdge(s, u, val);
            } else if(val < 0) {
                dinic.addEdge(u, t, -val);
            }

            // 建立依赖关系 (无穷大边)
            if(i < j) {
                // 区间 [i,j] 依赖于 [i+1, j] 和 [i, j-1]
                // 选了父必须选子 -> 父连向子
                dinic.addEdge(u, id[i+1][j], INF);
                dinic.addEdge(u, id[i][j-1], INF);
            } else if(i == j) {
                // 单点 [i,i] 依赖于它的代号节点
                // 选了该寿司，必须支付该代号的固定成本 mx^2
                dinic.addEdge(u, type_id[a[i]], INF);
            }
        }
    }

    // 处理代号节点
    // 只要选择了某个代号的寿司（无论多少个），都要支付 mx^2
    // 代号节点连向 T，容量为 mx^2 (这是成本)
    // 这里的 x 就是代号值
    for(int x = 1; x <= 1000; x++){
        if(type_id[x]) {
            int u = type_id[x];
            long long cost = (long long)m * x * x;
            dinic.addEdge(u, t, cost);
        }
    }
}

// 使用示例：
int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    init();
    
    // 最大权闭合子图结论：最大收益 = 所有正权值之和 - 最小割(最大流)
    long long max_profit = total_positive_weight - dinic.maxFlow(s, t);
    
    cout << max_profit << "\n";
  
    return 0;
}

