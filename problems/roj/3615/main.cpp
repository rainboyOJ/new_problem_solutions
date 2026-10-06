/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 15:14
 * update_at: 2026-10-06 15:14
 */

#include <iostream>
#include <algorithm>
#include <numeric>
using namespace std;

typedef long long ll;

ll A, B, L;            // 题面给定的 A、B、L
ll best_a, best_b;     // 当前最优的 A'、B'

// 判断候选 (x1,y1) 是否比 (x2,y2) 更优：误差更小，或误差相同则字典序更小
bool better(ll x1, ll y1, ll x2, ll y2) {
    // 误差分别为 (x1*B - A*y1)/(y1*B) 与 (x2*B - A*y2)/(y2*B)
    // 两正数分母相同因子 B 可约去，只需交叉相乘比较
    ll left  = (x1 * B - A * y1) * y2;
    ll right = (x2 * B - A * y2) * y1;
    if (left != right) return left < right;
    if (x1 != x2) return x1 < x2;
    return y1 < y2;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> A >> B >> L;

    bool first = true; // 是否已找到第一个合法候选
    for (ll a = 1; a <= L; ++a) {
        for (ll b = 1; b <= L; ++b) {
            if (gcd(a, b) != 1) continue;          // 必须互质
            if (a * B < A * b) continue;            // 必须不小于原比例 A/B
            if (first || better(a, b, best_a, best_b)) {
                best_a = a;
                best_b = b;
                first = false;
            }
        }
    }

    cout << best_a << ' ' << best_b << '\n';
    return 0;
}
