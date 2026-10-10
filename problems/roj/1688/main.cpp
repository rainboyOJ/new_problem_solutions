/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-07 15:30
 * update_at: 2026-10-07 15:30
 */
// main.cpp：两次 BFS 求 1 到 n 的最短路中颜色序列字典序最小的那条。
// 题目数据默认 ll；本题所有量都在 int 范围内（n,m ≤ 2·10^5，颜色 ≤ 10^9），
// 大数组一律用 int，把峰值内存压进 64MB 的时限。
#include <cstdio>
#include <climits>

typedef long long ll;

const int MAXN = 100005;      // 点数上限
const int MAXM = 200005 * 2;  // 边数上限：一条无向边存两条半边

// 无向图用链式前向星；一个 Edge 就是一条半边，字段聚合在一个 struct 里
struct Edge {
    int to;     // 这条半边指向的点
    int color;  // 这条边的颜色
    int nxt;    // 同一出发点上的下一条半边，0 表示结束
};

Edge edge[MAXM];     // 半边池，edge[i] 是第 i 条半边
int head[MAXN];      // head[u]：从 u 出发的第一条半边编号
int edge_cnt;        // 已加入的半边数量

int dist_to_n[MAXN]; // dist_to_n[v]：v 到 n 的最短边数，-1 表示不可达
int in_layer[MAXN];  // in_layer[v]：v 是否已经作为某个最优前缀的终点入层
int queue_bfs[MAXN]; // 反向 BFS 用的手写队列
int cur_layer[MAXN]; // 当前层的节点
int nxt_layer[MAXN]; // 下一层的节点
int out_seq[MAXN];   // 路径上的颜色序列（长度就是最短路长度 D）

// 加入一条无向边，两个方向各存一条半边
void add_edge(int u, int v, int c) {
    edge_cnt++;
    edge[edge_cnt].to = v;
    edge[edge_cnt].color = c;
    edge[edge_cnt].nxt = head[u];
    head[u] = edge_cnt;

    edge_cnt++;
    edge[edge_cnt].to = u;
    edge[edge_cnt].color = c;
    edge[edge_cnt].nxt = head[v];
    head[v] = edge_cnt;
}

// 从 n 反向 BFS，求出每个点到 n 的最短边数
void bfs_reverse(int n) {
    for (int i = 1; i <= n; i++) dist_to_n[i] = -1;
    int q_head = 0, q_tail = 0;
    dist_to_n[n] = 0;
    queue_bfs[q_tail++] = n;
    while (q_head < q_tail) {
        int u = queue_bfs[q_head++];
        for (int e = head[u]; e != 0; e = edge[e].nxt) {
            int v = edge[e].to;
            if (dist_to_n[v] == -1) {          // 反向 BFS 首次到达即最短
                dist_to_n[v] = dist_to_n[u] + 1;
                queue_bfs[q_tail++] = v;
            }
        }
    }
}

// 从 1 出发逐层推进，长度已被固定为 D，每层只在"能走完剩余最短路"的
// 出边里取最小颜色，就得到字典序最小的颜色序列；每个点只入层一次，
// 因此所有层的出边扫描量合计 O(n + m)
void build_answer(int n, int& out_len) {
    int D = dist_to_n[1];                  // 最短路长度（边数）
    out_len = 0;
    for (int i = 1; i <= n; i++) in_layer[i] = 0;
    int cur_len = 0;
    cur_layer[cur_len++] = 1;              // 第 0 层的唯一节点
    in_layer[1] = 1;
    while (out_len < D) {
        int target = D - out_len - 1;      // 下一层节点必须满足 dist_to_n == target
        int cmin = INT_MAX;
        for (int i = 0; i < cur_len; i++) {
            int u = cur_layer[i];
            for (int e = head[u]; e != 0; e = edge[e].nxt) {
                int v = edge[e].to;
                if (dist_to_n[v] == target && edge[e].color < cmin) cmin = edge[e].color;
            }
        }
        out_seq[out_len++] = cmin;         // 这一位的颜色确定为 cmin
        int nxt_len = 0;
        for (int i = 0; i < cur_len; i++) {
            int u = cur_layer[i];
            for (int e = head[u]; e != 0; e = edge[e].nxt) {
                int v = edge[e].to;
                // 只保留"走最小颜色且 dist 恰好少 1"的点，它们一定能续走到 n
                if (dist_to_n[v] == target && edge[e].color == cmin && !in_layer[v]) {
                    in_layer[v] = 1;
                    nxt_layer[nxt_len++] = v;
                }
            }
        }
        for (int i = 0; i < nxt_len; i++) cur_layer[i] = nxt_layer[i];
        cur_len = nxt_len;
    }
}

int main() {
    ll T;                                  // 数据组数
    if (scanf("%lld", &T) != 1) return 0;
    while (T--) {
        int n, m;
        scanf("%d %d", &n, &m);
        edge_cnt = 0;                      // 多组数据：邻接表按组重建
        for (int i = 1; i <= n; i++) head[i] = 0;
        for (int i = 0; i < m; i++) {
            int a, b, c;
            scanf("%d %d %d", &a, &b, &c);
            if (a == b) continue;          // 自环不可能落在最短路上，直接丢掉
            add_edge(a, b, c);
        }

        bfs_reverse(n);

        if (dist_to_n[1] == -1) {          // 题面未定义 1 到 n 不连通的情况，约定输出 0 与空行
            printf("0\n\n");
            continue;
        }

        int out_len;
        build_answer(n, out_len);
        printf("%d\n", out_len);
        for (int i = 0; i < out_len; i++)
            printf("%d%c", out_seq[i], i + 1 == out_len ? '\n' : ' ');
    }
    return 0;
}
