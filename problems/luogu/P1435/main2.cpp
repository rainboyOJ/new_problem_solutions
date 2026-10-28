/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-28 21:20
 * update_at: 2026-10-28 21:20
 */
// main2.cpp：与 main.cpp 完全相同的转移，只是把 O(l^2) 的表压成两行，空间 O(l)。
// 下标从 1 开始；i 表示区间左端点，j 表示右端点。
#include <bits/stdc++.h>
using namespace std;

const int MAXL = 1005;

string t;         // t[1..n] 是原串
int f[2][MAXL];   // f[cur][*] 存 f[i+1][*]；f[cur^1][*] 用来写 f[i][*]

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    cin >> s;
    int n = s.size();
    t = " " + s;

    // 起点：i+1 = n+1，区间为空，整行都是 0（数组初值即为 0）
    int cur = 0;

    // i 从右往左扫，保证算 f[i][*] 时 f[i+1][*] 那一行已经算好
    for (int i = n - 1; i >= 1; --i) {
        int nxt = cur ^ 1;   // 本行的目标位置
        // 本行的下标 i 不去写，读到时仍是初值 0，正好对应单字符区间 f[i][i] = 0
        for (int j = i + 1; j <= n; ++j) {
            if (t[i] == t[j]) {
                // 两端配对，答案等于内层区间 [i+1, j-1]，在旧行里
                f[nxt][j] = f[cur][j - 1];
            } else {
                // 在右侧补 t[i]（消掉左端）或在左侧补 t[j]（消掉右端）
                f[nxt][j] = min(f[cur][j], f[nxt][j - 1]) + 1;
            }
        }
        cur = nxt;           // 本行变成下一轮的旧行
    }

    cout << f[cur][n] << "\n";
    return 0;
}
