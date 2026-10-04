/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-03 11:16
 * update_at: 2026-10-03 11:16
 */
// main.cpp：正解。按行优先顺序逐格决定颜色(0 白 / 1 黑)，每落一子立刻检查受影响的 3x3 约束。
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAXN = 15;

int n, m;
char g[MAXN][MAXN];     // 输入棋盘：数字或 '_'
int need[MAXN][MAXN];   // need[i][j] = 数字约束；-1 表示这一格没有数字
int tot[MAXN][MAXN];    // 约束 (i,j) 的窗口在棋盘内的格子总数
int part[MAXN][MAXN];   // 已确定颜色的格子中，落在窗口内的黑格数
int known[MAXN][MAXN];  // 已确定颜色的格子中，落在窗口内的格子数
int ans[MAXN][MAXN];    // 每个格子最终的颜色
bool found;             // 是否已经找到解

// 在 (i,j) 填颜色 b：s = 1 表示落子，s = -1 表示撤销
// 只会影响与 (i,j) 切比雪夫距离不超过 1 的数字约束
void apply(int i, int j, int b, int s) {
    for (int r = max(1, i - 1); r <= min(n, i + 1); r++) {
        for (int c = max(1, j - 1); c <= min(m, j + 1); c++) {
            if (need[r][c] < 0) continue;
            part[r][c] += s * b;
            known[r][c] += s;
        }
    }
}

// 判断刚落子的 (i,j) 所影响的约束是否还有可能被满足
bool feasible(int i, int j) {
    for (int r = max(1, i - 1); r <= min(n, i + 1); r++) {
        for (int c = max(1, j - 1); c <= min(m, j + 1); c++) {
            int d = need[r][c];
            if (d < 0) continue;                 // 这一格没有数字
            if (part[r][c] > d) return false;    // 黑格已经超标
            // 窗口里还没确定的格子全部填黑也不够，剪掉
            if (part[r][c] + tot[r][c] - known[r][c] < d) return false;
        }
    }
    return true;
}

void dfs(int i, int j) {
    if (found) return;
    if (i > n) {         // 所有格子都已确定，过程中每个约束都被检查过
        found = true;
        return;
    }
    int ni = i, nj = j + 1;
    if (nj > m) { ni = i + 1; nj = 1; }
    for (int b = 0; b <= 1; b++) {   // 先试白色，保证得到的是字典序最小的解
        ans[i][j] = b;
        apply(i, j, b, 1);
        if (feasible(i, j)) dfs(ni, nj);
        apply(i, j, b, -1);
        if (found) return;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> g[i][j];
            if (g[i][j] == '_') need[i][j] = -1;
            else need[i][j] = g[i][j] - '0';
        }
    }

    // 预处理每个约束窗口落在棋盘内的格子个数，棋盘外的格子不参与计数
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            int r1 = max(1, i - 1), r2 = min(n, i + 1);
            int c1 = max(1, j - 1), c2 = min(m, j + 1);
            tot[i][j] = (r2 - r1 + 1) * (c2 - c1 + 1);
        }
    }

    dfs(1, 1);

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cout << ans[i][j];
        }
        cout << "\n";
    }
    return 0;
}
