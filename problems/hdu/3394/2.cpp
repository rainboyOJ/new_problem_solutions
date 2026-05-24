/**
 * Author by Rainboy blog: https://rainboylv.com github : https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * date: 2026-01-09 15:42:58
 */
#include <bits/stdc++.h>
using namespace std;
typedef  long long ll;
typedef  unsigned long long ull;

const int maxn = 2e6+5;
const int maxe = 4e6+5;

int n, m;

// ---------------- TarjanEBCC 模板 (Two-pass) ----------------
struct TarjanEBCC {
    // ---------------- 图存储 ----------------
    struct edge {
        int u, v, next;
    } e[maxe * 2];
    int head[maxn], e_cnt;
    
    // ---------------- 找桥变量 ----------------
    int dfn[maxn], low[maxn], timer;
    bool is_bridge[maxe * 2]; 

    // ---------------- 染色变量 ----------------
    int bcc_id[maxn]; // 每个点所属的分量编号
    int bcc_cnt;      // 边双连通分量总数

    void init(int n) {
        e_cnt = 0;
        timer = 0;
        bcc_cnt = 0;
        for (int i = 0; i <= n; i++) {
            head[i] = -1;
            dfn[i] = low[i] = 0;
            bcc_id[i] = 0;
        }
        // 清空桥标记，注意要清空到当前最大边数，这里简化处理清空前 2*m
        // 为安全起见，实际比赛中建议按 e_cnt 清空或者用 vector
        memset(is_bridge, 0, sizeof(bool) * (2 * m + 10)); 
    }

    void add_edge(int u, int v) {
        e[e_cnt] = {u, v, head[u]};
        head[u] = e_cnt++;
        
        e[e_cnt] = {v, u, head[v]};
        head[v] = e_cnt++;
    }

    // pass 1: tarjan 找桥
    void tarjan(int u, int in_edge) {
        dfn[u] = low[u] = ++timer;
        for (int i = head[u]; ~i; i = e[i].next) {
            int v = e[i].v;
            
            // 这里的 in_edge 是进入 u 的边的编号
            // i ^ 1 是反向边，即不能走回父亲的边
            if (i != (in_edge ^ 1)) { 
                if (!dfn[v]) {
                    tarjan(v, i);
                    low[u] = min(low[u], low[v]);
                    if (low[v] > dfn[u]) {
                        is_bridge[i] = is_bridge[i ^ 1] = true;
                    }
                } else {
                    low[u] = min(low[u], dfn[v]);
                }
            }
        }
    }

    // pass 2: dfs 染色
    void dfs_color(int u, int id) {
        bcc_id[u] = id;
        for (int i = head[u]; ~i; i = e[i].next) {
            int v = e[i].v;
            if (!is_bridge[i] && !bcc_id[v]) {
                dfs_color(v, id);
            }
        }
    }

    // 主过程
    void solve(int n) {
        // 1. 找桥
        for (int i = 1; i <= n; i++) {
            if (!dfn[i]) tarjan(i, -1);
        }

        // 2. 染色
        for (int i = 1; i <= n; i++) {
            if (!bcc_id[i]) {
                bcc_cnt++;
                dfs_color(i, bcc_cnt);
            }
        }
    }

} ebcc;

// 辅助统计数组
int cnt_v[maxn]; // 每个 BCC 中的点数
int cnt_e[maxn]; // 每个 BCC 中的边数

void solve_problem() {
    ebcc.init(n);
    
    // 读入数据并建图
    for(int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        // 题目输入 0~n-1，转为 1~n
        ebcc.add_edge(u + 1, v + 1);
    }

    // 运行 Tarjan 求 e-BCC
    ebcc.solve(n);

    // --- 统计答案 ---
    
    // 初始化统计数组
    for(int i = 1; i <= ebcc.bcc_cnt; i++) {
        cnt_v[i] = 0;
        cnt_e[i] = 0;
    }

    // 1. 统计每个 BCC 的点数
    for(int i = 1; i <= n; i++) {
        if(ebcc.bcc_id[i]) {
            cnt_v[ebcc.bcc_id[i]]++;
        }
    }

    int bridge_ans = 0;
    int clash_ans = 0;

    // 2. 遍历所有边 (每次步进2，只看正向边)
    for(int i = 0; i < ebcc.e_cnt; i += 2) {
        if(ebcc.is_bridge[i]) {
            bridge_ans++;
        } else {
            // 如果不是桥，属于某个 BCC
            int u = ebcc.e[i].u;
            // 累加该 BCC 的边数
            cnt_e[ebcc.bcc_id[u]]++;
        }
    }

    // 3. 计算冲突边
    for(int i = 1; i <= ebcc.bcc_cnt; i++) {
        // 如果 BCC 内 边数 > 点数，说明是复杂环，所有边冲突
        if(cnt_e[i] > cnt_v[i]) {
            clash_ans += cnt_e[i];
        }
    }

    cout << bridge_ans << " " << clash_ans << "\n";
}

signed main () {
    ios::sync_with_stdio(false); cin.tie(0);
    while (cin >> n >> m) {
        if(n == 0 && m == 0) break;
        solve_problem();
    }
    return 0;
}
