/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-24 17:45
 * update_at: 2026-10-24 17:45
 */
// P5536 【XR-3】核心城市
// 剥叶分层视角：每轮把当前所有叶子剥掉一层，层号 = 被剥掉的轮次。
// 层号最大的 k 个点天然连通，正好当核心；答案就是第 k+1 大的层号。
#include <bits/stdc++.h>
using namespace std;

const int maxn = 100000 + 5; // 城市数上限

typedef long long ll;

ll n;                  // 城市数
ll k;                  // 核心城市个数
vector<int> g[maxn];   // g[u]：与城市 u 直接相连的城市
int remain_deg[maxn];  // remain_deg[u]：剥叶过程中 u 还没被剥掉的边数
int layer[maxn];       // layer[u]：u 在第几轮被剥掉，叶子是第 1 轮

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> k;
    for (ll i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
        remain_deg[u]++;
        remain_deg[v]++;
    }

    // 第 1 轮：所有叶子入队，层号记为 1（n=2 时两个点度数都是 1）。
    queue<int> q;
    for (int u = 1; u <= n; u++) {
        if (remain_deg[u] <= 1) {
            layer[u] = 1;
            q.push(u);
        }
    }

    // 逐轮往里剥：出队一个已被剥掉的点 u，把它唯一剩下的邻居 v 的边数减一；
    // v 减到 1 说明 v 也成了叶子，层号 = u 的层号 + 1，入队等下一轮处理。
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v : g[u]) {
            if (remain_deg[v] <= 1) continue; // 已剥掉的邻居不再处理
            remain_deg[v]--;
            if (remain_deg[v] == 1) {
                layer[v] = layer[u] + 1;
                q.push(v);
            }
        }
    }

    // 层号越大越靠近树中心：前 k 大的点就是连通核心，
    // 剩下点里层号最大的就是降序第 k+1 个，它到核心的距离恰为这个层号。
    sort(layer + 1, layer + n + 1, greater<int>());
    cout << layer[k + 1] << '\n';

    return 0;
}
