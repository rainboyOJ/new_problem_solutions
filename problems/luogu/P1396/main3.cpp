/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-21 16:59
 * update_at: 2026-10-21 17:30
 */
// 营救的第三种解法：二分答案 + BFS。
// 答案具有单调性：若限制拥挤度上界为 L 时 s 能到 t，那么更大的 L 也一定能到。
// 于是二分 L，每次只走拥挤度 <= L 的边做一次 BFS/DFS 判连通。
// 复杂度 O((n+m) log W)，W 为最大拥挤度，本题 W <= 1e4，约 14 次搜索。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 10000 + 5;

struct Edge {
    int to;
    ll w;
};

int n, m, start_node, target_node;
vector<Edge> g[MAXN];
bool visited[MAXN];

// 只走拥挤度 <= limit 的边，判断 s 能否到达 t
bool reachable_within(ll limit) {
    fill(visited + 1, visited + n + 1, false);
    visited[start_node] = true;

    vector<int> st;
    st.push_back(start_node);
    while (!st.empty()) {
        int u = st.back();
        st.pop_back();
        if (u == target_node) return true;
        for (const Edge &e : g[u]) {
            if (e.w > limit) continue;  // 拥挤度超限的大道不能走
            if (visited[e.to]) continue;
            visited[e.to] = true;
            st.push_back(e.to);
        }
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> start_node >> target_node;
    ll max_w = 0;
    for (int i = 0; i < m; i++) {
        int u, v;
        ll w;
        cin >> u >> v >> w;
        g[u].push_back({v, w});
        g[v].push_back({u, w});
        max_w = max(max_w, w);
    }

    if (start_node == target_node) {
        cout << 0 << '\n';  // 不用走路，没有任何一段拥挤度
        return 0;
    }

    // 二分最小的可行上界：[low, high] 内一定存在答案
    ll low = 1, high = max_w;
    while (low < high) {
        ll mid = low + (high - low) / 2;
        if (reachable_within(mid)) {
            high = mid;  // mid 可行，答案可能是 mid 或更小
        } else {
            low = mid + 1;  // mid 不可行，答案一定更大
        }
    }

    cout << low << '\n';
    return 0;
}
