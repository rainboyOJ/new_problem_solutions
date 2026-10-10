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

int n, p;
int state[105];      // 神经元状态
int limit[105];      // 阈值
vector<pair<int, int> > adj[105];   // (v, w)
int indeg[105], outdeg[105];
int remain[105];

// 按拓扑序推进网络
void simulate() {
    vector<int> ready;
    for (int i = 1; i <= n; i++) {
        remain[i] = indeg[i];
        if (indeg[i] == 0) ready.push_back(i);
    }
    while (!ready.empty()) {
        int u = ready.back(); ready.pop_back();
        for (size_t i = 0; i < adj[u].size(); i++) {
            int v = adj[u][i].first, w = adj[u][i].second;
            if (state[u] > 0) state[v] += state[u] * w;
            remain[v]--;
            if (remain[v] == 0) ready.push_back(v);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> p;
    for (int i = 1; i <= n; i++) {
        cin >> state[i] >> limit[i];
    }
    for (int i = 0; i < p; i++) {
        int a, b, w;
        cin >> a >> b >> w;
        adj[a].push_back(make_pair(b, w));
        indeg[b]++;
        outdeg[a]++;
    }
    // 阈值先扣：有上游的神经元减 U_i
    for (int i = 1; i <= n; i++)
        if (indeg[i]) state[i] -= limit[i];

    simulate();

    bool any = false;
    for (int i = 1; i <= n; i++) {
        if (outdeg[i] == 0 && state[i] > 0) {
            cout << i << " " << state[i] << "\n";
            any = true;
        }
    }
    if (!any) cout << "NULL\n";
    return 0;
}
