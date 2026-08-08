#include <bits/stdc++.h>
using namespace std;

const int MAXN = 2005;
const int MAXM = 155;
const int INF = 1e9;

int n, board_size;
int x[MAXN], y[MAXN];
int dist_to_tree[MAXN];
bool vis[MAXN];
int board_dist[MAXM][MAXM];
int dx[8] = {-1, 1, 2, -2, -1, 1, 2, -2};
int dy[8] = {2, 2, 1, 1, -2, -2, -1, -1};

void bfs_from(int start_id) {
    for (int i = 1; i <= board_size; i++) {
        for (int j = 1; j <= board_size; j++) {
            board_dist[i][j] = -1;
        }
    }

    queue<pair<int, int>> q;
    q.push({x[start_id], y[start_id]});
    board_dist[x[start_id]][y[start_id]] = 0;

    while (!q.empty()) {
        pair<int, int> cur = q.front();
        q.pop();

        int cx = cur.first;
        int cy = cur.second;

        for (int i = 0; i < 8; i++) {
            int nx = cx + dx[i];
            int ny = cy + dy[i];

            if (nx <= 0 || ny <= 0 || nx > board_size || ny > board_size) {
                continue;
            }
            if (board_dist[nx][ny] != -1) {
                continue;
            }

            board_dist[nx][ny] = board_dist[cx][cy] + 1;
            q.push({nx, ny});
        }
    }

    for (int i = 1; i <= n; i++) {
        if (vis[i]) {
            continue;
        }
        int step = board_dist[x[i]][y[i]];
        if (step == -1) {
            continue;
        }
        dist_to_tree[i] = min(dist_to_tree[i], step + 1);
    }
}

int prim() {
    for (int i = 1; i <= n; i++) {
        dist_to_tree[i] = INF;
        vis[i] = false;
    }

    dist_to_tree[1] = 0;
    int answer = 0;

    for (int i = 1; i <= n; i++) {
        int u = 0;
        for (int j = 1; j <= n; j++) {
            if (vis[j]) {
                continue;
            }
            if (u == 0 || dist_to_tree[j] < dist_to_tree[u]) {
                u = j;
            }
        }

        if (u == 0 || dist_to_tree[u] == INF) {
            return -1;
        }

        vis[u] = true;
        answer += dist_to_tree[u];
        bfs_from(u);
    }

    return answer;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> board_size;
    for (int i = 1; i <= n; i++) {
        cin >> x[i] >> y[i];
    }

    cout << prim() << '\n';

    return 0;
}
