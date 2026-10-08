/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-08 19:44
 * update_at: 2026-10-08 19:44
 */
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

// 判断 x 是否为水仙花数：x 的百位、十位、个位数字的立方和是否等于 x 本身。
bool is_narcissistic(ll x) {
    ll hundred = x / 100;       // 百位数字 A
    ll ten = x / 10 % 10;       // 十位数字 B
    ll unit = x % 10;           // 个位数字 C
    return hundred * hundred * hundred + ten * ten * ten + unit * unit * unit == x;
}

void solve() {
    // 本题无输入：从 100 到 999 依次枚举，由小到大输出所有水仙花数。
    // 用整数乘法而不是 pow，避免浮点误差。
    for (ll x = 100; x <= 999; x++) {
        if (is_narcissistic(x)) {
            cout << x << "\n";
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}
