/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 05:37
 * update_at: 2026-10-05 05:37
 */

#include <iostream>
using namespace std;

typedef long long ll;

// 输出一项：指数为 1 时只写 p，否则写 p^e
void print_factor(ll p, int e) {
    cout << p;
    if (e > 1) cout << "^" << e;
}

int main() {
    ll n;
    cin >> n;

    bool first = true;          // 控制 * 分隔符只在项之间出现
    for (ll d = 2; d * d <= n; ++d) { // 试到 sqrt(n)，剩余 >1 即素数
        if (n % d != 0) continue;
        int e = 0;
        while (n % d == 0) {    // 除尽 d，统计指数
            n /= d;
            ++e;
        }
        if (!first) cout << "*";
        print_factor(d, e);
        first = false;
    }
    if (n > 1) {                 // 收尾补剩余的素因子
        if (!first) cout << "*";
        print_factor(n, 1);
    }
    cout << "\n";
    return 0;
}
