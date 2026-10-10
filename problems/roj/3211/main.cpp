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
int dist[105][105];   // 两环之间最少经过的绳索数

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            dist[i][j] = (i == j ? 0 : INF);

    // 成对读边，奇数落单的 token 自动丢弃（与原版一致）
    int a, b;
    while (cin >> a >> b) {
        dist[a - 1][b - 1] = dist[b - 1][a - 1] = 1;
    }

    // Floyd
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            if (dist[i][k] < INF) {
                for (int j = 0; j < n; j++) {
                    if (dist[i][k] + dist[k][j] < dist[i][j])
                        dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }

    int ans = 0;
    for (int u = 0; u < n; u++)
        for (int v = u + 1; v < n; v++)
            if (dist[u][v] < INF && dist[u][v] > ans)
                ans = dist[u][v];
    cout << ans << "\n";
    return 0;
}
