/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 16:51
 * update_at: 2026-10-06 16:51
 */

#include <iostream>
#include <cstdlib>
using namespace std;

typedef long long ll;

const int MAXN = 1005;

ll price[MAXN]; // price[i] 表示第 i 个纪念品的价格
ll f[MAXN];     // f[i] 表示一定保留第 i 个纪念品时最多能保留多少个

int main() {
    ll n;
    cin >> n;
    for (ll i = 1; i <= n; i++) {
        cin >> price[i];
    }

    ll best_keep = 0;
    for (ll i = 1; i <= n; i++) {
        f[i] = 1; // 前面接不上任何纪念品时，只保留第 i 个
        for (ll j = 1; j < i; j++) {
            // 保留序列里 i 的前一个元素是 j，两者价格差的绝对值不能为 1
            if (abs(price[i] - price[j]) != 1 && f[j] + 1 > f[i]) {
                f[i] = f[j] + 1;
            }
        }
        if (f[i] > best_keep) {
            best_keep = f[i];
        }
    }

    // 删得最少 = 留得最多，答案为总数减去最长合法子序列长度
    cout << n - best_keep << endl;
    return 0;
}
