/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-08 22:35
 * update_at: 2026-10-08 22:37
 */
// main.cpp：本题无输入，由小到大输出所有形如 aabb 的四位完全平方数。
#include <iostream>

using namespace std;

typedef long long ll;

void solve() {
    // n = k^2 要是四位数：31^2 = 961 < 1000，100^2 = 10000，故底数 k ∈ [32, 99]。
    for (ll k = 32; k <= 99; ++k) {
        ll n = k * k;
        ll a = n / 1000;         // 千位
        ll b = n / 100 % 10;     // 百位
        ll c = n / 10 % 10;      // 十位
        ll d = n % 10;           // 个位
        if (a == b && c == d) {  // 前两位相同且后两位相同，即形如 aabb
            cout << n << "\n";
        }
    }
}

int main() {
    solve();
    return 0;
}
