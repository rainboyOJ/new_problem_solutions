/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 10:11
 * update_at: 2026-10-05 10:11
 */

#include <cstdio>

typedef long long ll;

const int MAXN = 1000005;

ll q[MAXN]; // q[i] 表示 Blah 数集升序排列的第 i 个元素

int main() {
    ll a, n;
    while (scanf("%lld %lld", &a, &n) == 2) {
        q[1] = a;
        int p = 1; // 2x+1 一族的队首指针
        int r = 1; // 3x+1 一族的队首指针
        for (int i = 2; i <= n; ++i) {
            ll x = 2 * q[p] + 1; // 2x+1 一族的队首候选
            ll y = 3 * q[r] + 1; // 3x+1 一族的队首候选
            if (x < y) {
                q[i] = x;
                p = p + 1;
            } else if (y < x) {
                q[i] = y;
                r = r + 1;
            } else { // 两族候选相等时同时消费，天然去重
                q[i] = x;
                p = p + 1;
                r = r + 1;
            }
        }
        printf("%lld\n", q[n]);
    }
    return 0;
}
