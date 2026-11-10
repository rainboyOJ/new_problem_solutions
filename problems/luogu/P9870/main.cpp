/**
 * Problem: luogu P9870 - [NOIP2023] 双序列拓展
 * Author: rainboy
 * Date: 2026-11-10 23:30
 * Description: 极值十字架连通性 + 前后缀最值引导贪心跳步
 */
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAXN = 500005;

int n, m;
int a[MAXN], b[MAXN];
int pa[MAXN], va[MAXN], pb[MAXN], vb[MAXN];

struct RangeExtremum {
    int mx, mn;
};

RangeExtremum pre_a[MAXN], pre_b[MAXN];
RangeExtremum suf_a[MAXN], suf_b[MAXN];

void build_extremum() {
    pre_a[1] = {1, 1};
    for (int i = 2; i <= n; ++i) {
        pre_a[i] = pre_a[i - 1];
        if (a[i] > a[pre_a[i].mx]) pre_a[i].mx = i;
        if (a[i] < a[pre_a[i].mn]) pre_a[i].mn = i;
    }

    pre_b[1] = {1, 1};
    for (int i = 2; i <= m; ++i) {
        pre_b[i] = pre_b[i - 1];
        if (b[i] > b[pre_b[i].mx]) pre_b[i].mx = i;
        if (b[i] < b[pre_b[i].mn]) pre_b[i].mn = i;
    }

    suf_a[n] = {n, n};
    for (int i = n - 1; i >= 1; --i) {
        suf_a[i] = suf_a[i + 1];
        if (a[i] > a[suf_a[i].mx]) suf_a[i].mx = i;
        if (a[i] < a[suf_a[i].mn]) suf_a[i].mn = i;
    }

    suf_b[m] = {m, m};
    for (int i = m - 1; i >= 1; --i) {
        suf_b[i] = suf_b[i + 1];
        if (b[i] > b[suf_b[i].mx]) suf_b[i].mx = i;
        if (b[i] < b[suf_b[i].mn]) suf_b[i].mn = i;
    }
}

bool check_left(int x, int y) {
    while (x > 1 && y > 1) {
        RangeExtremum nx = pre_a[x - 1];
        RangeExtremum ny = pre_b[y - 1];
        if (a[nx.mn] < b[ny.mn]) {
            x = nx.mn;
        } else if (a[nx.mx] < b[ny.mx]) {
            y = ny.mx;
        } else {
            return false;
        }
    }
    return true;
}

bool check_right(int x, int y) {
    while (x < n && y < m) {
        RangeExtremum nx = suf_a[x + 1];
        RangeExtremum ny = suf_b[y + 1];
        if (a[nx.mn] < b[ny.mn]) {
            x = nx.mn;
        } else if (a[nx.mx] < b[ny.mx]) {
            y = ny.mx;
        } else {
            return false;
        }
    }
    return true;
}

bool solve_once() {
    bool swapped = false;
    if (a[1] == b[1]) return false;
    if (a[1] > b[1]) {
        swap(n, m);
        for (int i = 1; i <= max(n, m); ++i) {
            swap(a[i], b[i]);
        }
        swapped = true;
    }

    build_extremum();

    RangeExtremum x_all = pre_a[n];
    RangeExtremum y_all = pre_b[m];

    bool ans = false;
    // 必要条件：全局最值满足不等式，且两端点满足不等式
    if (a[x_all.mn] < b[y_all.mn] && a[x_all.mx] < b[y_all.mx] && a[n] < b[m]) {
        ans = check_left(x_all.mn, y_all.mx) && check_right(x_all.mn, y_all.mx);
    }

    if (swapped) {
        for (int i = 1; i <= max(n, m); ++i) {
            swap(a[i], b[i]);
        }
        swap(n, m);
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int c, q;
    if (!(cin >> c >> n >> m >> q)) return 0;

    for (int i = 1; i <= n; ++i) cin >> a[i];
    for (int i = 1; i <= m; ++i) cin >> b[i];

    cout << (solve_once() ? '1' : '0');

    while (q--) {
        int kx, ky;
        cin >> kx >> ky;
        for (int i = 1; i <= kx; ++i) {
            cin >> pa[i] >> va[i];
            swap(a[pa[i]], va[i]);
        }
        for (int i = 1; i <= ky; ++i) {
            cin >> pb[i] >> vb[i];
            swap(b[pb[i]], vb[i]);
        }

        cout << (solve_once() ? '1' : '0');

        // 复原修改
        for (int i = 1; i <= kx; ++i) {
            swap(a[pa[i]], va[i]);
        }
        for (int i = 1; i <= ky; ++i) {
            swap(b[pb[i]], vb[i]);
        }
    }
    cout << "\n";

    return 0;
}
