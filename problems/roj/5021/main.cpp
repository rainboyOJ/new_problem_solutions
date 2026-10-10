/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-08 22:08
 * update_at: 2026-10-08 22:08
 */
// main.cpp：一本通 2019：【例4.4】求阶乘。
// 题面：读入正整数 n（1 ≤ n ≤ 20），用 for 循环输出 n! = 1×2×…×n。
// 关键点：int 上限 2^31-1 = 2147483647，从 n = 13 起 n! = 6227020800 就溢出；
//        20! = 2432902008176640000 < 2^63-1 = 9223372036854775807，用 ll 恰好够。
#include <iostream>

using namespace std;

typedef long long ll;

ll n; // 题面输入的正整数，1 ≤ n ≤ 20

void read_input() {
    cin >> n;
}

// 从 1 累乘到 n。累乘变量初值必须是 1（本题 n ≥ 1）。
void solve() {
    ll ans = 1;
    for (ll i = 1; i <= n; i++) {
        ans *= i;
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    read_input();
    solve();

    return 0;
}
