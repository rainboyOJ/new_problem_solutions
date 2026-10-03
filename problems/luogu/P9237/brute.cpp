/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-03 11:16
 * update_at: 2026-10-03 11:16
 */
// brute.cpp：暴力解。按行优先顺序枚举每个格子的颜色，递归到最后一格才检查全部约束。
// 每层先试 0 再试 1，所以第一个合法方案就是字典序最小的解，和正解输出一致，方便对拍。
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAXN = 15;

int n, m;
int need[MAXN][MAXN];  // need[i][j] = 数字约束；-1 表示这一格没有数字
int col[MAXN][MAXN];   // 当前枚举到的染色
bool found;

// 检查整个棋盘是否满足所有数字约束
bool check_all() {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (need[i][j] < 0) continue;
            int cnt = 0;
            for (int r = max(1, i - 1); r <= min(n, i + 1); r++) {
                for (int c = max(1, j - 1); c <= min(m, j + 1); c++) {
                    cnt += col[r][c];
                }
            }
            if (cnt != need[i][j]) return false;
        }
    }
    return true;
}

// dep 从 0 数到 n*m-1，对应格子 (dep/m+1, dep%m+1)
void dfs(int dep) {
    if (found) return;
    if (dep == n * m) {
        if (check_all()) found = true;
        return;
    }
    int i = dep / m + 1;
    int j = dep % m + 1;
    for (int b = 0; b <= 1; b++) {
        col[i][j] = b;
        dfs(dep + 1);
        if (found) return;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            char ch;
            cin >> ch;
            if (ch == '_') need[i][j] = -1;
            else need[i][j] = ch - '0';
        }
    }

    dfs(0);

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cout << col[i][j];
        }
        cout << "\n";
    }
    return 0;
}
