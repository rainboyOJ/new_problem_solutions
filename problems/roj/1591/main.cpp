/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 00:55
 * update_at: 2026-10-06 00:55
 */

#include <cstdio>
#include <iostream>
using namespace std;

typedef long long ll;

ll cnt[10]; // 1~n 中每个数码出现次数

// 计算 1~n 中各数码出现次数，结果存入全局 cnt[]
void count_up_to(ll n) {
    for (int i = 0; i < 10; ++i) cnt[i] = 0;
    if (n <= 0) return;
    for (ll w = 1; w <= n; w *= 10) {
        ll high = n / (w * 10);
        ll cur = (n / w) % 10;
        ll low = n % w;
        // 数码 1~9：当前位直接按 high、cur、low 分三段计算
        for (int d = 1; d <= 9; ++d) {
            if (d < cur) cnt[d] += (high + 1) * w;
            else if (d == cur) cnt[d] += high * w + low + 1;
            else cnt[d] += high * w;
        }
        // 数码 0：跳过前导零，高位前缀从 1 开始
        if (cur == 0) cnt[0] += (high - 1) * w + low + 1;
        else cnt[0] += high * w;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    ll a, b;
    if (!(cin >> a >> b)) return 0;
    ll ans[10];
    count_up_to(b);
    for (int i = 0; i < 10; ++i) ans[i] = cnt[i];
    count_up_to(a - 1);
    for (int i = 0; i < 10; ++i) {
        ans[i] -= cnt[i];
        if (i) cout << ' ';
        cout << ans[i];
    }
    cout << '\n';
    return 0;
}
