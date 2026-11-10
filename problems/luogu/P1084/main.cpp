/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-11-10 23:05
 * update_at: 2026-11-10 23:05
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

using ll = long long;

const int MAXN = 50005;
const int MAX_LOG = 18;

// 树的边结构
struct Edge {
    int to;
    int weight;
};

vector<Edge> tree[MAXN];

// 倍增祖先与距离
int up[MAXN][MAX_LOG];
ll dist_to_anc[MAXN][MAX_LOG];

// 军队驻扎位置
int army[MAXN];

// 标记某个节点是否已被驻扎
bool has_army[MAXN];

// 标记根节点的某个直接子树是否需要被覆盖
bool need_cover[MAXN];

// 军队到达根节点后的信息
struct RestArmy {
    ll rest_time;
    int root_son; // 从根节点的哪个子树走出来的
};

// 根节点的儿子节点信息
struct SonInfo {
    int id;
    ll dist;
};

// DFS 预处理倍增表
void dfs_init(int u, int fa, int w) {
    up[u][0] = fa;
    dist_to_anc[u][0] = w;
    for (int j = 1; j < MAX_LOG; ++j) {
        up[u][j] = up[up[u][j - 1]][j - 1];
        dist_to_anc[u][j] = dist_to_anc[u][j - 1] + dist_to_anc[up[u][j - 1]][j - 1];
    }

    for (const auto& e : tree[u]) {
        if (e.to == fa) continue;
        dfs_init(e.to, u, e.weight);
    }
}

// 检查子树 u 的叶子是否全部被封锁
bool dfs_check(int u, int fa) {
    if (has_army[u]) return true; // 当前点有军队，整棵子树已被覆盖

    bool is_leaf = true;
    for (const auto& e : tree[u]) {
        if (e.to == fa) continue;
        is_leaf = false;
        if (!dfs_check(e.to, u)) {
            return false;
        }
    }

    // 如果是叶子且未被驻扎，则未被覆盖
    if (is_leaf) return false;
    return true;
}

bool check(ll mid, int n, int m, const vector<SonInfo>& sons) {
    for (int i = 1; i <= n; ++i) {
        has_army[i] = false;
    }

    vector<RestArmy> rest_armies;
    // min_rest_army[v] 记录从根儿子 v 走出来的军队中剩余时间最小的值（若有）
    // 用于自保贪心判断
    vector<pair<ll, int>> son_armies; // (rest_time, army_idx)

    for (int i = 1; i <= m; ++i) {
        int u = army[i];
        ll cur_time = mid;

        // 倍增向上跳，只要不超过根节点 1
        for (int j = MAX_LOG - 1; j >= 0; --j) {
            if (up[u][j] > 1 && dist_to_anc[u][j] <= cur_time) {
                cur_time -= dist_to_anc[u][j];
                u = up[u][j];
            }
        }

        // 检查是否能跨过根节点 1
        if (up[u][0] == 1 && dist_to_anc[u][0] <= cur_time) {
            // 能到达根节点 1
            rest_armies.push_back({cur_time - dist_to_anc[u][0], u});
        } else {
            // 不能到达根节点 1，停在 u
            has_army[u] = true;
        }
    }

    // 检查根的各个儿子的子树覆盖情况
    vector<SonInfo> uncovered_sons;
    for (const auto& son : sons) {
        if (!dfs_check(son.id, 1)) {
            uncovered_sons.push_back(son);
        }
    }

    // 将能到根的军队按剩余时间升序排序
    sort(rest_armies.begin(), rest_armies.end(), [](const RestArmy& a, const RestArmy& b) {
        return a.rest_time < b.rest_time;
    });

    // 记录每个根儿子是否已有“留守”军队
    // 若某个未覆盖的子树有军队能够到达根节点，且该军队无法去别处或它是该子树唯一的最小代价者，先自保
    vector<bool> used_army(rest_armies.size(), false);
    vector<int> min_army_for_son(n + 1, -1);
    for (int i = 0; i < static_cast<int>(rest_armies.size()); ++i) {
        int sid = rest_armies[i].root_son;
        if (min_army_for_son[sid] == -1) {
            min_army_for_son[sid] = i;
        }
    }

    vector<SonInfo> final_uncovered;
    for (const auto& son : uncovered_sons) {
        int aidx = min_army_for_son[son.id];
        // 如果有从该子树出来的军队，且该军队剩余时间不足以去别的子树再回来（rest_time < 2 * son.dist）
        if (aidx != -1 && rest_armies[aidx].rest_time < 2 * son.dist) {
            used_army[aidx] = true;
        } else {
            final_uncovered.push_back(son);
        }
    }

    // 收集剩余未使用的军队
    vector<ll> free_armies;
    for (size_t i = 0; i < rest_armies.size(); ++i) {
        if (!used_army[i]) {
            free_armies.push_back(rest_armies[i].rest_time);
        }
    }

    // 排序未覆盖的儿子（按到根的距离从小到大）
    sort(final_uncovered.begin(), final_uncovered.end(), [](const SonInfo& a, const SonInfo& b) {
        return a.dist < b.dist;
    });

    // 双指针贪心匹配
    size_t army_ptr = 0;
    for (const auto& son : final_uncovered) {
        while (army_ptr < free_armies.size() && free_armies[army_ptr] < son.dist) {
            army_ptr++;
        }
        if (army_ptr == free_armies.size()) {
            return false; // 无法覆盖
        }
        army_ptr++;
    }

    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) return 0;

    ll total_dist = 0;
    for (int i = 1; i < n; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        tree[u].push_back({v, w});
        tree[v].push_back({u, w});
        total_dist += w;
    }

    int m;
    cin >> m;
    for (int i = 1; i <= m; ++i) {
        cin >> army[i];
    }

    // 预处理倍增
    dfs_init(1, 0, 0);

    // 收集根节点的直接儿子
    vector<SonInfo> sons;
    for (const auto& e : tree[1]) {
        sons.push_back({e.to, e.weight});
    }

    // 军队总数必须不小于根节点的直接子节点数
    if (m < static_cast<int>(sons.size())) {
        cout << -1 << "\n";
        return 0;
    }

    // 二分答案
    ll left = 0, right = total_dist;
    ll ans = -1;

    while (left <= right) {
        ll mid = left + (right - left) / 2;
        if (check(mid, n, m, sons)) {
            ans = mid;
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }

    cout << ans << "\n";

    return 0;
}
