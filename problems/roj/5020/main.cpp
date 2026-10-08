/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-08 22:05
 * update_at: 2026-10-08 22:07
 */
// 一本通 2018《【例4.3】输出奇偶数之和》
// 题面两处描述自相矛盾：「题目描述」写“奇数的和、偶数的和”，
// 但「输出」节写“偶数之和与奇数之和”。以样例 n=10 -> "30 25"
// （偶数和 30、奇数和 25）为准，并由全部 10 个测试点交叉确认：
// 偶数之和在前、奇数之和在后。
#include <cstdio>

typedef long long ll;

ll n;         // 输入上界，题面保证 1 <= n <= 100
ll sum_even;  // 1~n 内所有偶数之和
ll sum_odd;   // 1~n 内所有奇数之和

// 按题面要求用 for 循环一趟累加出两个和。
void solve() {
    for (ll i = 1; i <= n; i++) {
        if (i % 2 == 0) {
            sum_even += i;
        } else {
            sum_odd += i;
        }
    }
    // 先偶数和、后奇数和，中间一个空格，行末换行；n = 1 时输出 "0 1"
    printf("%lld %lld\n", sum_even, sum_odd);
}

int main() {
    if (scanf("%lld", &n) != 1) return 0;  // 无输入时静默退出
    solve();
    return 0;
}
