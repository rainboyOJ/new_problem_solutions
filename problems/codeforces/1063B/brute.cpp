/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-11-13 10:45
 * update_at: 2026-11-13 10:45
 */
// brute.cpp：基于优先队列堆优化的 Dijkstra 最短路解法，用于对拍验证
#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <tuple>

using namespace std;

const int maxn = 2005;
const int INF = 1e9;

string grid[maxn];
int dist_l[maxn][maxn];

// 上下右边权为 0，向左边权为 1
const int dx[4] = {-1, 1, 0, 0};
const int dy[4] = {0, 0, 1, -1};
const int dw[4] = {0, 0, 0, 1};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    int r, c;
    cin >> r >> c;
    r--; c--; // 转换为 0-indexed

    long long max_l, max_r;
    cin >> max_l >> max_r;

    for (int i = 0; i < n; ++i) {
        cin >> grid[i];
        for (int j = 0; j < m; ++j) {
            dist_l[i][j] = INF;
        }
    }

    // 堆优化 Dijkstra：存储 (dist, x, y)
    priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<tuple<int, int, int>>> pq;
    dist_l[r][c] = 0;
    pq.push({0, r, c});

    while (!pq.empty()) {
        auto [d, x, y] = pq.top();
        pq.pop();

        if (d > dist_l[x][y]) continue;

        for (int k = 0; k < 4; ++k) {
            int nx = x + dx[k];
            int ny = y + dy[k];
            int w = dw[k];

            if (nx >= 0 && nx < n && ny >= 0 && ny < m && grid[nx][ny] == '.') {
                if (dist_l[nx][ny] > d + w) {
                    dist_l[nx][ny] = d + w;
                    pq.push({dist_l[nx][ny], nx, ny});
                }
            }
        }
    }

    int ans = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (dist_l[i][j] < INF) {
                long long L = dist_l[i][j];
                long long R = L + (j - c);
                if (L <= max_l && R <= max_r) {
                    ans++;
                }
            }
        }
    }

    cout << ans << "\n";
    return 0;
}
