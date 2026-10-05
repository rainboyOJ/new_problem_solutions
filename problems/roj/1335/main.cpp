/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 10:10
 * update_at: 2026-10-05 10:10
 */
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 105;

int n, m;
int a[MAXN][MAXN];      // a[i][j]：网格格子，0 白 1 黑
int seen[MAXN][MAXN];   // seen[i][j]：格子 (i,j) 是否已归属某块，0/1 标记

int dr[4] = {-1, 1, 0, 0}; // 四连通方向：上、下、左、右
int dc[4] = {0, 0, -1, 1};

// 从 (sr, sc) 出发用栈淹没整块黑格，每入栈一格立即标记，避免重复入栈。
void flood(int sr, int sc) {
    seen[sr][sc] = 1;
    stack<pair<int,int>> stk;
    stk.push({sr, sc});
    while (!stk.empty()) {
        pair<int,int> cur = stk.top();
        stk.pop();
        int r = cur.first;
        int c = cur.second;
        for (int k = 0; k < 4; k++) {
            int nr = r + dr[k];
            int nc = c + dc[k];
            // 越界 / 白格 / 已归属 一并挡掉
            if (nr < 0 || nr >= n || nc < 0 || nc >= m) continue;
            if (a[nr][nc] == 0) continue;
            if (seen[nr][nc]) continue;
            seen[nr][nc] = 1;
            stk.push({nr, nc});
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> a[i][j];
        }
    }

    // 外层扫全图：每碰到未访问的黑格就开一个新块并淹没。
    int blocks = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (a[i][j] != 0 && !seen[i][j]) {
                blocks++;
                flood(i, j);
            }
        }
    }

    cout << blocks << "\n";
    return 0;
}
