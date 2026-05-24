/**
 * Author by Rainboy blog: https://rainboylv.com github : https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * date: 2026-01-12 20:04:52
 * Problem: P2065 [TJOI2011] 卡片
 * Algorithm: Max Flow (Dinic) + Prime Factorization
 */

#include <bits/stdc++.h>
using namespace std;

// 点数预估：蓝色500 + 红色500 + 质数节点(动态)
// 边数预估：S->蓝 + 红->T + 蓝->质数 + 质数->红
const int maxn = 50005; 
const int maxe = 500005; 
const long long INF = 1e18;

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
        level.resize(n+5);
        cur.resize(n+5);
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

// --- 质数筛与分解工具 ---
// int primes[5000], p_cnt = 0;
// bool is_prime[5000];
//
// // 预处理 sqrt(10^7) ≈ 3162 内的质数
// void sieve() {
//     memset(is_prime, true, sizeof(is_prime));
//     is_prime[0] = is_prime[1] = false;
//     for (int i = 2; i < 5000; i++) {
//         if (is_prime[i]) primes[p_cnt++] = i;
//         for (int j = 0; j < p_cnt && i * primes[j] < 5000; j++) {
//             is_prime[i * primes[j]] = false;
//             if (i % primes[j] == 0) break;
//         }
//     }
// }

const int MAX_N = 1000000;  // 最大范围
std::vector<int> primes;
std::vector<bool> is_composite;
int p_cnt= 0;
// bool is_composite[MAX_N + 1];  // true 表示是合数

void get_primes_euler(int n) {
    // 初始化
    // for (int i = 0; i <= n; i++) is_composite[i] = false;
    is_composite.clear();
    is_composite.assign(n+5,0);
    primes.clear();
    
    for (int i = 2; i <= n; i++) {
        if (!is_composite[i]) primes.push_back(i);
        
        for (int j = 0; j < primes.size(); j++) {
            int p = primes[j];
            if (1LL * p * i > n) break;
            
            is_composite[i * p] = true;
            
            // 【核心关键】
            // 如果 i 被 p 整除，说明 i 的最小质因子就是 p。
            // 如果继续枚举下一个素数 p_next (p_next > p)，
            // 构造出的合数 X = i * p_next。
            // X 的最小质因子将会是 p (因为 i 包含因子 p)，而不是 p_next。
            // 这违背了"用最小质因子筛除"的原则，因此必须 break。
            if (i % p == 0) break;
        }
    }
}

// 分解质因数
vector<int> facs;
void get_factors(int x) {
    facs.clear();
    for (int i = 0; i < p_cnt && primes[i] * primes[i] <= x; i++) {
        if (x % primes[i] == 0) {
            facs.push_back(primes[i]);
            while (x % primes[i] == 0) x /= primes[i];
        }
    }
    if (x > 1) facs.push_back(x);
}

int m, n;
map<int, int> p_to_id; // 质数 -> 节点编号 映射
int node_cnt; // 当前节点总数分配器

void solve() {
    cin >> m >> n;
    
    // 节点分配规划:
    // S = 0
    // T = 1
    // Blue Cards: 2 ~ m+1
    // Red Cards: m+2 ~ m+n+1
    // Primes: 从 m+n+2 开始动态分配
    
    int s = 0, t = 1;
    node_cnt = m + n + 2;

    p_to_id.clear();
    
    // 初始化 Dinic，给一个较大的预估值，或者动态扩容
    // 因为这里不知道会有多少质数节点，先给个安全的上限，init 主要负责清空 head 数组
    dinic.init(maxn - 10); 

    // 1. 处理蓝色卡片
    for (int i = 1; i <= m; i++) {
        int val;
        cin >> val;
        int u = i + 1; // 蓝色卡片节点编号
        
        // S -> Blue
        dinic.addEdge(s, u, 1);
        
        // Blue -> Primes
        get_factors(val);
        for (int p : facs) {

            // 一个新的质数,还没有被记录
            if (p_to_id.find(p) == p_to_id.end()) {
                p_to_id[p] = node_cnt++;
            }
            int p_node = p_to_id[p];
            dinic.addEdge(u, p_node, 1);
        }
    }

    // 2. 处理红色卡片
    for (int i = 1; i <= n; i++) {
        int val;
        cin >> val;
        // int v = m + 1 + i + 1; // 红色卡片节点编号 (偏移 m+1)
        int v = m+ i +1;
        
        // Red -> T
        dinic.addEdge(v, t, 1);
        
        // Primes -> Red
        get_factors(val);
        for (int p : facs) {
            if (p_to_id.find(p) == p_to_id.end()) {
                p_to_id[p] = node_cnt++;
            }
            int p_node = p_to_id[p];
            dinic.addEdge(p_node, v, 1);
        }
    }

    // 经过中间层 `primes` 过滤后
    // 1. blue red 的配对 只能 选择 gcd(blue,red) >1 的
    // 2. !!!! 中间层 代表了 一种筛选条件 !!!
    
    // 更新 Dinic 的节点总数，用于循环边界优化
    dinic.n = node_cnt;

    cout << dinic.maxFlow(s, t) << endl;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    get_primes_euler(1e7+1); // 先预处理质数
    p_cnt = primes.size();
    

    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    
    return 0;
}
