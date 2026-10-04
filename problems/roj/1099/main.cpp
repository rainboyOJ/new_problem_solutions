/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 01:08
 * update_at: 2026-10-05 01:08
 */
#include <cstdio>

typedef long long ll;

const int MAXL = 105000; // 上界：第 10000 个质数是 104729，筛到 105000 足够

bool is_composite[MAXL + 1]; // is_composite[i] = true 表示 i 是合数

int main() {
    // 埃拉托斯特尼筛：枚举每个质数 i，从 i*i 开始标记它的倍数为合数
    for (ll i = 2; i * i <= MAXL; i++) {
        if (!is_composite[i]) {
            for (ll j = i * i; j <= MAXL; j += i) {
                is_composite[j] = true;
            }
        }
    }

    ll n; // 要求的质数序号
    scanf("%lld", &n);

    // 按升序扫描筛表，数到第 n 个质数即为答案
    ll count = 0;
    ll ans = 0;
    for (ll i = 2; i <= MAXL; i++) {
        if (!is_composite[i]) {
            count++;
            if (count == n) {
                ans = i;
                break;
            }
        }
    }
    printf("%lld\n", ans);
    return 0;
}
