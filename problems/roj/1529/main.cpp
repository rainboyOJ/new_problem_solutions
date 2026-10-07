/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-07 15:13
 * update_at: 2026-10-07 15:13
 */
#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

const ll MAXN = 1005;  // 节点数上限：题面给的是 1 < N < 1000

ll n, m;       // 当前测试样例的节点数、边数
ll deg[MAXN];  // deg[v] = 点 v 的度数；自环 (v,v) 给 v 贡献 2 度
ll fa[MAXN];   // 并查集父亲数组，只用来判断「有边的点」是否连成一片

// 并查集找根，带路径压缩（写成循环，避免深递归）
ll find_root(ll x) {
    ll root = x;
    while (fa[root] != root) root = fa[root];
    while (fa[x] != root) {
        ll nxt = fa[x];
        fa[x] = root;
        x = nxt;
    }
    return root;
}

// 合并两个点所在的集合
void union_set(ll a, ll b) {
    ll ra = find_root(a);
    ll rb = find_root(b);
    if (ra != rb) fa[ra] = rb;
}

// 判断当前这张图是否存在欧拉回路（deg 和 fa 已由 main 填好）
bool has_euler_circuit() {
    // 条件一：所有点的度数都是偶数，否则一笔画必然回不到起点
    for (ll v = 1; v <= n; v++) {
        if (deg[v] % 2 != 0) return false;
    }

    // 条件二：所有「有边相连」的点必须落在同一个连通块里
    // 数一数度数为正的顶点里有几个并查集根，超过一个说明边分散在多块中
    ll root_cnt = 0;
    for (ll v = 1; v <= n; v++) {
        if (deg[v] == 0) continue;  // 孤立点不参与连通性判断，直接跳过
        if (find_root(v) == v) root_cnt++;
    }
    return root_cnt <= 1;  // 一条边都没有时 root_cnt 为 0，视作存在空回路
}

int main() {
    while (scanf("%lld", &n) == 1 && n != 0) {  // 读到 N 为 0 时输入结束
        scanf("%lld", &m);

        for (ll v = 1; v <= n; v++) {
            deg[v] = 0;  // 每个样例重新清空度数和并查集
            fa[v] = v;
        }

        for (ll i = 1; i <= m; i++) {
            ll u, v;
            scanf("%lld %lld", &u, &v);
            deg[u]++;
            deg[v]++;         // 无向边：两个端点各加一度
            union_set(u, v);  // 把这条边的两个端点并入同一个集合
        }

        printf("%d\n", has_euler_circuit() ? 1 : 0);
    }
    return 0;
}
