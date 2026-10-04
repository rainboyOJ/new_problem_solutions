/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-04 23:37
 * update_at: 2026-10-04 23:37
 */
#include <iostream>
using namespace std;

typedef long long ll;

ll w;       // 邮件重量（克）
char ch;    // 是否加急：y/n

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> w >> ch;
    ll ans = 8;                 // 基本费
    if (w > 1000) {
        ll e = w - 1000;        // 超重部分
        ll units = (e + 499) / 500; // 每 500 克向上取整
        ans += units * 4;       // 超重费
    }
    if (ch == 'y') ans += 5;    // 加急费
    cout << ans << "\n";
    return 0;
}
