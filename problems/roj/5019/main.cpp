/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-08 16:13
 * update_at: 2026-10-08 16:13
 */

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

ll n; // 输入的上界（题面保证 1 <= n <= 100）

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    if (!(cin >> n)) return 0; // 无输入时静默退出（题面保证有输入）

    bool printed = false;             // 是否已经输出过至少一个偶数
    for (ll i = 2; i <= n; i += 2) {  // 从最小的偶数 2 起，步长 2
        if (printed) cout << " ";     // 偶数之间用一个空格隔开，行首行末不留空格
        cout << i;
        printed = true;
    }
    // n = 1 时 1~n 内没有偶数，答案为空，输出 0 字节（与标准数据 problem1.out 一致）
    if (printed) cout << "\n";

    return 0;
}
