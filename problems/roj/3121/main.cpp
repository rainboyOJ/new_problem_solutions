/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-10 11:30
 * update_at: 2026-10-10 11:30
 */
// 区间第 k 小：可持久化权值线段树，版本区间相减。
#include <cstdio>
#include <vector>
#include <algorithm>

typedef long long ll;

const ll MAXNODE = 3000000;

struct Node {
    int lc;  // 左儿子编号
    int rc;  // 右儿子编号
    int cnt; // 子树内数的个数
};

Node node[MAXNODE];
ll tot = 0;

std::vector<ll> vals;
std::vector<int> roots; // roots[i] = 插入前 i 个数后的树根

// 在 prev 版本上把离散化下标 pos 的计数 +1，返回新版本节点编号
int insert(int prev, ll lo, ll hi, ll pos) {
    tot++;
    int root = (int)tot;
    node[root] = node[prev];
    node[root].cnt++;
    int cur = root, old = prev;
    while (hi - lo > 1) {
        ll mid = (lo + hi) / 2;
        if (pos < mid) {
            tot++;
            int nd = (int)tot;
            node[nd] = node[node[old].lc];
            node[nd].cnt++;
            node[cur].lc = nd;
            cur = nd;
            old = node[old].lc;
            hi = mid;
        } else {
            tot++;
            int nd = (int)tot;
            node[nd] = node[node[old].rc];
            node[nd].cnt++;
            node[cur].rc = nd;
            cur = nd;
            old = node[old].rc;
            lo = mid;
        }
    }
    return root;
}

// 在版本区间 (u, v] 上求第 k 小的离散化下标
ll kth(int u, int v, ll k, ll lo, ll hi) {
    while (hi - lo > 1) {
        ll mid = (lo + hi) / 2;
        ll left_cnt = node[node[v].lc].cnt - node[node[u].lc].cnt; // 值落在左半区的个数
        if (k <= left_cnt) {
            u = node[u].lc;
            v = node[v].lc;
            hi = mid;
        } else {
            k -= left_cnt;
            u = node[u].rc;
            v = node[v].rc;
            lo = mid;
        }
    }
    return lo;
}

int main() {
    ll n, m;
    if (scanf("%lld %lld", &n, &m) != 2) return 0; // 空输入安全返回
    std::vector<ll> a(n);
    for (ll i = 0; i < n; i++) {
        scanf("%lld", &a[i]);
    }

    vals = a;
    std::sort(vals.begin(), vals.end());
    vals.erase(std::unique(vals.begin(), vals.end()), vals.end());
    ll kinds = (ll)vals.size();

    roots.assign(n + 1, 0);
    for (ll i = 1; i <= n; i++) {
        ll pos = std::lower_bound(vals.begin(), vals.end(), a[i - 1]) - vals.begin();
        roots[i] = insert(roots[i - 1], 0, kinds, pos);
    }

    for (ll q = 0; q < m; q++) {
        ll l, r, k;
        scanf("%lld %lld %lld", &l, &r, &k); // 区间 [l,r] 的第 k 小 = 前缀 r 减前缀 l-1
        printf("%lld\n", vals[kth(roots[l - 1], roots[r], k, 0, kinds)]);
    }
    return 0;
}
