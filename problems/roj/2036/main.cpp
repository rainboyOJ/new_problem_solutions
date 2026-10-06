/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 09:33
 * update_at: 2026-10-06 09:33
 */
#include <iostream>
#include <string>
#include <queue>
using namespace std;

typedef long long ll;

const ll MAXR = 210; // 2*100+3 = 203，留一点余量
const ll MAXC = 82;  // 2*38+3 = 79，留一点余量

ll w, h;
string grid[MAXR];   // grid[r][c] 是补齐后的字符画；最外圈是补出来的空白
ll dist[MAXR][MAXC]; // dist[r][c] 表示字符位 (r,c) 到迷宫外的最少字符步数，-1 表示未访问
ll total_rows;       // 补齐后总行数 2*h+3
ll total_cols;       // 补齐后总列数 2*w+3

// 从迷宫外（补出来的最外圈）做一次多源 BFS，只走空格，求每个字符位的字符距离。
void flood_fill() {
    ll dr[4] = {-1, 1, 0, 0};
    ll dc[4] = {0, 0, -1, 1};
    queue<pair<ll, ll> > q;

    for (ll r = 0; r < total_rows; r++) {
        for (ll c = 0; c < total_cols; c++) {
            dist[r][c] = -1;
            if (r == 0 || r == total_rows - 1 || c == 0 || c == total_cols - 1) {
                dist[r][c] = 0; // 最外圈就是迷宫外的自由空间，整体作为超级源点
                q.push(make_pair(r, c));
            }
        }
    }

    while (!q.empty()) {
        ll r = q.front().first;
        ll c = q.front().second;
        q.pop();
        for (ll k = 0; k < 4; k++) {
            ll nr = r + dr[k];
            ll nc = c + dc[k];
            if (nr < 0 || nr >= total_rows || nc < 0 || nc >= total_cols) continue;
            if (grid[nr][nc] != ' ') continue; // 栅栏和柱子都不是空格，水自然过不去
            if (dist[nr][nc] != -1) continue;
            dist[nr][nc] = dist[r][c] + 1;
            q.push(make_pair(nr, nc));
        }
    }
}

int main() {
    cin >> w >> h;
    total_rows = 2 * h + 3;
    total_cols = 2 * w + 3;

    string line;
    size_t line_width = 2 * w + 1; // 原始字符画每行的字符数
    getline(cin, line);            // 吃掉读入 W H 后的换行
    // 补齐四周各一圈空白：第 0 行与最后一行全空格，中间每行左右各加一个空格
    grid[0] = string(total_cols, ' ');
    for (ll r = 0; r < 2 * h + 1; r++) {
        getline(cin, line);
        if (!line.empty() && line[line.size() - 1] == '\r') line.erase(line.size() - 1);
        while (line.size() < line_width) line.push_back(' '); // 原数据可能去掉行尾空格
        grid[r + 1] = " " + line.substr(0, line_width) + " ";
    }
    grid[total_rows - 1] = string(total_cols, ' ');

    flood_fill();

    // 格子 (r,c) 的格心在补齐网格中的位置是 (2r+2, 2c+2)。牛每走一步跨 2 个字符位，
    // 所以格心的字符距离恰好是该格子到最近出口步数的两倍，取最大距离整除 2 即为答案。
    ll ans = 0;
    for (ll r = 0; r < h; r++) {
        for (ll c = 0; c < w; c++) {
            ll steps = dist[2 * r + 2][2 * c + 2] / 2;
            if (steps > ans) ans = steps;
        }
    }
    cout << ans << endl;
    return 0;
}
