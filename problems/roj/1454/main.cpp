/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 23:55
 * update_at: 2026-10-05 23:55
 */
#include <iostream>
#include <queue>
#include <utility>
using namespace std;

typedef long long ll;

const int MAXN = 1005;

int n;
int grid[MAXN][MAXN];   // grid[i][j] 表示格子 (i, j) 的高度
char seen[MAXN][MAXN];  // seen[i][j] = 1 表示该格已被归入某个等权连通块

// 8 邻接方向：题面把「有公共顶点」也算相邻，所以含 4 条对角线
const int DIRR[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
const int DIRC[8] = {-1, 0, 1, -1, 1, -1, 0, 1};

// 从 (sr, sc) 洪泛一个高度全相同且 8 连通的块。
// is_peak 记录是否山峰（无更高的外部邻居），is_valley 记录是否山谷（无更矮的外部邻居）。
void bfs_block(int sr, int sc, bool &is_peak, bool &is_valley) {
    int height = grid[sr][sc];
    bool has_higher = false;  // 块外存在更高的邻居
    bool has_lower = false;   // 块外存在更矮的邻居

    queue<pair<int, int> > q;
    q.push(make_pair(sr, sc));
    seen[sr][sc] = 1;

    while (!q.empty()) {
        int r = q.front().first;
        int c = q.front().second;
        q.pop();

        for (int d = 0; d < 8; d++) {
            int nr = r + DIRR[d];
            int nc = c + DIRC[d];
            if (nr < 1 || nr > n || nc < 1 || nc > n) {
                continue;  // 出界：边界外不是格子，不参与比较
            }
            if (grid[nr][nc] == height) {
                if (!seen[nr][nc]) {  // 同高且未访问：并入当前块
                    seen[nr][nc] = 1;
                    q.push(make_pair(nr, nc));
                }
            } else if (grid[nr][nc] > height) {
                has_higher = true;
            } else {
                has_lower = true;
            }
        }
    }

    is_peak = !has_higher;
    is_valley = !has_lower;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> grid[i][j];
        }
    }

    ll peaks = 0;
    ll valleys = 0;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (!seen[i][j]) {
                bool is_peak = false;
                bool is_valley = false;
                bfs_block(i, j, is_peak, is_valley);
                if (is_peak) {
                    peaks++;
                }
                if (is_valley) {
                    valleys++;
                }
            }
        }
    }

    cout << peaks << " " << valleys << "\n";
    return 0;
}
