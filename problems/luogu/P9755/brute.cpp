/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-06 08:46
 * update_at: 2026-10-01 22:33
 */
// brute.cpp：小数据暴力解，二分天数后递归枚举所有合法的连通种植顺序。
// 只适合 n <= 10 左右的小数据，用来帮助理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 12;

int n;
ll need_h[MAXN]; // 目标高度 a[i]
ll b[MAXN];      // 每天长高 b[i] + x*c[i] 的截距
ll c[MAXN];      // 每天长高的斜率，可为负
bool edge[MAXN][MAXN]; // 邻接矩阵
ll deadline_day[MAXN]; // deadline_day[i]：点 i 的最晚种植日
bool planted[MAXN];    // planted[i]：点 i 是否已经种下

// 等差数列求和：sum_{x=l..r} (bb + cc*x)，用 __int128 防溢出
__int128 sum_linear(ll bb, ll cc, ll l, ll r) {
    if (l > r) return 0;
    __int128 cnt = (__int128)r - l + 1;
    __int128 sum_x = (__int128)(l + r) * cnt / 2;
    return (__int128)bb * cnt + (__int128)cc * sum_x;
}

// 点 u 在第 l..r 天的总生长量：sum_{x=l..r} max(b + x*c, 1)
__int128 growth_sum(int u, ll l, ll r) {
    if (l > r) return 0;
    if (c[u] >= 0) return sum_linear(b[u], c[u], l, r);
    ll dec = -c[u];
    ll last_big = (b[u] - 1) / dec;
    ll mid = min(r, last_big);
    __int128 result = 0;
    if (l <= mid) result += sum_linear(b[u], c[u], l, mid);
    if (mid + 1 <= r) result += (__int128)r - (mid + 1) + 1;
    return result;
}

// 二分点 u 的最晚种植日，不够种返回 0，超过 n 天封顶为 n
ll calc_deadline(int u, ll total_day) {
    if (growth_sum(u, 1, total_day) < need_h[u]) return 0;
    ll left = 1, right = total_day;
    while (left < right) {
        ll mid = (left + right + 1) / 2;
        if (growth_sum(u, mid, total_day) >= need_h[u]) left = mid;
        else right = mid - 1;
    }
    if (left > n) return n;
    return left;
}

// 点 u 现在能不能种：要么是入口 1，要么有已经种好的邻居
bool has_planted_neighbor(int u) {
    if (u == 1) return true;
    for (int v = 1; v <= n; v++) {
        if (edge[u][v] && planted[v]) {
            return true;
        }
    }
    return false;
}

// 枚举第 day 天种哪棵树；能铺满 1..n 天就找到了合法顺序
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

// 判断完成天数 total_day 是否可行
bool check(ll total_day) {
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

    // 先倍增找上界，再二分最小完成天数
    ll left = 1, right = 200;
    while (!check(right)) {
        right *= 2;
    }
    while (left < right) {
        ll mid = (left + right) / 2;
        if (check(mid)) right = mid;
        else left = mid + 1;
    }
    cout << left << '\n';
    return 0;
}
