#include <bits/stdc++.h>
using namespace std;

const int MAXR = 505;
const int MAXC = 505;
const int MAXV = 250000 + 5;

int w, l;
int h[MAXR][MAXC];
int comp_id[MAXR][MAXC];

int qx[MAXV], qy[MAXV];
int indeg[MAXV], outdeg[MAXV];
int comp_cnt;

int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};

bool in_board(int x, int y) {
    return x >= 1 && x <= l && y >= 1 && y <= w;
}

// 同高且四联通的格子可以互相滑到，所以它们本身就是一个强连通块。
void bfs_component(int sx, int sy) {
    int front = 0;
    int back = 0;

    qx[back] = sx;
    qy[back] = sy;
    back++;

    comp_cnt++;
    comp_id[sx][sy] = comp_cnt;

    while (front < back) {
        int x = qx[front];
        int y = qy[front];
        front++;

        for (int k = 0; k < 4; k++) {
            int nx = x + dx[k];
            int ny = y + dy[k];

            if (!in_board(nx, ny)) {
                continue;
            }
            if (comp_id[nx][ny] != 0) {
                continue;
            }
            if (h[nx][ny] != h[x][y]) {
                continue;
            }

            comp_id[nx][ny] = comp_cnt;
            qx[back] = nx;
            qy[back] = ny;
            back++;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> w >> l;
    for (int i = 1; i <= l; i++) {
        for (int j = 1; j <= w; j++) {
            cin >> h[i][j];
        }
    }

    for (int i = 1; i <= l; i++) {
        for (int j = 1; j <= w; j++) {
            if (comp_id[i][j] == 0) {
                bfs_component(i, j);
            }
        }
    }

    if (comp_cnt == 1) {
        cout << 0 << '\n';
        return 0;
    }

    // 缩点后只关心每个点是否有入边/出边，不需要去重后的完整边集。
    for (int i = 1; i <= l; i++) {
        for (int j = 1; j <= w; j++) {
            for (int k = 0; k < 4; k++) {
                int ni = i + dx[k];
                int nj = j + dy[k];

                if (!in_board(ni, nj)) {
                    continue;
                }

                int cu = comp_id[i][j];
                int cv = comp_id[ni][nj];

                if (cu == cv) {
                    continue;
                }

                if (h[i][j] > h[ni][nj]) {
                    outdeg[cu] = 1;
                    indeg[cv] = 1;
                }
            }
        }
    }

    int source_cnt = 0;
    int sink_cnt = 0;

    for (int i = 1; i <= comp_cnt; i++) {
        if (indeg[i] == 0) {
            source_cnt++;
        }
        if (outdeg[i] == 0) {
            sink_cnt++;
        }
    }

    cout << max(source_cnt, sink_cnt) << '\n';

    return 0;
}
