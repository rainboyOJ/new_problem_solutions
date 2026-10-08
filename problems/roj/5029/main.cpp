/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-08 22:37
 * update_at: 2026-10-08 22:37
 */
#include <iostream>
using namespace std;

typedef long long ll;

ll n; // 题面给定的自然数 n（n < 20），三角形行数

// 输出 n 行直角三角形：第 i 行恰好 i 个 '*'，行末一个换行。
// 外层循环控制行数，内层循环控制该行星号个数（教材例4.13 的两层嵌套循环）。
void solve() {
    for (ll row = 1; row <= n; row++) {
        for (ll col = 1; col <= row; col++) {
            cout << "*";
        }
        cout << "\n";
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;    // n 为 0 时两层循环都不执行，输出 0 字节（自然数含 0）
    solve();
    return 0;
}
