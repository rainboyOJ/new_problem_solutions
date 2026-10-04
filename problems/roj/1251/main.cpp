/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 07:02
 * update_at: 2026-10-05 07:02
 */
#include <iostream>
#include <queue>
#include <utility>
#include <string>
using namespace std;

typedef long long ll;

const ll MAXM = 25;
const ll MAXN = 25;

char grid[MAXM][MAXN]; // 迷宫网格
ll dist[MAXM][MAXN];   // 到起点的最少步数，-1 表示未访问
ll dr[4] = {-1, 1, 0, 0}; // 四方向行增量
ll dc[4] = {0, 0, -1, 1}; // 四方向列增量

// 判断格子是否在界内且可通行（非怪物）
bool walkable(ll m, ll n, ll r, ll c) {
    return r >= 1 && r <= m && c >= 1 && c <= n && grid[r][c] != '#';
}

// 从起点 (sr, sc) 走到终点 (tr, tc) 的最少步数；不可达返回 -1
ll bfs(ll m, ll n, ll sr, ll sc, ll tr, ll tc) {
    for (ll i = 1; i <= m; i++)
        for (ll j = 1; j <= n; j++)
            dist[i][j] = -1;

    queue<pair<ll, ll> > q;
    dist[sr][sc] = 0;
    q.push(make_pair(sr, sc));

    while (!q.empty()) {
        pair<ll, ll> cur = q.front();
        q.pop();
        ll r = cur.first;
        ll c = cur.second;
        if (r == tr && c == tc)
            return dist[r][c];
        for (ll k = 0; k < 4; k++) {
            ll nr = r + dr[k];
            ll nc = c + dc[k];
            if (walkable(m, n, nr, nc) && dist[nr][nc] == -1) {
                dist[nr][nc] = dist[r][c] + 1;
                q.push(make_pair(nr, nc));
            }
        }
    }
    return -1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    while (true) {
        ll m, n;
        cin >> m >> n;
        if (m == 0 && n == 0)
            break;
        ll sr = 0, sc = 0, tr = 0, tc = 0;
        for (ll i = 1; i <= m; i++) {
            string row;
            cin >> row;
            for (ll j = 1; j <= n; j++) {
                grid[i][j] = row[j - 1];
                if (grid[i][j] == '@') {
                    sr = i;
                    sc = j;
                } else if (grid[i][j] == '*') {
                    tr = i;
                    tc = j;
                }
            }
        }
        cout << bfs(m, n, sr, sc, tr, tc) << "\n";
    }
    return 0;
}
