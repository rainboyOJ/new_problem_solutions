/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-28 19:05
 * update_at: 2026-08-28 19:05
 */

// main.cpp：B. Color 最终解。
// 编号公式按官方 std 与数据采用行优先 (i-1)*m + j 理解（题面原文 (i-1)*n+j 为笔误）。
// 对称性等价于：每个红格子的镜像格子也是红的。

#include <bits/stdc++.h>
using namespace std;

const int MAXA = 100005;

int T;
int a;
long long n, m;
long long s[MAXA];               // 输入的染色编号（可能重复）
map<long long, bool> red;        // 被染红的格子集合（重复染色不改变集合）

// 计算格子编号 x 关于竖直中线（列 j 映到 m-j+1）的镜像格子编号。
// 记 x - 1 = t*m + (y-1)，即第 t+1 行第 y 列，则镜像为第 t+1 行第 m-y+1 列。
long long trans(long long x) {
    long long t = (x - 1) / m;          // 所在行（0 起始）
    long long y = x - t * m;            // 所在列（1..m）
    return t * m + (m - y + 1);
}

void solve() {
    red.clear();
    cin >> a >> n >> m;
    for (int i = 1; i <= a; i++) {
        cin >> s[i];
        red[s[i]] = true;
    }
    // 逐点检查：每个红格子的镜像必须也在集合中。
    // trans 是对合（翻两次回到原位），所以只需从红格子出发查一遍。
    for (int i = 1; i <= a; i++) {
        long long mir = trans(s[i]);
        if (!red.count(mir)) {
            cout << "No\n";
            return;
        }
    }
    cout << "Yes\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}