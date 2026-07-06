// brute.cpp：小数据暴力解，二分天数后递归枚举所有合法的连通种植顺序。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 12;

int n;
long long need_h[MAXN], b[MAXN], c[MAXN];
bool edge[MAXN][MAXN];
int deadline_day[MAXN];
bool planted[MAXN];

__int128 sum_linear(long long bb, long long cc, long long l, long long r) {
    if (l > r) return 0;
    __int128 cnt = (__int128)r - l + 1;
    __int128 sum_x = (__int128)(l + r) * cnt / 2;
    return (__int128)bb * cnt + (__int128)cc * sum_x;
}

__int128 growth_sum(int u, long long l, long long r) {
    if (l > r) return 0;
    if (c[u] >= 0) return sum_linear(b[u], c[u], l, r);
    long long dec = -c[u];
    long long last_big = (b[u] - 1) / dec;
    long long mid = min(r, last_big);
    __int128 result = 0;
    if (l <= mid) result += sum_linear(b[u], c[u], l, mid);
    if (mid + 1 <= r) result += (__int128)r - (mid + 1) + 1;
    return result;
}

int calc_deadline(int u, long long total_day) {
    if (growth_sum(u, 1, total_day) < need_h[u]) return 0;
    long long left = 1, right = total_day;
    while (left < right) {
        long long mid = (left + right + 1) / 2;
        if (growth_sum(u, mid, total_day) >= need_h[u]) left = mid;
        else right = mid - 1;
    }
    if (left > n) return n;
    return (int)left;
}

bool has_planted_neighbor(int u) {
    if (u == 1) return true;
    for (int v = 1; v <= n; v++) {
        if (edge[u][v] && planted[v]) {
            return true;
        }
    }
    return false;
}

bool dfs_order(int day) {
    if (day == n + 1) {
        return true;
    }
    for (int u = 1; u <= n; u++) {
        if (!planted[u] && has_planted_neighbor(u) && day <= deadline_day[u]) {
            planted[u] = true;
            if (dfs_order(day + 1)) {
                return true;
            }
            planted[u] = false;
        }
    }
    return false;
}

bool check(long long total_day) {
    if (total_day < n) return false;
    for (int i = 1; i <= n; i++) {
        deadline_day[i] = calc_deadline(i, total_day);
        if (deadline_day[i] == 0) return false;
        planted[i] = false;
    }
    return dfs_order(1);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> need_h[i] >> b[i] >> c[i];
    }
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        edge[u][v] = edge[v][u] = true;
    }

    long long left = 1, right = 200;
    while (!check(right)) {
        right *= 2;
    }
    while (left < right) {
        long long mid = (left + right) / 2;
        if (check(mid)) right = mid;
        else left = mid + 1;
    }
    cout << left << '\n';
    return 0;
}
