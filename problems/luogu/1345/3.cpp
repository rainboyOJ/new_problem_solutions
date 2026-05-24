/**
 * Author by Rainboy blog: https://rainboylv.com github : https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * date: 2026-01-17 19:29:00
 */

#include <bits/stdc++.h>
using namespace std;

// 【修正1】点数少，int范围足够。INF设为1e9防止溢出int
const int INF = 1e9; 
const int maxn = 1e6+5; 
const int maxe = 2e6+5; 

int n, m; 
int c1, c2;
int s, t; 

//oisnip_begin code/graph/linklist.cpp
struct linkList {
    typedef struct {int u,v,w,next;} edge;
    edge e[maxe];
    int h[maxn],edge_cnt=0;
    linkList(){ reset(); }

    void reset() {
        edge_cnt=0;
        memset(h,-1,sizeof(h));
    }

    // 【注意】这里 w 是 int，传入的值不能超过 int 范围
    void add(int u,int v,int w=0){
        e[edge_cnt] = {u,v,w,h[u]};
        h[u] = edge_cnt++;
    }
    
    edge& operator[](int i){ return e[i]; }
} e;
//oisnip_end code/graph/linklist.cpp

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
    
    // 【修正2】cap 使用 int 即可
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
                int v = e[i].v;
                int cap = e[i].w; 
                // 如果 cap 因为溢出变成负数，这里就会断掉
                if (cap > 0 && level[v] < 0) {
                    level[v] = level[u] + 1;
                    q.push(v);
                }
            }
        }
        return level[t] >= 0;
    }
    
    int dfs(int u, int t, int preFlow) {
        if (u == t || preFlow == 0) return preFlow;
        int flow = 0;
        
        for (int& cid = cur[u]; cid != -1; cid = e[cid].next) {
            auto& edge = e[cid]; 
            int to = edge.v;
            int cap = edge.w;
            
            if (level[u] + 1 != level[to] || cap <= 0) continue;
            
            int tr = dfs(to, t, min(preFlow, cap));

            e[cid].w -= tr ;     
            e[cid ^ 1].w += tr; 
            flow += tr;
            preFlow -= tr;
            if (preFlow == 0) break;
        }
        if (flow == 0) level[u] = -1;
        return flow;
    }
    
    int maxFlow(int s, int t) {
        int flow = 0;
        while (bfs(s, t)) {  
            for (int i = 0; i <= n; i++) cur[i] = e.h[i];  
            flow += dfs(s, t, INF);
        }
        return flow;
    }
} dinic;

void init(){
    cin >> n >> m >> c1 >> c2;
    dinic.init(2 * n + 5);
    
    // 1. 拆点建边
    for (int i = 1; i <= n; i++) {
        int u_in = i;
        int u_out = i + n;
        
        int cap = 1; 
        if (i == c1 || i == c2) cap = INF; // 这里的 INF 是 1e9，int 能装下
        
        dinic.addEdge(u_in, u_out, cap);
    }

    // 2. 线路建边
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        dinic.addEdge(u + n, v, INF);
        dinic.addEdge(v + n, u, INF);
    }

    s = c1;
    t = c2 + n;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    init();
    cout << dinic.maxFlow(s, t) << "\n";
    return 0;
}

