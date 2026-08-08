#include <bits/stdc++.h>
using namespace std;

const int MAXN = 105;

int n, m;
vector<pair<int, int> > sw[MAXN][MAXN];
bool light_on[MAXN][MAXN];
bool reachable[MAXN][MAXN];

int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};

bool inside(int x, int y) {
    return x >= 1 && x <= n && y >= 1 && y <= n;
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

    light_on[1][1] = true;
    reachable[1][1] = true;

    while (true) {
        bool changed = false;

        // 枚举当前所有已经能到达的房间，尝试打开更多灯。
        for (int x = 1; x <= n; x++) {
            for (int y = 1; y <= n; y++) {
                if (!reachable[x][y]) {
                    continue;
                }
                for (int i = 0; i < (int)sw[x][y].size(); i++) {
                    int tx = sw[x][y][i].first;
                    int ty = sw[x][y][i].second;
                    if (!light_on[tx][ty]) {
                        light_on[tx][ty] = true;
                        changed = true;
                    }
                }
            }
        }

        // 只要房间被点亮并且挨着已达房间，就能变成新的可达房间。
        for (int x = 1; x <= n; x++) {
            for (int y = 1; y <= n; y++) {
                if (!light_on[x][y] || reachable[x][y]) {
                    continue;
                }
                for (int k = 0; k < 4; k++) {
                    int nx = x + dx[k];
                    int ny = y + dy[k];
                    if (inside(nx, ny) && reachable[nx][ny]) {
                        reachable[x][y] = true;
                        changed = true;
                        break;
                    }
                }
            }
        }

        if (!changed) {
            break;
        }
    }

    int ans = 0;
    for (int x = 1; x <= n; x++) {
        for (int y = 1; y <= n; y++) {
            if (light_on[x][y]) {
                ans++;
            }
        }
    }

    cout << ans << '\n';
    return 0;
}
