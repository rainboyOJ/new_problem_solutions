/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 05:50
 * update_at: 2026-10-05 05:50
 */

#include <iostream>
#include <vector>
using namespace std;

typedef long long ll;

// 马走日的 8 个日字方向：(dr, dc) 表示行列偏移
const int DR[8] = { 1, 1, -1, -1, 2, 2, -2, -2 };
const int DC[8] = { 2, -2, 2, -2, 1, -1, 1, -1 };

// n <= 5, m <= 5
const int MAXN = 6;
const int MAXM = 6;
const int MAXK = 8;

// nbrs[r][c][k] 表示从 (r,c) 出发的第 k 个合法落点编号（编号 = r*m+c）；k_cnt[r][c] 是合法落点数
int nbrs[MAXN][MAXM][MAXK];
int k_cnt[MAXN][MAXM];

int n, m;
int total_cells;   // n*m
int visited;       // 已访问位图：第 pos 位为 1 表示该格子已访问
ll ans;            // 当前棋盘 + 起点下的全遍历路径条数

// dfs(pos, left)：从 pos 出发、还有 left 个格子未访问时的完整遍历条数。
// visited 进入时已置位 pos，退出前清位实现手工回溯。
void dfs(int pos, int left) {
    if (left == 0) {
        ans++;              // 所有格子恰好各走一次，计一条完整路径
        return;
    }
    int r = pos / m;
    int c = pos % m;
    for (int i = 0; i < k_cnt[r][c]; i++) {
        int nxt = nbrs[r][c][i];
        if ( (visited >> nxt & 1) == 0 ) {     // 落点未访问过
            visited |= 1 << nxt;                // 进入：置位
            dfs(nxt, left - 1);
            visited &= ~(1 << nxt);             // 回溯：清位
        }
    }
}

void build_neighbors() {
    // 预建邻接表：nbrs[r][c] 列出 (r,c) 一步可达的合法落点编号
    for (int r = 0; r < n; r++) {
        for (int c = 0; c < m; c++) {
            int cnt = 0;
            for (int k = 0; k < 8; k++) {
                int nr = r + DR[k];
                int nc = c + DC[k];
                if (0 <= nr && nr < n && 0 <= nc && nc < m) {
                    nbrs[r][c][cnt++] = nr * m + nc;
                }
            }
            k_cnt[r][c] = cnt;
        }
    }
}

void solve_one(int x, int y) {
    build_neighbors();
    int start_pos = x * m + y;
    visited = 1 << start_pos;
    ans = 0;
    dfs(start_pos, total_cells - 1);
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    if ( !(cin >> T) ) return 0;
    while (T--) {
        int x, y;
        cin >> n >> m >> x >> y;
        total_cells = n * m;
        solve_one(x, y);
    }
    return 0;
}
