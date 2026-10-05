/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 00:26
 * update_at: 2026-10-06 00:26
 */

#include <cstdio>
#include <cstring>

typedef long long ll;

const int MAXN = 505;
const int MAXE = 5205;

int n, m, w;    // 一个农场的规模：地、小路、虫洞
int edge_cnt;   // 当前农场已记录的边数
int eu[MAXE];   // eu[i] 表示第 i 条边的起点
int ev[MAXE];   // ev[i] 表示第 i 条边的终点
ll ew[MAXE];    // ew[i] 表示第 i 条边的权（虫洞取负）
ll dist[MAXN];  // dist[i] 表示超级源点到第 i 块地的最短时间

// 加一条 u -> v、权为 weight 的有向边。
void add_edge(int u, int v, ll weight) {
    edge_cnt++;
    eu[edge_cnt] = u;
    ev[edge_cnt] = v;
    ew[edge_cnt] = weight;
}

// 判断当前农场是否存在负环：以超级源点做 n 轮松弛，第 n 轮仍能松弛即有负环。
// "回到出发时刻之前"等价于存在总权为负的闭环，而负闭环必含负环，故只需判负环。
bool has_negative_cycle() {
    for (int i = 1; i <= n; i++)
        dist[i] = 0; // 超级源点到各点初值都为 0，一轮即可覆盖所有连通块
    for (int round = 1; round <= n; round++) {
        bool relaxed = false;
        for (int i = 1; i <= edge_cnt; i++) {
            if (dist[eu[i]] + ew[i] < dist[ev[i]]) {
                dist[ev[i]] = dist[eu[i]] + ew[i];
                relaxed = true;
            }
        }
        if (!relaxed)
            return false; // 本轮无松弛：距离已稳定，之后不可能再变小
    }
    return true; // 第 n 轮仍在松弛，存在负环
}

void solve() {
    int F;
    scanf("%d", &F);
    for (int farm = 1; farm <= F; farm++) {
        scanf("%d %d %d", &n, &m, &w);
        edge_cnt = 0;
        // 小路无向且权为正：来回各记一条边。
        for (int i = 1; i <= m; i++) {
            int s, e;
            ll t;
            scanf("%d %d %lld", &s, &e, &t);
            add_edge(s, e, t);
            add_edge(e, s, t);
        }
        // 虫洞有向且时间倒流：只记一条权为 -t 的边。
        for (int i = 1; i <= w; i++) {
            int s, e;
            ll t;
            scanf("%d %d %lld", &s, &e, &t);
            add_edge(s, e, -t);
        }
        if (has_negative_cycle())
            printf("YES\n");
        else
            printf("NO\n");
    }
}

int main() {
    solve();
    return 0;
}
