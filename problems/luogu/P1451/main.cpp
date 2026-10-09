/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-09 21:06
 * update_at: 2026-10-09 21:12
 */
// main.cpp：P1451 求细胞数量。
/* 扫描网格，每遇到一个还没被访问过的细胞数字，就用上下左右 BFS 淹掉整个细胞，答案加一。 */
// 代码分层：读入 / 洪水填充 / 统计输出各一个函数，main 只按顺序调用；
// 网格、方向数组、答案这些核心数据放全局，函数之间共享，比一大段 main 清楚。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 105;

int n, m;            // 网格行数、列数
// n,m <= 100，格子下标最多 104，答案最多 10^4，都在 int 范围内，所以网格和计数器用 int，不做类型转换
char g[MAXN][MAXN];  // g[i][j]：'1'..'9' 是细胞数字，'0' 不是细胞
int dx[4] = { -1, 1, 0, 0 }; // 四方向：上下左右（细胞只按上下左右粘连，不含对角线）
int dy[4] = { 0, 0, -1, 1 };

int ans; // 细胞个数，等于 BFS 启动的次数

// 读入 n、m 和 n 行长度为 m 的字符串
// 网格下标从 1 开始，扩展时判边界只要和 1、n、m 比大小
void read_input() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> (g[i] + 1); // 第 i 行整体读成字符串，直接写进 g[i][1..m]
    }
}

// 从 (sx, sy) 出发，把属于同一个细胞的所有格子都改成 '0'
// 直接改写网格，标记访问和清空细胞合成一步，省掉单独的 vis 数组
void flood_fill(int sx, int sy) {
    queue<pair<int, int>> q;
    g[sx][sy] = '0'; // 入队前就标记，保证每个格子最多入队一次
    q.push(make_pair(sx, sy));

    while (!q.empty()) {
        int x = q.front().first;
        int y = q.front().second;
        q.pop();

        for (int d = 0; d < 4; d++) {
            int nx = x + dx[d];
            int ny = y + dy[d];
            if (nx >= 1 && nx <= n && ny >= 1 && ny <= m && g[nx][ny] != '0') {
                g[nx][ny] = '0';
                q.push(make_pair(nx, ny));
            }
        }
    }
}

// 按行优先扫一遍网格：此时还留着的细胞数字，都不可能属于之前的细胞
void solve() {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (g[i][j] != '0') { // 还没被淹掉，从这里开始就是一个新细胞
                ans++;
                flood_fill(i, j);
            }
        }
    }
}

void output() {
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    read_input();
    solve();
    output();

    return 0;
}
