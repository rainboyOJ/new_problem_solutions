/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-09 21:11
 * update_at: 2026-10-09 21:11
 */
// main-stl.cpp：P1141 01迷宫（STL 写法）。
// 核心思路和 main.cpp 完全一样：能互相走到的格子属于同一个连通块，块内答案都等于块的大小，
// 所以只要对每个格子做一次 BFS 把整块大小写回块内所有格子，询问就能 O(1) 回答。
// 差别在数据怎么放：迷宫用 vector<string> 按行存，取 grid[x][y] 就是第 x 行第 y 列的字符；
// 而网格本身就是一个图，不需要另外建邻接表，扩展时检查上下左右四个相邻格即可。
// 队列里也不放坐标对，而是放压平下标 idx = x * n + y，出队时用 / n、% n 还原坐标。
// 代码分层：read_input / flood_fill / solve / answer，main 只按顺序调用。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

// 本题数据都在 int 范围内（n <= 1000、m <= 100000、块大小 <= 10^6），
// 所以下标、计数和答案统一用 int。
int n, m;
vector<string> grid;           // grid[x][y]：迷宫第 x 行第 y 列的字符，下标从 0 开始
vector<vector<int> > ans;      // ans[x][y]：格子 (x,y) 所在连通块的大小；0 表示还没处理过
vector<int> block_cells;       // 当前连通块包含的压平下标，用来把块大小统一回填

// 四个方向的增量：下、上、右、左
int dx[4] = {1, -1, 0, 0};
int dy[4] = {0, 0, 1, -1};

// 读入迷宫；grid 和 ans 都按 n 行 n 列开好
void read_input() {
    cin >> n >> m;

    grid.assign(n, string());
    for (int x = 0; x < n; x++) {
        cin >> grid[x];
    }

    ans.assign(n, vector<int>(n, 0));
}

// 从 (sx, sy) 出发把整个连通块处理完：
// BFS 数出块的大小，同时把块内格子记进 block_cells，最后统一写回答案
void flood_fill(int sx, int sy) {
    queue<int> q; // 队列里是压平下标 idx = x * n + y
    block_cells.clear();

    q.push(sx * n + sy);
    ans[sx][sy] = -1; // -1 表示“已经入队、大小还没定”，用它避免同一个格子重复入队

    while (!q.empty()) {
        int cur = q.front();
        q.pop();

        int x = cur / n; // 还原坐标：idx = x * n + y
        int y = cur % n;
        block_cells.push_back(cur);

        for (int d = 0; d < 4; d++) {
            int nx = x + dx[d];
            int ny = y + dy[d];
            if (nx < 0 || nx >= n || ny < 0 || ny >= n) continue; // 走出迷宫
            if (ans[nx][ny] != 0) continue;                       // 已经属于某个连通块
            if (grid[nx][ny] == grid[x][y]) continue;             // 只能走到数值不同的相邻格
            ans[nx][ny] = -1;
            q.push(nx * n + ny); // 新格子同样压平后入队
        }
    }

    int block_size = block_cells.size(); // 块的大小就是块内格子个数
    for (int k = 0; k < block_size; k++) {
        int x = block_cells[k] / n;
        int y = block_cells[k] % n;
        ans[x][y] = block_size; // 同一连通块内所有格子答案相同
    }
}

// 依次处理每个还没访问过的格子；它所在的整块会在这一次 flood_fill 里一次算完
void solve() {
    for (int x = 0; x < n; x++) {
        for (int y = 0; y < n; y++) {
            if (ans[x][y] == 0) {
                flood_fill(x, y);
            }
        }
    }
}

// 处理 m 个询问：查表输出，每个询问 O(1)
void answer() {
    for (int k = 0; k < m; k++) {
        int i, j;
        cin >> i >> j;
        cout << ans[i - 1][j - 1] << '\n'; // 题面行列从 1 开始，减一才是 vector 下标
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    read_input();
    solve();
    answer();

    return 0;
}
