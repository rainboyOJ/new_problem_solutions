/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 05:37
 * update_at: 2026-10-05 05:37
 */
// main.cpp：roj/1212 LETTERS。
// 从左上角出发四连通移动，路径上的字母不能重复，求最多经过多少个字母。
// 用 26 位掩码记录路径上用过的字母：字母不重复就蕴含格子不重复，不需要额外的访问数组。

#include <iostream>
using namespace std;

typedef long long ll;

const int MAXN = 21;

char grid[MAXN][MAXN]; // 字母矩阵，行列下标从 0 开始
ll rows;               // 行数 R
ll cols;               // 列数 S
ll best;               // 目前找到的最长路径长度，起点自身算 1

int dr[4] = {-1, 1, 0, 0}; // 上下左右四个方向的行增量
int dc[4] = {0, 0, -1, 1}; // 上下左右四个方向的列增量

// 从 (r,c) 出发继续搜索；mask 记录路径上已用字母，depth 是当前路径长度。
void dfs(ll r, ll c, ll mask, ll depth) {
    if (depth > best) {
        best = depth;
    }
    for (int d = 0; d < 4; d++) {
        ll nr = r + dr[d];
        ll nc = c + dc[d];
        if (nr < 0 || nr >= rows || nc < 0 || nc >= cols) {
            continue; // 越界
        }
        ll bit = 1LL << (grid[nr][nc] - 'A');
        if (mask & bit) {
            continue; // 该字母已经在路径上，不能进入
        }
        dfs(nr, nc, mask | bit, depth + 1); // mask|bit 是新掩码，父状态不被修改
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> rows >> cols;
    for (ll i = 0; i < rows; i++) {
        for (ll j = 0; j < cols; j++) {
            cin >> grid[i][j];
        }
    }

    best = 1;
    dfs(0, 0, 1LL << (grid[0][0] - 'A'), 1);
    cout << best << '\n';

    return 0;
}
