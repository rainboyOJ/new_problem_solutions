/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 10:38
 * update_at: 2026-10-12 14:56
 */
// main.cpp：把二叉树的父子链接当无向边，Floyd 求全源最短路，枚举医院位置取最小距离和。
//
// 结点的三个字段聚合成 struct：人口、左链接、右链接（0 表示无链接）。
// Floyd 用的距离矩阵 d[u][v] 是结点两两之间的关系，不属于某个结点的字段，
// 单独开全局二维数组，不和 Node 混在一起。

#include <iostream>

using namespace std;

typedef long long ll;

const int maxn = 105; // 题面 n <= 100，按上界开
const ll INF = 1e9;   // 距离上界：边权为 1，实际距离远小于它

struct Node {
    ll pop;  // 结点的居民人口数
    int lch; // 左链接指向的结点编号，0 表示无链接
    int rch; // 右链接指向的结点编号，0 表示无链接
};

Node node[maxn];   // node[u]：编号 u 的结点
ll d[maxn][maxn];  // d[u][v]：u 到 v 的最少边数
ll n;              // 结点数

// 读入每个结点的人口和左右链接
void read_input() {
    cin >> n;
    for (ll i = 1; i <= n; i++) {
        cin >> node[i].pop >> node[i].lch >> node[i].rch;
    }
}

// 初始化全源距离矩阵：自己到自己为 0，其余先设成 INF 等着被边更新
void init_dist() {
    for (ll i = 1; i <= n; i++) {
        for (ll j = 1; j <= n; j++) {
            d[i][j] = (i == j) ? 0 : INF;
        }
    }
}

// 把结点里的链接翻译成无向边（相邻距离 1）：链接是双向可走的
void build_edges() {
    for (ll i = 1; i <= n; i++) {
        if (node[i].lch != 0) {
            d[i][node[i].lch] = d[node[i].lch][i] = 1;
        }
        if (node[i].rch != 0) {
            d[i][node[i].rch] = d[node[i].rch][i] = 1;
        }
    }
}

// Floyd 全源最短路：枚举中转点 k，尝试用 i -> k -> j 缩短 i -> j
void floyd() {
    for (ll k = 1; k <= n; k++) {
        for (ll i = 1; i <= n; i++) {
            for (ll j = 1; j <= n; j++) {
                if (d[i][j] > d[i][k] + d[k][j]) {
                    d[i][j] = d[i][k] + d[k][j];
                }
            }
        }
    }
}

// 医院可以建在任意结点：枚举每个候选 u，求"人口 x 距离"的总和，取最小
ll min_total_distance() {
    ll ans = INF * INF; // 总路程的答案上界
    for (ll u = 1; u <= n; u++) {
        ll sum = 0;
        for (ll v = 1; v <= n; v++) {
            sum += node[v].pop * d[u][v];
        }
        if (sum < ans) {
            ans = sum;
        }
    }
    return ans;
}

void solve() {
    read_input();
    init_dist();
    build_edges();
    floyd();
    cout << min_total_distance() << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();
    return 0;
}
