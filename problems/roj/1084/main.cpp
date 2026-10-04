/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 00:33
 * update_at: 2026-10-05 00:34
 */
#include <cstdio>
#include <iostream>
#include <iomanip>
using namespace std;

typedef long long ll;

ll a, b;       // 底数与指数
ll r = 1;      // 当前乘积对 1000 取模后的余数

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> a >> b;

    // 每次乘 a 后只保留末三位，迭代 b 次
    for (ll i = 1; i <= b; i++) {
        r = r * a % 1000;
    }

    // 不足三位时前补零
    cout << setw(3) << setfill('0') << r << "\n";
    return 0;
}
