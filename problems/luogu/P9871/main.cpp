/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-11-10 23:35
 * update_at: 2026-11-10 23:58
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

using ll = long long;

const ll INF = 1e18;
const int MAXV = 600005;

struct Challenge {
    ll l, r, v;
};

vector<Challenge> challenges_at[MAXV];
vector<ll> p;

ll tree_max[MAXV << 2];
ll tree_tag[MAXV << 2];

void pushup(int u) {
    tree_max[u] = max(tree_max[u << 1], tree_max[u << 1 | 1]);
}

void apply_tag(int u, ll val) {
    tree_max[u] += val;
    tree_tag[u] += val;
}

void pushdown(int u) {
    if (tree_tag[u] != 0) {
        apply_tag(u << 1, tree_tag[u]);
        apply_tag(u << 1 | 1, tree_tag[u]);
        tree_tag[u] = 0;
    }
}

void build(int u, int l, int r) {
    tree_tag[u] = 0;
    tree_max[u] = -INF;
    if (l == r) return;
    int mid = l + (r - l) / 2;
    build(u << 1, l, mid);
    build(u << 1 | 1, mid + 1, r);
}

void update_add(int u, int l, int r, int ql, int qr, ll val) {
    if (ql <= l && r <= qr) {
        apply_tag(u, val);
        return;
    }
    pushdown(u);
    int mid = l + (r - l) / 2;
    if (ql <= mid) update_add(u << 1, l, mid, ql, qr, val);
    if (qr > mid) update_add(u << 1 | 1, mid + 1, r, ql, qr, val);
    pushup(u);
}

void update_set(int u, int l, int r, int pos, ll val) {
    if (l == r) {
        tree_max[u] = max(tree_max[u], val);
        return;
    }
    pushdown(u);
    int mid = l + (r - l) / 2;
    if (pos <= mid) update_set(u << 1, l, mid, pos, val);
    else update_set(u << 1 | 1, mid + 1, r, pos, val);
    pushup(u);
}

ll query_max(int u, int l, int r, int ql, int qr) {
    if (ql <= l && r <= qr) return tree_max[u];
    pushdown(u);
    int mid = l + (r - l) / 2;
    ll res = -INF;
    if (ql <= mid) res = max(res, query_max(u << 1, l, mid, ql, qr));
    if (qr > mid) res = max(res, query_max(u << 1 | 1, mid + 1, r, ql, qr));
    return res;
}

void solve() {
    ll n, m, k, d;
    cin >> n >> m >> k >> d;

    vector<Challenge> raw_challenges;
    p.clear();
    p.push_back(0); // 包含 0

    for (int i = 0; i < m; ++i) {
        ll x, y, v;
        cin >> x >> y >> v;
        ll l = x - y + 1;
        ll r = x;
        if (y <= k) {
            raw_challenges.push_back({l, r, v});
            p.push_back(r);
            p.push_back(l - 1);
            if (l >= 1) p.push_back(l); // 保证断点在 l-1 与打卡点 l 分开
        }
    }

    sort(p.begin(), p.end());
    p.erase(unique(p.begin(), p.end()), p.end());

    int tot = p.size();
    for (int i = 0; i <= tot; ++i) {
        challenges_at[i].clear();
    }

    auto get_pos = [&](ll val) {
        return lower_bound(p.begin(), p.end(), val) - p.begin();
    };

    for (const auto& c : raw_challenges) {
        int pos_r = get_pos(c.r);
        challenges_at[pos_r].push_back(c);
    }

    build(1, 0, tot - 1);

    // dp[i][0] 表示第 p[i] 天不打卡时的最大收益
    // dp[i][1] 表示第 p[i] 天打卡时的最大收益
    vector<ll> dp0(tot, 0), dp1(tot, -INF);

    // 初始状态：第 0 天不打卡，dp0[0] = 0
    // 放入线段树的基准值为 dp0[0] + d * 0 = 0
    update_set(1, 0, tot - 1, 0, 0);

    for (int i = 1; i < tot; ++i) {
        // 激活以 p[i] 结尾的挑战
        for (const auto& c : challenges_at[i]) {
            int pos_lim = get_pos(c.l - 1);
            if (pos_lim >= 0) {
                update_add(1, 0, tot - 1, 0, pos_lim, c.v);
            }
        }

        // 第 p[i] 天打卡：必须从某个断点 p[j] (p[j] >= p[i] - k) 之后开始连续打卡
        // 即打卡区间为 [p[j] + 1, p[i]]
        int left_idx = lower_bound(p.begin(), p.end(), p[i] - k) - p.begin();
        if (left_idx <= i - 1) {
            ll max_val = query_max(1, 0, tot - 1, left_idx, i - 1);
            if (max_val > -INF / 2) {
                dp1[i] = max_val - d * p[i];
            }
        }

        // 第 p[i] 天不打卡：直接从第 p[i-1] 天转移（无论第 p[i-1] 天打不打卡）
        dp0[i] = max(dp0[i - 1], dp1[i - 1]);

        // 只有不打卡的位置才能作为未来的断点 p[i]
        // 插入线段树的权值是 dp0[i] + d * p[i]
        update_set(1, 0, tot - 1, i, dp0[i] + d * p[i]);
    }

    cout << max(dp0[tot - 1], dp1[tot - 1]) << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int test_case_id, t;
    if (!(cin >> test_case_id >> t)) return 0;
    while (t--) {
        solve();
    }
    return 0;
}
