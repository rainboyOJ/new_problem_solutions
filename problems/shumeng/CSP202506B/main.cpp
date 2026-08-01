/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-08-01 09:45
 */
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k, x, y;
    cin >> n >> k >> x >> y;

    int distance[105][105];
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) distance[i][j] = -1;
    }

    int dx[8] = {-2, -2, -1, -1, 1, 1, 2, 2};
    int dy[8] = {-1, 1, -2, 2, -2, 2, -1, 1};
    queue<pair<int, int> > que;
    distance[x][y] = 0;
    que.push(make_pair(x, y));
    while (!que.empty()) {
        pair<int, int> current = que.front();
        que.pop();
        if (distance[current.first][current.second] == k) continue;

        for (int direction = 0; direction < 8; direction++) {
            int next_x = current.first + dx[direction];
            int next_y = current.second + dy[direction];
            if (next_x < 1 || next_x > n || next_y < 1 || next_y > n) continue;
            if (distance[next_x][next_y] != -1) continue;
            distance[next_x][next_y] = distance[current.first][current.second] + 1;
            que.push(make_pair(next_x, next_y));
        }
    }

    long long answer = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (distance[i][j] != -1 && distance[i][j] <= k) answer++;
        }
    }
    cout << answer << '\n';
    return 0;
}
