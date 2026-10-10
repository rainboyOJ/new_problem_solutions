/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-10 11:30
 * update_at: 2026-10-10 11:30
 */
// 关押罪犯：扩展域并查集，按怨气值从大到小处理每条仇恨边。
#include <cstdio>
#include <vector>
#include <algorithm>

typedef long long ll;

const ll MAXN = 20005;

struct Edge {
    ll a, b, c;
};

Edge edges[MAXN * 5];
ll fa[MAXN * 2]; // 扩展域：1..n 第一监狱域，n+1..2n 第二监狱域

bool edge_greater(const Edge& x, const Edge& y) {
    return x.c > y.c;
}

// 路径减半的迭代式查根
ll find(ll x) {
    while (fa[x] != x) {
        fa[x] = fa[fa[x]];
        x = fa[x];
    }
    return x;
}

int main() {
    ll n, m;
    if (scanf("%lld %lld", &n, &m) != 2) return 0; // 空输入安全返回
    for (ll i = 0; i < m; i++) {
        scanf("%lld %lld %lld", &edges[i].a, &edges[i].b, &edges[i].c);
    }
    std::sort(edges, edges + m, edge_greater); // 怨气值降序

    for (ll i = 0; i <= 2 * n; i++) {
        fa[i] = i;
    }

    for (ll i = 0; i < m; i++) {
        ll a = edges[i].a, b = edges[i].b, c = edges[i].c;
        ll ra = find(a), rb = find(b);
        if (ra == rb) { // 冲突不可避免，c 即市长看到的最小最大值
            printf("%lld\n", c);
            return 0;
        }
        fa[ra] = find(b + n); // a 与 b+n 同盟 => a、b 分居两狱
        fa[rb] = find(a + n);
    }
    printf("0\n"); // 所有仇恨都能化解
    return 0;
}
