/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 00:11
 * update_at: 2026-10-05 00:13
 */
#include <iostream>
using namespace std;

typedef long long ll;

const double LIMIT = 0.05; // 有效率差超过 5% 才判定为 better / worse

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll n;
    cin >> n;

    ll base_total, base_effective;
    cin >> base_total >> base_effective;
    double base = base_effective * 1.0 / base_total; // 鸡尾酒疗法有效率 x

    for (ll i = 0; i < n - 1; ++i) {
        ll total, effective;
        cin >> total >> effective;
        double diff = effective * 1.0 / total - base; // 新疗法有效率 y 与基准的差
        if (diff > LIMIT) {
            cout << "better\n";
        } else if (-diff > LIMIT) { // x - y > 5%
            cout << "worse\n";
        } else {
            cout << "same\n";
        }
    }

    return 0;
}
