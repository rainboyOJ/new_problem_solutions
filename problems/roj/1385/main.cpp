/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 00:20
 * update_at: 2026-10-05 00:20
 */

#include <cstdio>

typedef long long ll;

// 扩展域并查集：fa[1..n] 是朋友域，fa[n+1..2n] 是敌人域
// fa[x+n] 表示“x 的敌人”这个虚拟节点
ll fa[2005 * 2];
bool root_seen[2005 * 2]; // root_seen[r] 表示代表元 r 是否已经统计过
ll n, m, ans;

// 并查集查根，带路径压缩
ll find_root(ll x) {
    if (fa[x] == x) {
        return x;
    }
    fa[x] = find_root(fa[x]);
    return fa[x];
}

// 合并两个节点所在的集合
void union_set(ll x, ll y) {
    ll rx = find_root(x);
    ll ry = find_root(y);
    if (rx != ry) {
        fa[rx] = ry;
    }
}

int main() {
    scanf("%lld %lld", &n, &m);

    // 初始化：每个人有朋友域 x 和敌人域 x+n
    for (ll i = 1; i <= 2 * n; ++i) {
        fa[i] = i;
    }

    for (ll i = 1; i <= m; ++i) {
        ll p, x, y;
        scanf("%lld %lld %lld", &p, &x, &y);
        if (p == 0) {
            // 朋友：朋友的朋友是朋友，直接合并朋友域
            union_set(x, y);
        } else {
            // 敌人：x 与 y 的敌人域合并，y 与 x 的敌人域合并
            // 这样“敌人的敌人”会通过共同的敌人域节点自动连通
            union_set(x, y + n);
            union_set(y, x + n);
        }
    }

    // 统计 1..n 朋友域中不同代表元的数量，就是最大团伙数
    // 注意：代表元可能落在敌人域（合并方向导致），所以要按根去重，
    // 不能只数 find_root(i) == i 的 i
    for (ll i = 1; i <= n; ++i) {
        ll r = find_root(i);
        if (!root_seen[r]) {
            root_seen[r] = true;
            ans = ans + 1;
        }
    }
    printf("%lld\n", ans);

    return 0;
}
