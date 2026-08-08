#include <bits/stdc++.h>
using namespace std;

const int MAXN = 35;

int n, m, a, b;
int dista[MAXN][MAXN];
bool infected[MAXN][MAXN];
int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};

struct Node {
    int x;
    int y;
};

bool in_board(int x, int y) {
    return x >= 1 && x <= n && y >= 1 && y <= m;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> a >> b;

    vector<Node> cur;
    memset(dista, -1, sizeof(dista));

    for (int i = 1; i <= a; i++) {
        int x, y;
        cin >> x >> y;
        if (!infected[x][y]) {
            infected[x][y] = true;
            dista[x][y] = 0;
            cur.push_back((Node){x, y});
        }
    }

    // 朴素模拟：按“第 0 小时、第 1 小时……”一层一层扩散瘟疫。
    int hour = 0;
    while (!cur.empty()) {
        vector<Node> nxt;
        for (int idx = 0; idx < (int) cur.size(); idx++) {
            int x = cur[idx].x;
            int y = cur[idx].y;

            for (int i = 0; i < 4; i++) {
                int nx = x + dx[i];
                int ny = y + dy[i];

                if (!in_board(nx, ny)) {
                    continue;
                }
                if (infected[nx][ny]) {
                    continue;
                }

                infected[nx][ny] = true;
                dista[nx][ny] = hour + 1;
                nxt.push_back((Node){nx, ny});
            }
        }
        cur.swap(nxt);
        hour++;
    }

    for (int i = 1; i <= b; i++) {
        int x, y;
        cin >> x >> y;
        cout << dista[x][y] << '\n';
    }

    return 0;
}
