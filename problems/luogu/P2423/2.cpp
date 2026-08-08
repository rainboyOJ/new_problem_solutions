/**
 * Author by Rainboy blog: https://rainboylv.com github : https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * date: 2026-01-13 22:26:35
 * Problem: P2423 [HEOI2012] 朋友圈
 * Algorithm: Max Independent Set on Bipartite Graph (Maximum Clique in Complement)
 * * 核心思路:
 * 1. A国人之间: 只有奇偶性不同才能做朋友。这意味A国人中，朋友圈最多只能有2个人(一奇一偶)，或者1个人，或者0人。
 * -> 我们可以枚举A国人在朋友圈中的子集 S_A (大小为0, 1, 2)。
 * * 2. B国人之间: 朋友条件复杂。我们看"非朋友"条件(补图):
 * 非朋友 <=> 奇偶性不同 且 (a|b) 二进制由偶数个1。
 * 这意味着 B国人的补图是一个【二分图】(左边奇数，右边偶数)。
 * 原图的最大团(朋友圈) = 补图的最大独立集。
 * 二分图最大独立集 = 总点数 - 二分图最大匹配。
 * * 3. 算法流程:
 * - 预处理 B 国人补图的边。
 * - 枚举 A 国选出的集合 S_A (空, 1个, 2个一奇一偶)。
 * - 对于确定的 S_A，筛选出 B 国中所有能与 S_A 中所有人做朋友的候选集合 B'。
 * - 在 B' 构成的补图中求最大匹配，进而得到 B' 的最大独立集大小。
 * - 答案 = |S_A| + |B'的最大独立集|。
 */

#include <bits/stdc++.h>
using namespace std;

// 调整数组大小以适应题目范围
// 第一类数据: A, B <= 200
// 第二类数据: A <= 10, B <= 3000
const int maxn = 3005 + 5; // B国人数最大3000，加上源汇点
const int maxe = 3000 * 3000 / 2 + 5; // B国补图边数可能较多
const long long INF = 1e18;

// 全局变量
int A_cnt, B_cnt, M_rel;
int A_val[205]; // A国人友善值
int B_val[3005]; // B国人友善值
bool AB_friend[205][3005]; // AB之间是否朋友
int s, t; // 源点 汇点

// 存图的模板
struct linkList {
    typedef struct {int u,v,w,next;} edge;
    edge e[maxe];
    int h[maxn], edge_cnt=0;
    
    linkList(){
        reset();
    }

    void reset() {
        edge_cnt=0;
        memset(h, -1, sizeof(h)); // 注意：如果maxn很大，memset可能慢，需注意
    }

    void add(int u, int v, int w=0){
        e[edge_cnt] = {u, v, w, h[u]};
        h[u] = edge_cnt++;
    }
    
    edge& operator[](int i){ return e[i]; }
} e;

// Dinic算法最大流模板
struct Dinic {
    vector<int> level, cur;
    int n;
    
    void init(int n) {
        e.edge_cnt = 0;
        // 这里为了效率，只重置 0 到 n 的 head
        // memset(e.h, -1, sizeof(e.h)); // 全局重置太慢
        for(int i = 0; i <= n; ++i) e.h[i] = -1;

        level.assign(n + 5, 0);
        cur.assign(n + 5, 0);
        this->n = n;
    }
    
    void addEdge(int u, int v, int cap) {
        e.add(u, v, cap);    // 正向边
        e.add(v, u, 0);      // 反向边
    }
    
    bool bfs(int s, int t) {
        fill(level.begin(), level.end(), -1);
        queue<int> q;
        level[s] = 0;
        q.push(s);
        
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            
            for(int i = e.h[u]; ~i; i = e.e[i].next) {
                int v = e.e[i].v;
                int cap = e.e[i].w;
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
        
        for (int& cid = cur[u]; cid != -1; cid = e.e[cid].next) {
            int v = e.e[cid].v;
            int cap = e.e[cid].w;
            
            if (level[u] + 1 != level[v] || cap <= 0) continue;
            
            long long tr = dfs(v, t, min(preFlow, (long long)cap));
            
            e.e[cid].w -= tr;
            e.e[cid ^ 1].w += tr;
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
            for (int i = 0; i <= n; i++) cur[i] = e.h[i];
            flow += dfs(s, t, LLONG_MAX);
        }
        return flow;
    }
} dinic;

// --- 题目特定逻辑 ---

// B国补图的边：只有奇偶不同且 (a|b)有偶数个1 时才连边(代表冲突)
// 我们可以预处理这些关系
vector<int> B_comp_adj[3005]; // 存储B国人i在补图中的邻居

// 检查B国两人在补图中是否有边（即是否由于条件限制不能做朋友）
bool check_B_conflict(int i, int j) {
    // 只有奇偶性不同才可能在补图中有边(否则一定是朋友)
    // 题目: B国朋友条件: 奇偶相同 OR (a|b)有奇数个1
    // 反之(非朋友): 奇偶不同 AND (a|b)有偶数个1
    int val_i = B_val[i];
    int val_j = B_val[j];
    if ((val_i % 2) == (val_j % 2)) return false; // 奇偶相同一定是朋友，无冲突
    
    unsigned int or_val = (unsigned int)(val_i | val_j);
    int ones = __builtin_popcount(or_val);
    
    return (ones % 2 == 0); // 偶数个1则不是朋友(有冲突)
}

// 求解当前情况下的最大朋友圈大小
// A_subset: 选中的A国人列表
// current_ans: 当前已知的最大答案(用于剪枝)
int solve_case(const vector<int>& A_subset, int current_ans) {
    // 1. 筛选候选的 B 国人
    // B'中的人必须和 A_subset 中所有人都互为朋友
    vector<int> B_candidates;
    for (int j = 1; j <= B_cnt; ++j) {
        bool ok = true;
        for (int a_idx : A_subset) {
            if (!AB_friend[a_idx][j]) {
                ok = false;
                break;
            }
        }
        if (ok) B_candidates.push_back(j);
    }

    // 2. 剪枝
    // 如果 A选的人数 + B候选人数 <= 当前最优解，就算B全选也不可能更优
    if ((int)A_subset.size() + (int)B_candidates.size() <= current_ans) {
        return 0;
    }

    // 3. 构建二分图求最大匹配
    // B_candidates 构成了补图的一个诱导子图
    // 这个子图本身也是二分图(左:奇数, 右:偶数)
    // 节点编号映射: 
    // S=0, T=B_cnt+1
    // B国人保持原编号 1~B_cnt (虽然只有部分在图中)
    
    s = 0; 
    t = B_cnt + 1;
    dinic.init(t);

    for (int u : B_candidates) {
        if (B_val[u] % 2 != 0) { // 奇数: 源点 -> u
            dinic.addEdge(s, u, 1);
            // 连向偶数邻居
            for (int v_neighbor : B_comp_adj[u]) {
                // 注意: 邻居必须也在候选集中
                // 为了快速判断，这里我们可以不做O(N)查找，而是构建图时只处理存在的点
                // 但由于边表预处理了，这里需要确认 v_neighbor 是否在 B_candidates 中
                // 一个简单方法是标记数组，或者直接在这里不做判断，
                // 但为了正确性，必须保证流只在 candidates 之间流动。
                // 更好的方法：只添加两端都在 candidates 中的边。
            }
        } else { // 偶数: v -> 汇点
            dinic.addEdge(u, t, 1);
        }
    }

    // 添加内部边 (只在 candidates 之间)
    // 为了效率，我们可以用一个 bool 数组标记 candidates
    static bool is_candidate[3005];
    // 清空标记 (注意 B_cnt 可能较大，只清空用到的)
    // 但为了安全，循环清空或者memset
    for(int x : B_candidates) is_candidate[x] = true;

    for (int u : B_candidates) {
        if (B_val[u] % 2 != 0) { // 只处理左部点发出的边
            for (int v : B_comp_adj[u]) {
                if (is_candidate[v]) {
                    dinic.addEdge(u, v, 1);
                }
            }
        }
    }
    
    // 恢复标记 (回溯)
    for(int x : B_candidates) is_candidate[x] = false;

    int max_match = dinic.maxFlow(s, t);
    int max_independent_set_B = (int)B_candidates.size() - max_match;
    
    return (int)A_subset.size() + max_independent_set_B;
}

void solve() {
    // 读入 A, B, M
    cin >> A_cnt >> B_cnt >> M_rel;
    
    // 读入 A 值
    vector<int> A_odds, A_evens;
    for (int i = 1; i <= A_cnt; ++i) {
        cin >> A_val[i];
        if (A_val[i] % 2 != 0) A_odds.push_back(i);
        else A_evens.push_back(i);
    }
    
    // 读入 B 值
    for (int i = 1; i <= B_cnt; ++i) {
        cin >> B_val[i];
    }
    
    // 初始化关系
    // 1. A-B 关系
    for (int i = 1; i <= A_cnt; ++i) 
        for (int j = 1; j <= B_cnt; ++j) 
            AB_friend[i][j] = false;
            
    for (int i = 0; i < M_rel; ++i) {
        int u, v;
        cin >> u >> v;
        AB_friend[u][v] = true;
    }
    
    // 2. B-B 补图关系预处理
    for (int i = 1; i <= B_cnt; ++i) B_comp_adj[i].clear();
    
    // 只需枚举奇数和偶数之间的对
    // 为了方便，我们可以直接双重循环，或者分奇偶列表
    vector<int> B_odds, B_evens;
    for (int i = 1; i <= B_cnt; ++i) {
        if (B_val[i] % 2 != 0) B_odds.push_back(i);
        else B_evens.push_back(i);
    }
    
    for (int u : B_odds) {
        for (int v : B_evens) {
            if (check_B_conflict(u, v)) {
                // 补图中有边 (u奇, v偶)
                B_comp_adj[u].push_back(v);
                // B_comp_adj[v].push_back(u); // Dinic建图只需要单向: 左->右
            }
        }
    }

    int ans = 0;

    // --- 情况 0: 不选 A 国人 ---
    ans = max(ans, solve_case({}, ans));

    // --- 情况 1: 选 1 个 A 国人 ---
    for (int i = 1; i <= A_cnt; ++i) {
        ans = max(ans, solve_case({i}, ans));
    }

    // --- 情况 2: 选 2 个 A 国人 (必须一奇一偶) ---
    // A国人朋友条件: (a^b)%2==1 => 奇偶性不同
    for (int u : A_odds) {
        for (int v : A_evens) {
            // 这两个人必须互为朋友才能同时选
            // 奇偶不同已经是前提，所以一定是朋友?
            // 题目: A国人 (a^b)%2=1 是朋友。是的，只要奇偶不同就是朋友。
            ans = max(ans, solve_case({u, v}, ans));
        }
    }

    cout << ans << endl;
}

int main() {
    // 优化 I/O
    ios::sync_with_stdio(0); cin.tie(0);
    
    int T_cases;
    cin >> T_cases;
    while (T_cases--) {
        solve();
    }
    
    return 0;
}
