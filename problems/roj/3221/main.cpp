/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-10 11:30
 * update_at: 2026-10-10 11:30
 */
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

vector<int> adj[125];   // 左副本 u 喜欢的右副本
int match_r[125];
bool seen[125];

bool find_augment(int u) {
    for (size_t i = 0; i < adj[u].size(); i++) {
        int v = adj[u][i];
        if (seen[v]) continue;
        seen[v] = true;
        if (match_r[v] == 0 || find_augment(match_r[v])) {
            match_r[v] = u;
            return true;
        }
    }
    return false;
}

int max_matching(int n) {
    for (int i = 0; i <= n; i++) match_r[i] = 0;
    int matched = 0;
    for (int u = 1; u <= n; u++) {
        for (int i = 0; i <= n; i++) seen[i] = false;
        if (find_augment(u)) matched++;
    }
    return matched;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) {
        int n, m;
        cin >> n >> m;
        for (int i = 1; i <= n; i++) adj[i].clear();
        for (int i = 0; i < m; i++) {
            int x, y;
            cin >> x >> y;
            adj[x].push_back(y);
        }
        // 最小路径点覆盖 = 顶点数 - 最大匹配数
        cout << n - max_matching(n) << "\n";
    }
    return 0;
}
