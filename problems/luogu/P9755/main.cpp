/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-06 08:46
 * update_at: 2026-10-01 22:33
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
vector<int> order_nodes; // BFS 序，倒着遍历就是自底向上
int order_cnt;           // order_nodes 的长度，避免 size() 强转

// 等差数列求和：sum_{x=l..r} (bb + cc*x)
// 值域到 1e27 量级，用 __int128 防溢出（GCC 扩展，OJ 常用）。
__int128 sum_linear(ll bb, ll cc, ll l, ll r) {
    if (l > r) {
        return 0;
    }
    __int128 cnt = (__int128)r - l + 1;
    __int128 sum_x = (__int128)(l + r) * cnt / 2;
    return (__int128)bb * cnt + (__int128)cc * sum_x;
}

// 点 u 在第 l..T 天的总生长量：sum_{x=l..r} max(b + x*c, 1)
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
        result += (__int128)r - (mid + 1) + 1;
    }
    return result;
}

// 二分点 u 的最晚种植日：最小的 d 满足 sum(d..T) >= a[u]。
// 种到第 1 天都不够就返回 0；超过 n 天没意义，封顶为 n。
ll calc_deadline(int u, ll total_day) {
    if (growth_sum(u, 1, total_day) < need_h[u]) {
        return 0;
    }

    ll left = 1;
    ll right = total_day;
    while (left < right) {
        ll mid = (left + right + 1) / 2;
        if (growth_sum(u, mid, total_day) >= need_h[u]) {
            left = mid;
        } else {
            right = mid - 1;
        }
    }

    if (left > n) {
        return n;
    }
    return left;
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

    // 自底向上求每棵子树里最小的 deadline
    for (int i = order_cnt - 1; i >= 0; i--) {
        int u = order_nodes[i];
        min_subtree_deadline[u] = deadline_day[u];
        int child_cnt = child[u].size();
        for (int j = 0; j < child_cnt; j++) {
            int v = child[u][j];
            min_subtree_deadline[u] = min(min_subtree_deadline[u], min_subtree_deadline[v]);
        }
    }

    // 每天在"可种的点"里种 min_subtree_deadline 最小的，
    // 优先打开包含紧急节点的子树；种下时检查自己的 deadline 有没有过期。
    priority_queue<pair<ll, int>, vector<pair<ll, int> >, greater<pair<ll, int> > > heap;
    heap.push(make_pair(min_subtree_deadline[1], 1));

    for (int day = 1; day <= n; day++) {
        if (heap.empty()) {
            return false;
        }
        int u = heap.top().second;
        heap.pop();
        if (deadline_day[u] < day) {
            return false;
        }
        int child_cnt = child[u].size();
        for (int j = 0; j < child_cnt; j++) {
            int v = child[u][j];
            heap.push(make_pair(min_subtree_deadline[v], v));
        }
    }

    return true;
}

// 以 1 为根 BFS 建有根树，同时记录 BFS 序
void build_rooted_tree() {
    vector<int> parent(n + 1, 0);
    queue<int> q;
    parent[1] = -1;
    q.push(1);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        order_nodes.push_back(u);
        int adj_cnt = g[u].size();
        for (int i = 0; i < adj_cnt; i++) {
            int v = g[u][i];
            if (v == parent[u]) {
                continue;
            }
            parent[v] = u;
            child[u].push_back(v);
            q.push(v);
        }
    }
    order_cnt = order_nodes.size();
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

    build_rooted_tree();

    // 二分答案：保证 1e9 天内有解
    ll left = 1;
    ll right = 1000000000LL;
    while (left < right) {
        ll mid = (left + right) / 2;
        if (check(mid)) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }

    cout << left << '\n';
    return 0;
}
