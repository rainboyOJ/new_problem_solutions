#include <bits/stdc++.h>
using namespace std;

// main2.cpp: 针对小规模树与小 k 的树形 DP / 暴力验证（测试点 1~6）
// 在小规模数据下，我们也可以直接二分通勤半径 r，并通过枚举第一个中心或连通块形态来判定。
// 或者：由于 k <= n，当 k 是任意值时，我们通过剥叶子 + 核心森林的连通块分析进行检查。
// 这里给出一种直观的树上判定算法（二分半径 r + 贪心/搜寻）：
// 事实上，正解 main.cpp 已经完全覆盖所有测试点（O(N log N)），
// main2.cpp 可以作为对照解法：在树上剥叶子 r 轮后，直接显式缩点建出核心树，在核心树上求最长链！
// 这样不需要三邻居前三大值技巧，代码更直观好懂，适合教学讲解核心树的结构！

const int MAXN = 100005;
vector<int> G[MAXN];
int deg[MAXN], tim[MAXN], q_arr[MAXN];
int n, k;

// 显式求出核心树 C 的点数以及在 C 中的最大连通分量/链
bool check_explicit(int r) {
    for (int i = 1; i <= n; i++) {
        deg[i] = G[i].size();
        tim[i] = 0;
    }
    int head = 0, tail = 0;
    for (int i = 1; i <= n; i++) {
        if (deg[i] <= 1) {
            tim[i] = 1;
            q_arr[tail++] = i;
        }
    }
    while (head < tail) {
        int u = q_arr[head++];
        for (int v : G[u]) {
            deg[v]--;
            if (deg[v] == 1) {
                tim[v] = tim[u] + 1;
                q_arr[tail++] = v;
            }
        }
    }

    // 核心树中的点是 tim[u] > r 的点
    vector<int> core_nodes;
    for (int i = 1; i <= n; i++) {
        if (tim[i] > r) {
            core_nodes.push_back(i);
        }
    }

    int sz = core_nodes.size();
    if (sz <= k) return true; // 核心树点数不超过 k，直接全选或任意补点

    // 需要删掉 D = sz - k 个点
    int D = sz - k;
    if (D > 2 * r) return false;

    // 检查核心树中是否存在度为 2 的链，使得删掉长度为 D 的区间后，所有被删点到保留点的距离 <= r - 其悬挂子树深度
    // 标记核心点
    vector<bool> in_core(n + 1, false);
    for (int u : core_nodes) in_core[u] = true;

    // 计算核心树内部每个点的度数
    vector<int> core_deg(n + 1, 0);
    for (int u : core_nodes) {
        for (int v : G[u]) {
            if (in_core[v]) core_deg[u]++;
        }
    }

    // 核心树必须连通，且只能在某条链上挖去长度为 D 的一段
    // 该链上所有点的 core_deg 必须为 2（内部点），两端点可以是度数 >= 1 的点
    // 并且被挖掉的每个点 u，其在原树中除了核心树邻居外的子树深度 h_u 必须满足 dist(u, 保留端点) <= r - h_u
    // 原树中 u 的悬挂深度 h_u 就是 u 的非核心邻居的最大 tim
    vector<int> h(n + 1, 0);
    for (int u : core_nodes) {
        for (int v : G[u]) {
            if (!in_core[v]) {
                h[u] = max(h[u], tim[v]);
            }
        }
    }

    // 遍历核心树中所有极大度为 2 的链
    vector<bool> vis(n + 1, false);
    for (int start_node : core_nodes) {
        if (core_deg[start_node] == 2) continue; // 只从分支点或叶子出发找链
        for (int nxt : G[start_node]) {
            if (!in_core[nxt] || core_deg[nxt] != 2) continue;
            // 找到一条以 start_node 为起点的链
            vector<int> chain;
            int prev = start_node, cur = nxt;
            while (cur && core_deg[cur] == 2) {
                chain.push_back(cur);
                int next_node = 0;
                for (int v : G[cur]) {
                    if (in_core[v] && v != prev) {
                        next_node = v;
                        break;
                    }
                }
                prev = cur;
                cur = next_node;
            }
            int end_node = cur;
            // chain 包含了该段链内部所有度为 2 的点
            int m = chain.size();
            if (m < D) continue;

            // 在该链上滑动窗口检查是否有合法的长度为 D 的删除区间
            // 设链上点从 1 到 m，端点 0 为 start_node，端点 m+1 为 end_node
            // 删去 [L, L + D - 1]，其中 1 <= L 且 L + D - 1 <= m
            // 对每个被删点 chain[j] (0-based j, 即下标 j+1):
            // 到左保留端点 (L-1) 的距离是 (j + 1) - (L - 1) = j - L + 2
            // 到右保留端点 (L + D) 的距离是 (L + D) - (j + 1) = L + D - j - 1
            // 要求 min(j - L + 2, L + D - j - 1) <= r - h[chain[j]]
            // 采用差分数组快速检查
            vector<int> diff(m - D + 3, 0);
            for (int j = 0; j < m; j++) {
                int u = chain[j];
                int b_u = r - h[u];
                // 违背条件: min(j - L + 2, L + D - j - 1) > b_u
                // 即: j - L + 2 > b_u 且 L + D - j - 1 > b_u
                // 整理得: L < j + 2 - b_u  且  L > j + 1 + b_u - D
                int forbid_l = j + 2 + b_u - D;
                int forbid_r = j + 1 - b_u;
                forbid_l = max(1, forbid_l);
                forbid_r = min(m - D + 1, forbid_r);
                if (forbid_l <= forbid_r) {
                    diff[forbid_l]++;
                    diff[forbid_r + 1]--;
                }
            }
            int cur_cnt = 0;
            for (int L = 1; L <= m - D + 1; L++) {
                cur_cnt += diff[L];
                if (cur_cnt == 0) return true; // 存在合法删除方案
            }
        }
    }

    // 还有一种极端情况：整个核心树本身就是一条简单链，没有任何分支点（即所有点度数 <= 2）
    if (core_nodes.size() > 0) {
        bool all_chain = true;
        for (int u : core_nodes) {
            if (core_deg[u] > 2) { all_chain = false; break; }
        }
        if (all_chain) {
            // 找到核心树的两个端点之一
            int leaf = core_nodes[0];
            for (int u : core_nodes) {
                if (core_deg[u] <= 1) { leaf = u; break; }
            }
            vector<int> chain;
            int prev = 0, cur = leaf;
            while (cur) {
                chain.push_back(cur);
                int next_node = 0;
                for (int v : G[cur]) {
                    if (in_core[v] && v != prev) {
                        next_node = v;
                        break;
                    }
                }
                prev = cur;
                cur = next_node;
            }
            int m = chain.size();
            // 在这条整链上删去连续 D 个点，剩下的部分分成 <= 2 个连通块
            // 删除区间 [L, L + D - 1]，可以位于整链的内部（分成 2 块），或者两端（分成 1 块）
            // 差分判定
            vector<int> diff(m - D + 3, 0);
            for (int j = 0; j < m; j++) {
                int u = chain[j];
                int b_u = r - h[u];
                // 如果两端保留，距离 min(j - L + 1, L + D - j) > b_u
                // 考虑端点情况：若保留点存在，则距离按到最近保留点算；若一端为空，则只能靠另一端
                int forbid_l = j + 1 + b_u - D;
                int forbid_r = j - b_u;
                // 注意两端点：如果 L=0（删前缀），右边最近是 chain[D]，距离 (D - j)
                // 为统一，只要 min(左边最近, 右边最近) <= b_u
                // 统一写成通用区间过滤
                for (int L = 0; L <= m - D; L++) {
                    int dist_left = (L == 0 ? 1e9 : (j - (L - 1)));
                    int dist_right = (L + D >= m ? 1e9 : ((L + D) - j));
                    if (j >= L && j < L + D) {
                        if (min(dist_left, dist_right) > b_u) {
                            diff[L + 1]++;
                            diff[L + 2]--;
                        }
                    }
                }
            }
            int cur_cnt = 0;
            for (int L = 0; L <= m - D; L++) {
                cur_cnt += diff[L + 1];
                if (cur_cnt == 0) return true;
            }
        }
    }

    return false;
}

void solve() {
    cin >> n >> k;
    for (int i = 1; i <= n; i++) G[i].clear();
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        G[u].push_back(v);
        G[v].push_back(u);
    }
    int l = 0, r = n;
    while (l < r) {
        int mid = (l + r) / 2;
        if (check_explicit(mid)) r = mid;
        else l = mid + 1;
    }
    cout << l << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int c, t;
    if (!(cin >> c >> t)) return 0;
    while (t--) {
        solve();
    }
    return 0;
}
