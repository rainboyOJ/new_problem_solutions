#include <bits/stdc++.h>
using namespace std;

const int MAXN = 500005;
const long double INF = 1e100L;

struct Node {
    long long x, r, v;
} a[MAXN];

struct Line {
    // y = kx + b
    long double k, b;
    bool empty;
} seg[MAXN << 2];

int n;
long long home_x;
long long coord[MAXN];
int coord_cnt;
// dp[i]：把第 i 个点启动，并让它收到来自左边的信号的最小代价。
long double dp[MAXN];

long double value(const Line &line, long long x) {
    return line.k * (long double) x + line.b;
}

void insert_line(int idx, int l, int r, Line line) {
    if (seg[idx].empty) {
        seg[idx] = line;
        return;
    }

    int mid = (l + r) >> 1;
    long long xl = coord[l];
    long long xm = coord[mid];
    long long xr = coord[r];

    Line low = seg[idx];
    Line high = line;
    if (value(low, xm) > value(high, xm)) {
        swap(low, high);
    }
    seg[idx] = low;

    if (l == r) {
        return;
    }

    if (value(low, xl) > value(high, xl)) {
        insert_line(idx << 1, l, mid, high);
    } else if (value(low, xr) > value(high, xr)) {
        insert_line(idx << 1 | 1, mid + 1, r, high);
    }
}

long double query_min(int idx, int l, int r, int pos) {
    long double ans = INF;
    if (!seg[idx].empty) {
        ans = value(seg[idx], coord[pos]);
    }
    if (l == r) {
        return ans;
    }

    int mid = (l + r) >> 1;
    if (pos <= mid) {
        ans = min(ans, query_min(idx << 1, l, mid, pos));
    } else {
        ans = min(ans, query_min(idx << 1 | 1, mid + 1, r, pos));
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> home_x;
    for (int i = 1; i <= n; i++) {
        cin >> a[i].x >> a[i].r >> a[i].v;
    }

    sort(a + 1, a + n + 1, [](const Node &lhs, const Node &rhs) {
        if (lhs.x != rhs.x) {
            return lhs.x < rhs.x;
        }
        if (lhs.r != rhs.r) {
            return lhs.r < rhs.r;
        }
        return lhs.v < rhs.v;
    });

    coord_cnt = 0;
    for (int i = 1; i <= n; i++) {
        if (i == 1 || a[i].x != a[i - 1].x) {
            coord[++coord_cnt] = a[i].x;
        }
    }

    for (int i = 1; i < (MAXN << 2); i++) {
        seg[i].empty = true;
    }

    long double ans = INF;
    int i = 1;
    while (i <= n) {
        int j = i;
        while (j + 1 <= n && a[j + 1].x == a[i].x) {
            j++;
        }

        int pos = lower_bound(coord + 1, coord + coord_cnt + 1, a[i].x) - coord;

        for (int k = i; k <= j; k++) {
            if (k == 1) {
                // 第一个点就是移动公司本身，不需要接收费用，只需要启动费用。
                dp[k] = (long double) a[k].v;
            } else {
                long double best = INF;
                if (coord_cnt > 0 && !seg[1].empty) {
                    // 从所有左侧已建好的点里，找一个让当前点接收费用最小的。
                    best = min(best, query_min(1, 1, coord_cnt, pos));
                }
                if (best >= INF / 2) {
                    dp[k] = INF;
                } else {
                    dp[k] = best + (long double) a[k].v;
                }
            }

            if (dp[k] < INF / 2 && llabs(a[k].x - home_x) <= a[k].r) {
                ans = min(ans, dp[k]);
            }
        }

        for (int k = i; k <= j; k++) {
            if (dp[k] >= INF / 2) {
                continue;
            }
            Line line;
            // 若当前点 j 作为发送端，而后面某个点 i 要从它接收，
            // 额外费用是 sqrt((x_i - x_j)^2 / (4r_j)) = (x_i - x_j) / (2*sqrt(r_j))。
            // 所以转移可以写成：
            // dp[j] + v_i + x_i/(2*sqrt(r_j)) - x_j/(2*sqrt(r_j))
            // 对固定 j 来说，这就是一条关于 x_i 的直线。
            line.k = 1.0L / (2.0L * sqrtl((long double) a[k].r));
            line.b = dp[k] - line.k * (long double) a[k].x;
            line.empty = false;
            insert_line(1, 1, coord_cnt, line);
        }

        i = j + 1;
    }

    cout.setf(ios::fixed);
    cout << setprecision(3) << (double) ans << '\n';
    return 0;
}
