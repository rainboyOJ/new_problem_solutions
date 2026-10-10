/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-10 11:30
 * update_at: 2026-10-10 11:30
 */
// 分饼干：贪婪度降序排序后做「按块分配」的 DP，并沿最优决策回推方案。
#include <cstdio>
#include <vector>
#include <algorithm>

typedef long long ll;

const ll INF = 1000000000000000000LL / 4; // 「状态不可达」哨兵

ll n, m;
std::vector<ll> g;
std::vector<ll> order; // 贪婪度降序的下标排列
std::vector<ll> pre;   // pre[i] = 前 i 个人的贪婪度之和（按 order 顺序）
std::vector<std::vector<ll> > f;

bool greedy_less(ll x, ll y) {
    return g[x] > g[y]; // 贪婪度大的排在前面
}

// f[i][j] = 贪婪度降序的前 i 人恰好分到 j 块饼干时的最小怨气
void anger_table() {
    f.assign(n + 1, std::vector<ll>(m + 1, INF));
    f[0][0] = 0; // 前 0 人只有 j = 0 可达
    for (ll i = 1; i <= n; i++) {
        std::vector<ll> row(m + 1, INF);
        row[i] = 0; // 情况 B 的 k = 0：前 i 人各 1 块，怨气为 0
        // 情况 B：末尾 i-k 人各拿 1 块，合计 k * (pre[i] - pre[k])
        for (ll k = 1; k < i; k++) {
            ll weight = k * (pre[i] - pre[k]);
            for (ll j = i; j <= m; j++) {
                ll cand = f[k][j - i + k] + weight;
                if (cand < row[j]) row[j] = cand;
            }
        }
        // 情况 A：前 i 人都至少拿 2 块，集体减 1 块后大小关系不变
        for (ll j = 2 * i; j <= m; j++) {
            if (row[j - i] < row[j]) row[j] = row[j - i];
        }
        f[i] = row;
    }
}

// 沿最优决策回推，返回降序位置 1..n 上各人的饼干数
std::vector<ll> restore() {
    std::vector<ll> counts(n + 1, 0);
    ll extra = 0; // 已补回的「+1 层」数
    ll i = n, j = m;
    while (i) {
        // 情况 A：本层被「全体减 1 块」抹掉，回推时补一层
        if (j >= 2 * i && f[i][j - i] == f[i][j]) {
            extra++;
            j -= i;
            continue;
        }
        // 情况 B：断点 k 说明位置 k+1..i 各拿 1 块
        ll k = 0;
        for (ll t = 0; t < i; t++) {
            if (f[t][j - i + t] + t * (pre[i] - pre[t]) == f[i][j]) {
                k = t;
                break;
            }
        }
        for (ll pos = k + 1; pos <= i; pos++) {
            counts[pos] = 1 + extra;
        }
        j = j - i + k;
        i = k;
    }
    return counts;
}

int main() {
    if (scanf("%lld %lld", &n, &m) != 2) return 0; // 空输入安全返回
    g.assign(n, 0);
    for (ll i = 0; i < n; i++) {
        scanf("%lld", &g[i]);
    }

    order.resize(n);
    for (ll i = 0; i < n; i++) order[i] = i;
    std::sort(order.begin(), order.end(), greedy_less);

    pre.assign(n + 1, 0);
    for (ll i = 0; i < n; i++) {
        pre[i + 1] = pre[i] + g[order[i]];
    }

    anger_table();
    std::vector<ll> counts = restore();

    std::vector<ll> ans(n, 0);
    for (ll pos = 1; pos <= n; pos++) {
        ans[order[pos - 1]] = counts[pos]; // 换回输入顺序
    }

    printf("%lld\n", f[n][m]);
    for (ll i = 0; i < n; i++) {
        if (i) printf(" ");
        printf("%lld", ans[i]);
    }
    printf("\n");
    return 0;
}
