/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-11-11 00:15
 * update_at: 2026-11-11 00:15
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

using ll = long long;

const int MAXN = 50005;

struct Edge {
    int to;
    int weight;
};

vector<Edge> tree[MAXN];
int track_count; // 当前 check 统计出的合格赛道数量

// DFS 返回以 u 为根的子树向上传导的最长半链长度
int dfs(int u, int fa, int mid) {
    multiset<int> s;

    for (const auto& e : tree[u]) {
        if (e.to == fa) continue;
        int d = dfs(e.to, u, mid) + e.weight;
        if (d >= mid) {
            track_count++; // 自身已满足赛道长度要求
        } else {
            s.insert(d);
        }
    }

    int max_leftover = 0;

    // 在 s 中尽量贪心配对成 >= mid 的路径
    while (!s.empty()) {
        if (s.size() == 1) {
            max_leftover = max(max_leftover, *s.begin());
            break;
        }

        auto it_first = s.begin();
        int val = *it_first;
        s.erase(it_first);

        // 寻找能与 val 配对的最小元素 >= mid - val
        auto it_match = s.lower_bound(mid - val);
        if (it_match == s.end()) {
            // 没有能与 val 配对的元素，val 只能留下来尝试上传给父节点
            max_leftover = max(max_leftover, val);
        } else {
            // 配对成功，形成一条赛道
            track_count++;
            s.erase(it_match);
        }
    }

    return max_leftover;
}

bool check(int mid, int m) {
    track_count = 0;
    dfs(1, 0, mid);
    return track_count >= m;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    int total_weight = 0;
    for (int i = 1; i < n; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        tree[u].push_back({v, w});
        tree[v].push_back({u, w});
        total_weight += w;
    }

    int left = 1, right = total_weight;
    int ans = 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (check(mid, m)) {
            ans = mid;
            left = mid + 1; // 尝试更大的长度
        } else {
            right = mid - 1;
        }
    }

    cout << ans << "\n";

    return 0;
}
