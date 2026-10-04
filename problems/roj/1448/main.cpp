/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 02:25
 * update_at: 2026-10-05 02:25
 */

#include <cstdio>
#include <deque>
#include <iostream>
#include <string>

using namespace std;

typedef long long ll;

const int MAXN = 505; // N, M <= 500，格点数为 (N+1)*(M+1)

int n; // 元件行数
int m; // 元件列数

string grid[MAXN]; // grid[r][c] 是元件 (r,c) 的导线方向，'\\' 或 '/'

int dist[MAXN][MAXN]; // dist[r][c] = 从电源格点 (0,0) 到格点 (r,c) 的最少旋转次数，-1 表示不可达

// 从当前格点斜着跨过一块元件走到对角格点。
// 每项 = (行偏移, 列偏移, 直通所需方向)：跨过的元件总是位于 (min(行), min(列))。
const int STEP_CNT = 4;
const int step_r[STEP_CNT] = {-1, 1, -1, 1};
const int step_c[STEP_CNT] = {-1, 1, 1, -1};
const char step_need[STEP_CNT] = {'\\', '\\', '/', '/'}; // 方向相符则不用旋转，边权 0

// 0-1 BFS：图上的点是 (N+1)*(M+1) 个格点，边是斜跨一块元件。
// 边权 0 的邻点塞队头，边权 1 的塞队尾，保证出队时距离已是最短路。
ll zero_one_bfs() {
    for (int r = 0; r <= n; r++) {
        for (int c = 0; c <= m; c++) {
            dist[r][c] = -1;
        }
    }
    deque<pair<int, int> > dq; // 队列中每个元素是一个格点 (r,c)
    dist[0][0] = 0;
    dq.push_back(make_pair(0, 0));

    while (!dq.empty()) {
        int r = dq.front().first;
        int c = dq.front().second;
        dq.pop_front();
        int d = dist[r][c];
        if (r == n && c == m) {
            return d; // 第一次弹出终点即为答案
        }
        for (int k = 0; k < STEP_CNT; k++) {
            int nr = r + step_r[k];
            int nc = c + step_c[k];
            if (nr < 0 || nr > n || nc < 0 || nc > m) {
                continue; // 目标格点越界
            }
            // 跨过的元件就是两个格点围成的那一格：行列各取较小的那个
            int pr = r < nr ? r : nr;
            int pc = c < nc ? c : nc;
            int w = 0; // 元件方向正好能穿过时不用旋转
            if (grid[pr][pc] != step_need[k]) {
                w = 1; // 方向不符，要转 90°，代价 1
            }
            int nd = d + w;
            if (dist[nr][nc] == -1 || nd < dist[nr][nc]) {
                dist[nr][nc] = nd;
                if (w == 0) {
                    dq.push_front(make_pair(nr, nc));
                } else {
                    dq.push_back(make_pair(nr, nc));
                }
            }
        }
    }
    return -1; // 队列空掉仍未到终点，说明无法连通
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> m;
    for (int r = 0; r < n; r++) {
        cin >> grid[r];
    }
    ll ans = zero_one_bfs();
    if (ans < 0) {
        cout << "NO SOLUTION" << '\n';
    } else {
        cout << ans << '\n';
    }
    return 0;
}
