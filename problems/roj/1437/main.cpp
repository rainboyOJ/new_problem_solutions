/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 01:08
 * update_at: 2026-10-05 01:08
 */
// roj 1437 扩散
// 结论: 时刻 t 两个扩散菱形(曼哈顿距离意义)相交 <=> 曼哈顿距离 <= 2t
//       于是把边权看作两点曼哈顿距离, 答案 = 最小生成树最大边权的一半向上取整
// 做法: 完全图稠密, n<=50, 用 O(n^2) 的 Prim 求最小生成树
#include <cstdio>
using namespace std;
typedef long long ll;

const int MAXN = 55;
ll px[MAXN]; // 第 i 个点的横坐标
ll py[MAXN]; // 第 i 个点的纵坐标
ll min_dist[MAXN]; // min_dist[i] = 第 i 个点到当前生成树的最小曼哈顿距离
bool used[MAXN]; // used[i] = 点 i 是否已经并入生成树

ll abs_ll(ll v) {
    if (v < 0) {
        return -v;
    }
    return v;
}

// 两点曼哈顿距离
ll manhattan(int i, int j) {
    return abs_ll(px[i] - px[j]) + abs_ll(py[i] - py[j]);
}

int main() {
    ll n;
    scanf("%lld", &n);
    for (ll i = 1; i <= n; i++) {
        scanf("%lld%lld", &px[i], &py[i]);
    }

    // Prim: 先把点 1 放入生成树, 其余点的距离初始为到点 1 的曼哈顿距离
    for (ll i = 1; i <= n; i++) {
        min_dist[i] = manhattan(1, i);
    }
    used[1] = true;

    ll max_edge = 0; // 生成树中最大的边权(曼哈顿距离形式)
    for (ll round = 1; round <= n - 1; round++) {
        // 在未使用的点里找离生成树最近的点
        ll best = 0;
        for (ll i = 1; i <= n; i++) {
            if (used[i]) {
                continue;
            }
            if (best == 0 || min_dist[i] < min_dist[best]) {
                best = i;
            }
        }
        used[best] = true;
        if (min_dist[best] > max_edge) {
            max_edge = min_dist[best];
        }
        // 用新并入的点 best 松弛其余未使用的点
        for (ll i = 1; i <= n; i++) {
            if (used[i]) {
                continue;
            }
            ll d = manhattan(i, best);
            if (d < min_dist[i]) {
                min_dist[i] = d;
            }
        }
    }

    // 边权为曼哈顿距离 d, 对应扩散时刻为 ceil(d/2)
    ll ans = (max_edge + 1) / 2;
    printf("%lld\n", ans);
    return 0;
}
