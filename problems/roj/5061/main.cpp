/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-09 01:46
 * update_at: 2026-10-09 01:46
 */
#include <iostream>

using namespace std;

typedef long long ll;

ll x;  // 剩余班费

// 读入班费 x
void read_input() {
    cin >> x;
}

// 要买尽量多的笔，就先按最便宜的 4 元笔算出笔数上界 k = x / 4，
// 再看余数 r = x % 4：把若干支 4 元笔换成更贵的笔补上 r 元差价，笔数不变。
// 同笔数时数据采用「6 元笔尽量多」（即 (a, b, c) 字典序最大），故 r = 2 用 1 支 6 元笔
// 而不是 2 支 5 元笔。
void solve() {
    ll k = x / 4;  // 笔数上界
    ll r = x % 4;
    ll a = 0;      // 6 元笔数
    ll b = 0;      // 5 元笔数
    ll c = k;      // 4 元笔数，先全部按 4 元笔算，再按余数替换

    if (r == 1) {          // 1 支 4 元 -> 1 支 5 元
        b = 1;
        c -= 1;
    } else if (r == 2) {   // 1 支 4 元 -> 1 支 6 元
        a = 1;
        c -= 1;
    } else if (r == 3) {   // 2 支 4 元 -> 1 支 6 元 + 1 支 5 元
        a = 1;
        b = 1;
        c -= 2;
    }

    cout << a << " " << b << " " << c << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    read_input();
    solve();

    return 0;
}
