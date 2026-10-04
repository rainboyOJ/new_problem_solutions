/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 05:58
 * update_at: 2026-10-05 05:58
 */
#include <cstdio>
#include <algorithm>
using namespace std;

typedef long long ll;

const int MAXN = 20005;
int h[MAXN]; // h[i] 表示第 i 头奶牛的高度，值域只有 1..10000，用 int 即可

// 从高到低排序，让每头奶牛贡献的高度尽量大
bool cmp(int x, int y) {
    return x > y;
}

int main() {
    ll n, b;
    scanf("%lld %lld", &n, &b);
    for (ll i = 1; i <= n; i++) {
        scanf("%d", &h[i]);
    }
    sort(h + 1, h + n + 1, cmp);

    ll sum = 0; // 当前已叠奶牛的总高度
    ll ans = 0; // 已使用的奶牛头数
    for (ll i = 1; i <= n; i++) {
        sum += h[i];
        ans = i;
        // 总高度首次不低于书架高度，此时用掉的奶牛数最少
        if (sum >= b) {
            break;
        }
    }

    printf("%lld\n", ans);
    return 0;
}
