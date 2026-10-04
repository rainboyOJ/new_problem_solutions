/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-04 23:06
 * update_at: 2026-10-04 23:06
 */

#include <cstdio>
#include <algorithm>

typedef long long ll;

int main() {
    ll n, x, y;
    scanf("%lld %lld %lld", &n, &x, &y);

    ll eaten = (y + x - 1) / x; // 向上取整：正在啃的这一个也算不完整
    ll remain = std::max(n - eaten, 0LL); // 虫子吃得比整箱还多时剩余按 0 算

    printf("%lld\n", remain);
    return 0;
}
