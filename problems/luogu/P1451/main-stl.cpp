/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-09 21:12
 * update_at: 2026-10-09 21:12
 */
// main-stl.cpp：P1451 求细胞数量（STL 写法）。
// 做法和 main.cpp 一样：扫描网格，遇到还没被访问过的细胞数字就开始一个新的细胞计数，
// 从它出发 BFS，把上下左右相连的细胞数字全部访问掉。
// STL 版的差别在数据结构：
//   * 网格用 vector<string> 存，一行就是一个 string，读入时整行读进 grid[x]；
//   * BFS 队列里只存压平下标 idx = x * m + y，一个下标就能定位格子，
//     不用再开 queue<pair<int,int>>；
//   * 网格本身就是图，相邻关系能直接算出来，不需要建邻接表。
// 代码分层：读入 / 搜索 / 输出各一个函数，main 只按顺序调用；
// 网格、规模、答案这些核心数据放全局，函数之间共享。
#include <bits/stdc++.h>
using namespace std;

int n, m;            // 网格行数、列数
// n,m <= 100，压平下标 idx = x * m + y <= 10^4，答案 <= 10^4，都在 int 范围内，一律用 int，不做类型转换
vector<string> grid; // grid[x]：第 x 行字符串，grid[x][y] != '0' 表示这一格是细胞
int ans;             // 细胞个数，等于 BFS 启动的次数

// 读入 n、m 和 n 行字符串
// 下标从 0 开始，和 vector、string 的天然下标一致，不用再为边界做什么偏移
void read_input() {
    cin >> n >> m;
    grid.assign(n, "");
    for (int x = 0; x < n; x++) {
        cin >> grid[x]; // 一行读成一个 string，长度保证是 m
    }
}

// 从压平下标 start 出发，把属于同一个细胞的所有格子都改成 '0'
// 压平后上下左右是四个固定偏移：idx - m、idx + m、idx - 1、idx + 1
void flood_fill(int start) {
    queue<int> q;
    grid[start / m][start % m] = '0'; // 入队前就标记，保证每个格子最多入队一次
    q.push(start);

    while (!q.empty()) {
        int idx = q.front();
        q.pop();

        int x = idx / m; // 由压平下标还原出当前的行、列
        int y = idx % m;

        // 上下：加减一整行仍然落在同一列，不会跨行
        if (x > 0 && grid[x - 1][y] != '0') {
            grid[x - 1][y] = '0';
            q.push(idx - m);
        }
        if (x + 1 < n && grid[x + 1][y] != '0') {
            grid[x + 1][y] = '0';
            q.push(idx + m);
        }
        // 左右：必须用列号判断是否跨行，否则行首的 idx - 1 会跑到上一行行尾
        if (y > 0 && grid[x][y - 1] != '0') {
            grid[x][y - 1] = '0';
            q.push(idx - 1);
        }
        if (y + 1 < m && grid[x][y + 1] != '0') {
            grid[x][y + 1] = '0';
            q.push(idx + 1);
        }
    }
}

// 按行优先扫一遍网格：此时还留着的细胞数字，都不可能属于之前数过的细胞
void solve() {
    for (int x = 0; x < n; x++) {
        for (int y = 0; y < m; y++) {
            if (grid[x][y] != '0') { // 还没被淹掉，从这里开始就是一个新细胞
                ans++;
                flood_fill(x * m + y); // 行列压平成下标，交给 BFS
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
