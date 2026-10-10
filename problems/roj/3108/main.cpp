/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-10 11:30
 * update_at: 2026-10-10 11:30
 */
// 食物链：带权并查集（模 3 关系）一次扫描判定每句话真假。
#include <cstdio>

typedef long long ll;

const ll MAXN = 50005;

ll fa[MAXN]; // fa[i]: i 的父节点
ll d[MAXN];  // d[i]: i 对根的关系，0同类 / 1 i吃根 / 2 根吃i（模 3 环）
ll path[MAXN];

ll n, k;

// 两遍迭代：先找根，再自根向叶重压路径上的 d 为对根的关系
ll find(ll x) {
    ll r = x;
    while (fa[r] != r) {
        r = fa[r];
    }
    ll cnt = 0;
    ll u = x;
    while (u != r) {
        path[cnt++] = u;
        u = fa[u];
    }
    ll acc = 0;
    for (ll i = cnt - 1; i >= 0; i--) { // 根的子节点先算，边向上边累加
        ll v = path[i];
        acc = (acc + d[v]) % 3;
        d[v] = acc;
        fa[v] = r;
    }
    return r;
}

int main() {
    if (scanf("%lld %lld", &n, &k) != 2) return 0; // 空输入安全返回
    for (ll i = 0; i <= n; i++) {
        fa[i] = i;
        d[i] = 0;
    }

    ll ans = 0;
    for (ll i = 0; i < k; i++) {
        ll op, x, y;
        scanf("%lld %lld %lld", &op, &x, &y);
        ll r = op - 1; // op=1 同类 r=0；op=2 x吃y r=1
        if (x > n || y > n) { // 假话条件 2：编号越界
            ans++;
            continue;
        }
        ll fx = find(x), fy = find(y);
        if (fx == fy) { // 已有关系：核对 (d[x]-d[y]) mod 3 是否等于 r
            if (((d[x] - d[y] - r) % 3 + 3) % 3) {
                ans++; // 与前面真话冲突（含 x 吃 x）
            }
        } else { // 无矛盾则合并：x→根 = x→y + y→根
            fa[fx] = fy;
            d[fx] = ((r + d[y] - d[x]) % 3 + 3) % 3;
        }
    }
    printf("%lld\n", ans);
    return 0;
}
