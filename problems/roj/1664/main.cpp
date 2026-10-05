/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 01:45
 * update_at: 2026-10-06 01:45
 */

#include <cstdio>

typedef long long ll;

ll n;       // 石子堆数
ll x;       // 当前读入的一堆石子数
ll s;       // Nim 和：全部堆数的按位异或

int main() {
    scanf("%lld", &n);
    s = 0;
    for (ll i = 1; i <= n; i++) {
        scanf("%lld", &x);
        s ^= x; // 边读边异或，无需保存每堆数量
    }
    // Bouton 定理：Nim 和不为 0 先手必胜，为 0 先手必败
    if (s != 0)
        printf("win\n");
    else
        printf("lose\n");
    return 0;
}
