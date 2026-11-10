/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-11-01 08:26
 * update_at: 2026-11-10 20:26
 */
// main.cpp：二分答案 + 树上分层剥皮 + 核心度二链差分覆盖检测。
// 核心思路：二分通勤半径 radius。选定 radius 后，剥掉所有叶子向内长 radius 步得到核心 core。
// 方案合法当且仅当核心点数减 k 个点能在某条度为 2 的链上连续删除，且被删点的外向子树深度均 <= radius。
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// 点号、度数、轮数和差分覆盖数都不超过 10^6，用 int 即可。
const int MAXN = 1000005;
int n, k;
vector<int> graph[MAXN];
int peel_time[MAXN]; // 第几轮被剥去，原树叶子为第一轮
int degree_now[MAXN], pending[MAXN];
int core_size[MAXN]; // core_size[r]：剥去 r 轮后还剩多少点
int first_neighbor[MAXN], second_neighbor[MAXN]; // 当前核心中的两个邻居
int outside_height[MAXN]; // 经过非核心邻居走出去，最深有多少条边
bool chain_node[MAXN]; // 当前核心中度为二、尚未扫描的点
int chain[MAXN], difference[MAXN]; // 当前链的点号、禁止起点区间的差分

// 同时剥去当前所有叶子，队列自然按轮数递增处理。
void prepare_peeling() {
    int head = 0, tail = 0;
    for (int u = 1; u <= n; u++) {
        degree_now[u] = graph[u].size();
        peel_time[u] = 0;
        if (degree_now[u] <= 1) {
            peel_time[u] = 1;
            pending[tail++] = u;
        }
    }
    while (head < tail) {
        int u = pending[head++];
        for (int v : graph[u]) {
            degree_now[v]--;
            if (degree_now[v] == 1) {
                peel_time[v] = peel_time[u] + 1;
                pending[tail++] = v;
            }
        }
    }
    fill(core_size, core_size + n + 2, 0);
    for (int u = 1; u <= n; u++) core_size[peel_time[u] - 1]++;
    for (int r = n - 1; r >= 0; r--) core_size[r] += core_size[r + 1];
}

// chain[1..m] 是一整条度二链，删 [s+1, s+removed]，保留其左右端点。
// 通过差分数组标记每个被删点外向枝条所禁止的删除起点 s。
bool check_chain(int m, int removed, int radius) {
    if (m < removed) return false;
    int choices = m - removed + 1; // 合法起点 s 为 0..choices-1
    fill(difference, difference + choices + 1, 0);
    for (int j = 1; j <= m; j++) {
        int budget = radius - outside_height[chain[j]];
        int left = max(0, j + budget - removed);
        int right = min(choices, j - budget); // 禁止区间 [left, right)
        if (left < right) {
            difference[left]++;
            difference[right]--;
        }
    }
    int blocked = 0;
    for (int s = 0; s < choices; s++) {
        blocked += difference[s];
        if (blocked == 0) return true; // 找到一个不违反任何外枝覆盖限制的连续删除区间
    }
    return false;
}

// 从每条度二链的端头出发，扫过后直接取消标记，避免重复处理。
bool scan_chains(int removed, int radius) {
    for (int start = 1; start <= n; start++) {
        if (!chain_node[start]) continue;
        int a = first_neighbor[start], b = second_neighbor[start];
        if (chain_node[a] && chain_node[b]) continue; // 必须从链端点出发
        int previous = chain_node[a] ? b : a;
        int u = start, length = 0;
        while (chain_node[u]) {
            chain[length + 1] = u;
            length++;
            chain_node[u] = false;
            int next_node = (first_neighbor[u] == previous ?
                             second_neighbor[u] : first_neighbor[u]);
            previous = u;
            u = next_node;
        }
        if (check_chain(length, removed, radius)) return true;
    }
    return false;
}

int top_first[MAXN], top_second[MAXN]; // 邻居中剥叶时间最大的两个点号
int third_time[MAXN]; // 邻居剥叶时间的第三大值，不足三个时为零

// 判定只需知道哪些邻居能活过 radius 轮，提前保留前三大即可。
void prepare_neighbors() {
    for (int u = 1; u <= n; u++) {
        int a = 0, b = 0, third = 0;
        for (int neighbor : graph[u]) {
            int v = neighbor;
            if (peel_time[v] > peel_time[a]) swap(v, a);
            if (peel_time[v] > peel_time[b]) swap(v, b);
            third = max(third, peel_time[v]);
        }
        top_first[u] = a;
        top_second[u] = b;
        third_time[u] = third;
    }
}

// 检查通勤半径为 radius 时是否满足条件
bool check(int radius) {
    int removed = core_size[radius] - k;
    if (removed <= 0) return true; // 核心剩余点数已不超过 k，无需删除
    if (removed > 2 * radius) return false; // 单个被删区间长度不能超过 2 * radius 的覆盖极限
    for (int u = 1; u <= n; u++) {
        first_neighbor[u] = top_first[u];
        second_neighbor[u] = top_second[u];
        outside_height[u] = third_time[u];
        chain_node[u] = (peel_time[u] > radius &&
                         peel_time[top_second[u]] > radius &&
                         third_time[u] <= radius);
    }
    return scan_chains(removed, radius);
}

void solve() {
    cin >> n >> k;
    for (int u = 1; u <= n; u++) graph[u].clear();
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    prepare_peeling();
    prepare_neighbors();

    // 闭区间二分通勤半径 radius，ans 记账
    int left = 0, right = n, ans = n;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (check(mid)) {
            ans = mid;
            right = mid - 1; // 答案可行，向左收缩寻找更小半径
        } else {
            left = mid + 1;  // 半径不足以覆盖，向右扩大
        }
    }
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int c, tests;
    if (!(cin >> c >> tests)) return 0;
    while (tests--) solve();
    return 0;
}
