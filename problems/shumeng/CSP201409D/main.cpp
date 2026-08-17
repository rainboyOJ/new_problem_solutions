/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-08-17 22:55
 */
#include <bits/stdc++.h>
using namespace std;

struct Customer {
    int x;
    int y;
    int amount;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, k, d;
    cin >> n >> m >> k >> d;

    vector<pair<int, int> > stores(m);
    for (int i = 0; i < m; i++) {
        cin >> stores[i].first >> stores[i].second;
    }

    vector<Customer> customers(k);
    for (int i = 0; i < k; i++) {
        cin >> customers[i].x >> customers[i].y >> customers[i].amount;
    }

    vector<vector<bool> > blocked(n + 1, vector<bool>(n + 1, false));
    for (int i = 0; i < d; i++) {
        int x, y;
        cin >> x >> y;
        blocked[x][y] = true;
    }

    const int INF = 0x3f3f3f3f;
    vector<vector<int> > dist(n + 1, vector<int>(n + 1, INF));
    queue<pair<int, int> > q;
    for (int i = 0; i < m; i++) {
        int x = stores[i].first;
        int y = stores[i].second;
        if (!blocked[x][y] && dist[x][y] == INF) {
            dist[x][y] = 0;
            q.push(make_pair(x, y));
        }
    }

    int dx[4] = {-1, 1, 0, 0};
    int dy[4] = {0, 0, -1, 1};
    while (!q.empty()) {
        pair<int, int> current = q.front();
        q.pop();

        for (int dir = 0; dir < 4; dir++) {
            int nx = current.first + dx[dir];
            int ny = current.second + dy[dir];
            if (nx < 1 || nx > n || ny < 1 || ny > n) {
                continue;
            }
            if (blocked[nx][ny] || dist[nx][ny] != INF) {
                continue;
            }
            dist[nx][ny] = dist[current.first][current.second] + 1;
            q.push(make_pair(nx, ny));
        }
    }

    long long answer = 0;
    for (int i = 0; i < k; i++) {
        answer += (long long)dist[customers[i].x][customers[i].y] * customers[i].amount;
    }

    cout << answer << '\n';
    return 0;
}
