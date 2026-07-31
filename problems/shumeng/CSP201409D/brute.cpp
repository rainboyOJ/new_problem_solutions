/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-07-31 18:40
 */
// brute.cpp：小数据暴力解，对每个客户单独 BFS 到最近分店。
#include <bits/stdc++.h>
using namespace std;

struct Customer {
    int x;
    int y;
    int amount;
};

int n;
vector<pair<int, int> > stores;
vector<vector<bool> > blocked;

int shortest_distance(int start_x, int start_y) {
    const int INF = 0x3f3f3f3f;
    vector<vector<int> > dist(n + 1, vector<int>(n + 1, INF));
    queue<pair<int, int> > q;
    dist[start_x][start_y] = 0;
    q.push(make_pair(start_x, start_y));

    int dx[4] = {-1, 1, 0, 0};
    int dy[4] = {0, 0, -1, 1};
    while (!q.empty()) {
        pair<int, int> current = q.front();
        q.pop();
        for (int i = 0; i < (int)stores.size(); i++) {
            if (current.first == stores[i].first && current.second == stores[i].second) {
                return dist[current.first][current.second];
            }
        }

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
    return INF;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int m, k, d;
    cin >> n >> m >> k >> d;

    stores.resize(m);
    for (int i = 0; i < m; i++) {
        cin >> stores[i].first >> stores[i].second;
    }

    vector<Customer> customers(k);
    for (int i = 0; i < k; i++) {
        cin >> customers[i].x >> customers[i].y >> customers[i].amount;
    }

    blocked.assign(n + 1, vector<bool>(n + 1, false));
    for (int i = 0; i < d; i++) {
        int x, y;
        cin >> x >> y;
        blocked[x][y] = true;
    }

    long long answer = 0;
    for (int i = 0; i < k; i++) {
        answer += (long long)shortest_distance(customers[i].x, customers[i].y) * customers[i].amount;
    }
    cout << answer << '\n';
    return 0;
}
