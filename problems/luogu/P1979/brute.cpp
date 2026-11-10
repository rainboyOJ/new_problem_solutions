/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-11-11 00:32
 * update_at: 2026-11-11 00:32
 */
// brute.cpp：全状态朴素 BFS，用于小规模对拍基准
#include <cstring>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

const int dx[4] = {-1, 1, 0, 0};
const int dy[4] = {0, 0, -1, 1};

int n, m, q;
int grid[10][10];
int dis[10][10][10][10];

struct Node {
    int sx, sy, ex, ey;
};

void solve() {
    int ex, ey, sx, sy, tx, ty;
    cin >> ex >> ey >> sx >> sy >> tx >> ty;

    if (sx == tx && sy == ty) {
        cout << 0 << "\n";
        return;
    }

    memset(dis, -1, sizeof(dis));
    queue<Node> Q;

    dis[sx][sy][ex][ey] = 0;
    Q.push({sx, sy, ex, ey});

    while (!Q.empty()) {
        auto [cx, cy, cex, cey] = Q.front();
        Q.pop();

        int d = dis[cx][cy][cex][cey];

        if (cx == tx && cy == ty) {
            cout << d << "\n";
            return;
        }

        // 空白格向 4 个方向移动
        for (int i = 0; i < 4; ++i) {
            int nex = cex + dx[i];
            int ney = cey + dy[i];

            if (nex < 1 || nex > n || ney < 1 || ney > m) continue;
            if (grid[nex][ney] == 0) continue;

            // 如果移入的位置恰好是目标棋子，目标棋子移动到原空白格位置
            int nsx = cx, nsy = cy;
            if (nex == cx && ney == cy) {
                nsx = cex;
                nsy = cey;
            }

            if (dis[nsx][nsy][nex][ney] == -1) {
                dis[nsx][nsy][nex][ney] = d + 1;
                Q.push({nsx, nsy, nex, ney});
            }
        }
    }

    cout << -1 << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    if (!(cin >> n >> m >> q)) return 0;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            cin >> grid[i][j];
        }
    }

    while (q--) {
        solve();
    }

    return 0;
}
