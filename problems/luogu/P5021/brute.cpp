/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-11-11 00:15
 * update_at: 2026-11-11 00:15
 */

// brute.cpp：小数据验证基线
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Edge {
    int to, weight;
};

vector<Edge> tree[105];
int total_ans;

int dfs(int u, int fa, int mid) {
    vector<int> a;
    for (const auto& e : tree[u]) {
        if (e.to == fa) continue;
        int d = dfs(e.to, u, mid) + e.weight;
        if (d >= mid) total_ans++;
        else a.push_back(d);
    }
    sort(a.begin(), a.end());
    vector<bool> used(a.size(), false);
    for (size_t i = 0; i < a.size(); ++i) {
        if (used[i]) continue;
        for (size_t j = a.size() - 1; j > i; --j) {
            if (!used[j] && a[i] + a[j] >= mid) {
                used[i] = used[j] = true;
                total_ans++;
                break;
            }
        }
    }
    for (int i = (int)a.size() - 1; i >= 0; --i) {
        if (!used[i]) return a[i];
    }
    return 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    if (!(cin >> n >> m)) return 0;
    int tot_w = 0;
    for (int i = 1; i < n; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        tree[u].push_back({v, w});
        tree[v].push_back({u, w});
        tot_w += w;
    }

    int l = 1, r = tot_w, res = 1;
    while (l <= r) {
        int mid = l + (r - l) / 2;
        total_ans = 0;
        dfs(1, 0, mid);
        if (total_ans >= m) {
            res = mid;
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }
    cout << res << "\n";
    return 0;
}
