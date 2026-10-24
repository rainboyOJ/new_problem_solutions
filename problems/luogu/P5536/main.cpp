/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-13 08:02
 * update_at: 2026-10-24 12:32
 */
// P5536 【XR-3】核心城市
// 剥叶分层：从所有叶子开始一轮一轮往里剥，层号 = 该点被剥掉的轮次。
// 层号最大的 k 个点天然连通，正好当核心；答案就是第 k+1 大的层号。
#include <bits/stdc++.h>
using namespace std;

const int maxn = 100000 + 5; // 城市数上限

typedef long long ll;

ll n;                 // 城市数
ll k;                 // 核心城市个数
vector<int> g[maxn];  // g[u]：与城市 u 直接相连的所有城市
int degree_arr[maxn]; // degree_arr[u]：u 还剩几条边没被剥掉（剥叶过程中不断减少）
int layer[maxn];      // layer[u]：u 在第几轮被剥掉，叶子是第 1 轮

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> k;
    for (ll i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
        degree_arr[u]++;
        degree_arr[v]++;
    }

    // 第一轮：所有叶子（n = 2 时两个点度数都是 1）入队，层号记为 1。
    queue<int> q;
    for (int u = 1; u <= n; u++) {
        if (degree_arr[u] <= 1) {
            layer[u] = 1;
            q.push(u);
        }
    }

    // 之后逐轮往里剥：出队一个已被剥掉的点 u，把它唯一剩下的邻居 v 的度数减一；
    // v 减到 1 说明 v 也变成了叶子，层号 = u 的层号 + 1，入队等下一轮处理。
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v : g[u]) {
            if (degree_arr[v] <= 1) continue; // 已经剥掉的邻居不再处理
            degree_arr[v]--;
            if (degree_arr[v] == 1) {
                layer[v] = layer[u] + 1;
                q.push(v);
            }
        }
    }

    // 层号降序后，前 k 大对应的点当核心；剩下点里层号最大的那个离核心最远，
    // 它的层号就是答案，也就是降序后第 k + 1 个层号。
    sort(layer + 1, layer + n + 1, greater<int>());
    cout << layer[k + 1] << '\n';

    return 0;
}
