/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 05:32
 * update_at: 2026-10-05 05:32
 */
// 差分约束 + 二分答案：
// 设 S(i) = x(0) + x(1) + ... + x(i-1)，其中 x(i) 是 t = i 的被雇佣人数，S(24) = M 为总雇佣人数。
// 每个小时段 i 的在岗人数是起始时刻落在 {i-7, ..., i} (mod 24) 的人数和，写成前缀和之差后，
// 逐条约束都是 S(v) >= S(u) + w 的形式；把 M 用两条互反的边钉死，判定就变成最长路是否出现正环。
// 可行性关于 M 单调（多雇一人只会让人数变多），所以在 [0, N] 上二分最小可行的 M。

#include <bits/stdc++.h>
using namespace std;

const int HOURS = 24;    // 一天 24 个小时段
const int SHIFT = 8;     // 每人连续工作恰好 8 小时
const int NODES = 25;    // 前缀和节点 S(0) ~ S(24)
const int MAXEDGE = 128; // 边数上限：24 * 2 条链边 + 24 条需求边 + 2 条钉死边 = 74

typedef long long ll;

// 链式前向星存图，每条边表示约束 S(v) >= S(u) + w
int head[NODES], to[MAXEDGE], nxt[MAXEDGE], edge_cnt;
int weight[MAXEDGE];

int need[HOURS];    // need[i] = R(i)，第 i 个小时段最少需要的在岗人数
int supply[HOURS];  // supply[i] = 起始时刻为 i 的申请者人数，即 x(i) 的上界
ll dist[NODES];     // 最长路距离，最长路解是逐分量最小的可行前缀和
bool in_queue[NODES];  // 该节点当前是否在 SPFA 队列中
int relax_cnt[NODES];  // 每个点被成功松弛的次数，超过 NODES 次说明存在正环

// 加一条 u -> v、权 w 的边。
void add_edge(int u, int v, int w) {
    edge_cnt++;
    to[edge_cnt] = v;
    weight[edge_cnt] = w;
    nxt[edge_cnt] = head[u];
    head[u] = edge_cnt;
}

// 按假定的总雇佣人数 total 建图（total = S(24)）。
void build_graph(int total) {
    edge_cnt = 0;
    for (int i = 0; i < NODES; i++) head[i] = 0;
    for (int i = 0; i < HOURS; i++) {
        add_edge(i, i + 1, 0);           // S(i+1) >= S(i)：前缀不减，即 x(i) >= 0
        add_edge(i + 1, i, -supply[i]);  // S(i) >= S(i+1) - c(i)：x(i) <= c(i)
    }
    for (int i = 0; i < HOURS; i++) {
        int start = i - SHIFT + 1;  // 覆盖小时段 i 的起始时刻区间左端
        if (start >= 0) {
            add_edge(start, i + 1, need[i]);  // 同一天：S(i+1) - S(start) >= R(i)
        } else {
            // 跨午夜：S(i+1) + (S(24) - S(i+17)) >= R(i)，即 S(i+1) >= S(i+17) + R(i) - M
            add_edge(start + HOURS, i + 1, need[i] - total);
        }
    }
    add_edge(0, HOURS, total);   // S(24) >= S(0) + M
    add_edge(HOURS, 0, -total);  // S(0) >= S(24) - M，两条边把 S(24) 锁成 M
}

// 判定总雇佣人数为 total 时是否存在可行方案：跑最长路，有正环则约束矛盾。
bool feasible(int total) {
    build_graph(total);
    queue<int> q;
    for (int i = 0; i < NODES; i++) {
        dist[i] = 0;         // 全部初值为 0 并入队，等价于超级源点向各点连 0 权边
        in_queue[i] = true;
        relax_cnt[i] = 0;
        q.push(i);
    }
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        in_queue[u] = false;
        for (int e = head[u]; e != 0; e = nxt[e]) {
            int v = to[e];
            if (dist[u] + weight[e] > dist[v]) {
                dist[v] = dist[u] + weight[e];
                relax_cnt[v]++;
                if (relax_cnt[v] > NODES) return false;  // 正环：约束互相矛盾
                if (!in_queue[v]) {
                    in_queue[v] = true;
                    q.push(v);
                }
            }
        }
    }
    return dist[HOURS] >= total;
}

void solve() {
    int T;
    scanf("%d", &T);
    while (T--) {
        for (int i = 0; i < HOURS; i++) scanf("%d", &need[i]);
        int n;
        scanf("%d", &n);
        for (int i = 0; i < HOURS; i++) supply[i] = 0;
        for (int i = 0; i < n; i++) {
            int start_hour;
            scanf("%d", &start_hour);
            supply[start_hour]++;
        }

        // 可行性对 M 单调：多雇一个申请人不会让任何小时段的人数减少，故二分最小 M。
        int lo = 0, hi = n;
        while (lo < hi) {
            int mid = (lo + hi) / 2;
            if (feasible(mid)) hi = mid;
            else lo = mid + 1;
        }
        if (feasible(lo)) printf("%d\n", lo);
        else printf("No Solution\n");
    }
}

int main() {
    solve();
    return 0;
}
