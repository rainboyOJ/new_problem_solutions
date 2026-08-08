#include <bits/stdc++.h>
using namespace std;

const int MAXN = 30;
const int INF = 0x3f3f3f3f;

struct Interval {
    int l, r;
    int len;
};

int n, m;
Interval a[MAXN];
int ans = INF;

void dfs(int idx, int chosen, int cur_l, int cur_r, int min_len, int max_len) {
    if (chosen == m) {
        ans = min(ans, max_len - min_len);
        return;
    }
    if (idx > n) {
        return;
    }
    if (chosen + (n - idx + 1) < m) {
        return;
    }
    if (chosen > 0 && max_len - min_len >= ans) {
        return;
    }

    // 选择当前区间。
    int next_l = a[idx].l;
    int next_r = a[idx].r;
    int next_min_len = a[idx].len;
    int next_max_len = a[idx].len;
    if (chosen > 0) {
        next_l = max(cur_l, a[idx].l);
        next_r = min(cur_r, a[idx].r);
        next_min_len = min(min_len, a[idx].len);
        next_max_len = max(max_len, a[idx].len);
    }

    // 已选区间的公共交集只会越来越小，一旦为空就不可能再变回合法。
    if (next_l <= next_r) {
        dfs(idx + 1, chosen + 1, next_l, next_r, next_min_len, next_max_len);
    }

    // 不选当前区间。
    dfs(idx + 1, chosen, cur_l, cur_r, min_len, max_len);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // 这是一个小数据精确暴力：
    // 枚举恰好选哪 m 个区间，再检查它们是否有公共点。
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> a[i].l >> a[i].r;
        a[i].len = a[i].r - a[i].l;
    }

    dfs(1, 0, -INF, INF, INF, -INF);

    if (ans == INF) {
        cout << -1 << '\n';
    } else {
        cout << ans << '\n';
    }

    return 0;
}
