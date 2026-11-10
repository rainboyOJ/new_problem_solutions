/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-06 08:46
 * update_at: 2026-11-10 20:24
 */
// main.cpp：二分完成天数，把每个点转成最晚种植日，再做树上 EDF 调度。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 100005;

int n;
ll need_h[MAXN]; // 目标高度 a[i]
ll b[MAXN];      // 每天长高 b[i] + x*c[i] 的截距
ll c[MAXN];      // 每天长高的斜率，可为负

vector<int> g[MAXN];    // 原树邻接表
vector<int> child[MAXN]; // 以 1 为根的有根树的孩子表
ll deadline_day[MAXN];   // deadline_day[i]：点 i 的最晚种植日
ll min_subtree_deadline[MAXN]; // 子树内最小的 deadline，做 EDF 优先级

// 等差数列求和：sum_{x=l..r} (bb + cc*x)
// 值域到 1e27 量级，用 __int128 防溢出（GCC 扩展，OJ 常用）。
__int128 sum_linear(ll bb, ll cc, ll l, ll r) {
    if (l > r) {
        return 0;
    }
    __int128 cnt = static_cast<__int128>(r) - l + 1;
    __int128 sum_x = static_cast<__int128>(l + r) * cnt / 2;
    return static_cast<__int128>(bb) * cnt + static_cast<__int128>(cc) * sum_x;
}

// 点 u 在第 l..r 天的总生长量：sum_{x=l..r} max(b + x*c, 1)
// c < 0 时把区间切成两段：b + x*c >= 1 的部分等差求和，后面每天按 1 算。
__int128 growth_sum(int u, ll l, ll r) {
    if (l > r) {
        return 0;
    }
    if (c[u] >= 0) {
        return sum_linear(b[u], c[u], l, r);
    }

    ll dec = -c[u];
    ll last_big = (b[u] - 1) / dec; // x <= last_big 时 b + x*c 至少为 1
    ll mid = min(r, last_big);
    __int128 result = 0;
    if (l <= mid) {
        result += sum_linear(b[u], c[u], l, mid);
    }
    if (mid + 1 <= r) {
        result += static_cast<__int128>(r) - (mid + 1) + 1;
    }
    return result;
}

// 二分点 u 的最晚种植日：满足 sum(d..total_day) >= a[u] 的最大天数 d。
// 种到第 1 天都不够就返回 0；超过 n 天封顶为 n。
ll calc_deadline(int u, ll total_day) {
    if (growth_sum(u, 1, total_day) < need_h[u]) {
        return 0;
    }

    ll l = 1;
    ll r = total_day;
    ll ans = 1;
    while (l <= r) {
        ll mid = l + (r - l) / 2;
        if (growth_sum(u, mid, total_day) >= need_h[u]) {
            ans = mid;
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }

    if (ans > n) {
        return n;
    }
    return ans;
}

// 直接递归后序遍历：自底向上统计子树内最小最晚种植日
void dfs_subtree_deadline(int u) {
    min_subtree_deadline[u] = deadline_day[u];
    for (int v : child[u]) {
        dfs_subtree_deadline(v);
        min_subtree_deadline[u] = min(min_subtree_deadline[u], min_subtree_deadline[v]);
    }
}

// 判断完成天数 total_day 是否可行：
// 每天种一个点、父亲早于儿子、每个点不晚于自己的 deadline。
bool check(ll total_day) {
    if (total_day < n) {
        return false;
    }

    for (int i = 1; i <= n; i++) {
        deadline_day[i] = calc_deadline(i, total_day);
        if (deadline_day[i] == 0) {
            return false;
        }
    }

    // 递归自底向上求每棵子树里最小的 deadline
    dfs_subtree_deadline(1);

    // 每天在"可种的点"里种 min_subtree_deadline 最小的，
    // 优先打开包含紧急节点的子树；种下时检查自己的 deadline 有没有过期。
    priority_queue<pair<ll, int>, vector<pair<ll, int> >, greater<pair<ll, int> > > heap;
    heap.push({min_subtree_deadline[1], 1});

    for (int day = 1; day <= n; day++) {
        if (heap.empty()) {
            return false;
        }
        int u = heap.top().second;
        heap.pop();
        if (deadline_day[u] < day) {
            return false;
        }
        for (int v : child[u]) {
            heap.push({min_subtree_deadline[v], v});
        }
    }

    return true;
}

// 递归以 1 为根建有根树 child 表
void dfs_build_tree(int u, int fa) {
    for (int v : g[u]) {
        if (v == fa) {
            continue;
        }
        child[u].push_back(v);
        dfs_build_tree(v, u);
    }
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
        g[u].push_back(v);
        g[v].push_back(u);
    }

    dfs_build_tree(1, 0);

    // 二分答案：闭区间 while (l <= r) + ans 记账，保证 1e9 天内有解
    ll l = n;
    ll r = 1000000000LL;
    ll ans = r;
    while (l <= r) {
        ll mid = l + (r - l) / 2;
        if (check(mid)) {
            ans = mid;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }

    cout << ans << '\n';
    return 0;
}
