/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-31 21:33
 * update_at: 2026-10-31 21:33
 */
// main2.cpp：直接枚举接法和分叉段的 O(n²) 版本，只用于 n<=5000。
#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long ll;

const int MAXN = 5005;
ll n, d;
ll x[MAXN]; // 已按从小到大给出的坐标
ll rightmost[MAXN], leftmost[MAXN]; // 一步能到达的最右、最左下标，包含自己
ll prefix_count[MAXN]; // 能无分叉地接到该点、且正向贪心恰好落到该点的起点数
ll suffix_count[MAXN]; // 能无分叉地从该点接出、且反向贪心恰好回到该点的终点数

// 坐标有序，两个边界指针都只需单向移动。
void build_reach() {
    ll r = 1;
    for (ll i = 1; i <= n; i++) {
        while (r < n && x[r + 1] - x[i] <= d) r++;
        rightmost[i] = r;
    }
    ll l = n;
    for (ll i = n; i >= 1; i--) {
        while (l > 1 && x[i] - x[l - 1] <= d) l--;
        leftmost[i] = l;
    }
    rightmost[0] = 0;
    leftmost[n + 1] = n + 1;
}

// 先把所有候选终点、起点逐个检查，线性版会把循环换成区间长度。
void count_extensions() {
    for (ll i = n; i >= 1; i--) {
        suffix_count[i] = 1;
        ll r = rightmost[i];
        if (r == i) continue;
        for (ll j = i + 1; j < r; j++) {
            if (leftmost[j] == i) suffix_count[i]++;
        }
        if (leftmost[r] == i) suffix_count[i] += suffix_count[r];
    }
    for (ll i = 1; i <= n; i++) {
        prefix_count[i] = 1;
        ll l = leftmost[i];
        if (l == i) continue;
        for (ll j = l + 1; j < i; j++) {
            if (rightmost[j] == i) prefix_count[i]++;
        }
        if (rightmost[l] == i) prefix_count[i] += prefix_count[l];
    }
}

ll count_pairs() {
    ll answer = 0;
    for (ll u = 1; u <= n; u++) {
        ll p = rightmost[u];
        if (p <= u + 1) continue;
        for (ll v = p + 1; v <= rightmost[p]; v++) {
            if (leftmost[v] != p - 1) continue;
            ll left_choices = 1, right_choices = 1;
            if (leftmost[p - 1] == u) left_choices = prefix_count[u];
            if (v == rightmost[p]) right_choices = suffix_count[v];
            answer += left_choices * right_choices;
        }
    }
    return answer;
}

void solve() {
    scanf("%lld%lld", &n, &d);
    for (ll i = 1; i <= n; i++) scanf("%lld", &x[i]);
    build_reach();
    count_extensions();
    printf("%lld\n", count_pairs());
}

int main() {
    ll c, tests;
    if (scanf("%lld%lld", &c, &tests) != 2) return 0;
    while (tests--) solve();
    return 0;
}
