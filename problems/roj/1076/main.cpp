/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 00:21
 * update_at: 2026-10-05 00:21
 */

#include <iostream>
using namespace std;

typedef long long ll;

ll n;              // 测量次数
ll cur_run;        // 以当前位置结尾的连续正常段长度
ll ans;            // 最长连续正常小时数

// 判断一次测量 (s, d) 是否属于正常血压
bool is_normal(ll s, ll d) {
    return 90 <= s && s <= 140 && 60 <= d && d <= 90;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> n;
    for (ll i = 1; i <= n; ++i) {
        ll s, d;
        cin >> s >> d;
        if (is_normal(s, d)) {
            ++cur_run;                 // 正常则当前段延长一格
        } else {
            cur_run = 0;               // 异常则清零
        }
        if (cur_run > ans) {
            ans = cur_run;             // 逐步更新最长长度
        }
    }

    cout << ans << '\n';
    return 0;
}
