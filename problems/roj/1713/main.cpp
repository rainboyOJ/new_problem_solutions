/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-07 17:50
 * update_at: 2026-10-07 17:50
 */
// 1713 生成树：所有生成树的"边权 gcd"的 lcm。
//
// 关键结论：记 D = { d >= 1 : 只保留权值能被 d 整除的边后图连通 }，则答案 = lcm(D)。
//   任取生成树 T，g = gcd(T) 整除 T 的每条边，故 T 全部落在 G_g 里，G_g 连通，g ∈ D；
//   反过来 d ∈ D 时取 G_d 的生成树 T，有 d | gcd(T)。两边取 lcm 即得相等。
// 于是只需对 d = 1..maxW 判一次连通性，连通就 ans = lcm(ans, d)。
//
// 复杂度：每个 d 重置一次并查集 O(N)，共 O(N * maxW)；并查集合并次数为 Σ_e τ(w_e)
// （τ 为约数个数，1e5 条边 × 平均约 10 个约数）。N <= 1000、maxW <= 32767 时约 4e7 次
// 基本操作，1s 内安全。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull; // 答案上界为 2^64-1（样例 9 已超过 2^63-1），必须无符号

const int MAXN = 1005;
const int MAXM = 100005;
const int MAXW = 32770; // 2^15 - 1 = 32767，权值桶数组开大一点

struct Edge {
    int u, v, w;
};

int n, m;
Edge e[MAXM];      // 全部边，按权值升序排序后存放
int cnt[MAXW];     // cnt[w] = 权值恰为 w 的边数
int st[MAXW];      // 权值 w 的边在排序后数组中的起始下标

int par[MAXN];     // 并查集：父指针
int sz[MAXN];      // 并查集：按大小合并用的集合大小

void dsu_init() {
    for (int i = 1; i <= n; ++i) {
        par[i] = i;
        sz[i] = 1;
    }
}

int find_root(int x) {
    while (par[x] != x) {
        par[x] = par[par[x]]; // 路径减半
        x = par[x];
    }
    return x;
}

// 合并两个集合，返回是否真的合并（即是否减少了一个连通块）
bool unite(int a, int b) {
    a = find_root(a);
    b = find_root(b);
    if (a == b) return false;
    if (sz[a] < sz[b]) {
        int t = a;
        a = b;
        b = t;
    }
    par[b] = a;
    sz[a] += sz[b];
    return true;
}

ull gcd_ull(ull a, ull b) {
    while (b) {
        ull t = a % b;
        a = b;
        b = t;
    }
    return a;
}

// 每个中间 lcm 都整除最终答案，所以 a / gcd(a, b) * b 不会中途溢出
ull lcm_ull(ull a, ull b) {
    return a / gcd_ull(a, b) * b;
}

bool cmp_w(const Edge& a, const Edge& b) {
    return a.w < b.w;
}

int main() {
    scanf("%d %d", &n, &m);
    int maxW = 0;
    for (int i = 0; i < m; ++i) {
        scanf("%d %d %d", &e[i].u, &e[i].v, &e[i].w);
        ++cnt[e[i].w];
        if (e[i].w > maxW) maxW = e[i].w;
    }

    // n = 1（此时必然 m = 0）只有唯一的空生成树，约定答案为 1
    if (n <= 1 || maxW == 0) {
        printf("1\n");
        return 0;
    }

    // 按权值分桶：排序后 cnt/st 即可把"权值为 k 的边"定位成一段连续区间
    sort(e, e + m, cmp_w);
    st[0] = 0;
    for (int w = 0; w < maxW; ++w) {
        st[w + 1] = st[w] + cnt[w];
    }

    ull ans = 1;
    for (int d = 1; d <= maxW; ++d) {
        // d 的倍数里一条边都没有时 G_d 必不连通，先跳过，省掉一次并查集重置
        bool any = false;
        for (int k = d; k <= maxW; k += d) {
            if (cnt[k]) {
                any = true;
                break;
            }
        }
        if (!any) continue;

        dsu_init();
        int comp = n; // 当前连通块个数
        for (int k = d; k <= maxW && comp > 1; k += d) {
            for (int i = st[k]; i < st[k] + cnt[k]; ++i) {
                if (unite(e[i].u, e[i].v)) --comp;
            }
        }
        if (comp == 1) ans = lcm_ull(ans, (ull)d); // G_d 连通 ⇔ d ∈ D
    }

    printf("%llu\n", ans);
    return 0;
}
