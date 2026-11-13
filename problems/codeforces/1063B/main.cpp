/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-11-13 09:38
 * update_at: 2026-11-13 09:38
 */
#include <iostream>
#include <string>
#include <vector>
#include <deque>
#include <algorithm>

using namespace std;

const int maxn = 2005;
const int INF = 1e9;

string grid[maxn];
int dist_l[maxn][maxn]; // 到达 (i, j) 所需的最少向左移动步数 L

// 移动方向：上下右边权为 0，向左边权为 1
const int dx[4] = {-1, 1, 0, 0};
const int dy[4] = {0, 0, 1, -1};
const int dw[4] = {0, 0, 0, 1};

int main() {
    // 提升标准流性能
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    int r, c;
    cin >> r >> c;
    r--; c--; // 转换为 0-indexed 下标

    long long max_l, max_r;
    cin >> max_l >> max_r;

    for (int i = 0; i < n; ++i) {
        cin >> grid[i];
        for (int j = 0; j < m; ++j) {
            dist_l[i][j] = INF;
        }
    }

    // 0-1 BFS：利用双端队列维护最短路
    deque<pair<int, int>> q;
    dist_l[r][c] = 0;
    q.push_front({r, c});

    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop_front();

        int d = dist_l[x][y];

        for (int k = 0; k < 4; ++k) {
            int nx = x + dx[k];
            int ny = y + dy[k];
            int w = dw[k];

            if (nx >= 0 && nx < n && ny >= 0 && ny < m && grid[nx][ny] == '.') {
                if (dist_l[nx][ny] > d + w) {
                    dist_l[nx][ny] = d + w;
                    if (w == 0) {
                        q.push_front({nx, ny});
                    } else {
                        q.push_back({nx, ny});
                    }
                }
            }
        }
    }

    // 利用守恒公式 R - L = j - c 反推 R，并统计可达格数量
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
