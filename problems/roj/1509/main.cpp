/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-04 22:40
 * update_at: 2026-10-05 05:28
 */
// 差分约束 + SPFA 最长路：
// 设 S(x) = Z 中落在 [0, x] 的整数个数，则
//   1. 区间要求：S(b_i) >= S(a_i - 1) + c_i
//   2. 前缀不减：S(x) >= S(x - 1)
//   3. 每个整数至多选一次：S(x - 1) >= S(x) - 1
// 三类不等式全是 >= 形式，各建一条边后求最长路，即得逐分量最小的可行解。
// |Z| 的最小值 = S(max b) - S(-1)。

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 50005;   // 节点数：坐标 -1 ~ 50000，编号 = 坐标 + 1
const int MAXM = 200005;  // 边数：n 条区间边 + 每对相邻点两条链边

typedef long long ll;

// 链式前向星存图
int head[MAXN], to[MAXM], nxt[MAXM], edge_cnt;
int weight[MAXM];          // 边权：区间边为 c_i，链边为 0 或 -1

int n;                     // 区间个数
int max_b;                 // 最右端点，编号上界为 max_b + 1
int dist[MAXN];            // 最长路距离，即分量最小的可行前缀计数
bool in_queue[MAXN];       // 该节点当前是否在 SPFA 队列中

// 加一条 u -> v、权 w 的边。
void add_edge(int u, int v, int w) {
    edge_cnt++;
    to[edge_cnt] = v;
    weight[edge_cnt] = w;
    nxt[edge_cnt] = head[u];
    head[u] = edge_cnt;
}

// SPFA 求最长路：dist 全部初始化为 0 并全部入队，等价于超级源点连 0 权边。
// 题目保证 c_i <= b_i - a_i + 1，图中无正环，队列必然收敛。
void spfa_longest() {
    queue<int> q;
    for (int i = 0; i <= max_b + 1; i++) {
        dist[i] = 0;
        in_queue[i] = true;
        q.push(i);
    }
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        in_queue[u] = false;
        int du = dist[u];   // 弹出时才读取，保证用的是 u 的最新距离
        for (int i = head[u]; i != 0; i = nxt[i]) {
            int v = to[i];
            if (du + weight[i] > dist[v]) {
                dist[v] = du + weight[i];
                if (!in_queue[v]) {
                    in_queue[v] = true;
                    q.push(v);
                }
            }
        }
    }
}

void solve() {
    scanf("%d", &n);
    max_b = 0;
    for (int i = 1; i <= n; i++) {
        int a, b, c;
        scanf("%d %d %d", &a, &b, &c);
        // 区间边：a_i - 1 -> b_i 权 c_i；编号 = 坐标 + 1，免去 a_i = 0 的特判
        add_edge(a, b + 1, c);
        if (b > max_b) max_b = b;
    }
    // 相邻点之间的两条链边，把每个前缀的增量夹在 {0, 1} 里
    for (int v = 1; v <= max_b + 1; v++) {
        add_edge(v - 1, v, 0);    // S(坐标 v) >= S(坐标 v - 1)
        add_edge(v, v - 1, -1);   // S(坐标 v - 1) >= S(坐标 v) - 1
    }

    spfa_longest();

    // 最少选点数 = S(max b) - S(-1)；比最右端点更右的数不属于任何区间，不必考虑
    printf("%d\n", dist[max_b + 1] - dist[0]);
}

int main() {
    solve();
    return 0;
}
