#include <bits/stdc++.h>
using namespace std;

const int INF = 1000000000;

int n, h;
int w[20], c[20];
int best;

void dfs(int id, int weight, int cost) {
    if (cost >= best) {
        return;
    }
    if (weight >= h) {
        best = cost;
        return;
    }
    if (id > n) {
        return;
    }

    // 直接枚举第 id 种草买多少包，适合小数据验证。
    int limit = (h - weight + w[id] - 1) / w[id] + 1;
    for (int cnt = 0; cnt <= limit; ++cnt) {
        dfs(id + 1, weight + cnt * w[id], cost + cnt * c[id]);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> h;
    for (int i = 1; i <= n; ++i) {
        cin >> w[i] >> c[i];
    }

    best = INF;
    dfs(1, 0, 0);
    cout << best << '\n';
    return 0;
}
