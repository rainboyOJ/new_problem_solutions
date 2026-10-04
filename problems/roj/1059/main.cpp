/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-04 23:49
 * update_at: 2026-10-04 23:49
 */
#include <cstdio>

typedef long long ll;

ll n;   // 学生人数
ll sum; // 年龄总和

int main() {
    scanf("%lld", &n);
    for (ll i = 1; i <= n; i++) {
        ll a; // 当前学生的年龄
        scanf("%lld", &a);
        sum += a;
    }
    printf("%.2f\n", (double)sum / (double)n); // 保留两位小数，补齐末尾的 0
    return 0;
}
