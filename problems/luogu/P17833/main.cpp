/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-31 21:33
 * update_at: 2026-10-31 21:33
 */
#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long ll;

const int MAXN = 2000005;
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

ll interval_size(ll left, ll right) {
    return max(0LL, right - left + 1);
}

// 保证接出的部分只有一条路径，而且不会让分叉核心的位置发生变化。
void count_extensions() {
    for (ll i = n; i >= 1; i--) {
        suffix_count[i] = 1; // 不再往右接，直接把 i 当终点
        ll r = rightmost[i];
        if (r == i) continue;

        // 最后一步没跳满：终点 j<r，且反向最左一步恰好回到 i。
        ll first_end = max(i + 1, rightmost[i - 1] + 1);
        suffix_count[i] += interval_size(first_end, r - 1);
        // 跳满到 r：必须能原路回到 i，之后复用 r 的全部合法接法。
        if (leftmost[r] == i) suffix_count[i] += suffix_count[r];
    }
    for (ll i = 1; i <= n; i++) {
        prefix_count[i] = 1; // 不再往左接，直接把 i 当起点
        ll l = leftmost[i];
        if (l == i) continue;

        ll last_start = min(i - 1, leftmost[i + 1] - 1);
        prefix_count[i] += interval_size(l + 1, last_start);
        if (rightmost[l] == i) prefix_count[i] += prefix_count[l];
    }
}

ll count_pairs() {
    ll answer = 0;
    for (ll u = 1; u <= n; u++) {
        ll p = rightmost[u]; // 唯一分叉的两个点必须是 p-1 和 p
        if (p <= u + 1) continue; // u 右侧还不够放下两个分叉点

        // 汇合点 v 要在 p 右边，且 leftmost[v]=p-1。
        ll first_meet = max(p + 1, rightmost[p - 2] + 1);
        ll last_meet = rightmost[p - 1];
        if (first_meet > last_meet) continue;

        ll left_choices = 1;
        if (leftmost[p - 1] == u) left_choices = prefix_count[u];

        // 每个汇合点都能直接当终点；只有跳满到 rightmost[p] 才能继续接。
        ll right_choices = interval_size(first_meet, last_meet);
        if (last_meet == rightmost[p]) {
            right_choices += suffix_count[last_meet] - 1;
        }
        answer += left_choices * right_choices;
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
