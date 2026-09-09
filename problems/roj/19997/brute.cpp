/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-28 19:05
 * update_at: 2026-08-28 19:05
 */

// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
// 只适用于 n*m 很小的数据（这里限制 n,m <= 100）：
// 直接开二维数组标记每个格子是否被染红，再对每个红格子检查镜像格子是否被染。
// 这是"逐格模拟"的朴素写法；n,m 达到 1e7 时网格无法开数组，就是 main.cpp 要解决的瓶颈。

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 105;

int a, n, m;
int f[MAXN][MAXN];   // f[x][y] = 1 表示第 x 行第 y 列被染红
int s[10005];

// 把编号 x 转成 (x行, y列)：行优先编号 (x-1)*m + y = 编号。
void decode(long long x, int &row, int &col) {
    row = (int)((x - 1) / m) + 1;
    col = (int)((x - 1) % m) + 1;
}

void solve() {
    cin >> a >> n >> m;
    memset(f, 0, sizeof(f));
    for (int i = 1; i <= a; i++) {
        cin >> s[i];
        int x, y;
        decode(s[i], x, y);
        f[x][y] = 1;
    }
    // 对每个被染红的格子，检查它关于竖直中线（列 y 映到 m-y+1）的镜像是否被染。
    for (int i = 1; i <= a; i++) {
        int x, y;
        decode(s[i], x, y);
        if (f[x][m - y + 1] == 0) {
            cout << "No\n";
            return;
        }
    }
    cout << "Yes\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}