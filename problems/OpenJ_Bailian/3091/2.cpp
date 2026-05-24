#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

const int MAXN = 1005;  // 景点数 N <= 1000
const int MAXM = 2005;  // 道路数 R <= 1000 (无向边需 * 2)

struct EBCC_TwoPass {
    // ---------------- 图存储 (链式前向星) ----------------
    struct Edge {
        int to;
        int next;
    } e[MAXM]; // 边数组
    int head[MAXN], tot;
    
    // ---------------- Pass 1: 找桥变量 ----------------
    int dfn[MAXN], low[MAXN], timer;
    bool is_bridge[MAXM]; // 标记边的编号是否为桥

    // ---------------- Pass 2: 染色变量 ----------------
    int bcc_id[MAXN]; // 每个点属于哪个分量
    int bcc_cnt;      // 分量总数

    // 初始化函数 (多组数据必备)
    void init(int n) {
        tot = 0;
        timer = 0;
        bcc_cnt = 0;
        // 初始化 head 为 -1
        memset(head, -1, sizeof(int) * (n + 1));
        // 清空 Tarjan 相关数组
        memset(dfn, 0, sizeof(int) * (n + 1));
        memset(low, 0, sizeof(int) * (n + 1));
        // 清空染色数组
        memset(bcc_id, 0, sizeof(int) * (n + 1));
        // 清空桥标记 (最大边数)
        memset(is_bridge, 0, sizeof(is_bridge));
    }

    // 加边 (无向图需调用两次，但在外部调用，这里只负责存一条有向的)
    void add_edge_internal(int u, int v) {
        e[tot].to = v;
        e[tot].next = head[u];
        head[u] = tot++;
    }

    // Pass 1: Tarjan 找桥
    // u: 当前点, in_edge: 走到 u 的那条边的编号
    void tarjan(int u, int in_edge) {
        dfn[u] = low[u] = ++timer;
        
        for (int i = head[u]; i != -1; i = e[i].next) {
            int v = e[i].to;
            
            // 核心技巧：如果是刚才走过来的反向边，直接跳过
            // 0^1=1, 1^1=0, 2^1=3...
            if (i == (in_edge ^ 1)) continue; 

            if (!dfn[v]) {
                tarjan(v, i);
                low[u] = min(low[u], low[v]);
                
                // 桥的判定
                if (low[v] > dfn[u]) {
                    is_bridge[i] = true;     // 正向边标记为桥
                    is_bridge[i ^ 1] = true; // 反向边也标记为桥
                }
            } else {
                low[u] = min(low[u], dfn[v]);
            }
        }
    }

    // Pass 2: DFS 染色
    // id: 当前分量的编号
    void dfs_color(int u, int id) {
        bcc_id[u] = id;
        for (int i = head[u]; i != -1; i = e[i].next) {
            int v = e[i].to;
            // 如果这条边是被标记的桥，则视为不通，不走
            // 如果对面已经染过色，也不走
            if (is_bridge[i]) continue;
            if (bcc_id[v]) continue;
            
            dfs_color(v, id);
        }
    }

    // 主处理流程
    void solve(int n) {
        // 第一步：找桥 (图连通，从1开始即可)
        tarjan(1, -1); 

        // 第二步：染色
        for (int i = 1; i <= n; i++) {
            if (!bcc_id[i]) {
                bcc_cnt++;
                dfs_color(i, bcc_cnt);
            }
        }
    }
} solver;

// 缩点树的度数数组
int degree[MAXN]; 

int main() {
    // 优化 IO
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, r;
    while (cin >> n >> r) {
        solver.init(n);

        for (int i = 0; i < r; i++) {
            int u, v;
            cin >> u >> v;
            // 手动加双向边，利用 tot 0,1 配对的特性
            solver.add_edge_internal(u, v);
            solver.add_edge_internal(v, u);
        }

        // 运行 Two-pass 算法
        solver.solve(n);

        // 如果整个图就是一个边双连通分量，不需要加边
        if (solver.bcc_cnt == 1) {
            cout << 0 << "\n";
            continue;
        }

        // 计算缩点树中每个节点的度数
        // 清空度数数组 (只用到 1 ~ bcc_cnt)
        for(int i = 1; i <= solver.bcc_cnt; i++) degree[i] = 0;

        // 遍历所有节点的所有出边
        for (int u = 1; u <= n; u++) {
            for (int i = solver.head[u]; i != -1; i = solver.e[i].next) {
                int v = solver.e[i].to;
                // 如果边两端颜色不同，说明这是连接两个分量的桥
                if (solver.bcc_id[u] != solver.bcc_id[v]) {
                    degree[solver.bcc_id[u]]++;
                }
            }
        }

        // 统计叶子节点 (度数为1)
        int leaf_count = 0;
        for (int i = 1; i <= solver.bcc_cnt; i++) {
            // 注意：上面的循环对每个分量的出度都正确累加了
            // 比如分量 A 有一条桥连向 B，遍历 A 中节点时 degree[A]++
            // 不需要除以 2，因为我们判断的是 degree == 1
            if (degree[i] == 1) {
                leaf_count++;
            }
        }

        // 答案公式: (leaf + 1) / 2
        cout << (leaf_count + 1) / 2 << "\n";
    }

    return 0;
}
