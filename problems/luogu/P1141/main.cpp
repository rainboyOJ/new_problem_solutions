/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-09 21:11
 * update_at: 2026-10-09 21:11
 */
// main.cpp：P1141 01迷宫（正式主解）。
// 核心思路：能互相走到的格子构成一个连通块，块内格子的答案完全相同，都等于块的大小。
// 所以不用对每个询问单独搜索：对每个还没处理过的格子做一次 BFS，
// 数出整块大小后一次性写回块内所有格子；之后每个询问只是一次 O(1) 查表。
// 代码分层：read_input / flood_fill / answer，main 只按顺序调用；
// 迷宫和答案这些核心数据放全局，函数之间直接共享。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

// 本题数据都在 int 范围内（n <= 1000、m <= 100000、块大小 <= 10^6），
// 所以下标、计数和答案统一用 int；迷宫字符用 char 省一半内存。
const int MAXN = 1005; // n <= 1000，多开 5 是给下标 1..n 留出边界冗余，省掉数组越界的判断

char g[MAXN][MAXN];      // g[i][j]：迷宫第 i 行第 j 列的字符 '0' 或 '1'，行列下标从 1 开始
int ans[MAXN][MAXN];     // ans[i][j]：格子 (i,j) 所在连通块的大小；0 表示还没处理过
int block_cells[MAXN * MAXN]; // BFS 时按访问顺序记下当前连通块里的格子，用于后面统一回填答案
int n, m;

// 四个方向的增量：下、上、右、左
int dx[4] = {1, -1, 0, 0};
int dy[4] = {0, 0, 1, -1};

// 读入 n、m 和 n 行迷宫字符串
void read_input() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        string row;
        cin >> row;
        for (int j = 1; j <= n; j++) {
            g[i][j] = row[j - 1]; // 字符串下标从 0 开始，题面行列从 1 开始
        }
    }
}

// 从 (sx, sy) 出发把整个连通块处理完：
// 先 BFS 数出块的大小，并把块内格子编码成 x * MAXN + y 记进 block_cells，
// 最后统一把块大小写回这些格子
void flood_fill(int sx, int sy) {
    queue<pair<int, int> > q; // 队列里是待扩展的格子坐标
    q.push(make_pair(sx, sy));
    ans[sx][sy] = -1; // -1 表示“已经入队、大小还没定”，用它避免同一个格子重复入队

    int block_size = 0;
    while (!q.empty()) {
        pair<int, int> cur = q.front();
        q.pop();
        int x = cur.first;
        int y = cur.second;

        block_cells[block_size] = x * MAXN + y; // 编码成整数存下来，比两个平行数组省事
        block_size++;

        for (int d = 0; d < 4; d++) {
            int nx = x + dx[d];
            int ny = y + dy[d];
            if (nx < 1 || nx > n || ny < 1 || ny > n) continue; // 走出迷宫
            if (ans[nx][ny] != 0) continue;                     // 已经属于某个连通块
            if (g[nx][ny] == g[x][y]) continue;                 // 只能走到数值不同的相邻格
            ans[nx][ny] = -1;
            q.push(make_pair(nx, ny));
        }
    }

    for (int k = 0; k < block_size; k++) {
        int x = block_cells[k] / MAXN;
        int y = block_cells[k] % MAXN;
        ans[x][y] = block_size; // 同一连通块内所有格子答案相同
    }
}

// 依次处理每个还没访问过的格子；它所在的整块会在这一次 flood_fill 里一次算完
void flood_all() {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (ans[i][j] == 0) {
                flood_fill(i, j);
            }
        }
    }
}

// 处理 m 个询问：查表输出，每个询问 O(1)
void answer() {
    for (int k = 1; k <= m; k++) {
        int i, j;
        cin >> i >> j;
        cout << ans[i][j] << '\n';
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    read_input();
    flood_all();
    answer();

    return 0;
}
