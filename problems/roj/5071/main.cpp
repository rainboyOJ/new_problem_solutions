/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-09 02:20
 * update_at: 2026-10-09 07:31
 */
// main.cpp：读入一个三位数，把百位与个位对调后输出。
#include <iostream>

using namespace std;

typedef long long ll;

ll n; // 输入的三位数

// 拆分百位 h / 十位 t / 个位 u，重新组合成 u*100 + t*10 + h 后按整数输出。
// 个位为 0 时（100、890、900）新数的最高位变成 0，按整数输出即自然去掉前导零：
// 100 -> 1、890 -> 98、900 -> 9，而不是 "001"/"098"/"009"。
void solve() {
    ll h = n / 100;     // 百位
    ll t = n / 10 % 10; // 十位
    ll u = n % 10;      // 个位
    ll res = u * 100 + t * 10 + h; // 对调百位与个位后的整数
    cout << res << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    if (!(cin >> n)) return 0;
    solve();
    return 0;
}
