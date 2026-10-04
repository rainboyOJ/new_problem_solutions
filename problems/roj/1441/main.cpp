/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 01:16
 * update_at: 2026-10-05 01:16
 */
#include <iostream>
using namespace std;

typedef long long ll;

const int MAXM = 25;
const ll INF = 1e9;

ll n, m;
ll min_v[MAXM]; // min_v[i] 表示自顶向下 i 层都取最小尺寸时的最小体积和 sum_{k=1}^{i} k^3
ll min_s[MAXM]; // min_s[i] 表示自顶向下 i 层都取最小尺寸时的最小侧面积和 sum_{k=1}^{i} 2*k^2
ll best_s;      // 当前搜到的最小表面积系数 S

// 返回 floor(sqrt(x))，用整数二分求值，避免浮点误差和类型转换。
ll isqrt_ll(ll x) {
    if (x <= 0) return 0;
    ll lo = 1, hi = x, ans = 0;
    while (lo <= hi) {
        ll mid = (lo + hi) / 2;
        // 用 mid <= x / mid 代替 mid*mid <= x，避免乘法溢出
        if (mid <= x / mid) {
            ans = mid;
            lo = mid + 1;
        } else {
            hi = mid - 1;
        }
    }
    return ans;
}

// 自底向上搜索：正在确定第 layer 层，剩余体积为 v，已累计表面积系数为 s，
// r_prev 与 h_prev 是刚确定的更低一层的半径和高度（必须严格更大）。
void dfs(ll layer, ll v, ll s, ll r_prev, ll h_prev) {
    if (layer == 0) {
        if (v == 0 && s < best_s) best_s = s;
        return;
    }
    // 剪枝 1：剩余体积不足以填满剩余层
    if (v < min_v[layer]) return;
    // 剪枝 2：加上剩余层的最小侧面积仍不优于当前最优解
    if (s + min_s[layer] >= best_s) return;
    // 剪枝 3：剩余体积换算出的侧面积下界 2*v/r_prev 已无法更优
    if (s + 2 * v / r_prev >= best_s) return;

    ll v_left = v - min_v[layer - 1]; // 当前层与更低层可分配的体积
    ll max_r = isqrt_ll(v_left / layer); // 半径上限：保证剩余层每层至少留 1 的高度
    if (r_prev - 1 < max_r) max_r = r_prev - 1;
    for (ll r = max_r; r >= layer; r--) {
        ll max_h = v_left / (r * r);
        if (h_prev - 1 < max_h) max_h = h_prev - 1;
        for (ll h = max_h; h >= layer; h--) {
            dfs(layer - 1, v - r * r * h, s + 2 * r * h, r, h);
        }
    }
}

// 先枚举最底层（第 m 层）的半径与高度，最底层的底面积 R^2 只在此时计入一次。
void solve() {
    best_s = INF;
    ll max_r_m = isqrt_ll(n);
    for (ll r = max_r_m; r >= m; r--) {
        if (r * r + min_s[m] >= best_s) continue;
        ll max_h = (n - min_v[m - 1]) / (r * r);
        for (ll h = max_h; h >= m; h--) {
            ll cur_v = r * r * h;
            ll cur_s = r * r + 2 * r * h;
            if (cur_s + min_s[m - 1] >= best_s) continue;
            if (cur_s + 2 * (n - cur_v) / r >= best_s) continue;
            dfs(m - 1, n - cur_v, cur_s, r, h);
        }
    }
    if (best_s == INF) cout << 0 << endl;
    else cout << best_s << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;

    // 预处理最小体积和与最小侧面积和，供剪枝使用
    min_v[0] = 0;
    min_s[0] = 0;
    for (ll i = 1; i <= m; i++) {
        min_v[i] = min_v[i - 1] + i * i * i;
        min_s[i] = min_s[i - 1] + 2 * i * i;
    }

    solve();

    return 0;
}
