/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 05:42
 * update_at: 2026-10-05 05:45
 */
//
// main.cpp：roj 1215 迷宫
// 解法：从 A 出发做一次带 visited 的迭代 DFS（显式栈模拟），
//       每入栈即标记，弹到 B 返回 YES、栈空返回 NO。
//       A 或 B 是 '#' 直接判 NO；每组 O(n²)，n ≤ 100。
//
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 105; // n ≤ 100，留一点余量

char grid[MAXN][MAXN];   // 当前迷宫的 '.', '#' 网格
bool seen[MAXN][MAXN];   // 标记：本次搜索中该格是否已经入过栈
int dr[4] = {-1, 1, 0, 0}; // 上下左右四个方向偏移
int dc[4] = {0, 0, -1, 1};

// 在界内 且 落点是 '.' 且 未访问过，三条同时满足才能扩展。
bool can_go(int nr, int nc, int n) {
    return nr >= 0 && nr < n && nc >= 0 && nc < n
        && grid[nr][nc] == '.' && !seen[nr][nc];
}

// 从 A(ha, la) 出发做迭代 DFS，判断能否到达 B(hb, lb)。
bool reachable(int n, int ha, int la, int hb, int lb) {
    if (grid[ha][la] == '#' || grid[hb][lb] == '#') {
        return false; // 起点或终点是障碍直接判否
    }
    // 清空 seen：本组最多用 n×n 这么大，只需清理 [0,n)×[0,n)
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            seen[i][j] = false;
        }
    }

    // 显式栈保存 (r, c)；压栈前先标记，避免同一点被重复展开。
    pair<int,int> stk[MAXN * MAXN];
    int top = 0;
    stk[top++] = {ha, la};
    seen[ha][la] = true;

    while (top > 0) {
        pair<int,int> cur = stk[--top];
        if (cur.first == hb && cur.second == lb) {
            return true;
        }
        for (int k = 0; k < 4; k++) {
            int nr = cur.first + dr[k];
            int nc = cur.second + dc[k];
            if (can_go(nr, nc, n)) {
                seen[nr][nc] = true; // 入栈即标记
                stk[top++] = {nr, nc};
            }
        }
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int k;
    if (!(cin >> k)) return 0;
    for (int t = 0; t < k; t++) {
        int n;
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> grid[i];
        }
        int ha, la, hb, lb;
        cin >> ha >> la >> hb >> lb;
        bool ok = reachable(n, ha, la, hb, lb);
        cout << (ok ? "YES" : "NO") << "\n";
    }
    return 0;
}
