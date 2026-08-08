#include <bits/stdc++.h>
using namespace std;

const int MAXN = 105;
const int MAXM = 20005;

int n, m;
vector<pair<int, int> > sw[MAXN][MAXN];
bool light_on[MAXN][MAXN];
bool visited[MAXN][MAXN];

int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};

bool inside(int x, int y) {
    return x >= 1 && x <= n && y >= 1 && y <= n;
}

bool has_visited_neighbor(int x, int y) {
    for (int k = 0; k < 4; k++) {
        int nx = x + dx[k];
        int ny = y + dy[k];
        if (inside(nx, ny) && visited[nx][ny]) {
            return true;
        }
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int a, b, c, d;
        cin >> a >> b >> c >> d;
        sw[a][b].push_back(make_pair(c, d));
    }

    queue<pair<int, int> > q;
    light_on[1][1] = true;
    visited[1][1] = true;
    q.push(make_pair(1, 1));

    int ans = 1;

    while (!q.empty()) {
        pair<int, int> cur = q.front();
        q.pop();
        int x = cur.first;
        int y = cur.second;

        // 到达房间后，把这个房间能控制的灯全部打开。
        for (int i = 0; i < (int)sw[x][y].size(); i++) {
            int tx = sw[x][y][i].first;
            int ty = sw[x][y][i].second;

            if (!light_on[tx][ty]) {
                light_on[tx][ty] = true;
                ans++;

                // 新点亮的房间如果已经挨着可达区域，就能立刻走进去。
                if (!visited[tx][ty] && has_visited_neighbor(tx, ty)) {
                    visited[tx][ty] = true;
                    q.push(make_pair(tx, ty));
                }
            }
        }

        // 从当前房间继续走向四周所有“已点亮但还没访问”的房间。
        for (int k = 0; k < 4; k++) {
            int nx = x + dx[k];
            int ny = y + dy[k];
            if (!inside(nx, ny)) {
                continue;
            }
            if (!light_on[nx][ny] || visited[nx][ny]) {
                continue;
            }
            visited[nx][ny] = true;
            q.push(make_pair(nx, ny));
        }
    }

    cout << ans << '\n';
    return 0;
}
