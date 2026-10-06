/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 14:26
 * update_at: 2026-10-06 14:26
 */

#include <iostream>
using namespace std;

typedef long long ll;

const ll DIGIT = 2; // 要统计的数码

// [0, n] 中数码 DIGIT 出现的总次数，按位分段计数
ll count_upto(ll n) {
    ll total = 0;
    for (ll w = 1; w <= n; w *= 10) {
        ll higher = n / (w * 10); // 当前位的高位部分
        ll cur = (n / w) % 10;    // 当前位数字
        ll lower = n % w;         // 当前位的低位部分
        // 前缀 < higher 时该位贡献 w 个 DIGIT
        // 前缀 == higher 时：cur>DIGIT 补 w，cur==DIGIT 只到 lower+1，否则 0
        ll add;
        if (cur > DIGIT) {
            add = w;
        } else if (cur == DIGIT) {
            add = lower + 1;
        } else {
            add = 0;
        }
        total += higher * w + add;
    }
    return total;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    ll L, R;
    cin >> L >> R;
    // 区间 [L, R] 用前缀差转化为单点求值
    cout << count_upto(R) - count_upto(L - 1) << "\n";
    return 0;
}
