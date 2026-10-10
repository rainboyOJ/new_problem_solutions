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

const int INF = 1000000000;

int n, m;
int price[100005];
vector<int> out[100005], rev[100005];
bool from1[100005], to_n[100005];
int floor_[100005];

// 沿邻接表标出从 start 出发能到达的全部城市
void walk(int start, vector<int> g[], bool seen[]) {
    seen[start] = true;
    vector<int> stack;
    stack.push_back(start);
    while (!stack.empty()) {
        int u = stack.back(); stack.pop_back();
        for (size_t i = 0; i < g[u].size(); i++) {
            int v = g[u][i];
            if (!seen[v]) { seen[v] = true; stack.push_back(v); }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> price[i];
    for (int i = 0; i < m; i++) {
        int x, y, z;
        cin >> x >> y >> z;
        out[x].push_back(y);
        rev[y].push_back(x);
        if (z == 2) {
            out[y].push_back(x);
            rev[x].push_back(y);
        }
    }
    for (int i = 1; i <= n; i++) { from1[i] = false; to_n[i] = false; floor_[i] = INF; }
    walk(1, out, from1);
    walk(n, rev, to_n);

    // 按价格 1..100 分层多源传播：floor_[u] = 能到达 u 的可买入城市最低价
    vector<vector<int> > by_price(101);
    for (int u = 1; u <= n; u++) by_price[price[u]].push_back(u);
    for (int cost_ = 1; cost_ <= 100; cost_++) {
        for (size_t i = 0; i < by_price[cost_].size(); i++) {
            int src = by_price[cost_][i];
            if (!from1[src] || floor_[src] <= cost_) continue;
            floor_[src] = cost_;
            vector<int> stack;
            stack.push_back(src);
            while (!stack.empty()) {
                int u = stack.back(); stack.pop_back();
                for (size_t t = 0; t < out[u].size(); t++) {
                    int v = out[u][t];
                    if (floor_[v] > cost_) {
                        floor_[v] = cost_;
                        stack.push_back(v);
                    }
                }
            }
        }
    }

    int ans = 0;
    for (int s = 1; s <= n; s++)
        if (to_n[s] && floor_[s] < INF)
            ans = max(ans, price[s] - floor_[s]);
    cout << ans << "\n";
    return 0;
}
